CC=cc
CFLAGS=-Wall -Wextra -Wformat -pedantic -ggdb
IDIR=include
INCLUDE=-I$(IDIR)/
LIBS=
SRCS=main.c $(IDIR)/font.c
OUT=ascii-art

build:
	$(CC) $(CFLAGS) $(INCLUDE) -o $(OUT) $(SRCS) $(LIBS)

run: build
	./$(OUT) ./banner-font.ascii "Test message"
