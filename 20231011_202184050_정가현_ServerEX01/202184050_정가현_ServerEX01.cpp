#include "common.h"

#define SERVERPORT 9000
#define BUFSIZE 50

int main(int argc, char* argv[]) {
    int retval;

    // 윈속 초기화
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return 1;

    // 소켓 생성
    SOCKET listen_sock = socket(AF_INET6, SOCK_STREAM, 0);
    if (listen_sock == INVALID_SOCKET) err_quit("socket()");

    // bind()
    struct sockaddr_in6 serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin6_family = AF_INET6;
    serveraddr.sin6_addr = in6addr_any;  // INADDR_ANY 대신 in6addr_any 사용
    serveraddr.sin6_port = htons(SERVERPORT);
    retval = bind(listen_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if (retval == SOCKET_ERROR) err_quit("bind()");

    // listen()
    retval = listen(listen_sock, SOMAXCONN);
    if (retval == SOCKET_ERROR) err_quit("listen()");

    printf("[ TCP 채팅 서버 대기중... ]\n");

    while (1) {
        // 클라이언트 연결 대기
        struct sockaddr_in6 clientaddr;  // 클라이언트 주소 구조체를 sockaddr_in6로 변경
        int addrlen = sizeof(clientaddr);
        SOCKET client_sock = accept(listen_sock, (struct sockaddr*)&clientaddr, &addrlen);
        if (client_sock == INVALID_SOCKET) {
            err_quit("accept()");
            closesocket(listen_sock);
            WSACleanup();
            return 1;
        }

        // 데이터 통신에 사용할 변수
        char sendbuf[BUFSIZE];
        char recvbuf[BUFSIZE];

        // 클라이언트와 데이터 통신
        while (1) {
            // 클라이언트로부터 메시지 수신
            retval = recv(client_sock, recvbuf, BUFSIZE, 0);
            if (retval == SOCKET_ERROR) {
                err_quit("recv()");
                break;
            }
            else if (retval == 0) {
                printf("클라이언트와의 연결이 끊어졌습니다.\n");
                break;
            }

            // 받은 메시지 출력
            recvbuf[retval] = '\0';
            printf("클라이언트: %s", recvbuf);

            // 서버가 메시지 입력
            printf("나: ");
            fgets(sendbuf, BUFSIZE, stdin);

            // 데이터 보내기
            retval = send(client_sock, sendbuf, strlen(sendbuf), 0);
            if (retval == SOCKET_ERROR) {
                err_quit("send()");
                break;
            }
        }

        // 소켓 닫기
        closesocket(client_sock);
    }

    // 소켓 닫기
    closesocket(listen_sock);

    // 윈속 종료
    WSACleanup();
    return 0;
}
