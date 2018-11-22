CC=gcc
CFLAGS=-fPIE
ARFLAGS=rcs
DEPS=ansi.h
LIB=/data/data/com.termux/files/usr/lib
INC=$(LIB)/../include
BIN=$(LIB)/../bin

default: all
all: ansi.o libansi.so libansi.a test.o ansi fix install
.PHONY: clean install fix firstinst all default

ansi.o: ansi.c $(DEPS)
	$(CC) $(CFLAGS) -c ansi.c -o $@

libansi.so: ansi.o
	$(CC) $(CFLAGS) -shared -o $@ $^

libansi.a: ansi.o
	$(AR) $(ARFLAGS) $@ $^

test.o: test.c ansi.o
	$(CC) $(CFLAGS) $^ -o $@

ansi: bin.c ansi.o
	$(CC) $(CFLAGS) bin.c -o $@ -L./ -lansi


install: libansi.so
	install -m 755 libansi.so $(LIB)
	install -m 755 ansi.h $(INC)
	install -m 755 ansi $(BIN)

clean: *.o
	rm *.o

fix: *
	chmod 775 *

firstinst: FORCE
	$(shell export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:`pwd`)

FORCE:
