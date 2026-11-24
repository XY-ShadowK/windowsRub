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
