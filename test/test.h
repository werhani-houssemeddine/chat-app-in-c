#include <stdio.h>
#include <stdarg.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

enum TEST_COLOR { SUCCESS, WARNING, ERROR };

void success_message(const char *fmt, ...);
void warning_message(const char *fmt, ...);
void error_message(const char *fmt, ...);
