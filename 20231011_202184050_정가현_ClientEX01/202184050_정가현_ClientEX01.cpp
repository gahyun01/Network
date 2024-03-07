#include "common.h"

char* SERVERIP = (char*)"::1";  // IPv6 루프백 주소
#define SERVERPORT 9000
#define BUFSIZE 50

int main(int argc, char* argv[]) {
    int retval;

    // 명령행 인수가 있으면 IP 주소로 사용
    if (argc > 1) SERVERIP = argv[1];

    // 윈속 초기화
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return 1;

    // 소켓 생성
    SOCKET sock = socket(AF_INET6, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) err_quit("socket()");

    // connect()
    struct sockaddr_in6 serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, SERVERIP, &serveraddr.sin6_addr);
    serveraddr.sin6_port = htons(SERVERPORT);
    retval = connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if (retval == SOCKET_ERROR) err_quit("connect()");

    // 데이터 통신에 사용할 변수
    char sendbuf[BUFSIZE];
    char recvbuf[BUFSIZE];

    while (1) {
        // 클라이언트가 메시지 입력
        printf("나: ");
        fgets(sendbuf, BUFSIZE, stdin);

        // 데이터 보내기
        retval = send(sock, sendbuf, strlen(sendbuf), 0);
        if (retval == SOCKET_ERROR) {
            err_display("send()");
            break;
        }

        // 서버로부터 메시지 수신
        retval = recv(sock, recvbuf, BUFSIZE, 0);
        if (retval == SOCKET_ERROR) {
            err_display("recv()");
            break;
        }
        else if (retval == 0) {
            printf("서버와의 연결이 끊어졌습니다.\n");
            break;
        }

        // 수신한 메시지 출력
        recvbuf[retval] = '\0';
        printf("상대방: %s", recvbuf);
    }

    // 소켓 닫기
    closesocket(sock);

    // 윈속 종료
    WSACleanup();
    return 0;
}
