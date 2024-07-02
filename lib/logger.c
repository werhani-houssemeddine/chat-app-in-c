#include "logger.h"

void log_error(char* error) {

}

void log_info(char *message) {

}

// Using the same name for the struct and the variables does not cause an error
// because in C, they are located in two different memory areas.
const struct Logger Logger = { .error = log_error, .info = log_info };
