Colorize cells in a column according their values. The plugin demonstrates how to change a cell background and to do some actions on plugin's activation/deactivation.<br>

### How to build by mingw64
```
set PATH=c:\mingw64\mingw64\bin\;%PATH%
gcc -Wl,--kill-at -shared -static ./src/main.c -o heatmap.cmp -m64 -s -Os
```