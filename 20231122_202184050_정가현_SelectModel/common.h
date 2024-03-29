#define _CRT_SECURE_NO_WARNONGS		// 구형 c함수 사용 시 경고 끄기
#define _WINSOCK_DEPRECATED_NO_WARNINGS		// 구형 소켓 API 사용 시 경고 끄기

#include <winsock2.h>	// 윈속2 메인 헤더
#include <WS2tcpip.h>	// 윈속2 확장 헤더

#include <tchar.h>	// _T(), ...
#include <stdio.h>	// printf(), ...
#include <stdlib.h>		// exit(), ...
#include <string.h>		// strnpy(), ...

#pragma comment(lib, "ws2_32")	//ws2_32.lib 링크

//소켓 함수 오류 출력 후 종료
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

// 소켓 함수 오류 출력
void err_display(int errcode) {
	LPVOID IpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, errcode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&IpMsgBuf, 0, NULL
	);
	printf("[오류] %s \n", (char*)IpMsgBuf);
	LocalFree(IpMsgBuf);
}