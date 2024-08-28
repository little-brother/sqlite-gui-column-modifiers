Add spaces between each 3 digits.<br>

### How to build by mingw64
```
set PATH=c:\mingw64\mingw64\bin\;%PATH%
gcc -Wl,--kill-at -shared -static ./src/main.c -o 10_123.cmp -m64 -s -Os
```