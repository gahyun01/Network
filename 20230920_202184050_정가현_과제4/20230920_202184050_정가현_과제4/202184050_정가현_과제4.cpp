#include "common.h"

int main(int argc, char* argv[]) {
	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	/* -----------------
		IPv4 ��ȯ ����
	   -----------------
	*/

	// ������ IPv4 �ּ� ���A
	const char* ipv4test = "147.46.144.70";
	printf("IPv4 �ּ�(��ȯ ��) = %s\n", ipv4test);

	// WSAStringToAddress() �Լ� ����
	SOCKADDR_IN ipv4num;
	int addrlen4 = sizeof(ipv4num);
	WSAStringToAddressA((LPSTR)ipv4test, AF_INET, NULL, (SOCKADDR*)&ipv4num, &addrlen4);
	printf("IPv4 �ּ�(��ȯ ��) = %#x\n", ipv4num.sin_addr.s_addr);

	// inet_ntop() �Լ� ����
	char ipv4str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &ipv4num.sin_addr, ipv4str, sizeof(ipv4str));
	printf("IPv4 �ּ�(�ٽ� ��ȯ ��) = %s\n", ipv4str);
	printf("\n");


	/* -----------------
		IPv6 ��ȯ ����
	   -----------------
	*/

	// ������ IPv6 �ּ� ���
	const char* ipv6test = "2001:0230:abcd:ffab:0023:eb00:ffff:1111";
	printf("IPv6 �ּ�(��ȯ ��) = %s\n", ipv6test);

	// WSAStringToAddress() �Լ� ����
	SOCKADDR_IN6 ipv6num;
	int addrlen6 = sizeof(ipv6num);
	// printf("%d\n", addrlen6);
	WSAStringToAddressA((LPSTR)ipv6test, AF_INET6, NULL, (SOCKADDR*)&ipv6num, &addrlen6);
	printf("IPv6 �ּ�(��ȯ ��) = 0x");
	for (int i = 0; i < 16; i++)
		printf("%02x", ipv6num.sin6_addr.u.Byte[i]);
	printf("\n");

	// inet_ntop() �Լ� ����
	char ipv6str[INET6_ADDRSTRLEN];
	inet_ntop(AF_INET6, &ipv6num.sin6_addr, ipv6str, sizeof(ipv6str));
	printf("IPv6 �ּ�(�ٽ� ��ȯ ��) = %s\n", ipv6str);

	// ���� ����
	WSACleanup();
	return 0;
}