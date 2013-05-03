#pragma comment (lib, "ws2_32.lib")

#include <iostream>
#include <WinSock2.h>

int main()
{
	SOCKET s;
	struct sockaddr_in sa;
	WSADATA wsas;
	int result;
	WORD wersja;

	wersja = MAKEWORD(2,0);
	result = WSAStartup(wersja, &wsas);
	s = socket(AF_INET, SOCK_STREAM, 0);
	memset((void*)(&sa), 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(9999);
	sa.sin_addr.s_addr = inet_addr("127.0.0.1");

	char buf[80] = {0};

	if(connect(s, (struct sockaddr FAR *)&sa, sizeof(sa)) != 0)
	{
		std::cout << "blad polaczenia" << std::endl;
	}
	else
	{
		if(recv(s, buf, 80, 0) > 0)
		{
			std::cout << buf << std::endl;
		}
	}

	system("pause");

	return 0;
}