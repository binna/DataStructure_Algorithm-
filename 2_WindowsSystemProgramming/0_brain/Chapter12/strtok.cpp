#include <stdio.h>
#include <tchar.h>
#include <windows.h>



int _tmain(int argc, TCHAR* argv[])
{
	TCHAR string[] = 
		_T("Hey, get a life!")
		_T("you don't even have two pennies to rub together.");

	TCHAR seps[] = _T(" ,.!");
	PTCHAR nextToken;

	// ��ū �и� ����, ���ڿ� ���� �� ù ��° ��� ��ȯ
	TCHAR* token = _tcstok_s(string, seps, &nextToken);

	// ����ؼ� ��ū�� ��ȯ �� ���
	while (token != NULL)
	{
		_tprintf(_T(" %s\n"), token);
		token = _tcstok_s(NULL, seps, &nextToken);
	}

	return 0;
}