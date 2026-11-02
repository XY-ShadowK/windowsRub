/*
time: 2026/11/2 18:01:39
*/
#pragma once
#ifndef _WINDOWSRUB_HPP_
#define _WINDOWSRUB_HPP_

#ifdef _WIN32
#include <codecvt>
#include <string>
#include <cstring>
#endif

#ifdef _WIN32
#define UNIVERSE_MAIN \
int wmain(int argc, wchar_t* wargv[]) { \
    char** argv = new char*[argc]; \
    { \
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter; \
        std::string strU8; \
        for(int i = 0;i < argc;i ++) { \
            strU8 = converter.to_bytes(wargv[i]); \
            argv[i] = new char[strlen(strU8.c_str()) + 1]; \
            strcpy(argv[i], strU8.c_str()); \
        } \
    }
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