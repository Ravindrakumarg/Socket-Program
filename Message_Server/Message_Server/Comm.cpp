
/*
 * Comm.cpp for initializing socket
 */
#include "stdafx.h"
#include "Message_Server.h"
#include "WinSock.h"
#include "Windows.h"
#include "string.h"
#include "iostream"

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT		5678			/* Message server listening port*

/* Intializing the server socket*/
int
CMessageServer :: initialise_server ()
{
	HRESULT result;

	// initialization of winsock
	if (WSAStartup(0x0202, &__ws_adata) != 0)
	{
		PRINTE "winsock initialization failed"<<"\n"<<std::endl;
		WSACleanup ();
		return 1;
	}

	/* Creating server socket*/
	__server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (__server_socket == INVALID_SOCKET)
	{
		PRINTE "Error at Socket Initialazation:" << WSAGetLastError() << "\n";
		WSACleanup();
		return 1;
	}

	__server_address.sin_family		 = AF_INET;			/* Internet address */
	__server_address.sin_addr.s_addr = INADDR_ANY;		/* Listening to any clint address */
	__server_address.sin_port		 = DEFAULT_PORT;	/* Listening to this port */

	/* Binding server socket with __server_address */
	result = bind (__server_socket, (SOCKADDR *) &__server_address, sizeof(SOCKADDR_IN));
	if( result == SOCKET_ERROR )
	{
		PRINTE "Error on binding the socket:"<<WSAGetLastError()<<"\n";
		shutdown_server();
		WSACleanup ();
		return 1;
	}

	/* set the socket for listening */
	result = listen (__server_socket, SOMAXCONN);
	if ( result == SOCKET_ERROR )
	{
		PRINTE "Error on listening the socket:"<<WSAGetLastError()<<"\n";
		shutdown_server();
		WSACleanup ();
		return 1;
	}

	PRINTI "Server Socket Initialized"<<"\n\n";
	return 0;
}

/* Closing the socket */
void
CMessageServer :: shutdown_server(void)
{
	closesocket(__server_socket);
}