.POSIX:
.DELETE_ON_ERROR:

USE_WIRINGPI ?= 0
USE_FLTO ?= 0
USE_GDB ?= 0

CC := gcc
LIBS := -lm -ldl -lpthread -lncurses
INCS := -Icii/include
CURSES_CFLAGS := $(shell ncursesw6-config --cflags)
CURSES_LIBS := $(shell ncursesw6-config --libs)

CFLAGS += $(INCS) -Wall $(CURSES_CFLAGS)
SRC_CII := cii/src/except.c cii/src/fmt.c cii/src/str.c cii/src/text.c

SRC_LISP := library/bit.lsp \
            library/escape.lsp \
            library/i18n.lsp \
            library/logger.lsp \
            library/ndbm.lsp \
            library/opengl.lsp \
            library/regex.lsp \
            library/tcltk.lsp \
            library/virtty.lsp \
            library/prolog.lsp \
            library/datetime.lsp \
            library/plot.lsp \
            library/unistd.lsp

CFLAGS += -O3 -DNDEBUG=1 -Wno-stringop-truncation

ifeq ($(USE_FLTO),1)
CFLAGS += -flto
endif
ifeq ($(USE_GDB),1)
CFLAGS += -O0 -g
endif

ifeq ($(shell uname -n),raspberrypi)
CFLAGS += -O3 -DNDEBUG=1 -Wno-stringop-truncation -Wno-array-bounds
ifeq ($(USE_WIRINGPI),1)
    CFLAGS += -D__rpi__
    LIBS += -lwiringPi
endif
endif

SRC_CII += cii/src/mem.c
OBJ_CII := $(SRC_CII:.c=.o)
OBJ_LISP := $(SRC_LISP:.lsp=.o)

PREFIX := /usr/local
BINDIR := $(PREFIX)/bin
SHAREDIR ?= $(PREFIX)/share/eisl
SHARELIB := $(PREFIX)/share/eisl/library
DESTDIR :=
INSTALL := install
INSTALL_PROGRAM := $(INSTALL) -m755
MKDIR_PROGRAM := mkdir -p -m 755

# Use files from source tree at compile time
EASY_ISLISP := $(CURDIR)
export EASY_ISLISP

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
             long.o \
             link.o \
             parallel.o

TARGETS := eisl edlis

all: $(TARGETS)

# Build eisl
eisl: $(EISL_OBJS) $(OBJ_CII)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

%.o: %.c eisl.h ffi.h term.h cii/include/except.h
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.lsp eisl
	echo '(load "library/compiler.lsp") (compile-file "$<")' | ./eisl -r
	touch $@

# Dependencies
main.o: $(EISL_OBJS)
function.o: function.c eisl.h
extension.o: extension.c eisl.h
syntax.o: syntax.c eisl.h
data.o: data.c eisl.h
gbc.o: gbc.c eisl.h
cell.o: cell.c eisl.h
error.o: error.c eisl.h
bignum.o: bignum.c eisl.h
compute.o: compute.c eisl.h
edit.o: edit.c eisl.h
syntax_highlight.o: syntax_highlight.c eisl.h
long.o: long.c eisl.h
link.o: link.c eisl.h
parallel.o: parallel.c eisl.h

# Build edlis
edlis: edlis.o syn_highlight.o $(OBJ_CII)
	$(CC) $(CFLAGS) $^ -o $@ $(CURSES_LIBS)

edlis.o: edlis.c edlis.h term.h
	$(CC) $(CFLAGS) -c edlis.c

.PHONY: install
install: eisl edlis
	$(MKDIR_PROGRAM) $(DESTDIR)$(BINDIR)
	$(INSTALL_PROGRAM) eisl $(DESTDIR)$(BINDIR)/eisl
	$(INSTALL_PROGRAM) edlis $(DESTDIR)$(BINDIR)/edlis
	$(MKDIR_PROGRAM) $(DESTDIR)$(SHARELIB)
	$(INSTALL_PROGRAM) library/* $(DESTDIR)$(SHARELIB)
	$(INSTALL_PROGRAM) fast.h ffi.h $(DESTDIR)/$(SHAREDIR)

.PHONY: lisp
lisp: $(OBJ_LISP)

.PHONY: uninstall
uninstall:
	$(RM) $(DESTDIR)$(BINDIR)/eisl
	$(RM) $(DESTDIR)$(BINDIR)/edlis

.PHONY: clean
clean:
	$(RM) *.o $(OBJ_CII) $(OBJ_LISP) eisl edlis

.PHONY: check
check:
	cppcheck --enable=all --std=c11 --library=posix .