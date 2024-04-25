CC = gcc
SRC = libsyslinux-parser.c
OBJ = libsyslinux-parser.o
LIB = libsyslinux-parser.so

all: libsyslinux-parser
libsyslinux-parser: $(OBJ)
	$(CC) -shared -o $(LIB) $(OBJ)
$(OBJ): $(SRC)
	$(CC) -fPIC -c $(SRC) -o $(OBJ)
example:
	$(CC) example.c -o example
debug:
	$(CC) $(CFLAGS) -g $(SRC) -o debug
test: example
	./example
clean:
	rm -f $(OBJ) $(LIB) example debug
