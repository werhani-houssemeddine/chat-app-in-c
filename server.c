#include "headers/tcp.h"

void handle_incoming_requests(SOCKET sd) {
	printf("socket descriptor: %d\n", sd);
}

int main() {
	const struct Server app = Server;

	app.listen("3000", handle_incoming_requests);
	
	return 0;
}
