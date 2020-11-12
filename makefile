CC := gcc
LIBS = -lm -ldl 
LIBSRASPI = -lm -ldl -lwiringPi
INCS =  
CFLAGS ?= $(INCS) -Wall -O3 
PREFIX = /usr/local
bindir = $(PREFIX)/bin
DESTDIR = 
INSTALL = install
INSTALL_PROGRAM = $(INSTALL) -Dm755

EISL = eisl
EDLIS = edlis

FILES = library

EISL_OBJS = main.o \
	function.o \
	extension.o \
	syntax.o \
	data.o \
	gbc.o \
	cell.o \
	error.o \
	bignum.o \
	compute.o \
	edit.o

all: eisl edlis

eisl:
ifeq  ($(shell uname -n),raspberrypi)
eisl1: $(EISL_OBJS) $(EISL)
$(EISL): $(EISL_OBJS)
	$(CC) $(CFLAGS) $(EISL_OBJS) -o $(EISL) $(LIBSRASPI) 
else
eisl2: $(EISL_OBJS) $(EISL)
$(EISL): $(EISL_OBJS)
	$(CC) $(CFLAGS) $(EISL_OBJS) -o $(EISL) $(LIBS) 
endif



%.o: %.c eisl.h
	$(CC) $(CFLAGS) -c $< -o $@

edlis : edlis.o
	$(CC) $(CFLAGS) edlis.o -o edlis
edlis.o : edlis.c edlis.h
	$(CC) $(CFLAGS) -c edlis.c


install: $(EISL) $(EDLIS)
	$(INSTALL_PROGRAM) $(EISL) $(DESTDIR)$(bindir)/$(EISL)
	$(INSTALL_PROGRAM) $(EDLIS) $(DESTDIR)$(bindir)/$(EDLIS)
	mkdir -p /home/eisl
	cp fast.h /home/eisl
	cp library/compiler.lsp /home/eisl

uninstall:
	rm $(DESTDIR)$(bindir)/$(EISL)
	rm $(DESTDIR)$(bindir)/$(EDLIS)
	rm /home/eisl/*.*
	rmdir /home/eisl


.PHONY: clean
clean: -lm
	rm -f *.o
	rm eisl
	rm edlis

