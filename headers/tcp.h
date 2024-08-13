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
		#include <sys/select.h>
		#include <netinet/in.h>
		#include <arpa/inet.h>
		#include <netdb.h>
		#include <unistd.h>
	#endif

	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <assert.h>

	// Define macros
	#if defined(_WIN32)
		#define IS_VALID_SOCKET(s) ((s) != INVALID_SOCKET)
		#define CLOSE_SOCKET(s) closesocket(s)
	#else
		#define IS_VALID_SOCKET(s) ((s) >= 0)
		#define CLOSE_SOCKET(s) close(s)
		#define SOCKET int
	#endif

	// Define functions
	void initSocketForWindows();

	// Define data structures
	struct Server {
		void (*listen)(const char *host, const char *PORT, void (*cb)(SOCKET sd));
		void (*connect)(const char *host, const char *port, void (*cb)(SOCKET sd));
	};

	extern const struct Server Server;

#endif
