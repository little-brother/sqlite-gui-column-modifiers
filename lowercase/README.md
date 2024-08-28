Converts all uppercase letters in a string to lowercase. Can be replaced by a custom function `select lower(?1)`, but the plugin is faster.<br>

### How to build by mingw64
```
set PATH=c:\mingw64\mingw64\bin\;%PATH%
gcc -Wl,--kill-at -shared -static ./src/main.c -o lowercase.cmp -m64 -s -Os
```