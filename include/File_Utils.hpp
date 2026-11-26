#pragma once

#ifndef _FILE_UTILS_HPP_
#define _FILE_UTILS_HPP_

#include <string>
#include <cstring>

#include "File_Path.hpp"

_WINDOWS_RUB_FILE_BEGIN

inline FilePath getFilePathU8(const char* const path) {
    #if defined(_WIN32) && !defined(__CYGWIN__)
        return std::filesystem::u8path(path);
    #else
        return std::string(path);
    #endif
}

inline FilePath getFilePathU8(const char* const path, size_t length) {
    #if defined(_WIN32) && !defined(__CYGWIN__)
        return std::filesystem::u8path(std::string(path, length));
    #else
        return std::string(path, length);
    #endif
}

inline FilePath getFilePathU8(const std::string& path) {
    #if defined(_WIN32) && !defined(__CYGWIN__)
        return std::filesystem::u8path(path);
    #else
        return path;
    #endif
}

inline FILE* cFileOpen(FilePath filename, const char* mode) {
    if(strlen(mode) > 3) return NULL;
#if defined(_WIN32) && !defined(__CYGWIN__)
    wchar_t wMode[4] = {0};
    for (unsigned int i = 0; i < 3 && mode[i];i ++)
        wMode[i] = (wchar_t)(unsigned char)mode[i];
    return _wfopen(filename.wstring().c_str(), wMode);
#else
    return fopen(filename.c_str(), mode);
#endif
}

_WINDOWS_RUB_FILE_END

#endif