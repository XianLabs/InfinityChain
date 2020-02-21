#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "NodeConnector.h"
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

NodeConnector::NodeConnector(string hostAddr, unsigned short nPort)
{
	int Result = ConnectToPeer(hostAddr, nPort);
	int SendDataResult = SendPeerData(this->Socket, "Hello!");

}

int NodeConnector::ConnectToPeer(string HostName, unsigned short nPort)
{
	WSADATA wsaData;
	struct addrinfo *result = NULL, *ptr = NULL, hints;
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) 
	{
		printf("WSAStartup failed with error: %d\n", iResult);
		return WSAGetLastError();
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(HostName.c_str(), "7777", &hints, &result);
	if (iResult != 0) 
	{
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return WSAGetLastError();
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) 
	{

		// Create a SOCKET for connecting to server
		this->Socket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (this->Socket == INVALID_SOCKET)
		{
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return WSAGetLastError();
		}

		// Connect to server.
		iResult = connect(this->Socket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) 
		{
			closesocket(this->Socket);
			this->Socket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (this->Socket == INVALID_SOCKET)
	{
		printf("Unable to connect to server!\n");
		WSACleanup();
		return WSAGetLastError();
	}

	return 0;
}

int NodeConnector::SendPeerData(SOCKET PeerSocket, string data)
{
	// Send an initial buffer
	

	int iResult = send(PeerSocket, data.c_str(), data.length(), 0);
	if (iResult == SOCKET_ERROR)
	{
		printf("send failed with error: %d\n", WSAGetLastError());
		return WSAGetLastError();
	}

	printf("Bytes Sent: %ld\n", iResult);


	return 0;
}

int NodeConnector::RecvPeerData(SOCKET PeerSocket)
{
	int iResult = 0;
	char RecvBuf[1024];
	// Receive until the peer closes the connection
	do {

		iResult = recv(PeerSocket, RecvBuf, 1024, 0);
		if (iResult > 0)
			printf("Bytes received: %d\n", iResult);
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed with error: %d\n", WSAGetLastError());

		printf("%s\n", RecvBuf);

		if (strstr(RecvBuf, "IFXStartWork:2") != NULL)
		{
			printf("Starting mining block 2...\n");
			Blockchain bChain = Blockchain();
			bChain.AddBlock(Block(2, "SENSITIVE INFO!"));
		}


	} while (iResult > 0);


}

bool NodeConnector::ClosePeerConnection(SOCKET PeerSocket)
{
	//todo: send msg to peer that we are closing before actually closing

	if (!closesocket(PeerSocket))
	{
		printf("Failed to close socket: %d\n", PeerSocket);
		return false;
	}
		
	PeerSocket = INVALID_SOCKET;
	return true;
}

bool NodeConnector::LeaveNetwork()
{


	return true;
}
