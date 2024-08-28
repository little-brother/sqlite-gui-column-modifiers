#define UNICODE
#define _UNICODE

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>

#define PLUGIN_NAME              TEXT("10_123")
#define PLUGIN_VERSION           "1.0.0"
#define MAX_MODIFIER_OUTPUT_LEN  1024
#define SQLITE_INTEGER           1
#define SQLITE_FLOAT             2
#define SQLITE_TEXT              3
#define SQLITE_BLOB              4
#define SQLITE_NULL              5

BOOL __stdcall setText(HWND hListWnd, int colNo, const unsigned char* data, int dataLen, int dataType, TCHAR* output16) {
	if (dataType == SQLITE_INTEGER || dataType == SQLITE_FLOAT) {
		TCHAR* num = (TCHAR*)data;
		TCHAR* dot = _tcschr(num, TEXT('.'));
		int dotPos = dataLen - (dot ? _tcslen(dot) : 0);

		int offset = 0;
		for (int i = 0; i < dotPos; i++) {
			output16[offset + i] = num[dotPos - i - 1];
			if (i % 3 == 2)	{
				offset++;
				output16[offset + i] = TEXT(' ');
			}
		}
		_tcsrev(output16);

		offset += dotPos;
		if (dot) {
			output16[offset] = TEXT('.');
			offset++;
		}

		for (int i = 0; i < dataLen - dotPos - 1; i++) {
			output16[offset + i] = num[dotPos + i + 1];
			if (i % 3 == 2)	{
				offset++;
				output16[offset + i] = TEXT(' ');
			}
		}		
	} else if (dataType == SQLITE_TEXT) {
		_tcsncpy(output16, (TCHAR*)data,  MAX_MODIFIER_OUTPUT_LEN);
	} 

	return TRUE;
}