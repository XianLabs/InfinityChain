#ifndef NODECONNECTOR_H
#define NODECONNECTOR_H
#include <WinSock2.h>
#include <string>

using namespace std;

class NodeConnector
{
	SOCKET Socket;
	unsigned short nPort;
	
	struct sockaddr_in serv_addr;
	struct hostent *server;


public:
	NodeConnector(string hostAddr, unsigned short nPort);


};

#endif 