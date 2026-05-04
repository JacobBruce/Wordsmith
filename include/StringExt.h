#pragma once
#include <cstdlib>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <memory>
#include <wx/string.h>
#include <md4c-html.h>

static std::stringstream markdownInput;

inline void md_process_output(const MD_CHAR* text, MD_SIZE size, void* userdata) {
    markdownInput.write(text, size);
}

inline std::string MDtoHTML(const std::string& str) {
    static unsigned parserFlags = MD_FLAG_TABLES | MD_FLAG_TASKLISTS | MD_FLAG_STRIKETHROUGH | MD_FLAG_NOHTML;
    static unsigned rendererFlags = 0;

    markdownInput.str("");
    markdownInput.clear();

    int result = md_html(
        str.c_str(), str.length(),
        md_process_output, NULL,
        parserFlags, rendererFlags
    );

    if (result != 0) return "";

    return markdownInput.str();
}

inline void EncodeHTML(wxString& str) {
    str.Replace("&", "&amp;");
    str.Replace("#", "&num;");
    str.Replace("<", "&lt;");
    str.Replace(">", "&gt;");
    str.Replace("'", "&apos;");
    str.Replace("\"", "&quot;");
}

inline wxString EncodeHTML(const wxString& str) {
    wxString encodedText(str);
    EncodeHTML(encodedText);
    return encodedText;
}

inline bool HasLineBreak(const wxString& text)
{
    for (const auto& chr : text)
		if (chr == 10 || chr == 13) return true;

    return false;
}

inline bool HasWhiteSpace(const wxString& text)
{
    for (const auto& chr : text)
		if (iswspace(chr) || iswcntrl(chr)) return true;

    return false;
}

inline std::size_t CountWhiteSpace(const wxString& text)
{
    std::size_t occurrences = 0;

    for (const auto& chr : text)
		if (iswspace(chr) || iswcntrl(chr)) occurrences++;

    return occurrences;
}

inline std::size_t CountCharacters(const wxString& text)
{
    std::size_t characters = 0;

    for (const auto& chr : text)
		if (!iswspace(chr) || chr == 32 || chr == 160) characters++;

    return characters;
}

inline std::size_t CountParagraphs(const wxString& text)
{
    std::size_t paragraphs = 0;
	bool gotBreak = false;

	if (!text.empty() && text[0] != 10 && text[0] != 13)
		paragraphs++;

    for (const auto& chr : text)
		if (chr == 10 || chr == 13) {
			gotBreak = true;
		} else if (gotBreak) {
			gotBreak = false;
			paragraphs++;
		}

    return paragraphs;
}

inline void ReplaceStr(std::string& s, std::string search, std::string replace)
{
    for (size_t pos = 0; ; pos += replace.length()) {
        pos = s.find(search, pos);
		if (pos == std::string::npos) { break; };
        s.erase(pos, search.length());
        s.insert(pos, replace);
    }
}

inline std::string ReplaceStr(const std::string& s, std::string search, std::string replace)
{
    std::string result(s);

    for (size_t pos = 0; ; pos += replace.length()) {
        pos = result.find(search, pos);
		if (pos == std::string::npos) { break; };
        result.erase(pos, search.length());
        result.insert(pos, replace);
    }

    return result;
}

inline std::string& EncodeUriPath(std::string& str) {
    ReplaceStr(str, "%", "%25");
    ReplaceStr(str, " ", "%20");
    ReplaceStr(str, "#", "%23");
    ReplaceStr(str, "?", "%3F");
    ReplaceStr(str, "&", "%26");
    ReplaceStr(str, "=", "%3D");
    ReplaceStr(str, "<", "%3C");
    ReplaceStr(str, ">", "%3E");
    ReplaceStr(str, "`", "%60");
    ReplaceStr(str, "'", "%27");
    ReplaceStr(str, "\"", "%22");
    ReplaceStr(str, "\\", "/");
	return str;
}

inline std::size_t CountSubStr(const std::string& text, const std::string& str)
{
    std::size_t pos = 0;
    std::size_t occurrences = 0;

    while ((pos = text.find(str, pos)) != std::string::npos) {
        occurrences++;
        pos += str.length();
    }

    return occurrences;
}

inline std::size_t CountCharStr(const std::string& text, const char& c)
{
    std::size_t occurrences = 0;

    for (const char& chr : text) {
		if (chr == c) occurrences++;
    }

    return occurrences;
}

inline std::size_t CountRepStr(const std::string& text, const std::size_t& len)
{
    std::size_t occurrences = 0;
	std::size_t i, l;

    for (i=0; i+len < text.length(); i += len) {
		for (l=0; l < len; ++l) {
			if (text[i+l] != text[l])
				return occurrences;
		}
		occurrences++;
	}

    return occurrences;
}

inline std::vector<std::string> ExplodeStr(const std::string& text, const std::string sep)
{
    std::vector<std::string> tokens;
    std::size_t start = 0, end = 0;

    while ((end = text.find(sep, start)) != std::string::npos) {
        if (end != start) tokens.emplace_back(text.substr(start, end - start));
        start = end + sep.length();
    }

    if (end != start) {
        if (tokens.empty()) {
            tokens.emplace_back(text);
        } else {
            tokens.emplace_back(text.substr(start));
        }
    }

    return tokens;
}

inline void SplitStr(const std::string& text, const std::string& sep,
                                        std::vector<std::string>& dest)
{
    std::size_t start = 0, end = 0;

    while ((end = text.find(sep, start)) != std::string::npos) {
        if (end != start) dest.emplace_back(text.substr(start, end - start));
        start = end + sep.length();
    }

    if (end != start) {
        if (dest.empty()) {
            dest.emplace_back(text);
        } else {
            dest.emplace_back(text.substr(start));
        }
    }
}

inline std::string& TrimL(std::string &s, const char c)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [&](int ch) {
        return c != ch;
    }));

    return s;
}

inline std::string TrimL(const std::string &s, const char c)
{
	std::string result(s);

    result.erase(result.begin(), std::find_if(result.begin(), result.end(), [&](int ch) {
        return c != ch;
    }));

    return result;
}

inline std::string& TrimR(std::string &s, const char c)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [&](int ch) {
        return c != ch;
    }).base(), s.end());

    return s;
}

inline std::string TrimR(const std::string &s, const char c)
{
	std::string result(s);

    result.erase(std::find_if(result.rbegin(), result.rend(), [&](int ch) {
        return c != ch;
    }).base(), result.end());

    return result;
}

inline std::string& TrimLast(std::string &s, const char c)
{
    static size_t lastIndex;
    if (s.size() < 2) return s;
    lastIndex = s.size() - 1;
    if (s[lastIndex] == c)
        s.resize(lastIndex);
    return s;
}

inline std::string TrimLast(const std::string &s, const char c)
{
    static size_t lastIndex;
	std::string result(s);
    if (s.size() < 2) return result;
    lastIndex = result.size() - 1;
    if (result[lastIndex] == c)
        result.resize(lastIndex);
    return result;
}

inline std::string& TrimStr(std::string &s, const std::string &chars)
{
    for (const char& c : chars) TrimR(TrimL(s, chars[c]), chars[c]);

    return s;
}

inline std::string TrimStr(const std::string &s, const std::string &chars)
{
	std::string result(s);

    for (const char& c : chars) TrimR(TrimL(result, chars[c]), chars[c]);

    return result;
}

inline std::string& StrToUpper(std::string& str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

inline std::string StrToUpper(const std::string& str)
{
	std::string result(str);
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

inline std::string& StrToLower(std::string& str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

inline std::string StrToLower(const std::string& str)
{
	std::string result(str);
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

inline bool StrStartsWith(const std::string& str, const std::string& start)
{
    if (start.size() > str.size()) return false;
    return std::mismatch(start.begin(), start.end(), str.begin()).first == start.end();
}

inline bool StrEndsWith(const std::string& str, const std::string& end)
{
    if (end.size() > str.size()) return false;
    return std::equal(end.rbegin(), end.rend(), str.rbegin());
}

inline bool StrIsFalse(const std::string& str)
{
	return (str.empty() || str == "0" || StrToUpper(str) == "FALSE");
}

inline bool StrIsTrue(const std::string& str)
{
	return !StrIsFalse(str);
}

inline std::string RandomDigits(const int len)
{
    static const std::string digits1("123456789");
    static const std::string digitsN("0123456789");

    std::string result;
    result.reserve(len);

    result = digits1[rand() % (digits1.length() - 1)];

    for (int i=1; i < len; ++i)
        result += digitsN[rand() % (digitsN.length() - 1)];

    return result;
}
