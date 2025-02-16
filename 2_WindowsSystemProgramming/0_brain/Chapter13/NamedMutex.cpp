#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <process.h>

HANDLE hMutex;
DWORD dwWaitResult;

void ProcessBaseCriticalSection()
{
	dwWaitResult = WaitForSingleObject(hMutex, INFINITE);

	switch (dwWaitResult)
	{
	// �����尡 ���ؽ��� ����
	case WAIT_OBJECT_0:
		_tprintf(_T("thread got mutex!\n"));
		break;

	// time-out �߻�
	case WAIT_TIMEOUT:
		_tprintf(_T("timer expired!\n"));
		return;

	// ���ؽ� ��ȯ�� ������ �̷����� ����
	case WAIT_ABANDONED:
		return;
	}

	for (DWORD i = 0; i < 5; i++)
	{
		_tprintf(_T("Thread Running!\n"));
		Sleep(1000);
	}

	ReleaseMutex(hMutex);
}

int _tmain(int argc, TCHAR* argv[])
{
#if 0
	hMutex = CreateMutex(
		NULL, 
		FALSE, 
		_T("NamedMutex"));		// named mutex
#else
	if (hMutex == NULL)
	{
		hMutex = OpenMutex(
			MUTEX_ALL_ACCESS,		// ���� ���� ��û
			FALSE,					// �ڵ��� ������� ����
			_T("NamedMutex"));		// ���ؽ� ������Ʈ �̸�
	}
#endif

	if (hMutex == NULL)
	{
		_tprintf(_T("CreateMutex error: %d\n"), GetLastError());
		return -1;
	}

	ProcessBaseCriticalSection();

	CloseHandle(hMutex);
	return 0;
}