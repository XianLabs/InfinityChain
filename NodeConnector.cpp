#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "NodeConnector.h"
#pragma comment(lib, "ws2_32")

NodeConnector::NodeConnector(string hostAddr, unsigned short nPort)
{
	char buffer[256] = { 0 };
	this->Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->Socket < 0)
	{
		printf("ERROR opening socket: %d\n", WSAGetLastError());
		return;
	}

	this->server = gethostbyname(hostAddr.c_str());

	if (this->server == NULL) 
	{
		fprintf(stderr, "ERROR, no such host\n");
		closesocket(this->Socket);
		return;
	}

	ZeroMemory((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	memcpy((char *)server->h_addr,
		(char *)&serv_addr.sin_addr.s_addr,
		server->h_length);

	serv_addr.sin_port = htons(nPort);
	
	if (connect(this->Socket, (struct sockaddr *) &this->serv_addr, sizeof(this->serv_addr)) < 0)
	{
		printf("ERROR connecting: %d\n", WSAGetLastError());
		closesocket(this->Socket);
		return;
	}

	printf("Please enter the message: ");

	fgets(buffer, 255, stdin);
	
	int bytesSent = send(this->Socket, buffer, strlen(buffer), 0);
	if (bytesSent <= 0)
	{
		printf("Error sending message.\n");
		closesocket(this->Socket);
		return;
	}

	char RecvBuffer[1024] = { 0 };

	int bytesRecieved = recv(this->Socket, RecvBuffer, 1024, 0);
	if (bytesRecieved <= 0)
	{
		printf("Error recieving message.\n");
		closesocket(this->Socket);
		return;
	}

	printf("Message: %s\n", RecvBuffer);
}