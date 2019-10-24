
/*
 * Socket Client Program
 */
#ifndef __CHAT_CLIENT__
#define __CHAR_CLIENT__

#ifdef WIN32
#include "iostream"
#include "WinSock.h"
#include "Windows.h"

#define PRINTE std::cout<<
#define PRINTD std::cout<<
#define PRINTI std::cout<<
#endif

#include "ThreadRunnable.h"

#define EXIT_ON_ERROR exit(1);

class CChatClient : public CThreadRunnable
{
private:
	SOCKADDR_IN __client_address;
	SOCKET		__client_socket;
	WSADATA		__ws_adata;

public:
	CChatClient()
	{
		__client_socket = INVALID_SOCKET;
	}
	~CChatClient()
	{}

public:
	int		initializeClient(void);
	int		connectServer(void);
	void 	sendMessage(void );
	int		receiveMessage(void);
	void	ShutdownClient(void);
	void	chatWithServer(void);

	/*static void static_fun_2( void * args )
    {
      static_cast<CChatClient*>(args)->sendMessage();
    }*/
protected:
	void run(int args);
};

#endif //__CHAT_CLIENT__