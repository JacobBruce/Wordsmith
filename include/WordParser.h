#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <locale>
#include <cstring>
#include <limits>
#include <cstdint>
#include <cuchar>
#include <cerrno>
#include <cwctype>
#include <queue>
#include <unordered_set>
#include <parallel_hashmap/phmap.h>
#include "FileExt.h"

struct WordMaps {
	phmap::flat_hash_map<std::string, uint32_t> before;
	phmap::flat_hash_map<std::string, uint32_t> after;
	uint32_t count;
};

struct WordSets {
	phmap::flat_hash_map<uint32_t, uint32_t> before;
	phmap::flat_hash_map<uint32_t, uint32_t> after;
};

struct WordEntry {
	std::vector<std::string> definitions;
	std::vector<std::string> examples;
	std::vector<std::string> members;
	std::vector<std::string> related;
};

typedef std::vector<std::pair<uint32_t, uint32_t>> AfterLinks;

namespace WordParser {

	static uint8_t lowChars[27] = "abcdefghijklmnopqrstuvwxyz";
	static uint8_t lowCharsE[32] = //àáâãäåæçèéêëìíîïðñòóôõö×øùúûüýþ
	{
		224, 225, 226, 227, 228, 229, 230,
		231, 232, 233, 234, 235,
		236, 237, 238, 239, 240, 241,
		242, 243, 244, 245, 246, 215, 248,
		249, 250, 251, 252, 253, 254
	};

	static uint8_t capChars[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	static uint8_t capCharsE[32] = //ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ÷ØÙÚÛÜÝÞ
	{
		192, 193, 194, 195, 196, 197, 198,
		199, 200, 201, 202, 203,
		204, 205, 206, 207, 208, 209,
		210, 211, 212, 213, 214, 247, 216,
		217, 218, 219, 220, 221, 222
	};

	inline bool IsUTF8orASCII(const std::string& file_str)
	{
		uint8_t* chars = (uint8_t*)file_str.c_str();

		if ((chars[0] == 0xFF && chars[1] == 0xFE) || (chars[0] == 0xFE && chars[1] == 0xFF))
			return false;

		return true;
	}

	inline std::string U32ToU8(std::u32string_view u32str)
	{
		std::string u8str;
		u8str.reserve(u32str.length() * 2);

		std::mbstate_t state{};
		char buff[4];

		for (char32_t cp : u32str)
		{
			size_t rc = std::c32rtomb(buff, cp, &state);

			if (rc == static_cast<size_t>(-1))
				continue;

			if (rc == 0) {
				u8str.push_back('\0');
			} else {
				u8str.append(buff, rc);
			}
		}

		return u8str;
	}

	inline std::u32string U8ToU32(std::string_view u8str)
	{
		std::u32string u32str;
		u32str.reserve(u8str.length());

		std::mbstate_t state{};
		char32_t cp;

		const char* ptr = u8str.data();
		const char* end = ptr + u8str.length();

		while (ptr < end)
		{
			size_t rc = std::mbrtoc32(&cp, ptr, static_cast<size_t>(end - ptr), &state);

			if (rc == 0) {
				u32str += cp;
				ptr++;
			} else if (rc >= 1 && rc <= 4) {
				u32str += cp;
				ptr += rc;
			} else {
				if (rc == static_cast<size_t>(-3)) u32str += cp;
				std::mbrtoc32(nullptr, nullptr, 0, &state);
				ptr++;
			}
		}

		return u32str;
	}

	inline uint32_t UTF8CharLen(const uint32_t& c)
	{
		if (c < 128) {
			return 1;
		} else if (c < 2048) {
			return 2;
		} else if (c < 65536) {
			return 3;
		} else {//if (c < 1114112) {
			return 4;
		}
	}

	inline bool IsWhiteSpace(const uint32_t& c)
	{
		if (iswspace(c) || iswcntrl(c)) return true;
		return false;
	}

	inline bool IsAlpha(const uint32_t& c)
	{
		if (c < 65 || c > 255) {
			return false;
		} else if ((c > 64 && c < 91) || (c > 96 && c < 123)) {
			return true;
		} else if (c > 191 && (c != 215 && c != 247)) {
			return true;
		}

		return false;
	}

	inline bool IsLetter(const uint32_t& c)
	{
		if (IsAlpha(c)) return true;
		return c > 255 && std::iswalpha(static_cast<wint_t>(c));
	}

	inline bool IsDigit(const uint32_t& c)
	{
		return c > 47 && c < 58;
	}

	inline bool IsJoin(const uint32_t& c)
	{
		return c == 39 || c == 45 || c == 0x2019;
	}

	inline void StraightenApostrophes(wxString& word)
	{
		word.Replace(wxS("’"), wxS("'"));
	}

	inline bool IsEnd(const uint32_t& c)
	{
		return (c == 46 || c == 13 || c == 10 || c == 33 || c == 63);
	}

	inline bool IsEnd2(const uint32_t& a, const uint32_t& c)
	{
		return IsEnd(c) || IsEnd(a);
	}

	inline bool IsCap(const uint32_t& c) {
		return c > 64 && c < 91;
	}

	inline bool IsCapE(const uint32_t& c) {
		return c > 191 && c < 222;
	}

	inline bool IsCap2(const uint32_t& c)
	{
		return IsCap(c) || IsCapE(c);
	}

	inline bool IsLow(const uint32_t& c) {
		return c > 96 && c < 123;
	}

	inline bool IsLowE(const uint32_t& c) {
		return c > 223 && c < 255;
	}

	inline bool IsLow2(const uint32_t& c)
	{
		return IsLow(c) || IsLowE(c);
	}

	inline uint32_t UpperChar(const uint32_t& c)
	{
		if (IsLow(c)) {
			return capChars[c-97];
		} else if (IsLowE(c)) {
			return capCharsE[c-224];
		}

		return c;
	}

	inline uint32_t LowerChar(const uint32_t& c)
	{
		if (IsCap(c)) {
			return lowChars[c-65];
		} else if (IsCapE(c)) {
			return lowCharsE[c-192];
		}

		return c;
	}

	inline void UpperWord(wxString& word)
	{
		if (word.length() > 1 && IsLow2(word[0])) {

			wxString upperStr(word);
			upperStr[0] = UpperChar(word[0]);

			for (size_t i=1; i < word.size(); ++i) {
				upperStr[i] = UpperChar(word[i]);
				if (word[i] != upperStr[i]) return;
			}

			word = upperStr;
		}
	}

	inline void LowerWord(wxString& word)
	{
		if (word.length() > 1 && IsCap2(word[0])) {

			wxString lowStr(word);
			lowStr[0] = LowerChar(word[0]);

			for (size_t i=1; i < word.size(); ++i) {
				lowStr[i] = LowerChar(word[i]);
				if (word[i] != lowStr[i]) return;
			}

			word = lowStr;
		}
	}

	inline wxString UpperWord(const wxString& word)
	{
		wxString uppStr(word);
		UpperWord(uppStr);
		return uppStr;
	}

	inline wxString LowerWord(const wxString& word)
	{
		wxString lowStr(word);
		LowerWord(lowStr);
		return lowStr;
	}

	inline std::string UpperWordU8(const wxString& word)
	{
		return UpperWord(word).utf8_string();
	}

	inline std::string LowerWordU8(const wxString& word)
	{
		return LowerWord(word).utf8_string();
	}

	inline void UpperString(wxString& str)
	{
		for (size_t i = 0; i < str.length(); ++i)
			str[i] = UpperChar(str[i]);
	}

	inline void LowerString(wxString& str)
	{
		for (size_t i = 0; i < str.length(); ++i)
			str[i] = LowerChar(str[i]);
	}

	inline void UpperFirst(wxString& str)
	{
		if (!str.empty())
			str[0] = UpperChar(str[0]);
	}

	inline void LowerFirst(wxString& str)
	{
		if (!str.empty())
			str[0] = LowerChar(str[0]);
	}

	inline std::pair<size_t,float> CountWords(const wxString& text)
	{
		wxString word;
		bool gotWord = false;
		size_t wordCount = 0;
		size_t wordChars = 0;

		for (const wxUniChar& c : text)
		{
			if (IsAlpha(c) || IsDigit(c)) {
				word.append(c);
			} else if (IsJoin(c)) {
				if (!word.empty() && IsAlpha(word[word.length()-1])) {
					word.append(c);
				} else if (!word.empty()) {
					gotWord = true;
				}
			} else if (!word.empty()) {
				gotWord = true;
			}

			if (gotWord) {
				wordCount++;
				wordChars += word.length();

				word.clear();
				gotWord = false;
			}
		}

		if (!word.empty()) {
			wordCount++;
			wordChars += word.length();
		}

		if (wordCount > 0) {
			return std::make_pair(wordCount, wordChars / (float)wordCount);
		} else {
			return std::make_pair(0,0.f);
		}
	}

	inline bool LoadWordWeb(phmap::parallel_flat_hash_map<std::string, std::pair<uint32_t,AfterLinks>>& word_map,
							std::vector<std::pair<std::string, uint32_t>>& word_vec, std::string word_file)
	{
		std::ifstream inFile(word_file);
		std::vector<std::string> parts;
		std::vector<std::string> aParts;
		std::vector<std::string> bParts;
		std::string line;

		if (!inFile.is_open()) return false;

		std::getline(inFile, line);
		uint32_t counter = 0;
		uint32_t aCount;
		uint32_t wordCount(stoul(line));
		word_vec.reserve(wordCount);

		while (std::getline(inFile, line)) {

			SplitStr(line, ":", parts);
			wordCount = stoul(parts[1]);

			std::getline(inFile, line);
			aCount = stoul(line);

			std::pair<uint32_t,AfterLinks> links;
			links.second.reserve(aCount);
			links.first = counter++;

			while (aCount-- > 0) {
				std::getline(inFile, line);
				SplitStr(line, ":", aParts);
				links.second.emplace_back(std::make_pair(stoul(aParts[0]), stoul(aParts[1])));
				aParts.clear();
			}

			word_map[parts[0]] = links;

			word_vec.emplace_back(std::make_pair(parts[0], wordCount));

			parts.clear();
		}

		inFile.close();

		return true;
	}

	inline bool LoadSimWords(phmap::parallel_flat_hash_map<std::string, std::vector<std::pair<uint32_t,float>>>& simWords, std::string word_file)
	{
		std::ifstream inFile(word_file);
		std::vector<std::string> parts;
		std::string line;

		if (!inFile.is_open()) return false;

		while (std::getline(inFile, line)) {

			parts.clear();
			SplitStr(line, ":", parts);

			if (simWords.contains(parts[0])) return false;

			std::vector<std::pair<uint32_t,float>>& wordVec(simWords[parts[0]]);
			uint32_t simCount(stoul(parts[1]));
			wordVec.reserve(simCount);

			for (uint32_t i=0; i < simCount; ++i) {
				std::getline(inFile, line);
				parts.clear();
				SplitStr(line, ":", parts);
				wordVec.emplace_back(std::make_pair(stoul(parts[0]), stof(parts[1])));
			}
		}

		inFile.close();

		return true;
	}

	// Reads a whole binary file into memory and parses little-endian values from it (floats are IEEE 754).
	// Reading past the end sets failed and returns zero values instead of exiting, so loaders can return false.
	struct BinReader {
		std::string data;
		size_t pos = 0;
		bool failed = false;

		bool Open(const std::string& file_path)
		{
			std::ifstream inFile(file_path, std::ios::binary | std::ios::ate);
			if (!inFile.is_open()) return false;

			const std::streamoff size = inFile.tellg();
			if (size < 0) return false;

			data.resize((size_t)size);
			inFile.seekg(0);
			return (bool)inFile.read(data.data(), data.size());
		}

		bool AtEnd() const { return pos >= data.size(); }

		const char* Take(const size_t bytes)
		{
			if (failed || data.size() - pos < bytes) {
				failed = true;
				return nullptr;
			}

			const char* ptr = data.data() + pos;
			pos += bytes;
			return ptr;
		}

		uint8_t U8()
		{
			const char* ptr = Take(1);
			return ptr ? (uint8_t)*ptr : 0;
		}

		uint32_t U32()
		{
			const uint8_t* b = (const uint8_t*)Take(4);
			if (!b) return 0;
			return b[0] | ((uint32_t)b[1] << 8) | ((uint32_t)b[2] << 16) | ((uint32_t)b[3] << 24);
		}

		float F32()
		{
			static_assert(std::numeric_limits<float>::is_iec559 && sizeof(float) == 4, "Binary word files require IEEE 754 floats");
			const uint32_t bits = U32();
			float value;
			std::memcpy(&value, &bits, sizeof(value));
			return value;
		}

		std::string Str8()
		{
			const uint8_t size = U8();
			const char* ptr = Take(size);
			return ptr ? std::string(ptr, size) : std::string();
		}
	};

	// Loads a binary half word web (after links only) saved by WordParser's SaveWordWebHalfBin:
	//   u32 word count, then for each word:
	//   u8 word size, word bytes (UTF-8), u32 word count, u8 after size, after links (u32 word index, u32 count) ...
	inline bool LoadWordWebBin(phmap::parallel_flat_hash_map<std::string, std::pair<uint32_t,AfterLinks>>& word_map,
							   std::vector<std::pair<std::string, uint32_t>>& word_vec, std::string word_file)
	{
		BinReader reader;
		if (!reader.Open(word_file)) return false;

		const uint32_t wordCount = reader.U32();
		word_vec.reserve(word_vec.size() + wordCount);
		word_map.reserve(word_map.size() + wordCount);

		for (uint32_t i=0; i < wordCount && !reader.failed; ++i)
		{
			std::string word(reader.Str8());
			const uint32_t count = reader.U32();
			const uint8_t linkCount = reader.U8();

			std::pair<uint32_t,AfterLinks> links;
			links.first = i;
			links.second.reserve(linkCount);

			for (uint8_t j=0; j < linkCount; ++j) {
				const uint32_t index = reader.U32();
				links.second.emplace_back(index, reader.U32());
			}

			word_map[word] = std::move(links);
			word_vec.emplace_back(std::move(word), count);
		}

		return !reader.failed && reader.AtEnd();
	}

	// Loads binary sim words saved by WordParser's SaveSimWordsBin, for each word:
	//   u8 word size, word bytes, u8 list size, list of (u32 word index, f32 score) sorted by score (highest first)
	inline bool LoadSimWordsBin(phmap::parallel_flat_hash_map<std::string, std::vector<std::pair<uint32_t,float>>>& simWords, std::string word_file)
	{
		BinReader reader;
		if (!reader.Open(word_file)) return false;

		while (!reader.AtEnd() && !reader.failed)
		{
			std::string word(reader.Str8());
			const uint8_t simCount = reader.U8();

			if (simWords.contains(word)) return false;

			std::vector<std::pair<uint32_t,float>>& wordVec(simWords[word]);
			wordVec.reserve(simCount);

			for (uint8_t i=0; i < simCount; ++i) {
				const uint32_t index = reader.U32();
				wordVec.emplace_back(index, reader.F32());
			}
		}

		return !reader.failed;
	}

	inline void GenIndexMap(std::vector<std::pair<std::string, uint32_t>> words, phmap::parallel_flat_hash_map<std::string, uint32_t>& index_map)
	{
		std::u32string lastWord;

		for (size_t i=0; i < words.size(); ++i)
		{
			std::u32string word(U8ToU32(words[i].first));

			if (word.length() < 2) continue;
			if (word.length() > 2) word.resize(2);

			if (lastWord != word) {
				index_map[U32ToU8(word)] = i;
				lastWord = word;
			}
		}
	}

	inline void BuildExtraVec(const phmap::parallel_flat_hash_map<std::string, std::pair<uint32_t,AfterLinks>>& word_map,
							  const phmap::parallel_flat_hash_map<std::string, std::vector<std::string>>& word_syn,
							  std::vector<std::pair<std::string, uint32_t>>& extra_vec)
	{
		extra_vec.clear();
		extra_vec.reserve(50000);

		for (const auto& entry : word_syn)
		{
			if (entry.first.find(' ') != std::string::npos)
				continue;

			if (word_map.contains(entry.first))
				continue;

			extra_vec.emplace_back(entry.first, 1);
		}

		std::sort(extra_vec.begin(), extra_vec.end(),
			[](const std::pair<std::string, uint32_t>& a, const std::pair<std::string, uint32_t>& b) {
				return a.first < b.first;
		});
	}

	inline bool LoadWordNet(phmap::parallel_flat_hash_map<std::string, WordEntry>& word_net, phmap::parallel_flat_hash_map<std::string, std::vector<std::string>>& word_syn, std::string word_file)
	{
		std::ifstream inFile(word_file);
		std::string line, ssID;
		uint32_t defNum, exmNum, memNum, relNum, i;

		if (!inFile.is_open()) return false;

		while (std::getline(inFile, ssID))
		{
			auto& entry(word_net[ssID]);

			std::getline(inFile, line);
			defNum = stoul(line);
			std::getline(inFile, line);
			exmNum = stoul(line);
			std::getline(inFile, line);
			memNum = stoul(line);
			std::getline(inFile, line);
			relNum = stoul(line);

			entry.definitions.reserve(defNum);
			entry.examples.reserve(exmNum);
			entry.members.reserve(memNum);
			entry.related.reserve(relNum);

			for (i=0; i < defNum; ++i) {
				std::getline(inFile, line);
				entry.definitions.emplace_back(line);
			}

			for (i=0; i < exmNum; ++i) {
				std::getline(inFile, line);
				entry.examples.emplace_back(line);
			}

			for (i=0; i < memNum; ++i) {
				std::getline(inFile, line);
				entry.members.emplace_back(line);

				if (word_syn.contains(line)) {
					word_syn.at(line).emplace_back(ssID);
				} else {
					word_syn[line] = { ssID };
				}
			}

			for (i=0; i < relNum; ++i) {
				std::getline(inFile, line);
				entry.related.emplace_back(line);
			}
		}

		inFile.close();

		return true;
	}
};
