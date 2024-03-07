#include "common.h"

char* SERVERIP = (char*)"127.0.0.1";
#define SERVERPORT 9000
#define BUFSIZE 512

int main(int argc, char* argv[]) {
    int retval;

    // 명령행 인수가 있으면 IP 주소로 사용
    if (argc > 1) SERVERIP = argv[1];

    // 윈속 초기화
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return 1;

    // 소켓 생성
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) err_quit("socket()");

    //connect()
    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);
    serveraddr.sin_port = htons(SERVERPORT);
    retval = connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if (retval == SOCKET_ERROR) err_quit("connect()");

    //데이터 통신에 사용할 변수
    char buf[BUFSIZE + 1];
    int len;

    //서버와 데이터 통신
    while (1) {
        // 데이터 입력
        printf("\n[보낼 데이터] ");
        if (fgets(buf, BUFSIZE + 1, stdin) == NULL) // 만약 버퍼가 각각 값이 없을 때..? 엔터 키.파일 겟 스트링=fgets, 엔터키 누르면 무한반복 종료
            break;

        //'\n'문자 제거
        len = (int)strlen(buf); //len 함수 사용. send함수의 리턴 값은 len와 같음, 왜냐면 블롵킹 소켓을 사용하기 때문.
        if (buf[len - 1] == '\n')
            buf[len - 1] = '\0';
        if (strlen(buf) == 0)
            break;


        //데이터 보내기
        retval = send(sock, buf, (int)strlen(buf), 0);
        if (retval == SOCKET_ERROR) {
            err_display("send()");
            break;
        }
        printf("[TCP 클라이언트] %d바이트를 보냈습니다.\n", retval);
        
        // 데이터 받기
        retval = recv(sock, buf, retval, MSG_WAITALL); //클라이언트 소켓에 관련된 리시브
        if (retval == SOCKET_ERROR) {
            err_display("recv()");
            break;
        }
        else if (retval == 0)
            break;

        // 받은 데이터 출력
        //flags - mag피크 옵션: 데이터가 계속 남는 옵션, msgwaitall은 파라미터 값..?, 일단 flags = 0으로 설정할 거임.
        buf[retval] = '\0';
        printf("[TCP 클라이언트] %d바이트를 받았습니다.\n", retval);
        printf("[받은 데이터] %s\n", buf);
    }

    //소켓 닫기
    closesocket(sock);

    // 윈속 종료
    WSACleanup();
    return 0;
}