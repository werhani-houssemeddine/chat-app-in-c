#ifndef SCREEN_H 
  #define SCRREN_H 1

  #if defined(_WIN32)
    #include <conio.h>
    #include <windows.h>

    #define clear_console() (clrscr())
  #else

    #include <termios.h>
    #include <unistd.h>

    /* \033[H\033[J => this is a unicode for unix based system to clear the console */
    #define clear_console() (printf("\033[H\033[J"))
  #endif

  #include <stdio.h>

  struct Echo {
    void (*enable) ();
    void (*disable) ();
  };

  extern const struct Echo Echo;

#endif
