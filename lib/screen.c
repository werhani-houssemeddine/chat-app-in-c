#include "../headers/screen.h"

#if defined (_WIN32)
  void handle_screen_windows(int mode) {
    HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD console_mode;
    GetConsoleMode(hstdin, &console_mode);

    mode == 0 ? (console_mode &= ~ENABLE_ECHO_INPUT) : (console_mode |= ENABLE_ECHO_INPUT);
    
    SetConsoleMode(hstdin, console_mode);
  }

  void disable_echo() {
    handle_screen_windows(0);
  }
  
  void enable_echo() {
    handle_screen_windows(1);
  }

#else 
  void handle_screen_linux(int mode) {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    
    //? 0 will disable echo and 1 will enable it.
    mode == 0 ? (tty.c_lflag &= ~ECHO) : (tty.c_lflag |= ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
  }

  void disable_echo() {
    handle_screen_linux(0);
  }

  void enable_echo() {
    handle_screen_linux(1);
  }
#endif

const struct Echo Echo = { 
  .enable  = enable_echo,
  .disable = disable_echo
};
