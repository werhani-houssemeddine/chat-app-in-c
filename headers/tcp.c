#include "tcp.h"
#include "./../lib/logger.h"

void initSocketForWindows() {
	#if defined(_WIN32)
		WSADATA d;
		assert(!WSAStartup(MAKE_WORD(2, 2) &d) && "Failed to initialze socket in windows. \n");
	#endif
}

void handle_error(int condition, char* error) {
	if(condition) {
		fprintf(stderr, "%s Error code: %d\n", error, GET_SOCKET_ERRNO() );
		exit(EXIT_FAILURE);
	}
}

struct addrinfo make_address_hints() {
	struct addrinfo hints;
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	return hints;
}

SOCKET make_socket(struct addrinfo *addr) {
	SOCKET sd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
  handle_error(!IS_VALID_SOCKET(sd), "fn: make_socket failed. \n");
	
	return sd;
}

void bind_socket(struct addrinfo *addr, SOCKET sd) {
	int b = bind(sd, addr->ai_addr, addr->ai_addrlen);
	handle_error(b, "fn: bind_socket failed. \n");
}

void listen_socket(char* PORT, void (*cb)(SOCKET sd)) {
	struct addrinfo hints = make_address_hints();
	struct addrinfo *bind_address = NULL;
	getaddrinfo(NULL, PORT, &hints, &bind_address);
	
	printf("Make socket ...\n");
	SOCKET sd = make_socket(bind_address);

	printf("Bind socket ...\n");
	bind_socket(bind_address, sd);

	printf("free memory from 'bind_address' variable.\n");
	freeaddrinfo(bind_address);

	printf("Listennig to socket...\n");
	handle_error((listen(sd, 10) < 0), "fn: listen failed. \n");

	printf("Handle incoming requests...\n");
	cb(sd);
}

const struct Server Server = { 
	.listen = listen_socket 
};
