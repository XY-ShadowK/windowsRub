#pragma once

#ifndef _UNIVERSE_UTILS_HPP_
#define _UNIVERSE_UTILS_HPP_

#include "Windows_Rub.hpp"

#define _WINDOWS_RUB_UNIVERSE_UTILS_BEGIN WINDOWS_RUB_NAMESPACE_BEGIN(namespace UniverseUtils {)
#define _WINDOWS_RUB_UNIVERSE_UTILS_END WINDOWS_RUB_NAMESPACE_END(})
#define _WINDOWS_RUB_UNIVERSE_UTILS WINDOWS_RUB_NAMESPACE(::UniverseUtils::)

#include <new>
#include <cstdio>
#include <type_traits>

_WINDOWS_RUB_UNIVERSE_UTILS_BEGIN

inline int checkAllocateNoThrow(const void* const p2Check) {
    if(!p2Check) {
        fprintf(stderr, "can not allocate space.\n");
        return -1;
    }
    return 0;
}

#define WINDOWS_RUB_UNIVERSE_UTILS_NEW_NOTHROW new (std::nothrow)
#define WINDOWS_RUB_UNIVERSE_UTILS_CHECK_NOTHROW(p) checkAllocateNoThrow(p)

template<typename T, typename... ArgsT>
inline int allocateMemory(const T*& p2Allocate, ArgsT&&... args) noexcept {
    p2Allocate = nullptr;
    p2Allocate = WINDOWS_RUB_UNIVERSE_UTILS_NEW_NOTHROW T(std::forward<ArgsT>(args)...);
    return WINDOWS_RUB_UNIVERSE_UTILS_CHECK_NOTHROW(p2Allocate);
}

template<typename T, typename... ArgsT>
inline int allocateArrayMemory(const T*& p2Allocate, size_t length, ArgsT&&... args) noexcept {
    p2Allocate = nullptr;
    p2Allocate = WINDOWS_RUB_UNIVERSE_UTILS_NEW_NOTHROW T[length](std::forward<ArgsT>(args)...);
    return WINDOWS_RUB_UNIVERSE_UTILS_CHECK_NOTHROW(p2Allocate);
}

template<typename T, typename... ArgsT>
inline int allocateMemory(T*& p2Allocate, ArgsT&&... args) noexcept {
    const T* cP2Allocate = p2Allocate;
    int ret = allocateMemeory(cP2Allocate, std::forward<ArgsT>(args)...);
    if(ret)
        return ret;
    p2Allocate = const_cast<T*>(cP2Allocate);
    return 0;
}

template<typename T, typename... ArgsT>
inline int allocateArrayMemory(T*& p2Allocate, size_t length, ArgsT&&... args) noexcept {
    const T* cP2Allocate = p2Allocate;
    int ret = allocateArrayMemory(cP2Allocate, length, std::forward<ArgsT>(args)...);
    if(ret)
        return ret;
    p2Allocate = const_cast<T*>(cP2Allocate);
    return 0;
}

template<typename T>
inline void releaseMemory(T*& p2Release) {
    delete p2Release;
    p2Release = nullptr;
}

template<typename T>
inline void releaseArrayMemory(T*& p2Release) {
    delete[] p2Release;
    p2Release = nullptr;
}

_WINDOWS_RUB_UNIVERSE_UTILS_END

#endif