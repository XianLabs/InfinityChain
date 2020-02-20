#ifndef NODESERVER_H
#define NODESERVER_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>


using namespace std;

class NodeServer
{
	unsigned short nPort;
	SOCKET Socket, NewSocket;
	struct sockaddr_in serv_addr, cli_addr;

private:
	


public:
	NodeServer(unsigned short nPort);
	BOOL Listen();
};


#endif
