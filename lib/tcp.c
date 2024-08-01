#include "../headers/tcp.h"
#include "../headers/logger.h"

void initSocketForWindows() {
	#if defined(_WIN32)
		WSADATA d;
		assert(!WSAStartup(MAKE_WORD(2, 2) &d) && "Failed to initialze socket in windows. \n");
	#endif
}

void clean_socket(SOCKET socket) {
	//? Close socket
	CLOSE_SOCKET(socket);
	
	//? Clean up winsock for windows OP
	#if defined(_WIN32)
		WSACleanup();
	#endif
}

void handle_error(int condition, char* error) {
	if(condition) {
		fprintf(stderr, "%sError code: %d\n", error, GET_SOCKET_ERRNO() );
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

SOCKET accept_socket(SOCKET sd) {
	struct sockaddr_storage client_address;
	socklen_t socket_client_len = sizeof(client_address);

	SOCKET s = accept(sd, (struct sockaddr*) &client_address, &socket_client_len);
	handle_error(!IS_VALID_SOCKET(s), "fn: accept_socket failed .\n");

	return s;
}

void listen_socket(const char* host, const char* PORT, void (*cb)(SOCKET sd)) {
	initSocketForWindows();

	struct addrinfo hints = make_address_hints();
	struct addrinfo *bind_address = NULL;
	 
	//? Use "localhost" (127.0.0.1) as the default host (IP) if
	//? the provided host (function parameter) is NULL.
	if(host == NULL) {
		getaddrinfo("127.0.1.1", PORT, &hints, &bind_address);
	} else {
		getaddrinfo(host, PORT, &hints, &bind_address);
	}
	
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

	printf("Close socket and clean up...\n");
	clean_socket(sd);
}

struct addrinfo make_hints_remote_addr() {
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_socktype = SOCK_STREAM;

	return hints;
}

void get_remote_address(struct addrinfo *peer_address) {
	char address_buffer[1000];
	char service_buffer[1000];

	getnameinfo(
		peer_address->ai_addr,
		peer_address->ai_addrlen,
		address_buffer,
		sizeof(address_buffer),
		service_buffer,
		sizeof(service_buffer),
		NI_NUMERICHOST
	);

	printf("%s %s.\n", address_buffer, service_buffer);
}

void connection(SOCKET sd, struct addrinfo *peer_address) {
	int c = connect(sd, peer_address->ai_addr, peer_address->ai_addrlen);
	handle_error(c, "fn: connection failed.\n");
}

void connect_socket(const char *host, const char *port, void (*cb)(SOCKET sd)) {
	initSocketForWindows();

	struct addrinfo hints = make_hints_remote_addr();
	struct addrinfo *peer_address;


	printf("Config remote address ...\n");
	getaddrinfo(host, port, &hints, &peer_address);

	printf("Get remote address ...\n");
	get_remote_address(peer_address);

	printf("Make socket ...\n");
	SOCKET sd = make_socket(peer_address);

	printf("Connecting ...\n");
	connection(sd, peer_address);

	printf("free memory from 'peer_address' variable.\n");
	freeaddrinfo(peer_address);

	cb(sd);

}

const struct Server Server = { 
	.listen  = listen_socket,
	.connect = connect_socket
};
