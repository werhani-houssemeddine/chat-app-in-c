#include "../headers/request.h"
#include "../headers/tcp.h"
#include "../headers/error.h"

char *request_options_to_string(const struct R_Options *options) {
  char *buffer = malloc(sizeof(char) * 10000);
  sprintf(
		buffer, 
		"{\n\t"
		"method: %s,\n\t"
		"endpoint: %s,\n\t"
		"body: %s,\n"
		"}\n",
		options->method, options->endpoint, options->body
	);
  return buffer;
}

void recv_data(const int sd, const void (*cb)(void *buffer)) {
	char buffer[10000];
	
	int d = recv(sd, (void *)buffer, 10000, 0);
	handle_error(d == -1, "fn: receive data failed.\n");

	cb((void *)buffer);
}

void send_data(const int sd, char *buffer) {
	// Calculate the length of the buffer and add 1 for null terminator '\0'.
	int length = (strlen(buffer) * sizeof(char)) + 1;
	int s = send(sd, buffer, length, 0);

	handle_error(s == -1, "fn: send data failed.\n");
}

void fetch_data(const int sd, const struct R_Options options, const void (*cb)(void *buffer)) {
	send_data(sd, options.toString(options.self));
	recv_data(sd, cb);
}

struct R_Options make_request_options(const char *method, const char *endpoint, const char* body) {
  int is_method_valid = 
      !strcmp(method, "GET")    ||
      !strcmp(method, "POST")   ||
      !strcmp(method, "DELETE") ||
      !strcmp(method, "PUT");
  
  handle_error(is_method_valid == 0, "fn: request method invalid.\n");

  struct R_Options *options = malloc(sizeof(struct R_Options));
  
  if(options == NULL) {}

  options->endpoint = endpoint;
  options->method   = method;
  options->body     = body;
  options->self     = options;
  options->toString = request_options_to_string;

  return *options;
}

const struct Request Request = {
  .recv  = recv_data,
  .send  = send_data,
  .fetch = fetch_data,
};
