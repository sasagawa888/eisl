.POSIX:
.DELETE_ON_ERROR:

OPSYS ?= linux
CC := cc
LD := $(CC)
ifneq ($(OPSYS),macos)
	ifeq ($(OPSYS),openbsd)
		LIBS := -lm
	else
		LIBS := -lm -ldl
	endif
endif
LIBSRASPI := -lm -ldl -lwiringPi -lncurses
INCS := -Icii/include
ifeq ($(OPSYS),macos)
	CURSES_CFLAGS := $(shell ncurses5.4-config --cflags)
	CURSES_LIBS := $(shell ncurses5.4-config --libs)
else
	ifeq ($(OPSYS),openbsd)
		CURSES_LIBS := -lncurses
	else
		CURSES_CFLAGS := $(shell ncurses6-config --cflags)
		CURSES_LIBS := $(shell ncurses6-config --libs)
	endif
endif
CFLAGS := $(INCS) -Wall -Wextra -D_FORTIFY_SOURCE=2 $(CURSES_CFLAGS) -U_XOPEN_SOURCE -D_XOPEN_SOURCE=700
SRC_CII := cii/src/except.c cii/src/fmt.c cii/src/str.c cii/src/text.c
ifeq ($(DEBUG),1)
	CFLAGS += -O0 -g
	SRC_CII += cii/src/memchk.o cii/src/assert.o
	ifneq ($(OPSYS),openbsd)
		CFLAGS += -fsanitize=undefined
		LDFLAGS := -fsanitize=undefined
	endif
else
	CFLAGS += -O3 -flto -DNDEBUG=1
	SRC_CII += cii/src/mem.c
endif
OBJ_CII := $(SRC_CII:.c=.o)
CXX := c++
CXXFLAGS := $(CFLAGS) -std=c++98 -fno-exceptions -fno-rtti -Weffc++ $(CURSES_CFLAGS)
ifeq ($(CC),c++)
	CFLAGS := $(CXXFLAGS)
else
	CFLAGS += -std=c17
endif
ifneq ($(DEBUG),1)
	LDFLAGS += -flto
	ifeq ($(OPSYS),macos)
		LDFLAGS += -Wl,-S,-x
	else
		LDFLAGS += -s
	endif
endif
PREFIX := /usr/local
bindir := $(PREFIX)/bin
DESTDIR := 
INSTALL := install
INSTALL_PROGRAM := $(INSTALL) -m755

EISL_OBJS := main.o \
	function.o \
	extension.o \
	syntax.o \
	data.o \
	gbc.o \
	cell.o \
	error.o \
	bignum.o \
	compute.o \
	edit.o \
    syn_highlight.o \
	long.o

all: eisl edlis

eisl: $(EISL_OBJS) $(OBJ_CII)
ifeq  ($(shell uname -n),raspberrypi)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBSRASPI) 
else
	$(LD) $(LDFLAGS) $^ -o $@ $(LIBS) $(CURSES_LIBS)
endif

%.o: %.c eisl.h ffi.h term.h cii/include/except.h
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_CII) cii/include/except.h:
	git submodule init
	git submodule update

edlis : edlis.o syn_highlight.o $(OBJ_CII)
	$(CC) $(LDFLAGS) $^ -o $@ $(CURSES_LIBS)
edlis.o : edlis.c edlis.h term.h
	$(CC) $(CFLAGS) -c edlis.c

.PHONY: install
install: eisl edlis
	$(INSTALL_PROGRAM) eisl $(DESTDIR)$(bindir)/$(EISL)
	$(INSTALL_PROGRAM) edlis $(DESTDIR)$(bindir)/$(EDLIS)

.PHONY: uninstall
uninstall:
	$(RM) $(DESTDIR)$(bindir)/eisl
	$(RM) $(DESTDIR)$(bindir)/edlis

.PHONY: clean
clean:
	$(RM) *.o $(OBJ_CII) eisl edlis

.PHONY: check
check:
	cppcheck --enable=all --std=c11 --library=posix .
