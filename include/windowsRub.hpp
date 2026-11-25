/*
Modified Time: 2026/11/24 16:55:43
Copyright (c) 2026 XY-ShadowK
SPDX-License-Identifier: MPL-2.0
*/

#pragma once
#ifndef _WINDOWSRUB_HPP_
#define _WINDOWSRUB_HPP_

#ifdef _WINDOWSRUB_LOCALE_UTF8
#include <clocale>

#define SET_LOCALE_UTF8 \
    // std::setlocale(LC_ALL, ".65001");

#else
#define SET_LOCALE_UTF8
#endif

#if defined(_WIN32) && !defined(__CYGWIN__)
#include <Windows.h>
#include <string>
#include <cstring>
#include <cstdio>
#endif

#if defined(_WIN32) && !defined(__CYGWIN__)

inline int getLengthW2UTF8(const wchar_t* const wstring_c) {
    return WideCharToMultiByte(CP_UTF8, 0, wstring_c, -1, nullptr, 0, nullptr, nullptr);
}

inline int convertW2UTF8(const wchar_t* const wstring_c, char*& string_c, const int length) {
    if(WideCharToMultiByte(CP_UTF8, 0, wstring_c, -1, string_c, length, nullptr, nullptr) == 0)
        return -1;
    return 0;
}

inline int convertW2UTF8(const int num, const wchar_t* const* const wstrings_c, char**& strings_c) {
    strings_c = new char*[num];
    for(int i = 0;i < num;i ++) {
        int length = getLengthW2UTF8(wstrings_c[i]);
        if(length == 0)
            return -1;
        strings_c[i] = nullptr;
        strings_c[i] = new char[length];
        if(!strings_c[i]) {
            fprintf(stderr, "can not allocate space by new.\n");
            exit(-1);
        }
        if(convertW2UTF8(wstrings_c[i], strings_c[i], length)) {
            for(int j = 0;j <= i;j ++)
                delete[] strings_c[j];
            delete[] strings_c;
            return -1;
        }
    }
    return 0;
}

// only use wmain in msvc
#if defined(_MSC_VER) && !defined(_LIBCPP_VERSION)
    #define UNIVERSE_ENTRY \
    int wmain(const int argc, wchar_t* wargv[]) {
#else
    #define UNIVERSE_ENTRY \
    int main() { \
        wchar_t** wargv; \
        const int argc = [&wargv]{ \
            int temp = 0; \
            wargv = CommandLineToArgvW(GetCommandLineW(), &temp); \
            return temp; \
        }();
#endif

#define UNIVERSE_MAIN_RETURN(ret) \
    if(argv) { \
        for(int i = 0;i < argc;i ++) { \
            delete[] const_cast<char*>(argv[i]); \
        } \
        delete[] const_cast<char**>(argv); \
    } \
    return ret

#define UNIVERSE_MAIN \
UNIVERSE_ENTRY \
    char* const* const argv = [&argc, &wargv]() -> char** { \
        char** t_argv; \
        if(convertW2UTF8(argc, wargv, t_argv)) \
            return nullptr; \
        else \
            return t_argv; \
    }(); \
    if(!argv) { \
        UNIVERSE_MAIN_RETURN(-1); \
    } \
    SET_LOCALE_UTF8

#else
#define UNIVERSE_MAIN \
int main(int argc, char* argv[]) { \
    SET_LOCALE_UTF8
#define UNIVERSE_MAIN_RETURN(ret) \
    return ret
#endif

#define UNIVERSE_MAINEND \
}

#endif