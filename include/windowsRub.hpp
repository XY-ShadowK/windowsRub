/*
Modified Time: 2026/11/24 16:55:43
Copyright (c) 2026 XY-ShadowK
SPDX-License-Identifier: MPL-2.0
*/

#pragma once
#ifndef _WINDOWSRUB_HPP_
#define _WINDOWSRUB_HPP_

#ifdef _WIN32
#include <Windows.h>
#include <string>
#include <cstring>
#endif

#ifdef _WIN32

inline int convertW2UTF8(const int num, const wchar_t* const* const wstrings_c, char**& strings_c) {
    strings_c = new char*[num];
    for(int i = 0;i < num;i ++) {
        int len = WideCharToMultiByte(CP_UTF8, 0, wstrings_c[i], -1, nullptr, 0, nullptr, nullptr);
        if (len == 0)
            continue;
        strings_c[i] = nullptr;
        strings_c[i] = new char[len];
        if(!strings_c[i])
            exit(-1);
        if (WideCharToMultiByte(CP_UTF8, 0, wstrings_c[i], -1, strings_c[i], len, nullptr, nullptr) == 0) {
            for(int j = 0;j <= i;j ++)
                delete[] strings_c[j];
            delete[] strings_c;
            return -1;
        }
    }
    return 0;
}

// only use wmain in msvc
#if defined(_MSC_VER) && !defined(__clang__)
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
        if(convertW2UTF8(argc, wargv, t_argv) == 0) \
            return t_argv; \
        else \
            return nullptr; \
    }(); \
    if(!argv) { \
        UNIVERSE_MAIN_RETURN(-1); \
    }

#else
#define UNIVERSE_MAIN \
int main(int argc, char* argv[]) {
#define UNIVERSE_MAIN_RETURN(ret) \
    return ret
#endif

#define UNIVERSE_MAINEND \
}

#endif