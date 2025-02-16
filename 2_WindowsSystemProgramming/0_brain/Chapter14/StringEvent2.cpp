#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <process.h>

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam);
unsigned int WINAPI CountThreadFunction(LPVOID lpParam);

TCHAR string[100];
HANDLE hEvent;

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hThread[2];
	DWORD dwThreadIDs[2];

	hEvent = CreateEvent(	// event object ����
		NULL,	// ��� �Ұ�
		TRUE,	// manual-reset mode�� ����
		FALSE,	// non-signaled ���·� ����
		NULL);	// �̸����� event

	if (hEvent == NULL)
	{
		_fputts(_T("Event object creation error\n"), stdout);
		return -1;
	}

	hThread[0] = (HANDLE)_beginthreadex(
		NULL,
		0,
		OutputThreadFunction,
		NULL,
		0,
		(unsigned*)&dwThreadIDs[0]);

	hThread[1] = (HANDLE)_beginthreadex(
		NULL,
		0,
		CountThreadFunction,
		NULL,
		0,
		(unsigned*)&dwThreadIDs[1]);

	if (hThread[0] == 0 || hThread[1] == 0)
	{
		_fputts(_T("Thread creation error\n"), stdout);
		return -1;
	}

	_fputts(_T("Insert string : "), stdout);
	_fgetts(string, 30, stdin);

	SetEvent(hEvent);			// event�� state�� signaled ���·� ����

	WaitForMultipleObjects(
		2,			// �迭�� ����
		hThread,	// �ڵ��� �迭
		TRUE,		// ��� �ڵ��� ��ȣ�޴� ���·� �� ��, ����
		INFINITE);	// ���� ���

	CloseHandle(hEvent);		// event ������Ʈ �Ҹ�
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	return 0;
}

unsigned int __stdcall OutputThreadFunction(LPVOID lpParam)
{
	WaitForSingleObject(hEvent, INFINITE);

	_fputts(_T("Output string : "), stdout);
	_fputts(string, stdout);

	return 0;
}

unsigned int __stdcall CountThreadFunction(LPVOID lpParam)
{
	WaitForSingleObject(hEvent, INFINITE);

	_tprintf(_T("output string length : %d\n"), _tcslen(string) - 1);

	return 0;
}