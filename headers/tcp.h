#ifndef INIT_TCP_H
	#define INIT_TCP_H 1

	// Define headers
	#if defined(_WIN32)
		//
		#ifndef _WIN32_WINNT
			#define _WIN32_WINNT 0X0600
		#endif

		#include <winsock2.h>
		#include <ws2tcpip.h>
	#else
		#include <sys/types.h>
		#include <sys/socket.h>
		#include <netinet/in.h>
		#include <arpa/inet.h>
		#include <netdb.h>
		#include <unistd.h>
		#include <errno.h>
	#endif

	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <assert.h>

	// Define macros
	#if defined(_WIN32)
		#define IS_VALID_SOCKET(s) ((s) != INVALID_SOCKET)
		#define CLOSE_SOCKET(s) closesocket(s)
		#define GET_SOCKET_ERRNO() (WSAGetLastError())
	#else
		#define IS_VALID_SOCKET(s) ((s) >= 0)
		#define CLOSE_SOCKET(s) close(s)
		#define GET_SOCKET_ERRNO() (errno)
		#define SOCKET int
	#endif

	// Define functions
	void initSocketForWindows();

	// Define data structures
	struct Server {
		void (*listen)(char *host, char *PORT, void (*cb)(SOCKET sd));
	};

	extern const struct Server Server;

#endif
