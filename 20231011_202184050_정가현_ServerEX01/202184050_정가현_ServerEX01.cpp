#include "common.h"

#define SERVERPORT 9000
#define BUFSIZE 50

int main(int argc, char* argv[]) {
    int retval;

    // ���� �ʱ�ȭ
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return 1;

    // ���� ����
    SOCKET listen_sock = socket(AF_INET6, SOCK_STREAM, 0);
    if (listen_sock == INVALID_SOCKET) err_quit("socket()");

    // bind()
    struct sockaddr_in6 serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin6_family = AF_INET6;
    serveraddr.sin6_addr = in6addr_any;  // INADDR_ANY ��� in6addr_any ���
    serveraddr.sin6_port = htons(SERVERPORT);
    retval = bind(listen_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if (retval == SOCKET_ERROR) err_quit("bind()");

    // listen()
    retval = listen(listen_sock, SOMAXCONN);
    if (retval == SOCKET_ERROR) err_quit("listen()");

    printf("[ TCP ä�� ���� �����... ]\n");

    while (1) {
        // Ŭ���̾�Ʈ ���� ���
        struct sockaddr_in6 clientaddr;  // Ŭ���̾�Ʈ �ּ� ����ü�� sockaddr_in6�� ����
        int addrlen = sizeof(clientaddr);
        SOCKET client_sock = accept(listen_sock, (struct sockaddr*)&clientaddr, &addrlen);
        if (client_sock == INVALID_SOCKET) {
            err_quit("accept()");
            closesocket(listen_sock);
            WSACleanup();
            return 1;
        }

        // ������ ��ſ� ����� ����
        char sendbuf[BUFSIZE];
        char recvbuf[BUFSIZE];

        // Ŭ���̾�Ʈ�� ������ ���
        while (1) {
            // Ŭ���̾�Ʈ�κ��� �޽��� ����
            retval = recv(client_sock, recvbuf, BUFSIZE, 0);
            if (retval == SOCKET_ERROR) {
                err_quit("recv()");
                break;
            }
            else if (retval == 0) {
                printf("Ŭ���̾�Ʈ���� ������ ���������ϴ�.\n");
                break;
            }

            // ���� �޽��� ���
            recvbuf[retval] = '\0';
            printf("Ŭ���̾�Ʈ: %s", recvbuf);

            // ������ �޽��� �Է�
            printf("��: ");
            fgets(sendbuf, BUFSIZE, stdin);

            // ������ ������
            retval = send(client_sock, sendbuf, strlen(sendbuf), 0);
            if (retval == SOCKET_ERROR) {
                err_quit("send()");
                break;
            }
        }

        // ���� �ݱ�
        closesocket(client_sock);
    }

    // ���� �ݱ�
    closesocket(listen_sock);

    // ���� ����
    WSACleanup();
    return 0;
}
