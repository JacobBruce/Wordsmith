#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <assert.h>
#include "StringExt.h"

inline std::filesystem::path GetSafePath(const std::u8string& path_str)
{
	return std::filesystem::path(path_str);
}

inline std::filesystem::path GetSafePath(const std::string& path_str)
{
    return GetSafePath((const char8_t*)path_str.c_str());
}

inline std::vector<std::string> ListFolders(std::string dirpath)
{
    std::vector<std::string> result;

    for (const auto& p : std::filesystem::directory_iterator(GetSafePath(dirpath)))
        if (p.is_directory()) result.push_back(p.path().string());
    return result;
}

inline std::vector<std::string> ListFiles(std::string dirpath)
{
    std::vector<std::string> result;

    for (const auto& entry : std::filesystem::directory_iterator(GetSafePath(dirpath)))
        if (!entry.is_directory()) result.push_back(entry.path().string());

    return result;
}

inline std::vector<std::string> ListAllFiles(std::u8string dirpath)
{
    std::vector<std::string> result;

    for (const auto& entry : std::filesystem::recursive_directory_iterator(GetSafePath(dirpath)))
        if (!entry.is_directory()) result.push_back(entry.path().string());

    return result;
}

inline bool CreateDir(const std::string dirpath)
{
	// create_directories handles nested folders
	return std::filesystem::create_directories(GetSafePath(dirpath));
}

inline bool DirExists(const std::string dirpath) {
    std::filesystem::path safePath(GetSafePath(dirpath));
	return (std::filesystem::exists(safePath) && std::filesystem::is_directory(safePath));
}

inline bool FileExists(const std::string filepath) {
    return std::filesystem::exists(GetSafePath(filepath));
}

inline std::uintmax_t FileSize(const std::string filepath) {
    return std::filesystem::file_size(GetSafePath(filepath));
}

inline std::filesystem::file_time_type FileModTime(const std::string filepath) {
    return std::filesystem::last_write_time(GetSafePath(filepath));
}

inline std::string ParentPath(const std::string filepath) {
    return (const char*)GetSafePath(filepath).parent_path().u8string().c_str();
}

inline std::string FileName(const std::string filepath) {
    return (const char*)GetSafePath(filepath).filename().u8string().c_str();
}

inline std::string ReadFileStr(const std::string filepath, std::string& err)
{
    std::string fileStr;

	try {
        std::ifstream sourceFile(GetSafePath(filepath));
        fileStr.assign(std::istreambuf_iterator<char>(sourceFile),
                              std::istreambuf_iterator<char>());
	} catch (...) {
        err = "Couldn't read file: " + filepath;
	}

    return fileStr;
}

inline std::string WriteFileStr(const std::string filepath, const std::string str, bool append=false)
{
	std::ofstream destFile;

	try {
        if (append) {
            destFile.open(GetSafePath(filepath), std::ios_base::app);
        } else {
            destFile.open(GetSafePath(filepath));
        }

        if (destFile.is_open()) {
            destFile << str;
        } else {
            return "Couldn't create file: " + filepath;
        }
	} catch (...) {
        return "Couldn't write file: " + filepath;
	}

	destFile.close();

	return "";
}

inline std::vector<std::string> ReadFileLines(const std::string filepath, std::string& err)
{
    std::vector<std::string> result;

	try {
        std::ifstream ifs(GetSafePath(filepath));

        if (ifs.is_open()) {
            while (!ifs.eof()) {
                std::string line;
                std::getline(ifs, line);
                result.push_back(line);
            }

            ifs.close();
        } else {
            err = "Couldn't open file: " + filepath;
        }
	} catch (...) {
        err = "Couldn't read file: " + filepath;
	}

	return result;
}

inline std::string LoadConfigFile(std::string filepath, std::unordered_map<std::string,std::string>& str_map)
{
	std::string line, key, data;
	size_t bpos;

	try {
        std::ifstream configFile(GetSafePath(filepath));

        if (configFile.is_open()) {

            while (!configFile.eof()) {
                std::getline(configFile, line);
                TrimRight(line, "\r\n");
                if (line.empty() || line[0] == '#') continue;
                bpos = line.find("=");
                if (bpos == std::string::npos) continue;
                key = line.substr(0, bpos);
                data = line.substr(bpos+1);
                str_map[key] = data;
            }

            configFile.close();

        } else {
            return "Couldn't open config file: " + filepath;
        }
	} catch (...) {
        return "Couldn't read config file: " + filepath;
	}

	return "";
}

inline std::string SaveConfigFile(std::string filepath, const std::unordered_map<std::string,std::string>& str_map)
{
	try {
        std::ofstream configFile(GetSafePath(filepath));

        if (configFile.is_open()) {

            for (const auto& entry : str_map)
				configFile << entry.first << "=" << entry.second << std::endl;

            configFile.close();

        } else {
            return "Couldn't create config file: " + filepath;
        }
	} catch (...) {
        return "Couldn't write config file: " + filepath;
	}

	return "";
}

inline size_t CountStrInFile(const std::string& filepath, const std::string& str, std::string& err)
{
	std::string word;
	uint32_t result = 0;

	try {
        std::ifstream fileStream(GetSafePath(filepath));

        if (fileStream.is_open()) {
            while (fileStream >> word)
                if (word == str) result++;
        } else {
            err = "Couldn't open file: " + filepath;
        }
	} catch(...) {
        err = "Couldn't read file: " + filepath;
	}

	return result;
}
