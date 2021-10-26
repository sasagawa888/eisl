Script started on Mon Apr 21 19:16:17 1997
% tar zxvf ../nana/nana-1.00.tar.gz 
nana-1.00/Makefile.in
nana-1.00/doc/Makefile.in
nana-1.00/doc/Makefile.am
nana-1.00/doc/mdate-sh
nana-1.00/doc/stamp-vti
nana-1.00/doc/version.texi
nana-1.00/doc/nana.texi
nana-1.00/doc/nana.info
nana-1.00/doc/nana.info-1
nana-1.00/doc/nana.info-2
nana-1.00/doc/tex3patch
nana-1.00/doc/texinfo.tex
nana-1.00/doc/nana.ps.gz
nana-1.00/examples/Makefile.in
nana-1.00/examples/Makefile.am
nana-1.00/examples/main.c
nana-1.00/examples/ott.c
nana-1.00/examples/ott.h
nana-1.00/man/Makefile.in
nana-1.00/man/README
nana-1.00/man/Makefile.am
nana-1.00/man/nana-clg.1
nana-1.00/man/I.3
nana-1.00/man/DI.3
nana-1.00/man/L.3
nana-1.00/man/DL.3
nana-1.00/man/Q.3
nana-1.00/man/nana.3
nana-1.00/man/nana.1
nana-1.00/src/Makefile.in
nana-1.00/src/README
nana-1.00/src/ChangeLog
nana-1.00/src/Makefile.am
nana-1.00/src/TODO
nana-1.00/src/L.c
nana-1.00/src/I.c
nana-1.00/src/L_buffer.c
nana-1.00/src/now.c
nana-1.00/src/nanafilter.c
nana-1.00/src/nana-config.h
nana-1.00/src/nana.h
nana-1.00/src/DI.h
nana-1.00/src/I.h
nana-1.00/src/DL.h
nana-1.00/src/L.h
nana-1.00/src/Q.h
nana-1.00/src/GDB.h
nana-1.00/src/L_buffer.h
nana-1.00/src/now.h
nana-1.00/src/nana.in
nana-1.00/src/nana-clg.in
nana-1.00/src/nana-run.in
nana-1.00/src/nana-run.gdb
nana-1.00/src/nana-config.h.in
nana-1.00/src/nana-run-init.gdb
nana-1.00/test/Makefile.in
nana-1.00/test/README
nana-1.00/test/ChangeLog
nana-1.00/test/Makefile.am
nana-1.00/test/selftest.c
nana-1.00/test/Q.c
nana-1.00/test/I.c
nana-1.00/test/L.c
nana-1.00/test/Iok.c
nana-1.00/test/Ifail.c
nana-1.00/test/DI.c
nana-1.00/test/manyDL.c
nana-1.00/test/DS.c
nana-1.00/test/DL.c
nana-1.00/test/Ltime.c
nana-1.00/test/now.c
nana-1.00/test/checkall
nana-1.00/test/check.awk
nana-1.00/test/check.h
nana-1.00/gdb/Makefile.in
nana-1.00/gdb/README
nana-1.00/gdb/Makefile.am
nana-1.00/gdb/nana-trace.in
nana-1.00/gdb/nana-trace.gdb
nana-1.00/gdb/test.c
nana-1.00/gdb/quiet.diff
nana-1.00/README
nana-1.00/AUTHORS
nana-1.00/COPYING
nana-1.00/ChangeLog
nana-1.00/INSTALL
nana-1.00/Makefile.am
nana-1.00/NEWS
nana-1.00/THANKS
nana-1.00/TODO
nana-1.00/aclocal.m4
nana-1.00/config.guess
nana-1.00/config.sub
nana-1.00/configure
nana-1.00/configure.in
nana-1.00/install-sh
nana-1.00/mkinstalldirs
nana-1.00/REGISTRATION
nana-1.00/ANNOUNCE
% cd nana-1.00
% ./configure --prefix=- / $HOME/work/local     play
creating cache ./config.cache
checking host system type... i386-unknown-freebsd2.2.1
checking target system type... i386-unknown-freebsd2.2.1
checking build system type... i386-unknown-freebsd2.2.1
checking DI_MAKE_VALID_BREAKPOINT... asm("nop")
checking DL_MAKE_VALID_BREAKPOINT... asm("nop")
checking I_DEFAULT_HANDLER... asm("hlt")
checking ALWAYS_INCLUDE_MALLOC... 1
checking for gcc... gcc
checking whether the C compiler (gcc  ) works... yes
checking whether the C compiler (gcc  ) is a cross-compiler... no
checking whether we are using GNU C... yes
checking whether gcc accepts -g... yes
checking for mawk... no
checking for gawk... no
checking for nawk... no
checking for awk... awk
checking how to run the C preprocessor... gcc -E
checking for c++... c++
checking whether the C++ compiler (c++  ) works... yes
checking whether the C++ compiler (c++  ) is a cross-compiler... no
checking whether we are using GNU C++... yes
checking whether c++ accepts -g... yes
checking for a BSD compatible install... /usr/bin/install -c
checking whether make sets ${MAKE}... yes
checking for ranlib... ranlib
checking for gtar... tar
checking for inline... inline
checking for working const... yes
updating cache ./config.cache
creating ./config.status
creating Makefile
creating doc/Makefile
creating examples/Makefile
creating man/Makefile
creating src/Makefile
creating test/Makefile
creating gdb/Makefile
creating src/nana-config.h
creating src/nana
creating src/nana-run
creating src/nana-clg
creating gdb/nana-trace
% gmake
for subdir in src test examples doc man gdb; do		\
  target=`echo all-recursive | sed s/-recursive//`; \
  echo making $target in $subdir;	\
  (cd $subdir && gmake $target)	\
   || case "" in *k*) fail=yes;; *) exit 1;; esac; \
done && test -z "$fail"
making all in src
gmake[1]: Entering directory `/usr/home/pjm/work/play/nana-1.00/src'
gcc -c -I. -I.    -g -O2 L.c
gcc -c -I. -I.    -g -O2 I.c
gcc -c -I. -I.    -g -O2 L_buffer.c
gcc -c -I. -I.    -g -O2 now.c
rm -f libnana.a
ar cru libnana.a L.o I.o L_buffer.o now.o 
ranlib libnana.a
gcc -c -I. -I.    -g -O2 nanafilter.c
gcc  -o nanafilter nanafilter.o  
gmake[1]: Leaving directory `/usr/home/pjm/work/play/nana-1.00/src'
making all in test
gmake[1]: Entering directory `/usr/home/pjm/work/play/nana-1.00/test'
gmake[1]: Nothing to be done for `all'.
gmake[1]: Leaving directory `/usr/home/pjm/work/play/nana-1.00/test'
making all in examples
gmake[1]: Entering directory `/usr/home/pjm/work/play/nana-1.00/examples'
gmake[1]: Nothing to be done for `all'.
gmake[1]: Leaving directory `/usr/home/pjm/work/play/nana-1.00/examples'
making all in doc
gmake[1]: Entering directory `/usr/home/pjm/work/play/nana-1.00/doc'
gmake[1]: Nothing to be done for `all'.
gmake[1]: Leaving directory `/usr/home/pjm/work/play/nana-1.00/doc'
making all in man
gmake[1]: Entering directory `/usr/home/pjm/work/play/nana-1.00/man'
gmake[1]: Nothing to be done for `all'.
gmake[1]: Leaving directory `/usr/home/pjm/work/play/nana-1.00/man'
making all in gdb
gmake[1]: Entering directory `/usr/home/pjm/work/play/nana-1.00/gdb'
gmake[1]: Nothing to be done for `all'.
gmake[1]: Leaving directory `/usr/home/pjm/work/play/nana-1.00/gdb'
% gmae ke install
for subdir in src test examples doc man gdb; do		\
  target=`echo install-recursive | sed s/-recursive//`; \
  echo making $target in $subdir;	\
  (cd $subdir && gmake $target)	\
   || case "" in *k*) fail=yes;; *) exit 1;; esac; \
done && test -z "$fail"
making install in src
gmake[1]: Entering directory `/usr/home/pjm/work/play/nana-1.00/src'
../mkinstalldirs /home/pjm/work/play/lib
mkdir /home/pjm/work/play/lib
list="libnana.a"; for p in $list; do \
  if test -f $p; then \
    /usr/bin/install -c -m 644 $p /home/pjm/work/play/lib/$p; \
    ranlib /home/pjm/work/play/lib/$p; \
  else :; fi; \
done
../mkinstalldirs /home/pjm/work/play/libexec
mkdir /home/pjm/work/play/libexec
list="nanafilter "; for p in $list; do \
  if test -f $p; then \
    /usr/bin/install -c $p /home/pjm/work/play/libexec/`echo $p|sed 's,x,x,'`; \
  else :; fi; \
done
../mkinstalldirs /home/pjm/work/play/bin
mkdir /home/pjm/work/play/bin
list="nana nana-clg nana-run"; for p in $list; do \
  if test -f $p; then \
    /usr/bin/install -c -m 755 $p /home/pjm/work/play/bin/`echo $p|sed 's,x,x,'`; \
  else if test -f ./$p; then \
    /usr/bin/install -c -m 755 ./$p \
      /home/pjm/work/play/bin/`echo $p|sed 's,x,x,'`; \
  else :; fi; fi; \
done
../mkinstalldirs /home/pjm/work/play/libexec
list="nana-run.gdb nana-run-init.gdb"; for p in $list; do \
  if test -f $p; then \
    /usr/bin/install -c -m 755 $p /home/pjm/work/play/libexec/`echo $p|sed 's,x,x,'`; \
  else if test -f ./$p; then \
    /usr/bin/install -c -m 755 ./$p \
      /home/pjm/work/play/libexec/`echo $p|sed 's,x,x,'`; \
  else :; fi; fi; \
done
../mkinstalldirs /home/pjm/work/play/include
mkdir /home/pjm/work/play/include
list="nana-config.h nana.h DI.h I.h DL.h L.h Q.h GDB.h L_buffer.h now.h"; for p in $list; do \
  /usr/bin/install -c -m 644 ./$p /home/pjm/work/play/include/$p; \
done
gmake[1]: Leaving directory `/usr/home/pjm/work/play/nana-1.00/src'
making install in test
gmake[1]: Entering directory `/usr/home/pjm/work/play/nana-1.00/test'
gmake[1]: Leaving directory `/usr/home/pjm/work/play/nana-1.00/test'
making install in examples
gmake[1]: Entering directory `/usr/home/pjm/work/play/nana-1.00/examples'
gmake[1]: Leaving directory `/usr/home/pjm/work/play/nana-1.00/examples'
making install in doc
gmake[1]: Entering directory `/usr/home/pjm/work/play/nana-1.00/doc'
../mkinstalldirs /home/pjm/work/play/info
mkdir /home/pjm/work/play/info
for file in nana.info; do		\
  for ifile in `cd . && echo $file*`; do \
    /usr/bin/install -c -m 644 ./$ifile /home/pjm/work/play/info/$ifile; \
  done;					\
done
gmake[1]: Leaving directory `/usr/home/pjm/work/play/nana-1.00/doc'
making install in man
gmake[1]: Entering directory `/usr/home/pjm/work/play/nana-1.00/man'
../mkinstalldirs /home/pjm/work/play/man/man1
mkdir /home/pjm/work/play/man
mkdir /home/pjm/work/play/man/man1
../mkinstalldirs /home/pjm/work/play/man/man3
mkdir /home/pjm/work/play/man/man3
installing Q.3 as /home/pjm/work/play/man/man3/Q.3
installing DI.3 as /home/pjm/work/play/man/man3/DI.3
installing nana.3 as /home/pjm/work/play/man/man3/nana.3
installing DL.3 as /home/pjm/work/play/man/man3/DL.3
installing I.3 as /home/pjm/work/play/man/man3/I.3
installing L.3 as /home/pjm/work/play/man/man3/L.3
installing nana-clg.1 as /home/pjm/work/play/man/man1/nana-clg.1
installing nana.1 as /home/pjm/work/play/man/man1/nana.1
gmake[1]: Leaving directory `/usr/home/pjm/work/play/nana-1.00/man'
making install in gdb
gmake[1]: Entering directory `/usr/home/pjm/work/play/nana-1.00/gdb'
../mkinstalldirs /home/pjm/work/play/bin
list="nana-trace "; for p in $list; do \
  if test -f $p; then \
    /usr/bin/install -c -m 755 $p /home/pjm/work/play/bin/`echo $p|sed 's,x,x,'`; \
  else if test -f ./$p; then \
    /usr/bin/install -c -m 755 ./$p \
      /home/pjm/work/play/bin/`echo $p|sed 's,x,x,'`; \
  else :; fi; fi; \
done
../mkinstalldirs /home/pjm/work/play/libexec
list="nana-trace.gdb "; for p in $list; do \
  if test -f $p; then \
    /usr/bin/install -c -m 755 $p /home/pjm/work/play/libexec/`echo $p|sed 's,x,x,'`; \
  else if test -f ./$p; then \
    /usr/bin/install -c -m 755 ./$p \
      /home/pjm/work/play/libexec/`echo $p|sed 's,x,x,'`; \
  else :; fi; fi; \
done
gmake[1]: Leaving directory `/usr/home/pjm/work/play/nana-1.00/gdb'
% export PATH=$PATH:$HOME/work/play/bin
% gmake check
for subdir in src test examples doc man gdb; do		\
  target=`echo check-recursive | sed s/-recursive//`; \
  echo making $target in $subdir;	\
  (cd $subdir && gmake $target)	\
   || case "" in *k*) fail=yes;; *) exit 1;; esac; \
done && test -z "$fail"
making check in src
gmake[1]: Entering directory `/usr/home/pjm/work/play/nana-1.00/src'
gmake[1]: Nothing to be done for `check'.
gmake[1]: Leaving directory `/usr/home/pjm/work/play/nana-1.00/src'
making check in test
gmake[1]: Entering directory `/usr/home/pjm/work/play/nana-1.00/test'
gcc -c -I. -I.    -I../src -O selftest.c
gcc  -o selftest selftest.o  
gcc -c -I. -I.    -I../src -O Q.c
gcc  -o Q Q.o  
gcc -c -I. -I.    -I../src -O I.c
gcc  -o I I.o  
gcc -c -I. -I.    -I../src -O L.c
gcc  -o L L.o  
gcc -c -I. -I.    -I../src -O Iok.c
gcc  -o Iok Iok.o ../src/libnana.a 
gcc -c -I. -I.    -I../src -O Ifail.c
gcc  -o Ifail Ifail.o ../src/libnana.a 
gcc -c -I. -I.    -I../src -O DI.c
gcc  -o DI DI.o  
gcc -c -I. -I.    -I../src -O manyDL.c
gcc  -o manyDL manyDL.o  
gcc -c -I. -I.    -I../src -O DS.c
gcc  -o DS DS.o  
gcc -c -I. -I.    -I../src -O DL.c
gcc  -o DL DL.o  
gcc -c -I. -I.    -I../src -O Ltime.c
gcc  -o Ltime Ltime.o ../src/libnana.a 
gcc -c -I. -I.    -I../src -O now.c
gcc  -o now now.o ../src/libnana.a 
Mon Apr 21 19:18:16 CST 1997
Using "nana-1.00"
i386-unknown-freebsd2.2.1
gcc-2.7.2.1
GDB 4.16 (i386-unknown-freebsd), Copyright 1996 Free Software Foundation, Inc.
FreeBSD chingiz.cs.ntu.edu.au 2.2.1-RELEASE FreeBSD 2.2.1-RELEASE #0: Sun Apr 20 21:48:57 CST 1997     root@chingiz.cs.ntu.edu.au:/usr/src/sys/compile/CHINGIZ  i386
pjm

checking selftest.c using gcc -g
ok: * selftest.c: testing the testers selftest.c:36 
ok: *  each of the following pairs of tests should pass+fail selftest.c:38 
ok: CHECK(printf("hello"),hello) selftest.c:40 
fail: CHECK(printf("hello*"),hello) selftest.c:41 
ok: CHECKEMPTY() selftest.c:43 
fail: CHECKEMPTY(putchar('a')) selftest.c:44 
ok: CHECKFAIL(printf("fail")) selftest.c:46 
fail: CHECKFAIL(printf("fail*")) selftest.c:47 
ok: *  pattern of two ok followed by two fails selftest.c:49 
ok: CHECKTRUE(1==1) selftest.c:51 
ok: CHECKTRUE(1==1) selftest.c:51 
fail: CHECKTRUE(1==0) selftest.c:52 
fail: CHECKTRUE(1==0) selftest.c:52 
ok: CHECKFALSE(1==0) selftest.c:54 
ok: CHECKFALSE(1==0) selftest.c:54 
fail: CHECKFALSE(1==1) selftest.c:55 
fail: CHECKFALSE(1==1) selftest.c:55 
Error 7 failures, 10 successes selftest.c 
checking selftest.c using gcc -g -O
ok: * selftest.c: testing the testers selftest.c:36 
ok: *  each of the following pairs of tests should pass+fail selftest.c:38 
ok: CHECK(printf("hello"),hello) selftest.c:40 
fail: CHECK(printf("hello*"),hello) selftest.c:41 
ok: CHECKEMPTY() selftest.c:43 
fail: CHECKEMPTY(putchar('a')) selftest.c:44 
ok: CHECKFAIL(printf("fail")) selftest.c:46 
fail: CHECKFAIL(printf("fail*")) selftest.c:47 
ok: *  pattern of two ok followed by two fails selftest.c:49 
ok: CHECKTRUE(1==1) selftest.c:51 
ok: CHECKTRUE(1==1) selftest.c:51 
fail: CHECKTRUE(1==0) selftest.c:52 
fail: CHECKTRUE(1==0) selftest.c:52 
ok: CHECKFALSE(1==0) selftest.c:54 
ok: CHECKFALSE(1==0) selftest.c:54 
fail: CHECKFALSE(1==1) selftest.c:55 
fail: CHECKFALSE(1==1) selftest.c:55 
Error 7 failures, 10 successes selftest.c -O
checking selftest.c using gcc -g -O2
ok: * selftest.c: testing the testers selftest.c:36 
ok: *  each of the following pairs of tests should pass+fail selftest.c:38 
ok: CHECK(printf("hello"),hello) selftest.c:40 
fail: CHECK(printf("hello*"),hello) selftest.c:41 
ok: CHECKEMPTY() selftest.c:43 
fail: CHECKEMPTY(putchar('a')) selftest.c:44 
ok: CHECKFAIL(printf("fail")) selftest.c:46 
fail: CHECKFAIL(printf("fail*")) selftest.c:47 
ok: *  pattern of two ok followed by two fails selftest.c:49 
ok: CHECKTRUE(1==1) selftest.c:51 
ok: CHECKTRUE(1==1) selftest.c:51 
fail: CHECKTRUE(1==0) selftest.c:52 
fail: CHECKTRUE(1==0) selftest.c:52 
ok: CHECKFALSE(1==0) selftest.c:54 
ok: CHECKFALSE(1==0) selftest.c:54 
fail: CHECKFALSE(1==1) selftest.c:55 
fail: CHECKFALSE(1==1) selftest.c:55 
Error 7 failures, 10 successes selftest.c -O2
checking selftest.c using gcc -g -O3
ok: * selftest.c: testing the testers selftest.c:36 
ok: *  each of the following pairs of tests should pass+fail selftest.c:38 
ok: CHECK(printf("hello"),hello) selftest.c:40 
fail: CHECK(printf("hello*"),hello) selftest.c:41 
ok: CHECKEMPTY() selftest.c:43 
fail: CHECKEMPTY(putchar('a')) selftest.c:44 
ok: CHECKFAIL(printf("fail")) selftest.c:46 
fail: CHECKFAIL(printf("fail*")) selftest.c:47 
ok: *  pattern of two ok followed by two fails selftest.c:49 
ok: CHECKTRUE(1==1) selftest.c:51 
ok: CHECKTRUE(1==1) selftest.c:51 
fail: CHECKTRUE(1==0) selftest.c:52 
fail: CHECKTRUE(1==0) selftest.c:52 
ok: CHECKFALSE(1==0) selftest.c:54 
ok: CHECKFALSE(1==0) selftest.c:54 
fail: CHECKFALSE(1==1) selftest.c:55 
fail: CHECKFALSE(1==1) selftest.c:55 
Error 7 failures, 10 successes selftest.c -O3
checking Q.c using gcc -g
ok: * * Q.h tests Q.c:61 
ok: * ** basic tests for each routine Q.c:63 
ok: CHECKTRUE(A(int i = 0, i < N, i++, v[i] == i)) Q.c:65 
ok: CHECKTRUE(A(int i = 0, i < N, i++, v[i] == i)) Q.c:65 
ok: CHECKFALSE(A(int i = 0, i < N, i++, v[i] > i)) Q.c:66 
ok: CHECKFALSE(A(int i = 0, i < N, i++, v[i] > i)) Q.c:66 
ok: CHECKTRUE(E(int i = 0, i < N, i++, v[i] == 4)) Q.c:68 
ok: CHECKTRUE(E(int i = 0, i < N, i++, v[i] == 4)) Q.c:68 
ok: CHECKTRUE(E(int i = 0, i < N, i++, v[i] == 0)) Q.c:69 
ok: CHECKTRUE(E(int i = 0, i < N, i++, v[i] == 0)) Q.c:69 
ok: CHECKTRUE(E(int i = 0, i < N, i++, v[i] == 1)) Q.c:70 
ok: CHECKTRUE(E(int i = 0, i < N, i++, v[i] == 1)) Q.c:70 
ok: CHECKFALSE(E(int i = 0, i < N, i++, v[i] == 5)) Q.c:72 
ok: CHECKFALSE(E(int i = 0, i < N, i++, v[i] == 5)) Q.c:72 
ok: CHECKFALSE(E(int i = 0, i < N, i++, v[i] == -1)) Q.c:73 
ok: CHECKFALSE(E(int i = 0, i < N, i++, v[i] == -1)) Q.c:73 
ok: CHECKFALSE(E(int i = 0, i < N, i++, v[i] > i)) Q.c:74 
ok: CHECKFALSE(E(int i = 0, i < N, i++, v[i] > i)) Q.c:74 
ok: CHECKTRUE(C(int i = 0, i < N, i++, 1) == N) Q.c:76 
ok: CHECKTRUE(C(int i = 0, i < N, i++, 1) == N) Q.c:76 
ok: CHECKTRUE(C(int i = 0, i < N, i++, v[i] == 0) == 1) Q.c:77 
ok: CHECKTRUE(C(int i = 0, i < N, i++, v[i] == 0) == 1) Q.c:77 
ok: CHECKTRUE(C(int i = 0, i < N, i++, v[i] == 4) == 1) Q.c:78 
ok: CHECKTRUE(C(int i = 0, i < N, i++, v[i] == 4) == 1) Q.c:78 
ok: CHECKTRUE(C(int i = 0, i < N, i++, v[i] == 5) == 0) Q.c:79 
ok: CHECKTRUE(C(int i = 0, i < N, i++, v[i] == 5) == 0) Q.c:79 
ok: CHECKTRUE(E1(int i = 0, i < N, i++, v[i] == 4)) Q.c:81 
ok: CHECKTRUE(E1(int i = 0, i < N, i++, v[i] == 4)) Q.c:81 
ok: CHECKTRUE(E1(int i = 0, i < N, i++, v[i] == 0)) Q.c:82 
ok: CHECKTRUE(E1(int i = 0, i < N, i++, v[i] == 0)) Q.c:82 
ok: CHECKTRUE(E1(int i = 0, i < N, i++, v[i] == 1)) Q.c:83 
ok: CHECKTRUE(E1(int i = 0, i < N, i++, v[i] == 1)) Q.c:83 
ok: CHECKFALSE(E1(int i = 0, i < N, i++, v[i] > 4)) Q.c:85 
ok: CHECKFALSE(E1(int i = 0, i < N, i++, v[i] > 4)) Q.c:85 
ok: CHECKFALSE(E1(int i = 0, i < N, i++, v[i] == -1)) Q.c:86 
ok: CHECKFALSE(E1(int i = 0, i < N, i++, v[i] == -1)) Q.c:86 
ok: CHECKFALSE(E1(int i = 0, i < N, i++, v[i] == i)) Q.c:87 
ok: CHECKFALSE(E1(int i = 0, i < N, i++, v[i] == i)) Q.c:87 
ok: CHECKTRUE(S(int i = 0, i < N, i++, v[i]) == 10) Q.c:89 
ok: CHECKTRUE(S(int i = 0, i < N, i++, v[i]) == 10) Q.c:89 
ok: CHECKTRUE(S(int i = 0, i < 0, i++, v[i]) == 0) Q.c:90 
ok: CHECKTRUE(S(int i = 0, i < 0, i++, v[i]) == 0) Q.c:90 
ok: CHECKTRUE(S(int i = 0, i < N, i++, fv[i]) == fvsum) Q.c:92 
ok: CHECKTRUE(S(int i = 0, i < N, i++, fv[i]) == fvsum) Q.c:92 
ok: CHECKTRUE(S(int i = 0, i < 0, i++, fv[i]) == 0.0) Q.c:93 
ok: CHECKTRUE(S(int i = 0, i < 0, i++, fv[i]) == 0.0) Q.c:93 
ok: CHECKTRUE(P(int i = 1, i < N, i++, v[i]) == 24) Q.c:95 
ok: CHECKTRUE(P(int i = 1, i < N, i++, v[i]) == 24) Q.c:95 
ok: CHECKTRUE(P(int i = 1, i < 0, i++, v[i]) == 1) Q.c:96 
ok: CHECKTRUE(P(int i = 1, i < 0, i++, v[i]) == 1) Q.c:96 
ok: CHECKTRUE(P(int i = 0, i < N, i++, fv[i]) == fvprod) Q.c:98 
ok: CHECKTRUE(P(int i = 0, i < N, i++, fv[i]) == fvprod) Q.c:98 
ok: CHECKTRUE(P(int i = 0, i < 0, i++, fv[i]) == 1.0) Q.c:99 
ok: CHECKTRUE(P(int i = 0, i < 0, i++, fv[i]) == 1.0) Q.c:99 
ok: * ** check out nesting of operations Q.c:102 
ok: CHECKTRUE(A(int i = 0, i < N, i++, A(int j = 0, j < N, j++, m[i][j] == ((i == j) ? 1 : 0)))) Q.c:106 
ok: CHECKTRUE(A(int i = 0, i < N, i++, A(int j = 0, j < N, j++, m[i][j] == ((i == j) ? 1 : 0)))) Q.c:106 
ok: CHECKFALSE(A(int i = 0, i < N, i++, A(int j = 0, j < N, j++, m[i][j] == 0))) Q.c:110 
ok: CHECKFALSE(A(int i = 0, i < N, i++, A(int j = 0, j < N, j++, m[i][j] == 0))) Q.c:110 
ok: CHECKTRUE(A(int i = 0, i < N, i++, E(int j = 0, j < N, j++, m[i][j] == 1))) Q.c:114 
ok: CHECKTRUE(A(int i = 0, i < N, i++, E(int j = 0, j < N, j++, m[i][j] == 1))) Q.c:114 
ok: CHECKFALSE(E(int i = 0, i < N, i++, E(int j = 0, j < N, j++, m[i][j] == 2))) Q.c:118 
ok: CHECKFALSE(E(int i = 0, i < N, i++, E(int j = 0, j < N, j++, m[i][j] == 2))) Q.c:118 
ok: CHECKTRUE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 1))) Q.c:122 
ok: CHECKTRUE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 1))) Q.c:122 
ok: CHECKFALSE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 2))) Q.c:126 
ok: CHECKFALSE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 2))) Q.c:126 
ok: CHECKFALSE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 0))) Q.c:130 
ok: CHECKFALSE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 0))) Q.c:130 
ok: CHECKFALSE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 4))) Q.c:134 
ok: CHECKFALSE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 4))) Q.c:134 
ok: CHECKTRUE(S(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j])) == N) Q.c:137 
ok: CHECKTRUE(S(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j])) == N) Q.c:137 
ok: CHECKTRUE(P(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j])) == 1) Q.c:140 
ok: CHECKTRUE(P(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j])) == 1) Q.c:140 
ok: CHECKTRUE(C(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j]) == 1) == N) Q.c:143 
ok: CHECKTRUE(C(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j]) == 1) == N) Q.c:143 
ok: CHECKTRUE(C(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j]) == 2) == 0) Q.c:146 
ok: CHECKTRUE(C(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j]) == 2) == 0) Q.c:146 
ok: CHECKTRUE(A(int i = 0, i < N, i++, C(int j = 0, j < N, j++, m[i][j] == 1))) Q.c:149 
ok: CHECKTRUE(A(int i = 0, i < N, i++, C(int j = 0, j < N, j++, m[i][j] == 1))) Q.c:149 
ok: * ** test A(..)||E(..) Q.c:151 
ok: CHECKTRUE(T && T) Q.c:156 
ok: CHECKTRUE(T && T) Q.c:156 
ok: CHECKTRUE(T && 1) Q.c:157 
ok: CHECKTRUE(T && 1) Q.c:157 
ok: CHECKTRUE(!(F) && T) Q.c:158 
ok: CHECKTRUE(!(F) && T) Q.c:158 
ok: CHECKTRUE(F || T) Q.c:159 
ok: CHECKTRUE(F || T) Q.c:159 
ok: CHECKTRUE(F || 1) Q.c:160 
ok: CHECKTRUE(F || 1) Q.c:160 
ok: CHECKTRUE(T || 1) Q.c:161 
ok: CHECKTRUE(T || 1) Q.c:161 
ok: CHECKTRUE(T && T && T && (!(F)) && 1) Q.c:162 
ok: CHECKTRUE(T && T && T && (!(F)) && 1) Q.c:162 
ok: CHECKTRUE(T && T && T && T && T && (T || F)) Q.c:163 
ok: CHECKTRUE(T && T && T && T && T && (T || F)) Q.c:163 
ok: CHECKFALSE(F && T) Q.c:165 
ok: CHECKFALSE(F && T) Q.c:165 
ok: CHECKFALSE(T && F) Q.c:166 
ok: CHECKFALSE(T && F) Q.c:166 
ok: CHECKFALSE(T && 0) Q.c:167 
ok: CHECKFALSE(T && 0) Q.c:167 
ok: CHECKFALSE(!(F) && F) Q.c:168 
ok: CHECKFALSE(!(F) && F) Q.c:168 
ok: CHECKFALSE(F ? T : 0) Q.c:169 
ok: CHECKFALSE(F ? T : 0) Q.c:169 
ok: CHECKFALSE(F && F) Q.c:170 
ok: CHECKFALSE(F && F) Q.c:170 
ok: CHECKFALSE(F || F) Q.c:171 
ok: CHECKFALSE(F || F) Q.c:171 
ok: CHECKFALSE(T && T && T && F && 1) Q.c:172 
ok: CHECKFALSE(T && T && T && F && 1) Q.c:172 
ok: CHECKFALSE(T && T && T && F) Q.c:173 
ok: CHECKFALSE(T && T && T && F) Q.c:173 
Passed 116 tests completed successfully Q.c 
checking Q.c using gcc -g -O
ok: * * Q.h tests Q.c:61 
ok: * ** basic tests for each routine Q.c:63 
ok: CHECKTRUE(A(int i = 0, i < N, i++, v[i] == i)) Q.c:65 
ok: CHECKTRUE(A(int i = 0, i < N, i++, v[i] == i)) Q.c:65 
ok: CHECKFALSE(A(int i = 0, i < N, i++, v[i] > i)) Q.c:66 
ok: CHECKFALSE(A(int i = 0, i < N, i++, v[i] > i)) Q.c:66 
ok: CHECKTRUE(E(int i = 0, i < N, i++, v[i] == 4)) Q.c:68 
ok: CHECKTRUE(E(int i = 0, i < N, i++, v[i] == 4)) Q.c:68 
ok: CHECKTRUE(E(int i = 0, i < N, i++, v[i] == 0)) Q.c:69 
ok: CHECKTRUE(E(int i = 0, i < N, i++, v[i] == 0)) Q.c:69 
ok: CHECKTRUE(E(int i = 0, i < N, i++, v[i] == 1)) Q.c:70 
ok: CHECKTRUE(E(int i = 0, i < N, i++, v[i] == 1)) Q.c:70 
ok: CHECKFALSE(E(int i = 0, i < N, i++, v[i] == 5)) Q.c:72 
ok: CHECKFALSE(E(int i = 0, i < N, i++, v[i] == 5)) Q.c:72 
ok: CHECKFALSE(E(int i = 0, i < N, i++, v[i] == -1)) Q.c:73 
ok: CHECKFALSE(E(int i = 0, i < N, i++, v[i] == -1)) Q.c:73 
ok: CHECKFALSE(E(int i = 0, i < N, i++, v[i] > i)) Q.c:74 
ok: CHECKFALSE(E(int i = 0, i < N, i++, v[i] > i)) Q.c:74 
ok: CHECKTRUE(C(int i = 0, i < N, i++, 1) == N) Q.c:76 
ok: CHECKTRUE(C(int i = 0, i < N, i++, 1) == N) Q.c:76 
ok: CHECKTRUE(C(int i = 0, i < N, i++, v[i] == 0) == 1) Q.c:77 
ok: CHECKTRUE(C(int i = 0, i < N, i++, v[i] == 0) == 1) Q.c:77 
ok: CHECKTRUE(C(int i = 0, i < N, i++, v[i] == 4) == 1) Q.c:78 
ok: CHECKTRUE(C(int i = 0, i < N, i++, v[i] == 4) == 1) Q.c:78 
ok: CHECKTRUE(C(int i = 0, i < N, i++, v[i] == 5) == 0) Q.c:79 
ok: CHECKTRUE(C(int i = 0, i < N, i++, v[i] == 5) == 0) Q.c:79 
ok: CHECKTRUE(E1(int i = 0, i < N, i++, v[i] == 4)) Q.c:81 
ok: CHECKTRUE(E1(int i = 0, i < N, i++, v[i] == 4)) Q.c:81 
ok: CHECKTRUE(E1(int i = 0, i < N, i++, v[i] == 0)) Q.c:82 
ok: CHECKTRUE(E1(int i = 0, i < N, i++, v[i] == 0)) Q.c:82 
ok: CHECKTRUE(E1(int i = 0, i < N, i++, v[i] == 1)) Q.c:83 
ok: CHECKTRUE(E1(int i = 0, i < N, i++, v[i] == 1)) Q.c:83 
ok: CHECKFALSE(E1(int i = 0, i < N, i++, v[i] > 4)) Q.c:85 
ok: CHECKFALSE(E1(int i = 0, i < N, i++, v[i] > 4)) Q.c:85 
ok: CHECKFALSE(E1(int i = 0, i < N, i++, v[i] == -1)) Q.c:86 
ok: CHECKFALSE(E1(int i = 0, i < N, i++, v[i] == -1)) Q.c:86 
ok: CHECKFALSE(E1(int i = 0, i < N, i++, v[i] == i)) Q.c:87 
ok: CHECKFALSE(E1(int i = 0, i < N, i++, v[i] == i)) Q.c:87 
ok: CHECKTRUE(S(int i = 0, i < N, i++, v[i]) == 10) Q.c:89 
ok: CHECKTRUE(S(int i = 0, i < N, i++, v[i]) == 10) Q.c:89 
ok: CHECKTRUE(S(int i = 0, i < 0, i++, v[i]) == 0) Q.c:90 
ok: CHECKTRUE(S(int i = 0, i < 0, i++, v[i]) == 0) Q.c:90 
ok: CHECKTRUE(S(int i = 0, i < N, i++, fv[i]) == fvsum) Q.c:92 
ok: CHECKTRUE(S(int i = 0, i < N, i++, fv[i]) == fvsum) Q.c:92 
ok: CHECKTRUE(S(int i = 0, i < 0, i++, fv[i]) == 0.0) Q.c:93 
ok: CHECKTRUE(S(int i = 0, i < 0, i++, fv[i]) == 0.0) Q.c:93 
ok: CHECKTRUE(P(int i = 1, i < N, i++, v[i]) == 24) Q.c:95 
ok: CHECKTRUE(P(int i = 1, i < N, i++, v[i]) == 24) Q.c:95 
ok: CHECKTRUE(P(int i = 1, i < 0, i++, v[i]) == 1) Q.c:96 
ok: CHECKTRUE(P(int i = 1, i < 0, i++, v[i]) == 1) Q.c:96 
ok: CHECKTRUE(P(int i = 0, i < N, i++, fv[i]) == fvprod) Q.c:98 
ok: CHECKTRUE(P(int i = 0, i < N, i++, fv[i]) == fvprod) Q.c:98 
ok: CHECKTRUE(P(int i = 0, i < 0, i++, fv[i]) == 1.0) Q.c:99 
ok: CHECKTRUE(P(int i = 0, i < 0, i++, fv[i]) == 1.0) Q.c:99 
ok: * ** check out nesting of operations Q.c:102 
ok: CHECKTRUE(A(int i = 0, i < N, i++, A(int j = 0, j < N, j++, m[i][j] == ((i == j) ? 1 : 0)))) Q.c:106 
ok: CHECKTRUE(A(int i = 0, i < N, i++, A(int j = 0, j < N, j++, m[i][j] == ((i == j) ? 1 : 0)))) Q.c:106 
ok: CHECKFALSE(A(int i = 0, i < N, i++, A(int j = 0, j < N, j++, m[i][j] == 0))) Q.c:110 
ok: CHECKFALSE(A(int i = 0, i < N, i++, A(int j = 0, j < N, j++, m[i][j] == 0))) Q.c:110 
ok: CHECKTRUE(A(int i = 0, i < N, i++, E(int j = 0, j < N, j++, m[i][j] == 1))) Q.c:114 
ok: CHECKTRUE(A(int i = 0, i < N, i++, E(int j = 0, j < N, j++, m[i][j] == 1))) Q.c:114 
ok: CHECKFALSE(E(int i = 0, i < N, i++, E(int j = 0, j < N, j++, m[i][j] == 2))) Q.c:118 
ok: CHECKFALSE(E(int i = 0, i < N, i++, E(int j = 0, j < N, j++, m[i][j] == 2))) Q.c:118 
ok: CHECKTRUE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 1))) Q.c:122 
ok: CHECKTRUE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 1))) Q.c:122 
ok: CHECKFALSE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 2))) Q.c:126 
ok: CHECKFALSE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 2))) Q.c:126 
ok: CHECKFALSE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 0))) Q.c:130 
ok: CHECKFALSE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 0))) Q.c:130 
ok: CHECKFALSE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 4))) Q.c:134 
ok: CHECKFALSE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 4))) Q.c:134 
ok: CHECKTRUE(S(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j])) == N) Q.c:137 
ok: CHECKTRUE(S(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j])) == N) Q.c:137 
ok: CHECKTRUE(P(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j])) == 1) Q.c:140 
ok: CHECKTRUE(P(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j])) == 1) Q.c:140 
ok: CHECKTRUE(C(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j]) == 1) == N) Q.c:143 
ok: CHECKTRUE(C(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j]) == 1) == N) Q.c:143 
ok: CHECKTRUE(C(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j]) == 2) == 0) Q.c:146 
ok: CHECKTRUE(C(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j]) == 2) == 0) Q.c:146 
ok: CHECKTRUE(A(int i = 0, i < N, i++, C(int j = 0, j < N, j++, m[i][j] == 1))) Q.c:149 
ok: CHECKTRUE(A(int i = 0, i < N, i++, C(int j = 0, j < N, j++, m[i][j] == 1))) Q.c:149 
ok: * ** test A(..)||E(..) Q.c:151 
ok: CHECKTRUE(T && T) Q.c:156 
ok: CHECKTRUE(T && T) Q.c:156 
ok: CHECKTRUE(T && 1) Q.c:157 
ok: CHECKTRUE(T && 1) Q.c:157 
ok: CHECKTRUE(!(F) && T) Q.c:158 
ok: CHECKTRUE(!(F) && T) Q.c:158 
ok: CHECKTRUE(F || T) Q.c:159 
ok: CHECKTRUE(F || T) Q.c:159 
ok: CHECKTRUE(F || 1) Q.c:160 
ok: CHECKTRUE(F || 1) Q.c:160 
ok: CHECKTRUE(T || 1) Q.c:161 
ok: CHECKTRUE(T || 1) Q.c:161 
ok: CHECKTRUE(T && T && T && (!(F)) && 1) Q.c:162 
ok: CHECKTRUE(T && T && T && (!(F)) && 1) Q.c:162 
ok: CHECKTRUE(T && T && T && T && T && (T || F)) Q.c:163 
ok: CHECKTRUE(T && T && T && T && T && (T || F)) Q.c:163 
ok: CHECKFALSE(F && T) Q.c:165 
ok: CHECKFALSE(F && T) Q.c:165 
ok: CHECKFALSE(T && F) Q.c:166 
ok: CHECKFALSE(T && F) Q.c:166 
ok: CHECKFALSE(T && 0) Q.c:167 
ok: CHECKFALSE(T && 0) Q.c:167 
ok: CHECKFALSE(!(F) && F) Q.c:168 
ok: CHECKFALSE(!(F) && F) Q.c:168 
ok: CHECKFALSE(F ? T : 0) Q.c:169 
ok: CHECKFALSE(F ? T : 0) Q.c:169 
ok: CHECKFALSE(F && F) Q.c:170 
ok: CHECKFALSE(F && F) Q.c:170 
ok: CHECKFALSE(F || F) Q.c:171 
ok: CHECKFALSE(F || F) Q.c:171 
ok: CHECKFALSE(T && T && T && F && 1) Q.c:172 
ok: CHECKFALSE(T && T && T && F && 1) Q.c:172 
ok: CHECKFALSE(T && T && T && F) Q.c:173 
ok: CHECKFALSE(T && T && T && F) Q.c:173 
Passed 116 tests completed successfully Q.c -O
checking Q.c using gcc -g -O2
ok: * * Q.h tests Q.c:61 
ok: * ** basic tests for each routine Q.c:63 
ok: CHECKTRUE(A(int i = 0, i < N, i++, v[i] == i)) Q.c:65 
ok: CHECKTRUE(A(int i = 0, i < N, i++, v[i] == i)) Q.c:65 
ok: CHECKFALSE(A(int i = 0, i < N, i++, v[i] > i)) Q.c:66 
ok: CHECKFALSE(A(int i = 0, i < N, i++, v[i] > i)) Q.c:66 
ok: CHECKTRUE(E(int i = 0, i < N, i++, v[i] == 4)) Q.c:68 
ok: CHECKTRUE(E(int i = 0, i < N, i++, v[i] == 4)) Q.c:68 
ok: CHECKTRUE(E(int i = 0, i < N, i++, v[i] == 0)) Q.c:69 
ok: CHECKTRUE(E(int i = 0, i < N, i++, v[i] == 0)) Q.c:69 
ok: CHECKTRUE(E(int i = 0, i < N, i++, v[i] == 1)) Q.c:70 
ok: CHECKTRUE(E(int i = 0, i < N, i++, v[i] == 1)) Q.c:70 
ok: CHECKFALSE(E(int i = 0, i < N, i++, v[i] == 5)) Q.c:72 
ok: CHECKFALSE(E(int i = 0, i < N, i++, v[i] == 5)) Q.c:72 
ok: CHECKFALSE(E(int i = 0, i < N, i++, v[i] == -1)) Q.c:73 
ok: CHECKFALSE(E(int i = 0, i < N, i++, v[i] == -1)) Q.c:73 
ok: CHECKFALSE(E(int i = 0, i < N, i++, v[i] > i)) Q.c:74 
ok: CHECKFALSE(E(int i = 0, i < N, i++, v[i] > i)) Q.c:74 
ok: CHECKTRUE(C(int i = 0, i < N, i++, 1) == N) Q.c:76 
ok: CHECKTRUE(C(int i = 0, i < N, i++, 1) == N) Q.c:76 
ok: CHECKTRUE(C(int i = 0, i < N, i++, v[i] == 0) == 1) Q.c:77 
ok: CHECKTRUE(C(int i = 0, i < N, i++, v[i] == 0) == 1) Q.c:77 
ok: CHECKTRUE(C(int i = 0, i < N, i++, v[i] == 4) == 1) Q.c:78 
ok: CHECKTRUE(C(int i = 0, i < N, i++, v[i] == 4) == 1) Q.c:78 
ok: CHECKTRUE(C(int i = 0, i < N, i++, v[i] == 5) == 0) Q.c:79 
ok: CHECKTRUE(C(int i = 0, i < N, i++, v[i] == 5) == 0) Q.c:79 
ok: CHECKTRUE(E1(int i = 0, i < N, i++, v[i] == 4)) Q.c:81 
ok: CHECKTRUE(E1(int i = 0, i < N, i++, v[i] == 4)) Q.c:81 
ok: CHECKTRUE(E1(int i = 0, i < N, i++, v[i] == 0)) Q.c:82 
ok: CHECKTRUE(E1(int i = 0, i < N, i++, v[i] == 0)) Q.c:82 
ok: CHECKTRUE(E1(int i = 0, i < N, i++, v[i] == 1)) Q.c:83 
ok: CHECKTRUE(E1(int i = 0, i < N, i++, v[i] == 1)) Q.c:83 
ok: CHECKFALSE(E1(int i = 0, i < N, i++, v[i] > 4)) Q.c:85 
ok: CHECKFALSE(E1(int i = 0, i < N, i++, v[i] > 4)) Q.c:85 
ok: CHECKFALSE(E1(int i = 0, i < N, i++, v[i] == -1)) Q.c:86 
ok: CHECKFALSE(E1(int i = 0, i < N, i++, v[i] == -1)) Q.c:86 
ok: CHECKFALSE(E1(int i = 0, i < N, i++, v[i] == i)) Q.c:87 
ok: CHECKFALSE(E1(int i = 0, i < N, i++, v[i] == i)) Q.c:87 
ok: CHECKTRUE(S(int i = 0, i < N, i++, v[i]) == 10) Q.c:89 
ok: CHECKTRUE(S(int i = 0, i < N, i++, v[i]) == 10) Q.c:89 
ok: CHECKTRUE(S(int i = 0, i < 0, i++, v[i]) == 0) Q.c:90 
ok: CHECKTRUE(S(int i = 0, i < 0, i++, v[i]) == 0) Q.c:90 
ok: CHECKTRUE(S(int i = 0, i < N, i++, fv[i]) == fvsum) Q.c:92 
ok: CHECKTRUE(S(int i = 0, i < N, i++, fv[i]) == fvsum) Q.c:92 
ok: CHECKTRUE(S(int i = 0, i < 0, i++, fv[i]) == 0.0) Q.c:93 
ok: CHECKTRUE(S(int i = 0, i < 0, i++, fv[i]) == 0.0) Q.c:93 
ok: CHECKTRUE(P(int i = 1, i < N, i++, v[i]) == 24) Q.c:95 
ok: CHECKTRUE(P(int i = 1, i < N, i++, v[i]) == 24) Q.c:95 
ok: CHECKTRUE(P(int i = 1, i < 0, i++, v[i]) == 1) Q.c:96 
ok: CHECKTRUE(P(int i = 1, i < 0, i++, v[i]) == 1) Q.c:96 
ok: CHECKTRUE(P(int i = 0, i < N, i++, fv[i]) == fvprod) Q.c:98 
ok: CHECKTRUE(P(int i = 0, i < N, i++, fv[i]) == fvprod) Q.c:98 
ok: CHECKTRUE(P(int i = 0, i < 0, i++, fv[i]) == 1.0) Q.c:99 
ok: CHECKTRUE(P(int i = 0, i < 0, i++, fv[i]) == 1.0) Q.c:99 
ok: * ** check out nesting of operations Q.c:102 
ok: CHECKTRUE(A(int i = 0, i < N, i++, A(int j = 0, j < N, j++, m[i][j] == ((i == j) ? 1 : 0)))) Q.c:106 
ok: CHECKTRUE(A(int i = 0, i < N, i++, A(int j = 0, j < N, j++, m[i][j] == ((i == j) ? 1 : 0)))) Q.c:106 
ok: CHECKFALSE(A(int i = 0, i < N, i++, A(int j = 0, j < N, j++, m[i][j] == 0))) Q.c:110 
ok: CHECKFALSE(A(int i = 0, i < N, i++, A(int j = 0, j < N, j++, m[i][j] == 0))) Q.c:110 
ok: CHECKTRUE(A(int i = 0, i < N, i++, E(int j = 0, j < N, j++, m[i][j] == 1))) Q.c:114 
ok: CHECKTRUE(A(int i = 0, i < N, i++, E(int j = 0, j < N, j++, m[i][j] == 1))) Q.c:114 
ok: CHECKFALSE(E(int i = 0, i < N, i++, E(int j = 0, j < N, j++, m[i][j] == 2))) Q.c:118 
ok: CHECKFALSE(E(int i = 0, i < N, i++, E(int j = 0, j < N, j++, m[i][j] == 2))) Q.c:118 
ok: CHECKTRUE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 1))) Q.c:122 
ok: CHECKTRUE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 1))) Q.c:122 
ok: CHECKFALSE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 2))) Q.c:126 
ok: CHECKFALSE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 2))) Q.c:126 
ok: CHECKFALSE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 0))) Q.c:130 
ok: CHECKFALSE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 0))) Q.c:130 
ok: CHECKFALSE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 4))) Q.c:134 
ok: CHECKFALSE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 4))) Q.c:134 
ok: CHECKTRUE(S(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j])) == N) Q.c:137 
ok: CHECKTRUE(S(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j])) == N) Q.c:137 
ok: CHECKTRUE(P(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j])) == 1) Q.c:140 
ok: CHECKTRUE(P(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j])) == 1) Q.c:140 
ok: CHECKTRUE(C(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j]) == 1) == N) Q.c:143 
ok: CHECKTRUE(C(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j]) == 1) == N) Q.c:143 
ok: CHECKTRUE(C(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j]) == 2) == 0) Q.c:146 
ok: CHECKTRUE(C(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j]) == 2) == 0) Q.c:146 
ok: CHECKTRUE(A(int i = 0, i < N, i++, C(int j = 0, j < N, j++, m[i][j] == 1))) Q.c:149 
ok: CHECKTRUE(A(int i = 0, i < N, i++, C(int j = 0, j < N, j++, m[i][j] == 1))) Q.c:149 
ok: * ** test A(..)||E(..) Q.c:151 
ok: CHECKTRUE(T && T) Q.c:156 
ok: CHECKTRUE(T && T) Q.c:156 
ok: CHECKTRUE(T && 1) Q.c:157 
ok: CHECKTRUE(T && 1) Q.c:157 
ok: CHECKTRUE(!(F) && T) Q.c:158 
ok: CHECKTRUE(!(F) && T) Q.c:158 
ok: CHECKTRUE(F || T) Q.c:159 
ok: CHECKTRUE(F || T) Q.c:159 
ok: CHECKTRUE(F || 1) Q.c:160 
ok: CHECKTRUE(F || 1) Q.c:160 
ok: CHECKTRUE(T || 1) Q.c:161 
ok: CHECKTRUE(T || 1) Q.c:161 
ok: CHECKTRUE(T && T && T && (!(F)) && 1) Q.c:162 
ok: CHECKTRUE(T && T && T && (!(F)) && 1) Q.c:162 
ok: CHECKTRUE(T && T && T && T && T && (T || F)) Q.c:163 
ok: CHECKTRUE(T && T && T && T && T && (T || F)) Q.c:163 
ok: CHECKFALSE(F && T) Q.c:165 
ok: CHECKFALSE(F && T) Q.c:165 
ok: CHECKFALSE(T && F) Q.c:166 
ok: CHECKFALSE(T && F) Q.c:166 
ok: CHECKFALSE(T && 0) Q.c:167 
ok: CHECKFALSE(T && 0) Q.c:167 
ok: CHECKFALSE(!(F) && F) Q.c:168 
ok: CHECKFALSE(!(F) && F) Q.c:168 
ok: CHECKFALSE(F ? T : 0) Q.c:169 
ok: CHECKFALSE(F ? T : 0) Q.c:169 
ok: CHECKFALSE(F && F) Q.c:170 
ok: CHECKFALSE(F && F) Q.c:170 
ok: CHECKFALSE(F || F) Q.c:171 
ok: CHECKFALSE(F || F) Q.c:171 
ok: CHECKFALSE(T && T && T && F && 1) Q.c:172 
ok: CHECKFALSE(T && T && T && F && 1) Q.c:172 
ok: CHECKFALSE(T && T && T && F) Q.c:173 
ok: CHECKFALSE(T && T && T && F) Q.c:173 
Passed 116 tests completed successfully Q.c -O2
checking Q.c using gcc -g -O3
ok: * * Q.h tests Q.c:61 
ok: * ** basic tests for each routine Q.c:63 
ok: CHECKTRUE(A(int i = 0, i < N, i++, v[i] == i)) Q.c:65 
ok: CHECKTRUE(A(int i = 0, i < N, i++, v[i] == i)) Q.c:65 
ok: CHECKFALSE(A(int i = 0, i < N, i++, v[i] > i)) Q.c:66 
ok: CHECKFALSE(A(int i = 0, i < N, i++, v[i] > i)) Q.c:66 
ok: CHECKTRUE(E(int i = 0, i < N, i++, v[i] == 4)) Q.c:68 
ok: CHECKTRUE(E(int i = 0, i < N, i++, v[i] == 4)) Q.c:68 
ok: CHECKTRUE(E(int i = 0, i < N, i++, v[i] == 0)) Q.c:69 
ok: CHECKTRUE(E(int i = 0, i < N, i++, v[i] == 0)) Q.c:69 
ok: CHECKTRUE(E(int i = 0, i < N, i++, v[i] == 1)) Q.c:70 
ok: CHECKTRUE(E(int i = 0, i < N, i++, v[i] == 1)) Q.c:70 
ok: CHECKFALSE(E(int i = 0, i < N, i++, v[i] == 5)) Q.c:72 
ok: CHECKFALSE(E(int i = 0, i < N, i++, v[i] == 5)) Q.c:72 
ok: CHECKFALSE(E(int i = 0, i < N, i++, v[i] == -1)) Q.c:73 
ok: CHECKFALSE(E(int i = 0, i < N, i++, v[i] == -1)) Q.c:73 
ok: CHECKFALSE(E(int i = 0, i < N, i++, v[i] > i)) Q.c:74 
ok: CHECKFALSE(E(int i = 0, i < N, i++, v[i] > i)) Q.c:74 
ok: CHECKTRUE(C(int i = 0, i < N, i++, 1) == N) Q.c:76 
ok: CHECKTRUE(C(int i = 0, i < N, i++, 1) == N) Q.c:76 
ok: CHECKTRUE(C(int i = 0, i < N, i++, v[i] == 0) == 1) Q.c:77 
ok: CHECKTRUE(C(int i = 0, i < N, i++, v[i] == 0) == 1) Q.c:77 
ok: CHECKTRUE(C(int i = 0, i < N, i++, v[i] == 4) == 1) Q.c:78 
ok: CHECKTRUE(C(int i = 0, i < N, i++, v[i] == 4) == 1) Q.c:78 
ok: CHECKTRUE(C(int i = 0, i < N, i++, v[i] == 5) == 0) Q.c:79 
ok: CHECKTRUE(C(int i = 0, i < N, i++, v[i] == 5) == 0) Q.c:79 
ok: CHECKTRUE(E1(int i = 0, i < N, i++, v[i] == 4)) Q.c:81 
ok: CHECKTRUE(E1(int i = 0, i < N, i++, v[i] == 4)) Q.c:81 
ok: CHECKTRUE(E1(int i = 0, i < N, i++, v[i] == 0)) Q.c:82 
ok: CHECKTRUE(E1(int i = 0, i < N, i++, v[i] == 0)) Q.c:82 
ok: CHECKTRUE(E1(int i = 0, i < N, i++, v[i] == 1)) Q.c:83 
ok: CHECKTRUE(E1(int i = 0, i < N, i++, v[i] == 1)) Q.c:83 
ok: CHECKFALSE(E1(int i = 0, i < N, i++, v[i] > 4)) Q.c:85 
ok: CHECKFALSE(E1(int i = 0, i < N, i++, v[i] > 4)) Q.c:85 
ok: CHECKFALSE(E1(int i = 0, i < N, i++, v[i] == -1)) Q.c:86 
ok: CHECKFALSE(E1(int i = 0, i < N, i++, v[i] == -1)) Q.c:86 
ok: CHECKFALSE(E1(int i = 0, i < N, i++, v[i] == i)) Q.c:87 
ok: CHECKFALSE(E1(int i = 0, i < N, i++, v[i] == i)) Q.c:87 
ok: CHECKTRUE(S(int i = 0, i < N, i++, v[i]) == 10) Q.c:89 
ok: CHECKTRUE(S(int i = 0, i < N, i++, v[i]) == 10) Q.c:89 
ok: CHECKTRUE(S(int i = 0, i < 0, i++, v[i]) == 0) Q.c:90 
ok: CHECKTRUE(S(int i = 0, i < 0, i++, v[i]) == 0) Q.c:90 
ok: CHECKTRUE(S(int i = 0, i < N, i++, fv[i]) == fvsum) Q.c:92 
ok: CHECKTRUE(S(int i = 0, i < N, i++, fv[i]) == fvsum) Q.c:92 
ok: CHECKTRUE(S(int i = 0, i < 0, i++, fv[i]) == 0.0) Q.c:93 
ok: CHECKTRUE(S(int i = 0, i < 0, i++, fv[i]) == 0.0) Q.c:93 
ok: CHECKTRUE(P(int i = 1, i < N, i++, v[i]) == 24) Q.c:95 
ok: CHECKTRUE(P(int i = 1, i < N, i++, v[i]) == 24) Q.c:95 
ok: CHECKTRUE(P(int i = 1, i < 0, i++, v[i]) == 1) Q.c:96 
ok: CHECKTRUE(P(int i = 1, i < 0, i++, v[i]) == 1) Q.c:96 
ok: CHECKTRUE(P(int i = 0, i < N, i++, fv[i]) == fvprod) Q.c:98 
ok: CHECKTRUE(P(int i = 0, i < N, i++, fv[i]) == fvprod) Q.c:98 
ok: CHECKTRUE(P(int i = 0, i < 0, i++, fv[i]) == 1.0) Q.c:99 
ok: CHECKTRUE(P(int i = 0, i < 0, i++, fv[i]) == 1.0) Q.c:99 
ok: * ** check out nesting of operations Q.c:102 
ok: CHECKTRUE(A(int i = 0, i < N, i++, A(int j = 0, j < N, j++, m[i][j] == ((i == j) ? 1 : 0)))) Q.c:106 
ok: CHECKTRUE(A(int i = 0, i < N, i++, A(int j = 0, j < N, j++, m[i][j] == ((i == j) ? 1 : 0)))) Q.c:106 
ok: CHECKFALSE(A(int i = 0, i < N, i++, A(int j = 0, j < N, j++, m[i][j] == 0))) Q.c:110 
ok: CHECKFALSE(A(int i = 0, i < N, i++, A(int j = 0, j < N, j++, m[i][j] == 0))) Q.c:110 
ok: CHECKTRUE(A(int i = 0, i < N, i++, E(int j = 0, j < N, j++, m[i][j] == 1))) Q.c:114 
ok: CHECKTRUE(A(int i = 0, i < N, i++, E(int j = 0, j < N, j++, m[i][j] == 1))) Q.c:114 
ok: CHECKFALSE(E(int i = 0, i < N, i++, E(int j = 0, j < N, j++, m[i][j] == 2))) Q.c:118 
ok: CHECKFALSE(E(int i = 0, i < N, i++, E(int j = 0, j < N, j++, m[i][j] == 2))) Q.c:118 
ok: CHECKTRUE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 1))) Q.c:122 
ok: CHECKTRUE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 1))) Q.c:122 
ok: CHECKFALSE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 2))) Q.c:126 
ok: CHECKFALSE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 2))) Q.c:126 
ok: CHECKFALSE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 0))) Q.c:130 
ok: CHECKFALSE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 0))) Q.c:130 
ok: CHECKFALSE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 4))) Q.c:134 
ok: CHECKFALSE(A(int i = 0, i < N, i++, E1(int j = 0, j < N, j++, m[i][j] == 4))) Q.c:134 
ok: CHECKTRUE(S(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j])) == N) Q.c:137 
ok: CHECKTRUE(S(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j])) == N) Q.c:137 
ok: CHECKTRUE(P(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j])) == 1) Q.c:140 
ok: CHECKTRUE(P(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j])) == 1) Q.c:140 
ok: CHECKTRUE(C(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j]) == 1) == N) Q.c:143 
ok: CHECKTRUE(C(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j]) == 1) == N) Q.c:143 
ok: CHECKTRUE(C(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j]) == 2) == 0) Q.c:146 
ok: CHECKTRUE(C(int i = 0, i < N, i++, S(int j = 0, j < N, j++, m[i][j]) == 2) == 0) Q.c:146 
ok: CHECKTRUE(A(int i = 0, i < N, i++, C(int j = 0, j < N, j++, m[i][j] == 1))) Q.c:149 
ok: CHECKTRUE(A(int i = 0, i < N, i++, C(int j = 0, j < N, j++, m[i][j] == 1))) Q.c:149 
ok: * ** test A(..)||E(..) Q.c:151 
ok: CHECKTRUE(T && T) Q.c:156 
ok: CHECKTRUE(T && T) Q.c:156 
ok: CHECKTRUE(T && 1) Q.c:157 
ok: CHECKTRUE(T && 1) Q.c:157 
ok: CHECKTRUE(!(F) && T) Q.c:158 
ok: CHECKTRUE(!(F) && T) Q.c:158 
ok: CHECKTRUE(F || T) Q.c:159 
ok: CHECKTRUE(F || T) Q.c:159 
ok: CHECKTRUE(F || 1) Q.c:160 
ok: CHECKTRUE(F || 1) Q.c:160 
ok: CHECKTRUE(T || 1) Q.c:161 
ok: CHECKTRUE(T || 1) Q.c:161 
ok: CHECKTRUE(T && T && T && (!(F)) && 1) Q.c:162 
ok: CHECKTRUE(T && T && T && (!(F)) && 1) Q.c:162 
ok: CHECKTRUE(T && T && T && T && T && (T || F)) Q.c:163 
ok: CHECKTRUE(T && T && T && T && T && (T || F)) Q.c:163 
ok: CHECKFALSE(F && T) Q.c:165 
ok: CHECKFALSE(F && T) Q.c:165 
ok: CHECKFALSE(T && F) Q.c:166 
ok: CHECKFALSE(T && F) Q.c:166 
ok: CHECKFALSE(T && 0) Q.c:167 
ok: CHECKFALSE(T && 0) Q.c:167 
ok: CHECKFALSE(!(F) && F) Q.c:168 
ok: CHECKFALSE(!(F) && F) Q.c:168 
ok: CHECKFALSE(F ? T : 0) Q.c:169 
ok: CHECKFALSE(F ? T : 0) Q.c:169 
ok: CHECKFALSE(F && F) Q.c:170 
ok: CHECKFALSE(F && F) Q.c:170 
ok: CHECKFALSE(F || F) Q.c:171 
ok: CHECKFALSE(F || F) Q.c:171 
ok: CHECKFALSE(T && T && T && F && 1) Q.c:172 
ok: CHECKFALSE(T && T && T && F && 1) Q.c:172 
ok: CHECKFALSE(T && T && T && F) Q.c:173 
ok: CHECKFALSE(T && T && T && F) Q.c:173 
Passed 116 tests completed successfully Q.c -O3
checking I.c using gcc -g
ok: * * I.h tests I.c:64 
ok: CHECKEMPTY(I(0 == 0)) I.c:66 
ok: CHECKFAIL(I(0 == 1)) I.c:67 
ok: CHECKEMPTY(I(1)) I.c:69 
ok: CHECKFAIL(I(0)) I.c:70 
ok: * ** Tests with quantifiers (based on check_Q.c) I.c:72 
ok: CHECKEMPTY(I(A(int i = 0, i < MAX, i++, v[i] == i))) I.c:74 
ok: CHECKFAIL(I(A(int i = 0, i < MAX, i++, v[i] > i))) I.c:75 
ok: CHECKEMPTY(I(E(int i = 0, i < MAX, i++, v[i] == 4))) I.c:77 
ok: CHECKEMPTY(I(E(int i = 0, i < MAX, i++, v[i] == 0))) I.c:78 
ok: CHECKEMPTY(I(E(int i = 0, i < MAX, i++, v[i] == 1))) I.c:79 
ok: CHECKFAIL(I(E(int i = 0, i < MAX, i++, v[i] == 5))) I.c:81 
ok: CHECKFAIL(I(E(int i = 0, i < MAX, i++, v[i] == -1))) I.c:82 
ok: CHECKFAIL(I(E(int i = 0, i < MAX, i++, v[i] > i))) I.c:83 
ok: CHECKEMPTY(I(C(int i = 0, i < MAX, i++, 1) == MAX)) I.c:85 
ok: CHECKEMPTY(I(C(int i = 0, i < MAX, i++, v[i] == 0) == 1)) I.c:86 
ok: CHECKEMPTY(I(C(int i = 0, i < MAX, i++, v[i] == 4) == 1)) I.c:87 
ok: CHECKEMPTY(I(C(int i = 0, i < MAX, i++, v[i] == 5) == 0)) I.c:88 
ok: CHECKEMPTY(I(E1(int i = 0, i < MAX, i++, v[i] == 4))) I.c:90 
ok: CHECKEMPTY(I(E1(int i = 0, i < MAX, i++, v[i] == 0))) I.c:91 
ok: CHECKEMPTY(I(E1(int i = 0, i < MAX, i++, v[i] == 1))) I.c:92 
ok: CHECKFAIL(I(E1(int i = 0, i < MAX, i++, v[i] > 4))) I.c:94 
ok: CHECKFAIL(I(E1(int i = 0, i < MAX, i++, v[i] == -1))) I.c:95 
ok: CHECKFAIL(I(E1(int i = 0, i < MAX, i++, v[i] == i))) I.c:96 
ok: CHECKFAIL(I(S(int i = 0, i < MAX, i++, v[i]) == 9)) I.c:98 
ok: CHECKEMPTY(I(S(int i = 0, i < 0, i++, v[i]) == 0)) I.c:99 
ok: CHECKEMPTY(I(S(int i = 0, i < MAX, i++, fv[i]) == fvsum)) I.c:101 
ok: CHECKEMPTY(I(S(int i = 0, i < 0, i++, fv[i])==0.0)) I.c:102 
ok: CHECKEMPTY(I(P(int i = 1, i < MAX, i++, v[i])==24)) I.c:104 
ok: CHECKEMPTY(I(P(int i = 1, i < 0, i++, v[i])==1)) I.c:105 
ok: CHECKEMPTY(I(P(int i = 0, i < MAX, i++, fv[i])==fvprod)) I.c:107 
ok: CHECKFAIL(I(P(int i = 0, i < 0, i++, fv[i]) != 1.0)) I.c:108 
ok: * ** check out nesting of operations I.c:111 
ok: CHECKEMPTY(I(A(int i = 0, i < MAX, i++, A(int j = 0, j < MAX, j++, m[i][j] == ((i == j) ? 1 : 0))))) I.c:115 
ok: CHECKFAIL(I(A(int i = 0, i < MAX, i++, A(int j = 0, j < MAX, j++, m[i][j] == 0)))) I.c:119 
ok: CHECKEMPTY(I(A(int i = 0, i < MAX, i++, E(int j = 0, j < MAX, j++, m[i][j] == 1)))) I.c:123 
ok: CHECKFAIL(I(E(int i = 0, i < MAX, i++, E(int j = 0, j < MAX, j++, m[i][j] == 2)))) I.c:127 
ok: CHECKEMPTY(I(A(int i = 0, i < MAX, i++, E1(int j = 0, j < MAX, j++, m[i][j] == 1)))) I.c:131 
ok: CHECKFAIL(I(A(int i = 0, i < MAX, i++, E1(int j = 0, j < MAX, j++, m[i][j] == 2)))) I.c:135 
ok: CHECKFAIL(I(A(int i = 0, i < MAX, i++, E1(int j = 0, j < MAX, j++, m[i][j] == 0)))) I.c:139 
ok: CHECKFAIL(I(A(int i = 0, i < MAX, i++, E1(int j = 0, j < MAX, j++, m[i][j] == 4)))) I.c:143 
ok: CHECKEMPTY(I(S(int i = 0, i < MAX, i++, S(int j = 0, j < MAX, j++, m[i][j])) == MAX)) I.c:146 
ok: CHECKEMPTY(I(P(int i = 0, i < MAX, i++, S(int j = 0, j < MAX, j++, m[i][j])) == 1)) I.c:149 
ok: CHECKEMPTY(I(C(int i = 0, i < MAX, i++, S(int j = 0, j < MAX, j++, m[i][j]) == 1) == MAX)) I.c:152 
ok: CHECKEMPTY(I(C(int i = 0, i < MAX, i++, S(int j = 0, j < MAX, j++, m[i][j]) == 2) == 0)) I.c:155 
ok: CHECKEMPTY(I(A(int i = 0, i < MAX, i++, C(int j = 0, j < MAX, j++, m[i][j] == 1)))) I.c:158 
Passed 46 tests completed successfully I.c 
checking I.c using gcc -g -O
ok: * * I.h tests I.c:64 
ok: CHECKEMPTY(I(0 == 0)) I.c:66 
ok: CHECKFAIL(I(0 == 1)) I.c:67 
ok: CHECKEMPTY(I(1)) I.c:69 
ok: CHECKFAIL(I(0)) I.c:70 
ok: * ** Tests with quantifiers (based on check_Q.c) I.c:72 
ok: CHECKEMPTY(I(A(int i = 0, i < MAX, i++, v[i] == i))) I.c:74 
ok: CHECKFAIL(I(A(int i = 0, i < MAX, i++, v[i] > i))) I.c:75 
ok: CHECKEMPTY(I(E(int i = 0, i < MAX, i++, v[i] == 4))) I.c:77 
ok: CHECKEMPTY(I(E(int i = 0, i < MAX, i++, v[i] == 0))) I.c:78 
ok: CHECKEMPTY(I(E(int i = 0, i < MAX, i++, v[i] == 1))) I.c:79 
ok: CHECKFAIL(I(E(int i = 0, i < MAX, i++, v[i] == 5))) I.c:81 
ok: CHECKFAIL(I(E(int i = 0, i < MAX, i++, v[i] == -1))) I.c:82 
ok: CHECKFAIL(I(E(int i = 0, i < MAX, i++, v[i] > i))) I.c:83 
ok: CHECKEMPTY(I(C(int i = 0, i < MAX, i++, 1) == MAX)) I.c:85 
ok: CHECKEMPTY(I(C(int i = 0, i < MAX, i++, v[i] == 0) == 1)) I.c:86 
ok: CHECKEMPTY(I(C(int i = 0, i < MAX, i++, v[i] == 4) == 1)) I.c:87 
ok: CHECKEMPTY(I(C(int i = 0, i < MAX, i++, v[i] == 5) == 0)) I.c:88 
ok: CHECKEMPTY(I(E1(int i = 0, i < MAX, i++, v[i] == 4))) I.c:90 
ok: CHECKEMPTY(I(E1(int i = 0, i < MAX, i++, v[i] == 0))) I.c:91 
ok: CHECKEMPTY(I(E1(int i = 0, i < MAX, i++, v[i] == 1))) I.c:92 
ok: CHECKFAIL(I(E1(int i = 0, i < MAX, i++, v[i] > 4))) I.c:94 
ok: CHECKFAIL(I(E1(int i = 0, i < MAX, i++, v[i] == -1))) I.c:95 
ok: CHECKFAIL(I(E1(int i = 0, i < MAX, i++, v[i] == i))) I.c:96 
ok: CHECKFAIL(I(S(int i = 0, i < MAX, i++, v[i]) == 9)) I.c:98 
ok: CHECKEMPTY(I(S(int i = 0, i < 0, i++, v[i]) == 0)) I.c:99 
ok: CHECKEMPTY(I(S(int i = 0, i < MAX, i++, fv[i]) == fvsum)) I.c:101 
ok: CHECKEMPTY(I(S(int i = 0, i < 0, i++, fv[i])==0.0)) I.c:102 
ok: CHECKEMPTY(I(P(int i = 1, i < MAX, i++, v[i])==24)) I.c:104 
ok: CHECKEMPTY(I(P(int i = 1, i < 0, i++, v[i])==1)) I.c:105 
ok: CHECKEMPTY(I(P(int i = 0, i < MAX, i++, fv[i])==fvprod)) I.c:107 
ok: CHECKFAIL(I(P(int i = 0, i < 0, i++, fv[i]) != 1.0)) I.c:108 
ok: * ** check out nesting of operations I.c:111 
ok: CHECKEMPTY(I(A(int i = 0, i < MAX, i++, A(int j = 0, j < MAX, j++, m[i][j] == ((i == j) ? 1 : 0))))) I.c:115 
ok: CHECKFAIL(I(A(int i = 0, i < MAX, i++, A(int j = 0, j < MAX, j++, m[i][j] == 0)))) I.c:119 
ok: CHECKEMPTY(I(A(int i = 0, i < MAX, i++, E(int j = 0, j < MAX, j++, m[i][j] == 1)))) I.c:123 
ok: CHECKFAIL(I(E(int i = 0, i < MAX, i++, E(int j = 0, j < MAX, j++, m[i][j] == 2)))) I.c:127 
ok: CHECKEMPTY(I(A(int i = 0, i < MAX, i++, E1(int j = 0, j < MAX, j++, m[i][j] == 1)))) I.c:131 
ok: CHECKFAIL(I(A(int i = 0, i < MAX, i++, E1(int j = 0, j < MAX, j++, m[i][j] == 2)))) I.c:135 
ok: CHECKFAIL(I(A(int i = 0, i < MAX, i++, E1(int j = 0, j < MAX, j++, m[i][j] == 0)))) I.c:139 
ok: CHECKFAIL(I(A(int i = 0, i < MAX, i++, E1(int j = 0, j < MAX, j++, m[i][j] == 4)))) I.c:143 
ok: CHECKEMPTY(I(S(int i = 0, i < MAX, i++, S(int j = 0, j < MAX, j++, m[i][j])) == MAX)) I.c:146 
ok: CHECKEMPTY(I(P(int i = 0, i < MAX, i++, S(int j = 0, j < MAX, j++, m[i][j])) == 1)) I.c:149 
ok: CHECKEMPTY(I(C(int i = 0, i < MAX, i++, S(int j = 0, j < MAX, j++, m[i][j]) == 1) == MAX)) I.c:152 
ok: CHECKEMPTY(I(C(int i = 0, i < MAX, i++, S(int j = 0, j < MAX, j++, m[i][j]) == 2) == 0)) I.c:155 
ok: CHECKEMPTY(I(A(int i = 0, i < MAX, i++, C(int j = 0, j < MAX, j++, m[i][j] == 1)))) I.c:158 
Passed 46 tests completed successfully I.c -O
checking I.c using gcc -g -O2
ok: * * I.h tests I.c:64 
ok: CHECKEMPTY(I(0 == 0)) I.c:66 
ok: CHECKFAIL(I(0 == 1)) I.c:67 
ok: CHECKEMPTY(I(1)) I.c:69 
ok: CHECKFAIL(I(0)) I.c:70 
ok: * ** Tests with quantifiers (based on check_Q.c) I.c:72 
ok: CHECKEMPTY(I(A(int i = 0, i < MAX, i++, v[i] == i))) I.c:74 
ok: CHECKFAIL(I(A(int i = 0, i < MAX, i++, v[i] > i))) I.c:75 
ok: CHECKEMPTY(I(E(int i = 0, i < MAX, i++, v[i] == 4))) I.c:77 
ok: CHECKEMPTY(I(E(int i = 0, i < MAX, i++, v[i] == 0))) I.c:78 
ok: CHECKEMPTY(I(E(int i = 0, i < MAX, i++, v[i] == 1))) I.c:79 
ok: CHECKFAIL(I(E(int i = 0, i < MAX, i++, v[i] == 5))) I.c:81 
ok: CHECKFAIL(I(E(int i = 0, i < MAX, i++, v[i] == -1))) I.c:82 
ok: CHECKFAIL(I(E(int i = 0, i < MAX, i++, v[i] > i))) I.c:83 
ok: CHECKEMPTY(I(C(int i = 0, i < MAX, i++, 1) == MAX)) I.c:85 
ok: CHECKEMPTY(I(C(int i = 0, i < MAX, i++, v[i] == 0) == 1)) I.c:86 
ok: CHECKEMPTY(I(C(int i = 0, i < MAX, i++, v[i] == 4) == 1)) I.c:87 
ok: CHECKEMPTY(I(C(int i = 0, i < MAX, i++, v[i] == 5) == 0)) I.c:88 
ok: CHECKEMPTY(I(E1(int i = 0, i < MAX, i++, v[i] == 4))) I.c:90 
ok: CHECKEMPTY(I(E1(int i = 0, i < MAX, i++, v[i] == 0))) I.c:91 
ok: CHECKEMPTY(I(E1(int i = 0, i < MAX, i++, v[i] == 1))) I.c:92 
ok: CHECKFAIL(I(E1(int i = 0, i < MAX, i++, v[i] > 4))) I.c:94 
ok: CHECKFAIL(I(E1(int i = 0, i < MAX, i++, v[i] == -1))) I.c:95 
ok: CHECKFAIL(I(E1(int i = 0, i < MAX, i++, v[i] == i))) I.c:96 
ok: CHECKFAIL(I(S(int i = 0, i < MAX, i++, v[i]) == 9)) I.c:98 
ok: CHECKEMPTY(I(S(int i = 0, i < 0, i++, v[i]) == 0)) I.c:99 
ok: CHECKEMPTY(I(S(int i = 0, i < MAX, i++, fv[i]) == fvsum)) I.c:101 
ok: CHECKEMPTY(I(S(int i = 0, i < 0, i++, fv[i])==0.0)) I.c:102 
ok: CHECKEMPTY(I(P(int i = 1, i < MAX, i++, v[i])==24)) I.c:104 
ok: CHECKEMPTY(I(P(int i = 1, i < 0, i++, v[i])==1)) I.c:105 
ok: CHECKEMPTY(I(P(int i = 0, i < MAX, i++, fv[i])==fvprod)) I.c:107 
ok: CHECKFAIL(I(P(int i = 0, i < 0, i++, fv[i]) != 1.0)) I.c:108 
ok: * ** check out nesting of operations I.c:111 
ok: CHECKEMPTY(I(A(int i = 0, i < MAX, i++, A(int j = 0, j < MAX, j++, m[i][j] == ((i == j) ? 1 : 0))))) I.c:115 
ok: CHECKFAIL(I(A(int i = 0, i < MAX, i++, A(int j = 0, j < MAX, j++, m[i][j] == 0)))) I.c:119 
ok: CHECKEMPTY(I(A(int i = 0, i < MAX, i++, E(int j = 0, j < MAX, j++, m[i][j] == 1)))) I.c:123 
ok: CHECKFAIL(I(E(int i = 0, i < MAX, i++, E(int j = 0, j < MAX, j++, m[i][j] == 2)))) I.c:127 
ok: CHECKEMPTY(I(A(int i = 0, i < MAX, i++, E1(int j = 0, j < MAX, j++, m[i][j] == 1)))) I.c:131 
ok: CHECKFAIL(I(A(int i = 0, i < MAX, i++, E1(int j = 0, j < MAX, j++, m[i][j] == 2)))) I.c:135 
ok: CHECKFAIL(I(A(int i = 0, i < MAX, i++, E1(int j = 0, j < MAX, j++, m[i][j] == 0)))) I.c:139 
ok: CHECKFAIL(I(A(int i = 0, i < MAX, i++, E1(int j = 0, j < MAX, j++, m[i][j] == 4)))) I.c:143 
ok: CHECKEMPTY(I(S(int i = 0, i < MAX, i++, S(int j = 0, j < MAX, j++, m[i][j])) == MAX)) I.c:146 
ok: CHECKEMPTY(I(P(int i = 0, i < MAX, i++, S(int j = 0, j < MAX, j++, m[i][j])) == 1)) I.c:149 
ok: CHECKEMPTY(I(C(int i = 0, i < MAX, i++, S(int j = 0, j < MAX, j++, m[i][j]) == 1) == MAX)) I.c:152 
ok: CHECKEMPTY(I(C(int i = 0, i < MAX, i++, S(int j = 0, j < MAX, j++, m[i][j]) == 2) == 0)) I.c:155 
ok: CHECKEMPTY(I(A(int i = 0, i < MAX, i++, C(int j = 0, j < MAX, j++, m[i][j] == 1)))) I.c:158 
Passed 46 tests completed successfully I.c -O2
checking I.c using gcc -g -O3
ok: * * I.h tests I.c:64 
ok: CHECKEMPTY(I(0 == 0)) I.c:66 
ok: CHECKFAIL(I(0 == 1)) I.c:67 
ok: CHECKEMPTY(I(1)) I.c:69 
ok: CHECKFAIL(I(0)) I.c:70 
ok: * ** Tests with quantifiers (based on check_Q.c) I.c:72 
ok: CHECKEMPTY(I(A(int i = 0, i < MAX, i++, v[i] == i))) I.c:74 
ok: CHECKFAIL(I(A(int i = 0, i < MAX, i++, v[i] > i))) I.c:75 
ok: CHECKEMPTY(I(E(int i = 0, i < MAX, i++, v[i] == 4))) I.c:77 
ok: CHECKEMPTY(I(E(int i = 0, i < MAX, i++, v[i] == 0))) I.c:78 
ok: CHECKEMPTY(I(E(int i = 0, i < MAX, i++, v[i] == 1))) I.c:79 
ok: CHECKFAIL(I(E(int i = 0, i < MAX, i++, v[i] == 5))) I.c:81 
ok: CHECKFAIL(I(E(int i = 0, i < MAX, i++, v[i] == -1))) I.c:82 
ok: CHECKFAIL(I(E(int i = 0, i < MAX, i++, v[i] > i))) I.c:83 
ok: CHECKEMPTY(I(C(int i = 0, i < MAX, i++, 1) == MAX)) I.c:85 
ok: CHECKEMPTY(I(C(int i = 0, i < MAX, i++, v[i] == 0) == 1)) I.c:86 
ok: CHECKEMPTY(I(C(int i = 0, i < MAX, i++, v[i] == 4) == 1)) I.c:87 
ok: CHECKEMPTY(I(C(int i = 0, i < MAX, i++, v[i] == 5) == 0)) I.c:88 
ok: CHECKEMPTY(I(E1(int i = 0, i < MAX, i++, v[i] == 4))) I.c:90 
ok: CHECKEMPTY(I(E1(int i = 0, i < MAX, i++, v[i] == 0))) I.c:91 
ok: CHECKEMPTY(I(E1(int i = 0, i < MAX, i++, v[i] == 1))) I.c:92 
ok: CHECKFAIL(I(E1(int i = 0, i < MAX, i++, v[i] > 4))) I.c:94 
ok: CHECKFAIL(I(E1(int i = 0, i < MAX, i++, v[i] == -1))) I.c:95 
ok: CHECKFAIL(I(E1(int i = 0, i < MAX, i++, v[i] == i))) I.c:96 
ok: CHECKFAIL(I(S(int i = 0, i < MAX, i++, v[i]) == 9)) I.c:98 
ok: CHECKEMPTY(I(S(int i = 0, i < 0, i++, v[i]) == 0)) I.c:99 
ok: CHECKEMPTY(I(S(int i = 0, i < MAX, i++, fv[i]) == fvsum)) I.c:101 
ok: CHECKEMPTY(I(S(int i = 0, i < 0, i++, fv[i])==0.0)) I.c:102 
ok: CHECKEMPTY(I(P(int i = 1, i < MAX, i++, v[i])==24)) I.c:104 
ok: CHECKEMPTY(I(P(int i = 1, i < 0, i++, v[i])==1)) I.c:105 
ok: CHECKEMPTY(I(P(int i = 0, i < MAX, i++, fv[i])==fvprod)) I.c:107 
ok: CHECKFAIL(I(P(int i = 0, i < 0, i++, fv[i]) != 1.0)) I.c:108 
ok: * ** check out nesting of operations I.c:111 
ok: CHECKEMPTY(I(A(int i = 0, i < MAX, i++, A(int j = 0, j < MAX, j++, m[i][j] == ((i == j) ? 1 : 0))))) I.c:115 
ok: CHECKFAIL(I(A(int i = 0, i < MAX, i++, A(int j = 0, j < MAX, j++, m[i][j] == 0)))) I.c:119 
ok: CHECKEMPTY(I(A(int i = 0, i < MAX, i++, E(int j = 0, j < MAX, j++, m[i][j] == 1)))) I.c:123 
ok: CHECKFAIL(I(E(int i = 0, i < MAX, i++, E(int j = 0, j < MAX, j++, m[i][j] == 2)))) I.c:127 
ok: CHECKEMPTY(I(A(int i = 0, i < MAX, i++, E1(int j = 0, j < MAX, j++, m[i][j] == 1)))) I.c:131 
ok: CHECKFAIL(I(A(int i = 0, i < MAX, i++, E1(int j = 0, j < MAX, j++, m[i][j] == 2)))) I.c:135 
ok: CHECKFAIL(I(A(int i = 0, i < MAX, i++, E1(int j = 0, j < MAX, j++, m[i][j] == 0)))) I.c:139 
ok: CHECKFAIL(I(A(int i = 0, i < MAX, i++, E1(int j = 0, j < MAX, j++, m[i][j] == 4)))) I.c:143 
ok: CHECKEMPTY(I(S(int i = 0, i < MAX, i++, S(int j = 0, j < MAX, j++, m[i][j])) == MAX)) I.c:146 
ok: CHECKEMPTY(I(P(int i = 0, i < MAX, i++, S(int j = 0, j < MAX, j++, m[i][j])) == 1)) I.c:149 
ok: CHECKEMPTY(I(C(int i = 0, i < MAX, i++, S(int j = 0, j < MAX, j++, m[i][j]) == 1) == MAX)) I.c:152 
ok: CHECKEMPTY(I(C(int i = 0, i < MAX, i++, S(int j = 0, j < MAX, j++, m[i][j]) == 2) == 0)) I.c:155 
ok: CHECKEMPTY(I(A(int i = 0, i < MAX, i++, C(int j = 0, j < MAX, j++, m[i][j] == 1)))) I.c:158 
Passed 46 tests completed successfully I.c -O3
checking L.c using gcc -g
ok: * L.h: basic tests L.c:44 
ok: CHECK(L("hello"),hello) L.c:45 
ok: CHECK(L("hello %d", 9+1),hello 10) L.c:46 
ok: CHECK(L("hello %d %s",9+1,"x"),hello 10 x) L.c:47 
ok: CHECK(L("hello %d\t%s",9+1,"x"),hello 10	x) L.c:48 
ok: CHECKEMPTY(L("hello")) L.c:51 
ok: CHECKEMPTY(L("hello %d", 9+1)) L.c:52 
Passed 7 tests completed successfully L.c 
checking L.c using gcc -g -O
ok: * L.h: basic tests L.c:44 
ok: CHECK(L("hello"),hello) L.c:45 
ok: CHECK(L("hello %d", 9+1),hello 10) L.c:46 
ok: CHECK(L("hello %d %s",9+1,"x"),hello 10 x) L.c:47 
ok: CHECK(L("hello %d\t%s",9+1,"x"),hello 10	x) L.c:48 
ok: CHECKEMPTY(L("hello")) L.c:51 
ok: CHECKEMPTY(L("hello %d", 9+1)) L.c:52 
Passed 7 tests completed successfully L.c -O
checking L.c using gcc -g -O2
ok: * L.h: basic tests L.c:44 
ok: CHECK(L("hello"),hello) L.c:45 
ok: CHECK(L("hello %d", 9+1),hello 10) L.c:46 
ok: CHECK(L("hello %d %s",9+1,"x"),hello 10 x) L.c:47 
ok: CHECK(L("hello %d\t%s",9+1,"x"),hello 10	x) L.c:48 
ok: CHECKEMPTY(L("hello")) L.c:51 
ok: CHECKEMPTY(L("hello %d", 9+1)) L.c:52 
Passed 7 tests completed successfully L.c -O2
checking L.c using gcc -g -O3
ok: * L.h: basic tests L.c:44 
ok: CHECK(L("hello"),hello) L.c:45 
ok: CHECK(L("hello %d", 9+1),hello 10) L.c:46 
ok: CHECK(L("hello %d %s",9+1,"x"),hello 10 x) L.c:47 
ok: CHECK(L("hello %d\t%s",9+1,"x"),hello 10	x) L.c:48 
ok: CHECKEMPTY(L("hello")) L.c:51 
ok: CHECKEMPTY(L("hello %d", 9+1)) L.c:52 
Passed 7 tests completed successfully L.c -O3
checking DI.c using gcc -g
ok: * DI.h tests DI.c:52 
ok: *  note: with -O3 we need a volatile for i least we fail since DI.c:53 
ok: *    i isn't created till after the assertions DI.c:54 
ok: CHECKEMPTY(DI(0 == 0)) DI.c:56 
ok: CHECKFAIL(DI(0 == 1)) DI.c:57 
ok: CHECKEMPTY(DI(i == 0)) DI.c:62 
ok: CHECKFAIL(DI(i == 1)) DI.c:63 
ok: CHECKEMPTY(DI(i == 1)) DI.c:66 
ok: CHECKFAIL(DI(i == 0)) DI.c:67 
ok: CHECKEMPTY(DI(i == 0)) DI.c:70 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i == 10)) DI.c:76 
ok: CHECKFAIL(DI(i == 1)) DI.c:79 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i != 10)) DI.c:85 
Passed 53 tests completed successfully DI.c 
checking DI.c using gcc -g -O
ok: * DI.h tests DI.c:52 
ok: *  note: with -O3 we need a volatile for i least we fail since DI.c:53 
ok: *    i isn't created till after the assertions DI.c:54 
ok: CHECKEMPTY(DI(0 == 0)) DI.c:56 
ok: CHECKFAIL(DI(0 == 1)) DI.c:57 
ok: CHECKEMPTY(DI(i == 0)) DI.c:62 
ok: CHECKFAIL(DI(i == 1)) DI.c:63 
ok: CHECKEMPTY(DI(i == 1)) DI.c:66 
ok: CHECKFAIL(DI(i == 0)) DI.c:67 
ok: CHECKEMPTY(DI(i == 0)) DI.c:70 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i == 10)) DI.c:76 
ok: CHECKFAIL(DI(i == 1)) DI.c:79 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i != 10)) DI.c:85 
Passed 53 tests completed successfully DI.c -O
checking DI.c using gcc -g -O2
ok: * DI.h tests DI.c:52 
ok: *  note: with -O3 we need a volatile for i least we fail since DI.c:53 
ok: *    i isn't created till after the assertions DI.c:54 
ok: CHECKEMPTY(DI(0 == 0)) DI.c:56 
ok: CHECKFAIL(DI(0 == 1)) DI.c:57 
ok: CHECKEMPTY(DI(i == 0)) DI.c:62 
ok: CHECKFAIL(DI(i == 1)) DI.c:63 
ok: CHECKEMPTY(DI(i == 1)) DI.c:66 
ok: CHECKFAIL(DI(i == 0)) DI.c:67 
ok: CHECKEMPTY(DI(i == 0)) DI.c:70 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i == 10)) DI.c:76 
ok: CHECKFAIL(DI(i == 1)) DI.c:79 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i != 10)) DI.c:85 
Passed 53 tests completed successfully DI.c -O2
checking DI.c using gcc -g -O3
ok: * DI.h tests DI.c:52 
ok: *  note: with -O3 we need a volatile for i least we fail since DI.c:53 
ok: *    i isn't created till after the assertions DI.c:54 
ok: CHECKEMPTY(DI(0 == 0)) DI.c:56 
ok: CHECKFAIL(DI(0 == 1)) DI.c:57 
ok: CHECKEMPTY(DI(i == 0)) DI.c:62 
ok: CHECKFAIL(DI(i == 1)) DI.c:63 
ok: CHECKEMPTY(DI(i == 1)) DI.c:66 
ok: CHECKFAIL(DI(i == 0)) DI.c:67 
ok: CHECKEMPTY(DI(i == 0)) DI.c:70 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i < 10)) DI.c:72 
ok: CHECKEMPTY(DI(1 <= i && i <= 10)) DI.c:74 
ok: CHECKEMPTY(DI(i == 10)) DI.c:76 
ok: CHECKFAIL(DI(i == 1)) DI.c:79 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i >= 10)) DI.c:81 
ok: CHECKFAIL(DI(i < 1 && i <= 10)) DI.c:83 
ok: CHECKFAIL(DI(i != 10)) DI.c:85 
Passed 53 tests completed successfully DI.c -O3
checking DL.c using gcc -g
ok: * L.h: basic tests DL.c:46 
ok: CHECK(DL("hello"),hello) DL.c:48 
ok: CHECK(DL("hello %d", 9+1),hello 10) DL.c:49 
ok: CHECK(DL("hello %d %s",9+1,"x"),hello 10 x) DL.c:50 
ok: CHECK(DL("hello %d\t%s",9+1,"x"),hello 10	x) DL.c:51 
ok: CHECKEMPTY(DL("hello")) DL.c:54 
ok: CHECKEMPTY(DL("hello %d", 9+1)) DL.c:55 
Passed 7 tests completed successfully DL.c 
checking DL.c using gcc -g -O
ok: * L.h: basic tests DL.c:46 
ok: CHECK(DL("hello"),hello) DL.c:48 
ok: CHECK(DL("hello %d", 9+1),hello 10) DL.c:49 
ok: CHECK(DL("hello %d %s",9+1,"x"),hello 10 x) DL.c:50 
ok: CHECK(DL("hello %d\t%s",9+1,"x"),hello 10	x) DL.c:51 
ok: CHECKEMPTY(DL("hello")) DL.c:54 
ok: CHECKEMPTY(DL("hello %d", 9+1)) DL.c:55 
Passed 7 tests completed successfully DL.c -O
checking DL.c using gcc -g -O2
ok: * L.h: basic tests DL.c:46 
ok: CHECK(DL("hello"),hello) DL.c:48 
ok: CHECK(DL("hello %d", 9+1),hello 10) DL.c:49 
ok: CHECK(DL("hello %d %s",9+1,"x"),hello 10 x) DL.c:50 
ok: CHECK(DL("hello %d\t%s",9+1,"x"),hello 10	x) DL.c:51 
ok: CHECKEMPTY(DL("hello")) DL.c:54 
ok: CHECKEMPTY(DL("hello %d", 9+1)) DL.c:55 
Passed 7 tests completed successfully DL.c -O2
checking DL.c using gcc -g -O3
ok: * L.h: basic tests DL.c:46 
ok: CHECK(DL("hello"),hello) DL.c:48 
ok: CHECK(DL("hello %d", 9+1),hello 10) DL.c:49 
ok: CHECK(DL("hello %d %s",9+1,"x"),hello 10 x) DL.c:50 
ok: CHECK(DL("hello %d\t%s",9+1,"x"),hello 10	x) DL.c:51 
ok: CHECKEMPTY(DL("hello")) DL.c:54 
ok: CHECKEMPTY(DL("hello %d", 9+1)) DL.c:55 
Passed 7 tests completed successfully DL.c -O3
checking DS.c using gcc -g
ok: * # testing DS.c DS.c:45 
ok: CHECKEMPTY(DS($i = i)) DS.c:47 
ok: CHECKEMPTY(DI($i == 10)) DS.c:49 
ok: CHECKEMPTY(DI(i == 11)) DS.c:50 
ok: CHECKEMPTY(DI(i == ($i + 1))) DS.c:51 
ok: CHECKFAIL(DI($i == i)) DS.c:52 
ok: CHECKEMPTY(DS($i = i)) DS.c:54 
ok: CHECKEMPTY(DI(i == $i)) DS.c:56 
ok: CHECKEMPTY(DI(i == 11)) DS.c:57 
ok: CHECKEMPTY(DI(i == ($i + 1))) DS.c:59 
ok: CHECKFAIL(DI($i == i)) DS.c:60 
Passed 11 tests completed successfully DS.c 
checking DS.c using gcc -g -O
ok: * # testing DS.c DS.c:45 
ok: CHECKEMPTY(DS($i = i)) DS.c:47 
ok: CHECKEMPTY(DI($i == 10)) DS.c:49 
ok: CHECKEMPTY(DI(i == 11)) DS.c:50 
ok: CHECKEMPTY(DI(i == ($i + 1))) DS.c:51 
ok: CHECKFAIL(DI($i == i)) DS.c:52 
ok: CHECKEMPTY(DS($i = i)) DS.c:54 
ok: CHECKEMPTY(DI(i == $i)) DS.c:56 
ok: CHECKEMPTY(DI(i == 11)) DS.c:57 
ok: CHECKEMPTY(DI(i == ($i + 1))) DS.c:59 
ok: CHECKFAIL(DI($i == i)) DS.c:60 
Passed 11 tests completed successfully DS.c -O
checking DS.c using gcc -g -O2
ok: * # testing DS.c DS.c:45 
ok: CHECKEMPTY(DS($i = i)) DS.c:47 
ok: CHECKEMPTY(DI($i == 10)) DS.c:49 
ok: CHECKEMPTY(DI(i == 11)) DS.c:50 
ok: CHECKEMPTY(DI(i == ($i + 1))) DS.c:51 
ok: CHECKFAIL(DI($i == i)) DS.c:52 
ok: CHECKEMPTY(DS($i = i)) DS.c:54 
ok: CHECKEMPTY(DI(i == $i)) DS.c:56 
ok: CHECKEMPTY(DI(i == 11)) DS.c:57 
ok: CHECKEMPTY(DI(i == ($i + 1))) DS.c:59 
ok: CHECKFAIL(DI($i == i)) DS.c:60 
Passed 11 tests completed successfully DS.c -O2
checking DS.c using gcc -g -O3
ok: * # testing DS.c DS.c:45 
ok: CHECKEMPTY(DS($i = i)) DS.c:47 
ok: CHECKEMPTY(DI($i == 10)) DS.c:49 
ok: CHECKEMPTY(DI(i == 11)) DS.c:50 
ok: CHECKEMPTY(DI(i == ($i + 1))) DS.c:51 
ok: CHECKFAIL(DI($i == i)) DS.c:52 
ok: CHECKEMPTY(DS($i = i)) DS.c:54 
ok: CHECKEMPTY(DI(i == $i)) DS.c:56 
ok: CHECKEMPTY(DI(i == 11)) DS.c:57 
ok: CHECKEMPTY(DI(i == ($i + 1))) DS.c:59 
ok: CHECKFAIL(DI($i == i)) DS.c:60 
Passed 11 tests completed successfully DS.c -O3

** Printing summary of results (see check.log for details)

** Printing list of failures
fail: CHECK(printf("hello*"),hello) selftest.c:41 
fail: CHECKEMPTY(putchar('a')) selftest.c:44 
fail: CHECKFAIL(printf("fail*")) selftest.c:47 
fail: CHECKTRUE(1==0) selftest.c:52 
fail: CHECKTRUE(1==0) selftest.c:52 
fail: CHECKFALSE(1==1) selftest.c:55 
fail: CHECKFALSE(1==1) selftest.c:55 
fail: CHECK(printf("hello*"),hello) selftest.c:41 
fail: CHECKEMPTY(putchar('a')) selftest.c:44 
fail: CHECKFAIL(printf("fail*")) selftest.c:47 
fail: CHECKTRUE(1==0) selftest.c:52 
fail: CHECKTRUE(1==0) selftest.c:52 
fail: CHECKFALSE(1==1) selftest.c:55 
fail: CHECKFALSE(1==1) selftest.c:55 
fail: CHECK(printf("hello*"),hello) selftest.c:41 
fail: CHECKEMPTY(putchar('a')) selftest.c:44 
fail: CHECKFAIL(printf("fail*")) selftest.c:47 
fail: CHECKTRUE(1==0) selftest.c:52 
fail: CHECKTRUE(1==0) selftest.c:52 
fail: CHECKFALSE(1==1) selftest.c:55 
fail: CHECKFALSE(1==1) selftest.c:55 
fail: CHECK(printf("hello*"),hello) selftest.c:41 
fail: CHECKEMPTY(putchar('a')) selftest.c:44 
fail: CHECKFAIL(printf("fail*")) selftest.c:47 
fail: CHECKTRUE(1==0) selftest.c:52 
fail: CHECKTRUE(1==0) selftest.c:52 
fail: CHECKFALSE(1==1) selftest.c:55 
fail: CHECKFALSE(1==1) selftest.c:55 

** Printing summary of results
Error 7 failures, 10 successes selftest.c 
Error 7 failures, 10 successes selftest.c -O
Error 7 failures, 10 successes selftest.c -O2
Error 7 failures, 10 successes selftest.c -O3
Passed 116 tests completed successfully Q.c 
Passed 116 tests completed successfully Q.c -O
Passed 116 tests completed successfully Q.c -O2
Passed 116 tests completed successfully Q.c -O3
Passed 46 tests completed successfully I.c 
Passed 46 tests completed successfully I.c -O
Passed 46 tests completed successfully I.c -O2
Passed 46 tests completed successfully I.c -O3
Passed 7 tests completed successfully L.c 
Passed 7 tests completed successfully L.c -O
Passed 7 tests completed successfully L.c -O2
Passed 7 tests completed successfully L.c -O3
Passed 53 tests completed successfully DI.c 
Passed 53 tests completed successfully DI.c -O
Passed 53 tests completed successfully DI.c -O2
Passed 53 tests completed successfully DI.c -O3
Passed 7 tests completed successfully DL.c 
Passed 7 tests completed successfully DL.c -O
Passed 7 tests completed successfully DL.c -O2
Passed 7 tests completed successfully DL.c -O3
Passed 11 tests completed successfully DS.c 
Passed 11 tests completed successfully DS.c -O
Passed 11 tests completed successfully DS.c -O2
Passed 11 tests completed successfully DS.c -O3
Note: you should get 7 failures/10 successes from selftest.c
Do you want to post the test report off to the author using e-mail?
enter y for yes, return for no.

no mail sent
PASS: checkall
PASS: Iok
========================
All 2 tests passed
========================
gmake[1]: Leaving directory `/usr/home/pjm/work/play/nana-1.00/test'
making check in examples
gmake[1]: Entering directory `/usr/home/pjm/work/play/nana-1.00/examples'
gcc -c -I. -I.    -g -O2 main.c
main.c:7: nana.h: No such file or directory
gmake[1]: *** [main.o] Error 1
gmake[1]: Leaving directory `/usr/home/pjm/work/play/nana-1.00/examples'
gmake: *** [check-recursive] Error 1
% exit
exit

Script done on Mon Apr 21 19:20:08 1997
