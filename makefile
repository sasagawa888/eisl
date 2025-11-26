.POSIX:
.DELETE_ON_ERROR:

USE_WIRINGPI ?= 0
USE_GPIO ?= 0
USE_FLTO ?= 0
USE_GDB ?= 0

CC := gcc
LIBS := -lm -ldl -lpthread -lncurses
INCS := 
CURSES_CFLAGS := $(shell ncursesw6-config --cflags) 
CURSES_LIBS := $(shell ncursesw6-config --libs)


CFLAGS += $(INCS) -Wall $(CURSES_CFLAGS) 

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
		library/datetime.lsp \
		library/plot.lsp \
		library/unistd.lsp 

CFLAGS += -O3

ifeq ($(USE_FLTO),1)
CFLAGS += -O3 -flto
endif
ifeq ($(USE_GDB),1)
CFLAGS += -O0 -g
endif 

ifeq  ($(shell uname -n),raspberrypi)
CFLAGS += -O3
endif

OBJ_LISP := $(SRC_LISP:.lsp=.o)

ifeq  ($(shell uname -n),raspberrypi)
CFLAGS += -D__rpi__
endif

ifeq  ($(shell uname -n),raspberrypi)
ifeq ($(USE_WIRINGPI),1)
CFLAGS += -D__rpiwiring__
LIBS += -lwiringPi
endif
endif

ifeq  ($(shell uname -n),raspberrypi)
ifeq ($(USE_GPIO),1)
CFLAGS += -D__rpigpio__
LIBS += -lgpiod
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
	link.o \
	parallel.o

TARGETS := eisl edlis 

all: $(TARGETS)

eisl: $(EISL_OBJS) 
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS) 

%.o: %.c eisl.h ffi.h term.h
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.lsp eisl
	echo '(load "library/compiler.lsp") (compile-file "$<")' | ./eisl -r
	touch $@


main.o: function.o extension.o syntax.o data.o gbc.o cell.o error.o bignum.o compute.o edit.o syn_highlight.o link.o parallel.o
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
link.o: link.c eisl.h 
parallel.o: parallel.c eisl.h


edlis: edlis.o syn_highlight.o 
	$(CC) $(CFLAGS) $^ -o $@ $(CURSES_LIBS)

edlis.o: edlis.c edlis.h term.h
	$(CC) $(CFLAGS) -c edlis.c


.PHONY: install
install: eisl edlis
	$(MKDIR_PROGRAM) $(DESTDIR)$(bindir)
	$(INSTALL_PROGRAM) eisl $(DESTDIR)$(bindir)/eisl
	$(INSTALL_PROGRAM) edlis $(DESTDIR)$(bindir)/edlis
	$(MKDIR_PROGRAM) $(DESTDIR)$(sharedir)
	$(INSTALL_PROGRAM) library/* $(DESTDIR)$(sharedir)
	$(INSTALL_PROGRAM) fast.h ffi.h $(DESTDIR)/$(PREFIX)/share/eisl

.PHONY: lisp
lisp: $(OBJ_LISP)

.PHONY: uninstall
uninstall:
	$(RM) $(DESTDIR)$(bindir)/eisl
	$(RM) $(DESTDIR)$(bindir)/edlis

.PHONY: clean
clean:
	$(RM) *.o $(OBJ_CII) $(OBJ_LISP) eisl edlis

.PHONY: check
check:
	cppcheck --enable=warning,performance,portability --std=c17 --library=posix -j4 .
