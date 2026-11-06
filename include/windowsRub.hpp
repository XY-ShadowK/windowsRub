/*
Modified Time: 2026/11/2 18:01:39
Copyright (c) 2026 XY-ShadowK
SPDX-License-Identifier: MPL-2.0
*/

#pragma once
#ifndef _WINDOWSRUB_HPP_
#define _WINDOWSRUB_HPP_

#ifdef _WIN32
#include <windows.h>
#include <string>
#include <cstring>
#endif

#ifdef _WIN32

inline void convertW2UTF8(const int num, const wchar_t* const* const wstrings_c, char** const strings_c) {
    for(int i = 0;i < num;i ++) {
        int len = WideCharToMultiByte(CP_UTF8, 0, wstrings_c[i], -1, nullptr, 0, nullptr, nullptr);
        if (len == 0)
            continue;
        strings_c[i] = nullptr;
        strings_c[i] = new char[len];
        if(!strings_c[i])
            exit(-1);
        if (WideCharToMultiByte(CP_UTF8, 0, wstrings_c[i], -1, strings_c[i], len, nullptr, nullptr) == 0) {
            delete[] strings_c[i];
            exit(-1);
        }
    }
}

#define UNIVERSE_MAIN \
int wmain(int argc, wchar_t* wargv[]) { \
    char** argv = new char*[argc]; \
    convertW2UTF8(argc, wargv, argv);
#define UNIVERSE_MAINEND \
    for(int i = 0;i < argc;i ++) { \
        delete[] argv[i]; \
    } \
    delete[] argv; \
}
#else
#define UNIVERSE_MAIN \
int main(int argc, char* argv[]) {
#define UNIVERSE_MAINEND \
}
#endif

#endif