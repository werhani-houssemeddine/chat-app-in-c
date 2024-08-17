#include "../headers/error.h"

void handle_error(int condition, char* error) {
	if(condition) {
		fprintf(stderr, "%sError code: %d\n", error, GET_SOCKET_ERRNO() );
		exit(EXIT_FAILURE);
	}
}

void handle_memory_allocation(void *ptr) {
	if(ptr == NULL) {
		printf("Error: failed allocation memory.\n");
		exit(EXIT_FAILURE);
	}
}