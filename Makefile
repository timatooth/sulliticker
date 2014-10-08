# Makefile for sulliticker
CC=gcc
CFLAGS=-c -W -Wall -ansi -pedantic
LDFLAGS=-lncurses -lcurl -lm
EXECUTABLE=sulliticker
OBJ=cJSON.o main.o curlhelper.o

all: sulliticker

$(EXECUTABLE): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(EXECUTABLE)

main.o: main.c
	$(CC) $(CFLAGS) main.c

curlhelper.o: curlhelper.c
	$(CC) $(CFLAGS) curlhelper.c

cJSON.o: cJSON.c
	$(CC) -c cJSON.c
clean:
	rm -rf *o sullitracker

install:
	cp sulliticker /usr/local/bin/sulliticker

uninstall:
	rm -rf /usr/local/bin/sulliticker
