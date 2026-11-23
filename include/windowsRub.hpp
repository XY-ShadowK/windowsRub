/*
Modified Time: 2026/11/2 18:01:39
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

inline void convertW2UTF8(const int num, const wchar_t* const* const wstrings_c, char**& strings_c) {
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
                delete[] strings_c[i];
            delete[] strings_c;
            exit(-1);
        }
    }
}

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

#define UNIVERSE_MAIN \
UNIVERSE_ENTRY \
    char* const* const argv = [&argc, &wargv]{ \
        char** t_argv; \
        convertW2UTF8(argc, wargv, t_argv); \
        return t_argv; \
    }();
#define UNIVERSE_MAINEND \
    for(int i = 0;i < argc;i ++) { \
        delete[] const_cast<char*>(argv[i]); \
    } \
    delete[] const_cast<char**>(argv); \
}

#else
#define UNIVERSE_MAIN \
int main(int argc, char* argv[]) {
#define UNIVERSE_MAINEND \
}
#endif

#endif