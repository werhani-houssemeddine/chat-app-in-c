#!/bin/sh

# This shell script is used to run either the server or client programs
# based on the passed argument. Invalid arguments will display an error message.
# For now, we will continue using this script. In the future, we plan to use a Makefile instead.

#? Note:
#? default port is 3000 
#? default host is 127.0.0.1

PROGRAM_TO_RUN="$1"

if [ "$1" = "client" ]; then

  # Compile client program and run it.
  gcc lib/tcp.c lib/interfaces_Impl/host.c client/main.c -lm -o client.out

  if [ $? -eq 0 ]; then
    echo "Compilation client successful. Running the program... "
    ./client.out --port 3000 --host 127.0.0.1
  else
    echo "Compilation client failed."
  fi
  
elif [ "$1" = "server" ]; then
  
  # Compile server program and run it.
  gcc lib/tcp.c server.c -o server.out

  if [ $? -eq 0 ]; then
    echo "Compilation server successful. Running the program... "
    ./server.out
  else
    echo "Compilation server failed."
  fi

else
  echo "Invalid program."
fi