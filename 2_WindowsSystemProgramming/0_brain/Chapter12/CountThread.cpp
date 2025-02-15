#include <stdio.h>
#include <tchar.h>
#include <windows.h>

#define MAX_THREADS (1024*10)

DWORD cntOfThread = 0;

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	DWORD threadNum = (DWORD)lpParam;

	while (1)
	{
		_tprintf(_T("thread Num: %d\n"), threadNum);
		Sleep(500);
	}

	return 0;
}

int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadID[MAX_THREADS];
	HANDLE hThread[MAX_THREADS];

	// 생상 가능한 최대 개수의 쓰레드 생성
	while (1)
	{
		hThread[cntOfThread] = CreateThread(
			NULL,						// 디폴트 보안 속성 지정
			0,							// 디폴트 스택 사이즈
			ThreadProc,					// 쓰레드 함수
			(LPVOID)cntOfThread,		// 쓰레드 함수의 전달 인자
			0,							// 디폴트 생성 flag 지정
			&dwThreadID[cntOfThread]);	// 쓰레드 ID 반환

		// 쓰레드 생성 확인
		if (hThread[cntOfThread] == NULL)
		{
			_tprintf(_T("MAXIMUM THREAD NUMBER: %d\n"), cntOfThread);
			break;
		}
		cntOfThread++;
	}

	for (DWORD i = 0; i < cntOfThread; i++)
	{
		CloseHandle(hThread[i]);
	}

	return 0;
}