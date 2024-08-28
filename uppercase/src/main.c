#define UNICODE
#define _UNICODE

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>

#define PLUGIN_NAME              TEXT("uppercase")
#define PLUGIN_VERSION           "1.0.0"
#define MAX_MODIFIER_OUTPUT_LEN  1024
#define SQLITE_BLOB              4
#define SQLITE_NULL              5

BOOL __stdcall setText(HWND hListWnd, int colNo, const unsigned char* data, int dataLen, int dataType, TCHAR* output16) {
	if (dataType != SQLITE_BLOB && dataType != SQLITE_NULL) {
		_tcsncpy(output16, (TCHAR*)data, MAX_MODIFIER_OUTPUT_LEN);
		_tcsupr(output16);
	}

	return TRUE;
}