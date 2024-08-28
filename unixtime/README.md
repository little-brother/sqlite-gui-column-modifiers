Convert UNIX-time to a date-time string. The plugin demonstates how to use ini-file.<br>
To change output format, create `unixtime.ini` with content
```
[unixtime]
format=%d-%m-%Y %H:%M:%S, %A
```

### How to build by mingw64
```
set PATH=c:\mingw64\mingw64\bin\;%PATH%
gcc -Wl,--kill-at -shared -static ./src/main.c -o unixtime.cmp -m64 -s -Os
```