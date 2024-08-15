#ifndef CUSTOM_ERROR_H
  #define CUSTOM_ERROR_H 1
  
  #if defined(_WIN32)
    #ifndef _WIN32_WINNT
			#define _WIN32_WINNT 0x0600
		#endif

    #include <winsock2.h>
    #include <windows.h>

    #define GET_SOCKET_ERRNO() (WSAGetLastError())
    #define GET_ERRNO() (GetLastError())

  #else
		#include <errno.h>

		#define GET_SOCKET_ERRNO() (errno)
    #define GET_ERRNO() (errno)
  
  #endif

  #include <stdio.h>
  #include <string.h>
  #include <stdlib.h>

  void handle_error(int condition, char* error);

#endif
