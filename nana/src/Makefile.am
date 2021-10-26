#
# Makefile.am - automake configuration file for nana.
#

include_HEADERS = nana-config.h nana.h \
	DI.h I.h DL.h L.h Q.h GDB.h L_buffer.h now.h \
	eiffel.h Qstl.h calls.h nana_error.h L_times.h \
	cycles.h

lib_LIBRARIES = libnana.a

pkgdata_DATA = nana-run.gdb nana-run-init.gdb

libnana_a_SOURCES = I.c L_buffer.c now.c calls.c nana_error.c L_times.c \
		cycles.c

bin_SCRIPTS = 	nana nana-clg nana-run nana-c++lg

libexec_PROGRAMS = nanafilter 

EXTRA_DIST = nana.in nana-clg.in nana-run.in nana-run.gdb \
		nana-config.h.in nana-run-init.gdb \
		assert.h nana-c++lg.in






