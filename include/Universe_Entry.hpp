/*
Modified Time: 2026/11/24 16:55:43
Copyright (c) 2026 XY-ShadowK
SPDX-License-Identifier: MPL-2.0
*/

#pragma once
#ifndef _UNIVERSE_ENTRY_HPP_
#define _UNIVERSE_ENTRY_HPP_

#include "Windows_Rub.hpp"

#define _WINDOWS_RUB_UNIVERSE_ENTRY_BEGIN WINDOWS_RUB_NAMESPACE_BEGIN(namespace UniverseEntry {)
#define _WINDOWS_RUB_UNIVERSE_ENTRY_END WINDOWS_RUB_NAMESPACE_END(})
#define _WINDOWS_RUB_UNIVERSE_ENTRY WINDOWS_RUB_NAMESPACE(::UniverseEntry::)

#ifdef _WINDOWS_RUB_LOCALE_UTF8
#include <clocale>

#define SET_LOCALE_UTF8 \
    // std::setlocale(LC_ALL, ".65001");

#else
#define SET_LOCALE_UTF8
#endif

#if defined(_WIN32) && !defined(__CYGWIN__)
#include <Windows.h>
#include <cstdio>

#include "Convert_Utils.hpp"
#include "Universe_Utils.hpp"
#endif

_WINDOWS_RUB_UNIVERSE_ENTRY_BEGIN

#if defined(_WIN32) && !defined(__CYGWIN__)

inline int convertArgvW2UTF8(const int num, const wchar_t* const* const wargv, char**& argv) {
    if(_WINDOWS_RUB_UNIVERSE_UTILS allocateArrayMemory(argv, num) == -1)
        exit(-1);
    for(int i = 0;i < num;i ++) {
        int length = _WINDOWS_RUB_CONVERT_UTILS getLengthW2UTF8(wargv[i]);
        if(length == 0)
            return -1;
        if(_WINDOWS_RUB_UNIVERSE_UTILS allocateArrayMemory(argv[i], length) == -1)
            exit(-1);
        if(_WINDOWS_RUB_CONVERT_UTILS convertW2UTF8(wargv[i], argv[i], length)) {
            for(int j = 0;j <= i;j ++)
                _WINDOWS_RUB_UNIVERSE_UTILS releaseArrayMemory(argv[j]);
            _WINDOWS_RUB_UNIVERSE_UTILS releaseArrayMemory(argv);
            return -1;
        }
    }
    return 0;
}

// only use wmain in msvc
#if defined(_MSC_VER)
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
        if(_WINDOWS_RUB_UNIVERSE_ENTRY convertArgvW2UTF8(argc, wargv, t_argv)) \
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

_WINDOWS_RUB_UNIVERSE_ENTRY_END

#endif