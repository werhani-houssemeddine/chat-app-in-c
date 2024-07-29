#include "headers/tcp.h"

struct Server app;

void handle_incoming_data(void *buffer) {
	printf("Incoming data: %s\n", (char *)buffer);
}

void handle_incoming_requests(SOCKET sd) {
	printf("socket descriptor: %d\n", sd);
	app.recv(sd, handle_incoming_data);
}

int main() {
	app = Server;
	
	app.listen("127.0.0.1", "3000", handle_incoming_requests);
	
	return 0;
}
