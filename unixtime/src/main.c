#define UNICODE
#define _UNICODE

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <time.h>

#define PLUGIN_NAME              TEXT("unixtime")
#define PLUGIN_VERSION           "1.0.0"
#define MAX_MODIFIER_OUTPUT_LEN  1024
#define SQLITE_BLOB              4
#define SQLITE_NULL              5

static TCHAR iniPath[MAX_PATH] = {0};
BOOL APIENTRY DllMain (HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved);
TCHAR* getStoredString(TCHAR* name, TCHAR* defValue);

BOOL __stdcall setText(HWND hListWnd, int colNo, const unsigned char* data, int dataLen, int dataType, TCHAR* output16) {
	if (dataType == SQLITE_BLOB || dataType == SQLITE_NULL || (dataLen != 10 && dataLen != 13))
		return FALSE;

	for (int i = 0; i < dataLen; i++) {
		if (!_istdigit(((TCHAR*)data)[i])) 
			return FALSE;
	}

	time_t rawtime = _ttoi64((TCHAR*)data) / (dataLen == 13 ? 1000 : 1);
	if (rawtime > 2120000000) // 07.03.2037
		return 0;

	struct tm* ptm = gmtime (&rawtime);
	TCHAR* format16 = getStoredString(TEXT("format"), TEXT("%d-%m-%Y")); // %d-%m-%Y %H:%M:%S, %A
	_tcsftime(output16, 256, format16, ptm);

	return TRUE;
}

BOOL APIENTRY DllMain (HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH && iniPath[0] == 0) {
		TCHAR path[MAX_PATH + 1] = {0};
		GetModuleFileName(hModule, path, MAX_PATH);
		TCHAR* dot = _tcsrchr(path, TEXT('.'));
		_tcsncpy(dot, TEXT(".ini"), 5);
		if (_taccess(path, 0) == 0)
			_tcscpy(iniPath, path);	
	}

	return TRUE;
}

TCHAR* getStoredString(TCHAR* name, TCHAR* defValue) { 
	TCHAR* buf = calloc(256, sizeof(TCHAR));
	if (0 == GetPrivateProfileString(PLUGIN_NAME, name, NULL, buf, 128, iniPath) && defValue)
		_tcsncpy(buf, defValue, 255);
	return buf;	
}