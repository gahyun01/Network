#define _CRT_SECURE_NO_WARNONGS		// ���� c�Լ� ��� �� ��� ����
#define _WINSOCK_DEPRECATED_NO_WARNINGS		// ���� ���� API ��� �� ��� ����

#include <winsock2.h>	// ����2 ���� ���
#include <WS2tcpip.h>	// ����2 Ȯ�� ���

#include <tchar.h>	// _T(), ...
#include <stdio.h>	// printf(), ...
#include <stdlib.h>		// exit(), ...
#include <string.h>		// strnpy(), ...

#pragma comment(lib, "ws2_32")	//ws2_32.lib ��ũ

//���� �Լ� ���� ��� �� ����
void err_quit(const char* msg) {
	LPVOID IpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&IpMsgBuf, 0, NULL
	);
	MessageBoxA(NULL, (const char*)IpMsgBuf, msg, MB_ICONERROR);
	LocalFree(IpMsgBuf);
	exit(1);
}

void err_display(const char* msg) {
	LPVOID IpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&IpMsgBuf, 0, NULL
	);
	printf("[%s] %s \n", msg, (char*)IpMsgBuf);
}

// ���� �Լ� ���� ���
void err_display(int errcode) {
	LPVOID IpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, errcode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&IpMsgBuf, 0, NULL
	);
	printf("[����] %s \n", (char*)IpMsgBuf);
	LocalFree(IpMsgBuf);
}