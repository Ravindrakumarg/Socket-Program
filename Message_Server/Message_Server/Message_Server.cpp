/*
 * Message_Server.cpp for handling client request
 */

#include "stdafx.h"
#include "Message_Server.h"
#include "WinSock.h"
#include "Windows.h"
#include "string.h"
#include "iostream"
#include "conio.h"

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN		512

/* Accepting Connection from Client */
int 
CMessageServer :: accept_connection ()
{
	SOCKADDR_IN __client_address;
	memset(&__client_address, 0, sizeof(__client_address));
	int client_len = sizeof(__client_address);
	int no_delay = 1, err;

	PRINTI "Waiting for Client....." << std::endl;
	/* Accepting the request from client side */
	__client_socket = accept(__server_socket, (SOCKADDR *) &__client_address, &client_len);
	if (__client_socket == INVALID_SOCKET)
	{
		PRINTE "Error is receiving connection from client"<< std::endl;
		shutdown_server();
		WSACleanup ();
		return 1;
	}

	struct sockaddr_in *inetaddr = (struct sockaddr_in *)&__client_address;
	PRINTI "Connection Accepted From Client:" << inet_ntoa(inetaddr->sin_addr) << std::endl;

	/* Set TCP_NODELAY for the socket */
	err = setsockopt(__server_socket, IPPROTO_TCP, TCP_NODELAY,(char *) &no_delay, sizeof(no_delay));
	if( err < 0 )
		PRINTW "Setsockopt(TCP_NODELAY) Failed for client socket" << std::endl;

	return 0;
}

/* Receiving data from client */
void
CMessageServer :: receive_data()
{
	char buf[DEFAULT_BUFLEN];
	memset (buf, ' ', sizeof(buf));
	HRESULT result = recv (__client_socket, buf, DEFAULT_BUFLEN, 0);
	if ( result < 0 )
	{
		PRINTE "Error occured while receiving:" << WSAGetLastError() << "\n";
		WSACleanup ();
		shutdown_server();
		EXIT_ON_ERROR;
	}
	PRINTI "CLIENT SAID:"<<buf<<"\n";

	if (!_stricmp (buf, "exit"))
	{
		PRINTI "Disconnecting Client and Exiting"<<std::endl;		
		_getch();
		closesocket(__client_socket);
		WSACleanup ();
		shutdown_server();
		EXIT_ON_ERROR;
	}
}

/* Sending data to client side */
void
CMessageServer :: send_data (void)
{
	char msg_buffer[DEFAULT_BUFLEN];
	memset(msg_buffer, ' ', sizeof(msg_buffer));
	
	PRINTI "SERVER:";
	std::cin.getline (msg_buffer, DEFAULT_BUFLEN);	

	HRESULT result = send (__client_socket, msg_buffer, DEFAULT_BUFLEN, 0);
	if ( result == SOCKET_ERROR)
	{
		PRINTE "Error Occured while sending data back to client"<<"\n";
		WSACleanup ();
		shutdown_server();
		EXIT_ON_ERROR;
	}
}

/* MAIN */
int _tmain(int argc, _TCHAR* argv[])
{
	CMessageServer server_hndlr;
	
	/*initailizing the server socket */
	if (server_hndlr.initialise_server())
	{ EXIT_ON_ERROR; }

	if (server_hndlr.accept_connection())
	{ EXIT_ON_ERROR; }

	while(1)
	{
		server_hndlr.receive_data();
		server_hndlr.send_data();
	}

	closesocket(server_hndlr.__client_socket);
	server_hndlr.shutdown_server();
	return 0;
}