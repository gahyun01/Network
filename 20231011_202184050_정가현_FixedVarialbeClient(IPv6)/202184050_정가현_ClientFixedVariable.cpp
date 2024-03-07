#include "common.h"

char* SERVERIP = (char*)"::1";  // IPv6 loopback �ּ�
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
    char buf[BUFSIZE];
    const char* testdata[] = {
        "�ȳ��ϼ���",
        "�ݰ�����",
        "���õ��� �� �̾߱Ⱑ ���� �� ���׿�",
        "���� �׷��׿�"
    };
    int len;

    // ������ ������ ���
    for (int i = 0; i < 4; i++) {
        // ������ �Է�(�ùķ��̼�)
        len = (int)strlen(testdata[i]);
        strncpy_s(buf, testdata[i], len);

        // ������ ������(���� ����)
        retval = send(sock, (char*)&len, sizeof(int), 0);
        if (retval == SOCKET_ERROR) {
            err_display("send()");
            break;
        }

        // ������ ������(���� ����)
        retval = send(sock, buf, len, 0);
        if (retval == SOCKET_ERROR) {
            err_display("send()");
            break;
        }

        printf("[ TCP Ŭ���̾�Ʈ ] %d+%d����Ʈ�� ���½��ϴ�.\n", (int)sizeof(int), retval);
    }

    // ���� �ݱ�
    closesocket(sock);

    // ���� ����
    WSACleanup();
    return 0;
}
