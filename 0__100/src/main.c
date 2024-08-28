#define UNICODE
#define _UNICODE

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <tchar.h>

#define PLUGIN_NAME              TEXT("0__100")
#define PLUGIN_VERSION           "1.0.0"
#define MAX_MODIFIER_OUTPUT_LEN  1024

#define SQLITE_INTEGER           1
#define SQLITE_FLOAT             2
#define SQLITE_TEXT              3
#define SQLITE_BLOB              4
#define SQLITE_NULL              5

BOOL __stdcall render(NMLVCUSTOMDRAW* pCustomDraw, const unsigned char* data, int dataLen, int dataType) {
	if (dataType != SQLITE_INTEGER && dataType != SQLITE_FLOAT) 
		return FALSE;

	double d = _tcstod((TCHAR*)data, NULL);
	if (d < 0 || d > 100)
		return FALSE;
			
	HWND hListWnd = pCustomDraw->nmcd.hdr.hwndFrom;
	HDC hDC = pCustomDraw->nmcd.hdc;
	RECT rc = pCustomDraw->nmcd.rc;

	PAINTSTRUCT ps = {0};
	ps.fErase = TRUE;
	BeginPaint(hListWnd, &ps);

	RECT rc2 = rc;
	rc2.right = rc.left + d * (rc.right - rc.left)/100.0;
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 200, 0));
	FillRect(hDC, &rc2, hBrush);
	DeleteObject(hBrush);

	DrawText(hDC, (TCHAR*)data, dataLen, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	
	EndPaint(hListWnd, &ps);	
		
	
	return TRUE;
}