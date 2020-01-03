
/*
 * CChat.cpp for initializing the client
 */

#include "stdafx.h"
#include "iostream"
#include "CChatClient.h"
#include "WinSock.h"
#include "Windows.h"
#include "WinBase.h"
#include "string.h"


#define SERVER_PORT		5678			/* Port on which server is listening */
#define SERVER_IP			"127.0.0.1"		/* server address as server is running on same machine */

/* Initializing the client socket for communicating with server*/
int
CChatClient :: initializeClient(void)
{
	if (WSAStartup(0x0202,&__ws_adata)!=0)
	{
		PRINTE "winsock initialization failed"<<"\n\n"<<std::endl;
		WSACleanup ();
		return 1;
	}

	__client_address.sin_family = AF_INET;						/* internet Communication */
	__client_address.sin_addr.s_addr = inet_addr(SERVER_IP);	/* Server address*/
	__client_address.sin_port = SERVER_PORT;					/* Server Listening on this port */

	/* Creating client socket */
	__client_socket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (__client_socket == INVALID_SOCKET)
	{
		PRINTE "Socket Creation failed:" << WSAGetLastError() <<"\n";
		WSACleanup();
		return 1;
	}
	
	PRINTI "Client Socket Created Successfully"<<"\n";
	return 0;
}

/* Close Client*/
void
CChatClient :: ShutdownClient()
{
	closesocket(__client_socket);
}