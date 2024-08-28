#define UNICODE
#define _UNICODE

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <tchar.h>

#define PLUGIN_NAME              TEXT("heatmap")
#define PLUGIN_VERSION           "1.0.0"
#define MAX_MODIFIER_OUTPUT_LEN  1024
#define MAX_MODIFIER_ERROR_LEN   255
#define NO_VALUE                 0.00012003

#define SQLITE_INTEGER           1
#define SQLITE_FLOAT             2
#define SQLITE_TEXT              3
#define SQLITE_BLOB              4
#define SQLITE_NULL              5

BOOL isNumber(const TCHAR* str, double* out);

BOOL __stdcall setColor(NMLVCUSTOMDRAW* pCustomDraw, const unsigned char* data, int dataLen, int dataType) {
	if (dataType != SQLITE_INTEGER && dataType != SQLITE_FLOAT) 
		return FALSE;

	HWND hListWnd = pCustomDraw->nmcd.hdr.hwndFrom;
	int colNo = pCustomDraw->iSubItem;
	TCHAR prop[32];
	_sntprintf(prop, 32, TEXT("MINMAX-%i"), colNo);
	double* pMinMax = (double*)GetProp(hListWnd, prop);
	if (pMinMax == 0)
		return FALSE;

	double d = _tcstod((TCHAR*)data, 0);
	double v = 2 * (d - pMinMax[0])/(pMinMax[1] - pMinMax[0]);
	pCustomDraw->clrTextBk = v < 1 ? RGB(v * 255, 255, 0) : RGB(255, (2 - v) * 255, 0);

	return TRUE;
}

BOOL __stdcall activate(HWND hListWnd, int colNo, TCHAR* err16) {
	TCHAR*** cache = (TCHAR***)GetProp(hListWnd, TEXT("CACHE"));
	int* resultset = (int*)GetProp(hListWnd, TEXT("RESULTSET"));
	HWND hHeader = ListView_GetHeader(hListWnd);
	int colCount = Header_GetItemCount(hHeader);
	int rowCount = *(int*)GetProp(hListWnd, TEXT("ROWCOUNT"));

	if (colNo < 0 || colNo >= colCount)
		return FALSE;

	double min = NO_VALUE;
	double max = NO_VALUE;

	for (int rowNo = 0; rowNo < rowCount; rowNo++) {
		double value;
		int _rowNo = resultset[rowNo]; // if the dataset has a filter
		if (isNumber(cache[_rowNo][colNo], &value)) {
			min = min == NO_VALUE || min > value ? value : min;
			max = max == NO_VALUE || max < value ? value : max;
		}
	}

	if (min == NO_VALUE) {
		_sntprintf(err16, MAX_MODIFIER_ERROR_LEN, TEXT("Error: There are no numbers in the column."));
		return FALSE;
	}

	if (min == max) {
		_sntprintf(err16, MAX_MODIFIER_ERROR_LEN, TEXT("Error: Max value is equal to min value in the column."));
		return FALSE;
	}
	
	double* pMinMax = calloc(2, sizeof(double));
	pMinMax[0] = min;
	pMinMax[1] = max;

	TCHAR prop[32];
	_sntprintf(prop, 32, TEXT("MINMAX-%i"), colNo);
	SetProp(hListWnd, prop, pMinMax);

	return TRUE;
}

BOOL __stdcall deactivate(HWND hListWnd, int colNo) {
	TCHAR prop[32];
	_sntprintf(prop, 32, TEXT("MINMAX-%i"), colNo);
	double* pMinMax = (double*)GetProp(hListWnd, prop);
	if (pMinMax) 
		free(pMinMax);
	RemoveProp(hListWnd, prop);

	return TRUE;
}

BOOL isNumber(const TCHAR* str, double* out) {
	int len = _tcslen(str);
	if (len == 0)
		return FALSE;

	double d;
	TCHAR *endptr;
	errno = 0;
	d = _tcstod(str, &endptr);
	BOOL rc = !(errno != 0 || *endptr != '\0');
	if (rc && out != NULL)
		*out = d;

	return rc;
}