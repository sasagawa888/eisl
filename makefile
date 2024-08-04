.POSIX:
.DELETE_ON_ERROR:

CC := cc
DC := ldc2
LD := $(CC)
ifneq  ($(shell uname),Darwin)
	ifeq  ($(shell uname),OpenBSD)
		LIBS := -lm
	else
		LIBS := -lm -ldl
	endif
endif
LIBSRASPI := -lm -ldl -lwiringPi
LIBTHREAD := -lpthread
INCS := -Icii/include

ifeq  ($(WITHOUT_CURSES),1)
	CURSES_CFLAGS := -DWITHOUT_CURSES=1
	CURSES_LIBS :=
else
	LIBSRASPI := $(LIBSRASPI) -lncurses
	ifeq  ($(shell uname),Darwin)
		CURSES_CFLAGS := $(shell ncurses5.4-config --cflags)
		CURSES_LIBS := $(shell ncurses5.4-config --libs)
		# NCURSES_PREFIX := $(shell brew --prefix ncurses)
		# CURSES_CFLAGS := $(shell $(NCURSES_PREFIX)/bin/ncurses6-config --cflags)
		# CURSES_LIBS := $(shell $(NCURSES_PREFIX)/bin/ncurses6-config --libs)
	else
		ifeq  ($(shell uname),OpenBSD)
			CURSES_LIBS := -lncurses
		else
			ifeq  ($(shell uname),FreeBSD)
				CURSES_LIBS := -lncurses
			else
				CURSES_CFLAGS := $(shell ncursesw6-config --cflags)
				CURSES_LIBS := $(shell ncursesw6-config --libs)
			endif
		endif
	endif
endif
CFLAGS += $(INCS) -g -Wall -Wextra -D_FORTIFY_SOURCE=2 $(CURSES_CFLAGS) -U_XOPEN_SOURCE -Inana/src
DFLAGS := --preview=all --de -w --O3 --release --betterC
SRC_CII := cii/src/except.c cii/src/fmt.c cii/src/str.c cii/src/text.c
SRC_D := dextension.d disl.d

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
	CFLAGS += -O3 -flto -DNDEBUG=1 -DWITHOUT_NANA=1
	SRC_CII += cii/src/mem.c
endif
OBJ_CII := $(SRC_CII:.c=.o)
OBJ_NANA := $(SRC_NANA:.c=.o)
OBJ_D := $(SRC_D:.d=.o)
OBJ_LISP := $(SRC_LISP:.lsp=.o)
CXX := c++
CXXFLAGS := $(CFLAGS) -std=c++98 -fno-exceptions -fno-rtti -Weffc++ $(CURSES_CFLAGS)
ifeq ($(CC),c++)
	CFLAGS := $(CXXFLAGS)
else
	CFLAGS += -std=c17
endif
ifeq  ($(shell uname -n),raspberrypi)
	CFLAGS += -D__rpi__
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
	link.o

ifeq  ($(WITHOUT_CURSES),1)
	# Without curses support, do not build edlis
	TARGETS := eisl $(OBJ_LISP)
else
	TARGETS := eisl edlis $(OBJ_LISP)
endif

all: $(TARGETS)

eisl: $(EISL_OBJS) $(OBJ_CII) $(OBJ_NANA)
ifeq  ($(shell uname -n),raspberrypi)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBSRASPI) $(LIBTHREAD)
else
	$(LD) $(LDFLAGS) $^ -o $@ $(LIBS) $(CURSES_LIBS) $(LIBTHREAD)
endif

%.o: %.c eisl.h ffi.h term.h cii/include/except.h nana/src/eiffel.h
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.d disl.d
	$(DC) $(DFLAGS) -c $<

%.o: %.lsp eisl
	echo '(load "library/compiler.lsp") (compile-file "$<")' | ./eisl -r

ifeq ($(DEBUG),1)
main.o: nana/src/nana-config.h
endif

nana/src/nana-config.h:
	-cd nana; autoreconf -fi; ./configure

edlis: edlis.o syn_highlight.o $(OBJ_CII) $(OBJ_NANA)
	$(CC) $(LDFLAGS) $^ -o $@ $(CURSES_LIBS)

edlis.o: edlis.c edlis.h term.h
	$(CC) $(CFLAGS) -c edlis.c


.PHONY: install
install: eisl edlis $(OBJ_LISP)
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
