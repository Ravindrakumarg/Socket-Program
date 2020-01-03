
/*
 * A Chatting Message Server
 * It will handle request from client
 */
#ifndef __MESSAGE_SERVER__
#define __MESSAGE_SERVER__

#include "iostream"
#include "WinSock.h"
#include "Windows.h"

#define PRINTE std::cout<<
#define PRINTW std::cout<<
#define PRINTI std::cout<<
#define PRINTD std::cout<<

#define EXIT_ON_ERROR exit(0);

class CMessageServer
{
public:
	CMessageServer()
	{
		memset(&__server_address, ' ', sizeof(__server_address));

		__server_socket = INVALID_SOCKET;
		__client_socket = INVALID_SOCKET;
	}

	~CMessageServer()
	{}

public:
	int initialise_server();
	int accept_connection();
	void receive_data();
	void send_data();
	void shutdown_server();

public:
	SOCKET		__client_socket;

private:
	SOCKADDR_IN	__server_address;		// Variable to Hold Server Address
	SOCKET		__server_socket;		// Server socket
	WSADATA		__ws_adata;

};
#endif //__MESSAGE_SERVER__