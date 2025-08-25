.POSIX:
.DELETE_ON_ERROR:

USE_WIRINGPI ?= 0
USE_FLTO ?= 0
COMPILE_LISP ?= 0
WITHOUT_CURSES ?= 0

CC := cc
DC := ldc2
LD := $(CC)
LIBS := -lm -ldl -lpthread -lncurses
LIBSRASPI := -lm -ldl -lpthread -lncurses
INCS := -Icii/include

ifeq  ($(WITHOUT_CURSES),1)
	CURSES_CFLAGS := -DWITHOUT_CURSES=1
	CURSES_LIBS :=
else
	CURSES_CFLAGS := $(shell ncursesw6-config --cflags)
	CURSES_LIBS := $(shell ncursesw6-config --libs)
endif

CFLAGS += $(INCS) -Wall $(CURSES_CFLAGS) -Inana/src
DFLAGS := --preview=all --de -w --O3 --release --betterC
SRC_CII := cii/src/except.c cii/src/fmt.c cii/src/str.c cii/src/text.c

# Files in library/ that need to be compiled
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

ifeq ($(DEBUG),1)
	CFLAGS += -Og -g -DEIFFEL_DOEND -DEIFFEL_CHECK=CHECK_ENSURE -DWITH_NANA=1
	SRC_CII += cii/src/memchk.c cii/src/assert.c
	SRC_NANA := nana/src/I.c
	ifneq  ($(shell uname),OpenBSD)
		CFLAGS += -fsanitize=undefined
		LDFLAGS += -fsanitize=undefined
	endif
else
	ifeq ($(USE_FLTO),1)
	CFLAGS += -O3 -flto -DNDEBUG=1 -DWITHOUT_NANA=1
	else
	CFLAGS += -O3 -DNDEBUG=1 -DWITHOUT_NANA=1
	endif
	SRC_CII += cii/src/mem.c
endif
OBJ_CII := $(SRC_CII:.c=.o)
OBJ_NANA := $(SRC_NANA:.c=.o)
OBJ_LISP := $(SRC_LISP:.lsp=.o)

ifeq  ($(shell uname -n),raspberrypi)
	ifneq ($(USE_WIRINGPI),1)
		CFLAGS += -D__rpi__
		LIBSRASPI += -lwringPi
	endif
endif
ifneq ($(DEBUG),1)
	LDFLAGS += -flto
	ifeq  ($(shell uname),Darwin)
		LDFLAGS += -Wl,-S,-x
	else
		LDFLAGS += -s
	endif
endif
PREFIX := /usr/local
SHAREDIR ?= $(PREFIX)/share/eisl
CFLAGS += -DSHAREDIR=$(SHAREDIR)
bindir := $(PREFIX)/bin
sharedir := $(PREFIX)/share/eisl/library
DESTDIR :=
INSTALL := install
INSTALL_PROGRAM := $(INSTALL) -m755
MKDIR_PROGRAM := mkdir -p -m 755

# Use files from source tree at compile time because
# sharedir isn't populated yet
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

ifeq  ($(WITHOUT_CURSES),1)
	# Without curses support, do not build edlis
	TARGETS := eisl $(OBJ_LISP)
else
	TARGETS := eisl edlis $(OBJ_LISP)
endif

all: $(TARGETS)

eisl: $(EISL_OBJS) $(OBJ_CII) $(OBJ_NANA)
ifeq  ($(shell uname -n),raspberrypi)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBSRASPI) 
else
	$(LD) $(LDFLAGS) $^ -o $@ $(LIBS) 
endif

%.o: %.c eisl.h ffi.h term.h cii/include/except.h nana/src/eiffel.h
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.lsp eisl
	echo '(load "library/compiler.lsp") (compile-file "$<")' | ./eisl -r


ifeq ($(DEBUG),1)
main.o: nana/src/nana-config.h
endif

main.o: function.o extension.o syntax.o data.o gbc.o cell.o error.o bignum.o compute.o edit.o syn_highlight.o long.o link.o parallel.o
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


nana/src/nana-config.h:
	-cd nana; autoreconf -fi; ./configure

edlis: edlis.o syn_highlight.o $(OBJ_CII) $(OBJ_NANA)
	$(CC) $(LDFLAGS) $^ -o $@ $(CURSES_LIBS)

edlis.o: edlis.c edlis.h term.h
	$(CC) $(CFLAGS) -c edlis.c


.PHONY: install
ifeq ($(COMPILE_LISP),1)
install: eisl edlis $(OBJ_LISP)
else 
install: eisl edlis
endif
	$(MKDIR_PROGRAM) $(DESTDIR)$(bindir)
	$(INSTALL_PROGRAM) eisl $(DESTDIR)$(bindir)/$(EISL)
	$(INSTALL_PROGRAM) edlis $(DESTDIR)$(bindir)/$(EDLIS)
	$(MKDIR_PROGRAM) $(DESTDIR)$(sharedir)
	$(INSTALL_PROGRAM) library/* $(DESTDIR)$(sharedir)
	$(INSTALL_PROGRAM) fast.h ffi.h $(DESTDIR)/$(PREFIX)/share/eisl

.PHONY: uninstall
uninstall:
	$(RM) $(DESTDIR)$(bindir)/eisl
	$(RM) $(DESTDIR)$(bindir)/edlis

.PHONY: clean
clean:
	$(RM) *.o $(OBJ_CII) $(OBJ_NANA) $(OBJ_D) $(OBJ_LISP) eisl edlis

.PHONY: check
check:
	cppcheck --enable=all --std=c11 --library=posix .
