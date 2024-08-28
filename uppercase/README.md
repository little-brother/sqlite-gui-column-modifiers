Converts all lowercase letters in a string to uppercase. Can be replaced by a custom function `select upper(?1)`, but the plugin is faster.<br>

### How to build by mingw64
```
set PATH=c:\mingw64\mingw64\bin\;%PATH%
gcc -Wl,--kill-at -shared -static ./src/main.c -o uppercase.cmp -m64 -s -Os
```