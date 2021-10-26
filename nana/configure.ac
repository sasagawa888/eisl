#
# configure.ac - used by autoconf to generate the configure script.
#
# Copyright (c) 1997 Phil Maker
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#

AC_INIT([nana],[3.0])
AC_CONFIG_SRCDIR([src/nana.h])

AC_CANONICAL_TARGET

PREV_VERSION=2.4
AM_INIT_AUTOMAKE
AC_SUBST(PREV_VERSION)

AC_ARG_ENABLE(rdtsc,--enable-rdtsc 		  use pentium rdtsc cycle timing,HAVE_RDTSC=1,HAVE_RDTSC=0)
AC_SUBST(HAVE_RDTSC)

AC_PROG_CC
AC_PROG_AWK
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_CXXCPP
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AC_CHECK_PROG(FMT, fmt, fmt, cat)
AC_ARG_PROGRAM 
AC_PATH_PROG(TAR,gtar,tar)
AC_PATH_PROG(FIND,gfind,find)
AC_PATH_PROG(GDB,gdb)
AC_C_INLINE
AC_C_CONST


# nana checking code
AC_DEFUN(nana_DEFINE,[
AC_MSG_CHECKING([$1])
if test -z "$$1"
then # use code to work out the value
  $3
# else its been defined by the user
fi

if test -z "$$1"
then 
  AC_MSG_RESULT("default")
else 
  AC_MSG_RESULT($$1)
  $1="#define $1$2 $$1"
fi
AC_SUBST($1)
])

# default code to call when a I(..)  failure occurs
#
#  The I_DEFAULT variable is used to select between 
#  fast which does a core dump ASAP versus verbose
#  which prints a nice message before core dumping.

nana_DEFINE(I_DEFAULT_HANDLER,(exprn,file,line,param),
[ 
  case "$I_DEFAULT" in
  fast)
    case "$target" in
    i?86-*-*|x86_64-*-*)
      I_DEFAULT_HANDLER='asm("hlt")'
      ;;
    sparc-*-*)
      # note the sparc handler used to be asm("stp")
      I_DEFAULT_HANDLER='asm("unimp")'
      ;;
    *)
      I_DEFAULT_HANDLER='abort()'
      ;;
    esac 
    ;;
  verbose)
    ;;
  *)
    ;;
  esac

])

# code to emit to ensure a breakpoint can be set at this location
#
# e.g. if(f>1) { f--; I(f>=0);} I(f>-1);  
#     needs to have a nop inserted so the first I(..) can be checked.
#

nana_DEFINE(DI_MAKE_VALID_BREAKPOINT,(exprn),
[ 
  case "$target" in
  sparc-*-*|i?86-*-*|x86_64-*-*)	
    DI_MAKE_VALID_BREAKPOINT='asm("nop")'
    ;;
  esac
])

# code to emit to ensure a DL breakpoint can be set at this location
nana_DEFINE(DL_MAKE_VALID_BREAKPOINT,(),
[ 
  case "$target" in
  sparc-*-*|i?86-*-*|x86_64-*-*)
    DL_MAKE_VALID_BREAKPOINT='asm("nop")'
    ;;
  esac
])

# on some systems we need to generate a dummy reference to malloc
# since it isn't normally linked in and is required by gdb

nana_DEFINE(ALWAYS_INCLUDE_MALLOC, /* no arguments */,
[
  case "$target" in
  *-*-*BSD*)
    ALWAYS_INCLUDE_MALLOC='0'
    ;;
  i?86-*-linux*)
    ALWAYS_INCLUDE_MALLOC='1'
    ;; 
  *)
    ALWAYS_INCLUDE_MALLOC='0'
    ;;
  esac
])


# support for cycle level counting for various machines
#
# Note: autodiscovery is a bit dubious for these things since they
#       are machine version specific (ie not all i386s have them)
#
 
AC_ARG_ENABLE(rdtsc,--enable-rdtsc 		  use pentium rdtsc cycle timing,HAVE_RDTSC=1,HAVE_RDTSC=0)
AC_SUBST(HAVE_RDTSC)


AC_CHECK_FUNCS(vsprintf vsnprintf gettimeofday)

AC_CONFIG_FILES([Makefile doc/Makefile examples/Makefile man/Makefile src/Makefile test/Makefile gdb/Makefile emacs/Makefile perf/Makefile src/nana-config.h src/nana src/nana-run src/nana-clg gdb/nana-trace gdb/nana-libtrace src/nana-c++lg shortform/Makefile shortform/nana-sfg shortform/nana-sfdir test/gammon])

AC_CONFIG_COMMANDS([default],[chmod +x src/nana src/nana-clg src/nana-c++lg src/nana-run test/gammon],[])

AC_OUTPUT

echo "* Displaying configure variables for C code"
make showconfig

