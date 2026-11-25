# windowsRub

[English](README.md) | 简体中文

## 用法

### 为CLI程序自动转换argv

使用宏 `UNIVERSE_MAIN` 和 `UNIVERSE_MAINEND`。

```C++
UNIVERSE_MAIN
	// argv将被自动转换为utf8编码
	// 你的main函数体
UNIVERSE_MAINEND
```

使用宏 `UNIVERSE_MAIN_RETURN` 替换main函数中的 `return` 。

```C++
// return 0;
UNIVERSE_MAIN_RETURN(0);
```

### 设置 locale 到 UTF-8

定义宏 `_WINDOWSRUB_LOCALE_UTF8` 或把它添加到编译器选项。

### Get system error

```C++
// 使用 SysGetLastErro() 获得 std::error_code
// 注意，这个函数只能用于获取系统error_code，但其他system_error头文件中定义的错误也可能设置它。
// 获取系统error_code
std::error_code errorCode = errorUtils::SysGetLastError();
// 获取格式化的字符串(错误码, 错误类别, 错误信息)
std::string errorInformation = errorUtils::errorCode2String(errorCode);
```
