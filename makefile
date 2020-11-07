CC := gcc
LIBS = -lm -ldl 
LIBSRASPI = -lm -ldl -lwiringPi
INCS =  
CFLAGS = $(INCS) -Wall -O3 
PREFIX = /usr/local
bindir = $(PREFIX)/bin
DESTDIR = 
INSTALL = install
INSTALL_PROGRAM = $(INSTALL) -Dm755

EISL = eisl
EDLIS = edlis

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
	$(CC) $(EISL_OBJS) -o $(EISL) $(LIBSRASPI) 
else
eisl2: $(EISL_OBJS) $(EISL)
$(EISL): $(EISL_OBJS)
	$(CC) $(EISL_OBJS) -o $(EISL) $(LIBS) 
endif



%.o: %.c eisl.h
	$(CC) -c $< -o $@ $(CFLAGS)

edlis : edlis.o
	$(CC) -O3 -Wall edlis.o -o edlis
edlis.o : edlis.c edlis.h
	$(CC)  -O3 -Wall -c edlis.c


install: $(EISL) $(EDLIS)
	$(INSTALL_PROGRAM) $(EISL) $(DESTDIR)$(bindir)/$(EISL)
	$(INSTALL_PROGRAM) $(EDLIS) $(DESTDIR)$(bindir)/$(EDLIS)

uninstall:
	rm $(DESTDIR)$(bindir)/$(EISL)
	rm $(DESTDIR)$(bindir)/$(EDLIS)


.PHONY: clean
clean: -lm
	rm -f *.o
	rm eisl
	rm edlis

