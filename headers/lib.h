#if defined(_WIN32)
  #include <conio.h>
  #define clear_console() (clrscr())
#else
  /* \033[H\033[J => this is a unicode for unix based system to clear the console */
  #define clear_console() (printf("\033[H\033[J"))
#endif
