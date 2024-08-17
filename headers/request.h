#ifndef REQUEST_H
  #define REQUEST_H 1

  #include <string.h>
  #include <stdio.h>
  #include <stdlib.h>

  struct R_Options {
    const char *method;
    const char *endpoint;
    const char *body;
    // char[][] headers;
    // char[][] queries;
    // char[][] params;

    struct R_Options *self;
    char* (*toString)(const struct R_Options *options);
  };

  struct Request {
    void (*recv) (const int sd, const void (*cb)(void *buffer));
    void (*send) (const int sd, char *buffer);
    void (*fetch) (const int sd, const struct R_Options, const void (*cb)(void *buffer));
  };

  struct R_Options make_request_options(const char *method, const char *endpoint, const char *body);

  extern const struct Request Request;

#endif
