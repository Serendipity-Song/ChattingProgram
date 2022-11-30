/*
	Client
*/

#include <iostream>
#include <string>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

int main()
{
	/*
		서버의 IP주소와 PORT번호를 저장합니다.
	*/
	const char* serverIpAddr = "127.0.0.1";
	enum ePort { PORT = 54000 };

	/*
		1. WinSock을 초기화합니다.
		: WSAStartup() 함수 사용
	*/
	WSADATA wsData;
	int wsResult = WSAStartup(MAKEWORD(2, 2), &wsData);
	if (wsResult != 0)
	{
		std::cerr << "Can't start Winsock, Err #" << wsResult << std::endl;
		return -1;
	}

	/*
		2. 소켓을 생성합니다.
		: socket() 함수 사용
	*/
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		std::cerr << "Can't create socket, Err #" << WSAGetLastError() << std::endl;
		WSACleanup();
		return -1;
	}

	/*
		3. sockaddr_in 구조체 변수 생성

		- inet_pton(): char* 타입의 IP 주소를 바이트 타입으로 변환하여 3번째 인자에 저장합니다.
	*/
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(PORT);
	int convResult = inet_pton(AF_INET, serverIpAddr, &hint.sin_addr);
	if (convResult != 1)
	{
		std::cerr << "Can't convert IP address, Err #" << convResult << std::endl;
		WSACleanup();
		return -1;
	}

	/*
		4. 서버에 연결(server의 bind와 비슷한 개념)
		: connect() 함수 사용, 소켓에 IP주소와 PORT번호와 같은 정보를 추가합니다.
	*/
	int connResult = connect(sock, reinterpret_cast<sockaddr*>(&hint), sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		std::cerr << "Can't connect to server, Err #" << WSAGetLastError() << std::endl;
		closesocket(sock);
		WSACleanup();
		return -1;
	}

	/*
		서버에 연결 후 Do somthing
	*/

	enum eBufSize { BUF_SIZE = 4096 };
	char buf[BUF_SIZE];
	std::string userMsg;

	// 유저의 메세지 입력을 반복하여 처리
	do
	{
		std::cout << "> ";
		std::getline(std::cin, userMsg);

		if (userMsg.size() > 0)
		{
			// 입력한 메세지를 서버에 전송합니다.
			int sendResult = send(sock, userMsg.c_str(), userMsg.size() + 1, 0);
			if (sendResult != SOCKET_ERROR)
			{
				// 서버로부터 전송된 메세지를 receive 합니다. (recv())
				ZeroMemory(buf, BUF_SIZE);
				int bytesReceived = recv(sock, buf, BUF_SIZE, 0);
				if (bytesReceived > 0)
				{
					// 서버로부터 받은 메세지를 출력합니다.
					std::cout << "SERVER> " << buf << std::endl;
				}
			}
		}

	} while (userMsg.size() > 0);

	// 소켓을 닫고 종료합니다.
	closesocket(sock);
	WSACleanup();

	return 0;
}