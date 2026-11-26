#pragma once

#ifndef _FILE_PATH_HPP_
#define _FILE_PATH_HPP_

#include "Windows_Rub.hpp"

#define _WINDOWS_RUB_FILE_BEGIN WINDOWS_RUB_NAMESPACE_BEGIN(namespace File {)
#define _WINDOWS_RUB_FILE_END WINDOWS_RUB_NAMESPACE_END(})
#define _WINDOWS_RUB_FILE WINDOWS_RUB_NAMESPACE(::File::)

#if defined(_WIN32) && !defined(__CYGWIN__)
#include <filesystem>
#else
#include <string>
#endif

_WINDOWS_RUB_FILE_BEGIN

#if defined(_WIN32) && !defined(__CYGWIN__)
using FilePath = std::filesystem::path;
#else
using FilePath = std::string;
#endif

_WINDOWS_RUB_FILE_END

#endif