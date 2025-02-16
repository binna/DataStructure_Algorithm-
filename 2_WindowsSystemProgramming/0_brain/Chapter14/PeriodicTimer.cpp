#include <stdio.h>
#include <tchar.h>
#include <windows.h>

#define _WIN32_WINNT		0x0400


int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hTimer = NULL;
	LARGE_INTEGER liDueTime;

	liDueTime.QuadPart = -100000000;

	// Ÿ�̸� ������Ʈ ����
	hTimer = CreateWaitableTimer(NULL, FALSE, _T("WaitableTimer"));

	if (!hTimer)
	{
		_tprintf(_T("CreateWaitableTimer failed(%d)\n"), GetLastError());
		return 1;
	}

	_tprintf(_T("CreateWait for 5 seconds ...\n"));

	// Ÿ�̸��� �˶��� 5�ʷ� ����
	SetWaitableTimer(hTimer, &liDueTime, 5000, NULL, NULL, FALSE);

	// Ÿ�̸��� �˶� ���
	while (1)
	{
		WaitForSingleObject(hTimer, INFINITE);
		_tprintf(_T("Timer was signaled.\n"));
		MessageBeep(MB_ICONEXCLAMATION);
	}

	return 0;
}