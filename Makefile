all: default_target

ifeq ($(PROGRAM), client)
default_target: client.out
else ifeq ($(PROGRAM), server)
default_target: server.out
else
default_target:
	@echo "Please specify a PROGRAM variable (e.g: make PROGRAM=client or make PROGRAM=server)"
endif

# Client program:
client: \
	client/main.o \
	lib/error.o \
	lib/tcp.o \
	lib/request.o \
	lib/screen.o \
	lib/interfaces_Impl/user.o \
	lib/interfaces_Impl/host.o
	gcc client/main.o lib/error.o lib/tcp.o lib/request.o lib/screen.o \
			lib/interfaces_Impl/user.o lib/interfaces_Impl/host.o -lm -o client.out

# Server program:
server: \
	server.o \
	lib/error.o \
	lib/tcp.o \
	lib/request.o \
	gcc lib/tcp.o lib/request.o server.o -o server.out

# Object files:
lib/error.o: lib/error.c
	gcc -c lib/error.c -o lib/error.o

lib/tcp.o: lib/tcp.c
	gcc -c lib/tcp.c -o lib/tcp.o

lib/request.o: lib/request.c
	gcc -c lib/request.c -o lib/request.o

client/main.o: client/main.c
	gcc -c client/main.c -o client/main.o

lib/screen.o: lib/screen.c
	gcc -c lib/screen.c -o lib/screen.o

lib/interfaces_Impl/user.o: lib/interfaces_Impl/user.c
	gcc -c lib/interfaces_Impl/user.c -o lib/interfaces_Impl/user.o

lib/interfaces_Impl/host.o: lib/interfaces_Impl/host.c
	gcc -c lib/interfaces_Impl/host.c -o lib/interfaces_Impl/host.o

server.o: server.c
	gcc -c server.c -o server.o

clean:
	rm -rf lib/*.o lib/interfaces_Impl/*.o client/*.o server.o *.out
