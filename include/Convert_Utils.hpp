#pragma once

#ifndef _CONVERT_UTILS_HPP_
#define _CONVERT_UTILS_HPP_

#include "Windows_Rub.hpp"

#define _WINDOWS_RUB_CONVERT_UTILS_BEGIN WINDOWS_RUB_NAMESPACE_BEGIN(namespace ConvertUtils {)
#define _WINDOWS_RUB_CONVERT_UTILS_END WINDOWS_RUB_NAMESPACE_END(})
#define _WINDOWS_RUB_CONVERT_UTILS WINDOWS_RUB_NAMESPACE(::ConvertUtils::)

#if defined(_WIN32) && !defined(__CYGWIN__)
#include <Windows.h>
#endif

_WINDOWS_RUB_CONVERT_UTILS_BEGIN

#if defined(_WIN32) && !defined(__CYGWIN__)

inline int getLengthW2UTF8(const wchar_t* const wstr) {
    return WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
}

inline int convertW2UTF8(const wchar_t* const wstr, char*& str, const int length) {
    if(WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, length, nullptr, nullptr) == 0)
        return -1;
    return 0;
}

#endif

_WINDOWS_RUB_CONVERT_UTILS_END

#endif