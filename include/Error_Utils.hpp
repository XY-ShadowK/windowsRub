#pragma once

#ifndef _ERRORUTILS_HPP_
#define _ERRORUTILS_HPP_

#include "Windows_Rub.hpp"

#define _WINDOWS_RUB_ERROR_UTILS_BEGIN WINDOWS_RUB_NAMESPACE_BEGIN(namespace ErrorUtils {)
#define _WINDOWS_RUB_ERROR_UTILS_END WINDOWS_RUB_NAMESPACE_END(})
#define _WINDOWS_RUB_ERROR_UTILS WINDOWS_RUB_NAMESPACE(::ErrorUtils::)

#include <string>
#include <system_error>

#if defined(_WIN32) && !defined(_LIBCPP_VERSION) && !defined(__CYGWIN__)
#include <Windows.h>

#include "Convert_Utils.hpp"
#include "Universe_Utils.hpp"
#endif

_WINDOWS_RUB_ERROR_UTILS_BEGIN

#if defined(_WIN32) && !defined(_LIBCPP_VERSION) && !defined(__CYGWIN__)
[[nodiscard]] const std::error_category& WindowsCategory() noexcept;
class WindowsErrorCategory : public std::error_category {
public:
    constexpr WindowsErrorCategory() noexcept : error_category(_System_addr) {}
    [[nodiscard]] virtual const char* name() const noexcept override {
        return std::system_category().name();
    }
    [[nodiscard]] virtual std::string message(int errorCode) const override {
        LPWSTR buffer = nullptr;
        size_t lengthW = FormatMessageW(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr,
            errorCode,
            LANG_USER_DEFAULT,
            (LPWSTR)&buffer,
            0,
            nullptr
        );
        if(lengthW == 0)
            return "Unknown error code";
            
        static constexpr const char* TRANSFORM_FAILURE_MESSAGE = "Transform error message charset to UTF-8 failed.(this is not the actual error message)";
        int lengthU8 = _WINDOWS_RUB_CONVERT_UTILS getLengthW2UTF8(buffer);
        if(lengthU8 == 0)
            return TRANSFORM_FAILURE_MESSAGE;
        char* bufferU8 = nullptr;
        if(_WINDOWS_RUB_UNIVERSE_UTILS allocateArrayMemory(bufferU8, lengthU8))
            exit(-1);
        std::string messageStr;
        if(_WINDOWS_RUB_CONVERT_UTILS convertW2UTF8(buffer, bufferU8, lengthU8))
            messageStr = TRANSFORM_FAILURE_MESSAGE;
        else
            // remove CRLF from FormatMessage
            messageStr = std::string(bufferU8, lengthU8 - 2);
        LocalFree(buffer);
        _WINDOWS_RUB_UNIVERSE_UTILS releaseArrayMemory(bufferU8);
        return messageStr;
    }
    [[nodiscard]] virtual std::error_condition default_error_condition(int errorValue) const noexcept override {
        const std::error_condition& errorCondition = std::system_category().default_error_condition(errorValue);
        if(errorCondition.category() == std::system_category())
            return std::error_condition(errorValue, *this);
        return errorCondition;
    }
};
[[nodiscard]] inline const std::error_category& WindowsCategory() noexcept {
    static WindowsErrorCategory WindowsErrorCategoryInstance;
    return WindowsErrorCategoryInstance;
}
#endif

inline std::error_code SysGetLastError() {
#if defined(_WIN32) && !defined(_LIBCPP_VERSION) && !defined(__CYGWIN__)
    return {(int)GetLastError(), WindowsCategory()};
#else
    return {errno, std::system_category()};
#endif
}

inline std::string errorCode2String(const std::error_code& errorCode) {
    return "Error : " + std::to_string(errorCode.value()) + ", Category : " + errorCode.category().name() + ", Message : " + errorCode.message();
}

_WINDOWS_RUB_ERROR_UTILS_END

#endif