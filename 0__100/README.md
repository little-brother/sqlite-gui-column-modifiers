The plugin demonstrates how to use a custom render to show numbers between 0 and 100 as a progress bar.<br>

### How to build by mingw64
```
set PATH=c:\mingw64\mingw64\bin\;%PATH%
gcc -Wl,--kill-at -shared -static ./src/main.c -o 0__100.cmp -m64 -s -Os -lgdi32
```