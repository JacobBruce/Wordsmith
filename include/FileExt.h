#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <assert.h>
#include "StringExt.h"

inline std::vector<std::string> ListFolders(std::u8string dirpath)
{
    std::vector<std::string> result;
    std::filesystem::path safePath(dirpath);

    for (const auto& p : std::filesystem::directory_iterator(safePath))
        if (p.is_directory()) result.push_back(p.path().string());
    return result;
}

inline std::vector<std::string> ListFiles(std::u8string dirpath)
{
    std::vector<std::string> result;
    std::filesystem::path safePath(dirpath);

    for (const auto& entry : std::filesystem::directory_iterator(safePath))
        if (!entry.is_directory()) result.push_back(entry.path().string());

    return result;
}

inline std::vector<std::string> ListAllFiles(std::u8string dirpath)
{
    std::vector<std::string> result;
    std::filesystem::path safePath(dirpath);

    for (const auto& entry : std::filesystem::recursive_directory_iterator(safePath))
        if (!entry.is_directory()) result.push_back(entry.path().string());

    return result;
}

inline bool CreateDir(const std::u8string dirpath)
{
    std::filesystem::path safePath(dirpath);
	// create_directories handles nested folders
	return std::filesystem::create_directories(safePath);
}

inline bool DirExists(const std::u8string dirpath) {
    std::filesystem::path safePath(dirpath);
	return (std::filesystem::exists(safePath) && std::filesystem::is_directory(safePath));
}

inline bool FileExists(const std::u8string filepath) {
    std::filesystem::path safePath(filepath);
    return std::filesystem::exists(safePath);
}

inline std::uintmax_t FileSize(const std::u8string filepath) {
    std::filesystem::path safePath(filepath);
    return std::filesystem::file_size(safePath);
}

inline std::string ParentPath(const std::u8string filepath) {
    std::filesystem::path safePath(filepath);
    return (const char*)safePath.parent_path().u8string().c_str();
}

inline std::string FileName(const std::u8string filepath) {
    std::filesystem::path safePath(filepath);
    return (const char*)safePath.filename().u8string().c_str();
}

inline std::string ReadFileStr(const std::u8string filepath, std::string& err)
{
    std::string fileStr;
    std::filesystem::path safePath(filepath);

	try {
        std::ifstream sourceFile(safePath);
        fileStr.assign(std::istreambuf_iterator<char>(sourceFile),
                              std::istreambuf_iterator<char>());
	} catch (...) {
        err = "Couldn't read file: " + std::string(filepath.begin(), filepath.end());
	}

    return fileStr;
}

inline std::string WriteFileStr(const std::u8string filepath, const std::string str, bool append=false)
{
	std::ofstream destFile;
    std::filesystem::path safePath(filepath);

	try {
        if (append) {
            destFile.open(safePath, std::ios_base::app);
        } else {
            destFile.open(safePath);
        }

        if (destFile.is_open()) {
            destFile << str;
        } else {
            return "Couldn't create file: " + std::string(filepath.begin(), filepath.end());
        }
	} catch (...) {
        return "Couldn't write file: " + std::string(filepath.begin(), filepath.end());
	}

	destFile.close();

	return "";
}

inline std::vector<std::string> ReadFileLines(const std::u8string filepath, std::string& err)
{
    std::filesystem::path safePath(filepath);
    std::ifstream ifs(safePath);
    std::vector<std::string> result;

	try {
        if (ifs.is_open()) {
            while (!ifs.eof()) {
                std::string line;
                std::getline(ifs, line);
                result.push_back(line);
            }

            ifs.close();
        } else {
            err = "Couldn't open file: " + std::string(filepath.begin(), filepath.end());
        }
	} catch (...) {
        err = "Couldn't read file: " + std::string(filepath.begin(), filepath.end());
	}

	return result;
}

inline std::string LoadConfigFile(std::u8string filepath, std::unordered_map<std::string,std::string>& str_map)
{
    std::filesystem::path safePath(filepath);
	std::ifstream configFile(safePath);
	std::string line, key, data;
	size_t bpos;

	try {
        if (configFile.is_open()) {

            while (!configFile.eof()) {
                std::getline(configFile, line);
                if (line.empty() || line[0] == '#') continue;
                bpos = line.find("=");
                if (bpos == std::string::npos) continue;
                key = line.substr(0, bpos);
                data = line.substr(bpos+1);
                str_map[key] = data;
            }

            configFile.close();

        } else {
            return "Couldn't open config file: " + std::string(filepath.begin(), filepath.end());
        }
	} catch (...) {
        return "Couldn't read config file: " + std::string(filepath.begin(), filepath.end());
	}

	return "";
}

inline std::string SaveConfigFile(std::u8string filepath, const std::unordered_map<std::string,std::string>& str_map)
{
    std::filesystem::path safePath(filepath);
	std::ofstream configFile(safePath);

	try {
        if (configFile.is_open()) {

            for (const auto& entry : str_map)
				configFile << entry.first << "=" << entry.second << std::endl;

            configFile.close();

        } else {
            return "Couldn't create config file: " + std::string(filepath.begin(), filepath.end());
        }
	} catch (...) {
        return "Couldn't write config file: " + std::string(filepath.begin(), filepath.end());
	}

	return "";
}

inline size_t CountStrInFile(const std::u8string& filepath, const std::string& str, std::string& err)
{
    std::filesystem::path safePath(filepath);
    std::ifstream fileStream(safePath);
	std::string word;
	uint32_t result = 0;

	try {
        if (fileStream.is_open()) {
            while (fileStream >> word)
                if (word == str) result++;
        } else {
            err = "Couldn't open file: " + std::string(filepath.begin(), filepath.end());
        }
	} catch(...) {
        err = "Couldn't read file: " + std::string(filepath.begin(), filepath.end());
	}

	return result;
}
