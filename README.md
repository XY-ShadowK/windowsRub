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
