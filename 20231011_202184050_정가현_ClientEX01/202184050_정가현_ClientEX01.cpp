#include "common.h"

char* SERVERIP = (char*)"::1";  // IPv6 ������ �ּ�
#define SERVERPORT 9000
#define BUFSIZE 50

int main(int argc, char* argv[]) {
    int retval;

    // ����� �μ��� ������ IP �ּҷ� ���
    if (argc > 1) SERVERIP = argv[1];

    // ���� �ʱ�ȭ
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return 1;

    // ���� ����
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

    // ������ ��ſ� ����� ����
    char sendbuf[BUFSIZE];
    char recvbuf[BUFSIZE];

    while (1) {
        // Ŭ���̾�Ʈ�� �޽��� �Է�
        printf("��: ");
        fgets(sendbuf, BUFSIZE, stdin);

        // ������ ������
        retval = send(sock, sendbuf, strlen(sendbuf), 0);
        if (retval == SOCKET_ERROR) {
            err_display("send()");
            break;
        }

        // �����κ��� �޽��� ����
        retval = recv(sock, recvbuf, BUFSIZE, 0);
        if (retval == SOCKET_ERROR) {
            err_display("recv()");
            break;
        }
        else if (retval == 0) {
            printf("�������� ������ ���������ϴ�.\n");
            break;
        }

        // ������ �޽��� ���
        recvbuf[retval] = '\0';
        printf("����: %s", recvbuf);
    }

    // ���� �ݱ�
    closesocket(sock);

    // ���� ����
    WSACleanup();
    return 0;
}
