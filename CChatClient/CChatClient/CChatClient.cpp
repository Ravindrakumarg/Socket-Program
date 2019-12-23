
/*
 * CChatClient.cpp to communicate with server
 */

#include "stdafx.h"
#include "iostream"
#include "CChatClient.h"
#include "WinSock.h"
#include "Windows.h"
#include "WinBase.h"
#include "string.h"
#include <conio.h>
#include <process.h>

extern "C"
{
#include "stdio.h"
}

#define MAX_BUF_LEN			512

/* Connecting to the Message Server */
int
CChatClient :: connectServer(void)
{
	HRESULT result;

	result = connect (__client_socket, (sockaddr*)&__client_address, sizeof(SOCKADDR_IN));
	if (__client_socket == INVALID_SOCKET)
	{
		PRINTE "Connection to the server failed failed:" << WSAGetLastError() <<"\n";
		WSACleanup();
		return 1;
	}

	PRINTI "Connection Stablished To Server" << "\n\n";
	return 0;
}

/* Sending Message to the message server */
void
CChatClient :: sendMessage (void)
{
	char msg_buffer[MAX_BUF_LEN];
	HRESULT result;
	PRINTI "CLIENT:";
	memset (msg_buffer, ' ', MAX_BUF_LEN);
	std::cin.getline(msg_buffer, MAX_BUF_LEN);

	result = send (__client_socket, msg_buffer, MAX_BUF_LEN, 0);
	if (result == SOCKET_ERROR)
	{
		PRINTE "Sending message has been failed:d"<<WSAGetLastError();
		WSACleanup();
		ShutdownClient();
		EXIT_ON_ERROR;
	}
}

/* Receiving Message from Message server */
int
CChatClient :: receiveMessage ()
{
	char msg_buffer[MAX_BUF_LEN];
	int receivebytes;
	memset(msg_buffer, ' ', sizeof(msg_buffer));
	receivebytes = recv (__client_socket, msg_buffer, MAX_BUF_LEN, 0);
	if (receivebytes > 0)
	{		
		PRINTI "SERVER SAID:"<<msg_buffer<<"\n";
		if (!_stricmp(msg_buffer, "exit"))
		{
			PRINTI "Server Exiting!!"<<std::endl;
			_getch();
			WSACleanup();
			ShutdownClient();
			EXIT_ON_ERROR;
		}
	}
	return receivebytes;
}

/* Doing sending or receving the message */
void 
CChatClient :: chatWithServer (void)
{
	int hThread, receivebytes;
	int send = 1, recv = 2;
	do
	{
		hThread = _beginthread(&CChatClient::run_thread, 0, (void *)send);	/* Sending message to server */
		
		//sendMessage();
		//receivebytes = receiveMessage();				/* Receiving Message from server */

		if (receivebytes <= 0)
		{
			PRINTE "Error on receving server message" << "\n";
		}
	}while (receivebytes > 0);

}

void
CChatClient :: run(int args)
{

}

	/** MAIN **/
int _tmain(int argc, _TCHAR* argv[])
{
	CChatClient chat_client;
	if (chat_client.initializeClient())
	{
		EXIT_ON_ERROR;
	}

	do /*Retrying for connection*/
	{
		if (chat_client.connectServer())
		{
			PRINTI "Tring Again After 1 Second" << "\n";
			Sleep(1000);
			continue;
		}
	} while(false);

//	chat_client.chatWithServer();

	return 0;
}