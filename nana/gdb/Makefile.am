#
# Makefile.am - automake configuration file for nana.
#

libexec_SCRIPTS = nana-trace.gdb 

bin_SCRIPTS = nana-trace nana-libtrace

EXTRA_DIST = nana-trace.in nana-trace.gdb test.c quiet.diff

ex-trace:
	gcc -g test.c
	sh ./nana-trace a.out

ex-libtrace:
	gcc -g -static test.c -lm
	(echo "printf"; echo "exit") | sh ./nana-libtrace a.out >test.gdb
	nana-run a.out -x test.gdb
	sh ./nana-libtrace a.out /usr/lib/libc.a >test.gdb
	nana-run a.out -x test.gdb
