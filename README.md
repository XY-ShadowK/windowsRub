# windowsRub

English | [简体中文](README_zh-CN.md)

## Usage

### Auto-Convert argv for CLI Program

Use macro `UNIVERSE_MAIN` and `UNIVERSE_MAINEND`.

```C++
UNIVERSE_MAIN
	// argv will automatically convert to utf-8 code
	// your main content
UNIVERSE_MAINEND
```

Use macro `UNIVERSE_MAIN_RETURN` to replace `return` in main.

```C++
// return 0;
UNIVERSE_MAIN_RETURN(0);
```

### Set locale to UTF-8

Define macro `_WINDOWS_RUB_LOCALE_UTF8` or add it to compiler options.

### Get system error

```C++
// Use SysGetLastErro() to get a std::error_code
// Note, this function can only be used to get error_code for system, but other errors defined in system_error may also set it.
// get error_code for system
std::error_code errorCode = WindowsRub::ErrorUtils::SysGetLastError();
// get formatted string(error code, error category, error message)
std::string errorInformation = WindowsRub::ErrorUtils::errorCode2String(errorCode);
```

### File Operation

Use `WindowsRub::File::FilePath` to storage universe filename/path.
Use `WindowsRub::File::getFilePathU8` to get it from UTF-8 string.

```c++
WindowsRub::File::FilePath filePath = WindowsRub::File::getFilePathU8(filePathUTF8);
```

Use `WindowsRub::File::cFileOpen` if you need C-style `FILE` pointer.

```c++
FILE* fp = WindowsRub::File::cFileOpen(filePath, mode);
```