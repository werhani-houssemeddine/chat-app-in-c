#include "test.h"

void print(const int color, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  
  // Specify color based on TEST_COLOR enum.
  color == SUCCESS ? printf(GREEN) : 
  color == WARNING ? printf(YELLOW): printf(RED);
   

  vprintf(fmt, args);
  printf(RESET "\n");
  va_end(args);
}

void success_message(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  print(SUCCESS, fmt, args);
  va_end(args);
}

void warning_message(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  print(WARNING, fmt, args);
  va_end(args);
}

void error_message(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  print(ERROR, fmt, args);
  va_end(args);
}