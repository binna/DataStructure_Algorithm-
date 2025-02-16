#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <process.h>

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam);
unsigned int WINAPI CountThreadFunction(LPVOID lpParam);

typedef struct _SynchString
{
	TCHAR string[100];
	HANDLE hEvent;
	HANDLE hMutex;
}SynchString;

SynchString gSynString;

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hThread[2];
	DWORD dwThreadIDs[2];

	gSynString.hEvent = CreateEvent(	// event object ����
		NULL,	// ��� �Ұ�
		TRUE,	// manual-reset mode�� ����
		FALSE,	// non-signaled ���·� ����
		NULL);	// �̸����� event

	gSynString.hMutex = CreateMutex(NULL, FALSE, NULL);

	if (gSynString.hEvent == NULL || gSynString.hMutex == NULL)
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
	_fgetts(gSynString.string, 30, stdin);

	SetEvent(gSynString.hEvent);		// event�� state�� signaled ���·� ����

	WaitForMultipleObjects(
		2,			// �迭�� ����
		hThread,	// �ڵ��� �迭
		TRUE,		// ��� �ڵ��� ��ȣ�޴� ���·� �� ��, ����
		INFINITE);	// ���� ���

	CloseHandle(gSynString.hEvent);		// event ������Ʈ �Ҹ�
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	return 0;
}

unsigned int __stdcall OutputThreadFunction(LPVOID lpParam)
{
	WaitForSingleObject(gSynString.hEvent, INFINITE);
	WaitForSingleObject(gSynString.hMutex, INFINITE);

	_fputts(_T("Output string : "), stdout);
	_fputts(gSynString.string, stdout);

	ReleaseMutex(gSynString.hMutex);

	return 0;
}

unsigned int __stdcall CountThreadFunction(LPVOID lpParam)
{
	WaitForSingleObject(gSynString.hEvent, INFINITE);
	WaitForSingleObject(gSynString.hMutex, INFINITE);

	_tprintf(_T("Output string length : %d\n"), _tcslen(gSynString.string) - 1);

	ReleaseMutex(gSynString.hMutex);

	return 0;
}