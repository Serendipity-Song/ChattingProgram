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
		������ IP�ּҿ� PORT��ȣ�� �����մϴ�.
	*/
	const char* serverIpAddr = "127.0.0.1";
	enum ePort { PORT = 54000 };

	/*
		1. WinSock�� �ʱ�ȭ�մϴ�.
		: WSAStartup() �Լ� ���
	*/
	WSADATA wsData;
	int wsResult = WSAStartup(MAKEWORD(2, 2), &wsData);
	if (wsResult != 0)
	{
		std::cerr << "Can't start Winsock, Err #" << wsResult << std::endl;
		return -1;
	}

	/*
		2. ������ �����մϴ�.
		: socket() �Լ� ���
	*/
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		std::cerr << "Can't create socket, Err #" << WSAGetLastError() << std::endl;
		WSACleanup();
		return -1;
	}

	/*
		3. sockaddr_in ����ü ���� ����

		- inet_pton(): char* Ÿ���� IP �ּҸ� ����Ʈ Ÿ������ ��ȯ�Ͽ� 3��° ���ڿ� �����մϴ�.
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
		4. ������ ����(server�� bind�� ����� ����)
		: connect() �Լ� ���, ���Ͽ� IP�ּҿ� PORT��ȣ�� ���� ������ �߰��մϴ�.
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
		������ ���� �� Do somthing
	*/

	enum eBufSize { BUF_SIZE = 4096 };
	char buf[BUF_SIZE];
	std::string userMsg;

	// ������ �޼��� �Է��� �ݺ��Ͽ� ó��
	do
	{
		std::cout << "> ";
		std::getline(std::cin, userMsg);

		if (userMsg.size() > 0)
		{
			// �Է��� �޼����� ������ �����մϴ�.
			int sendResult = send(sock, userMsg.c_str(), userMsg.size() + 1, 0);
			if (sendResult != SOCKET_ERROR)
			{
				// �����κ��� ���۵� �޼����� receive �մϴ�. (recv())
				ZeroMemory(buf, BUF_SIZE);
				int bytesReceived = recv(sock, buf, BUF_SIZE, 0);
				if (bytesReceived > 0)
				{
					// �����κ��� ���� �޼����� ����մϴ�.
					std::cout << "SERVER> " << buf << std::endl;
				}
			}
		}

	} while (userMsg.size() > 0);

	// ������ �ݰ� �����մϴ�.
	closesocket(sock);
	WSACleanup();

	return 0;
}