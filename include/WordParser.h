#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <locale>
#include <cstring>
#include <cstdint>
#include <cuchar>
#include <cerrno>
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
    static uint8_t lowCharsE[32] = "àáâãäåæçèéêëìíîïğñòóôõö×øùúûüış";
    static uint8_t capChars[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static uint8_t capCharsE[32] = "ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ÷ØÙÚÛÜİŞ";

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

    inline bool IsDigit(const uint32_t& c)
    {
        return c > 47 && c < 58;
    }

    inline bool IsJoin(const uint32_t& c)
    {
        return c == 39 || c == 45;
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
        if (word.length() > 1)
            word[0] = UpperChar(word[0]);
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

    /*inline bool LoadWordList(phmap::parallel_flat_hash_set<std::string>& words, std::string word_file, bool lower=false)
    {
        std::ifstream inFile(word_file);
        std::string line;

        if (!inFile.is_open()) return false;

        if (lower) {
            while (std::getline(inFile, line)) {
                LowerWord(line);
                words.emplace(line);
            }
        } else {
            while (std::getline(inFile, line))
                words.emplace(line);
        }

        return true;
    }*/

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
