#ifndef INIT_LOGGER_H
#define INIT_LOGGER_H 1

  struct Logger {
    void (*error)(char *error);
    void (*info)(char *message);
  };

  extern const struct Logger Logger;
  
#endif
