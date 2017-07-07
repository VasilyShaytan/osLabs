// BlockExeUsb.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <tchar.h>

using namespace std;

#ifdef _UNICODE
#  define _tcout wcout
#else
#  define _tcout cout
#endif // _UNICODE


//������ ����� � ������
int KeyToRegestrSystem(DWORD keyValue)
{
	// ���� �����
	_TCHAR szPath[] = _T("System\\CurrentControlSet\\Control\\StorageDevicePolicies\\");

	HKEY hKey;

	// ������� ���� � ����� HKEY_LOCAL_MACHINE
	if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, szPath, 0, NULL, REG_OPTION_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) != ERROR_SUCCESS) {
		_tcout << _T("��� �������� ����� ��������� ������") << endl;
		return 1;
	}

	// ����� �������� � ��������� ����
	if (RegSetValueEx(hKey, TEXT("ExecuteProtect"), 0, REG_DWORD, (const BYTE*)&keyValue, sizeof(keyValue)) != ERROR_SUCCESS) {
		_tcout << _T("��� ������ ������ ��������� ������") << endl;
		return 2;
	}

	// ��������� ��������� �����
	if (RegCloseKey(hKey) != ERROR_SUCCESS) {
		_tcout << _T("��� �������� ����� ��������� ������") << endl;
		return 3;
	};
	return 0;
}

//������ �����  � ������
int KeyToRegestr(DWORD keyValue)
{
	// ���� �����
	_TCHAR szPath[] = _T("Software\\Policies\\Microsoft\\Windows\\RemovableStorageDevices\\{53f5630d-b6bf-11d0-94f2-00a0c91efb8b}\\");

	HKEY hKey;

	// ������� ���� � ����� HKEY_LOCAL_MACHINE
	if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, szPath, 0, NULL, REG_OPTION_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) != ERROR_SUCCESS) {
		_tcout << _T("��� �������� ����� ��������� ������") << endl;
		return 1;
	}

	// ����� �������� � ��������� ����
	if (RegSetValueEx(hKey, TEXT("Deny_Execute"), 0, REG_DWORD, (const BYTE*)&keyValue, sizeof(keyValue)) != ERROR_SUCCESS) {
		_tcout << _T("��� ������ ������ ��������� ������") << endl;
		return 2;
	}

	// ��������� ��������� �����
	if (RegCloseKey(hKey) != ERROR_SUCCESS) {
		_tcout << _T("��� �������� ����� ��������� ������") << endl;
		return 3;
	};
	return 0;
}

//������ ���� � �������
void PrintMenu()
{
	cout << "1 - �������� ����������\n";
	cout << "2 - ��������� ����������\n";
	cout << "3 - ����� �� ���������\n";
	cout << "> ";
}

int _tmain(int argc, _TCHAR* argv[])
{
	// ������������� ������� ������� �������� ��� ������ ���������
	//_tsetlocale(LC_ALL, _T("Russain"));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//����� ������ ����
	int choice;
	cout << "������� ����:\n";
	do {
		PrintMenu(); //�������� ����
		cin >> choice; //�������� ����� ������

		switch (choice) {
		case 1: //�������� ����� ������������ exe
			((KeyToRegestr(1) && KeyToRegestrSystem(1)) == 0) ? cout << "\n���������� ��������.\n" : cout << "\n���, ���������� �� ��������.\n";
			break;
		case 2: //�������� ����� ��������������� exe
			((KeyToRegestr(0) && KeyToRegestrSystem(0)) == 0) ? cout << "\n���������� ���������.\n" : cout << "\n���, ���������� �� ���������.\n";
			break;
			/*case 3: //�������� ����� �������
			cout << "Goodbye!\n";
			break;*/
		default: //
				 //PrintMenu();
				 //cin >> choice;
			cout << "������ ������ � ���� ���.\n";
		}
	} while (choice != 3);

	//_tsystem(_T("pause"));
	return 0;
}