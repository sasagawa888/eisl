#
# Makefile.am - automake configuration file for nana.
#

EXTRA_DIST = README \
	     nop.tst c_ops.tst assert.tst quantifiers.tst log.tst \
	     summary.tst \
	     measure.sh \
	     perf.tex \
	     prelude.c postlude.c \
	     dcache.tst perf.tex \
	     bogomips.c 

all:
	@echo "use make perf if you want to do the measurements"

# Note: you require latex and latex2html for this build

perf:	bogomips.mtex uname.mtex summary.mtex dcache.mtex others
	rm -f code.tex
	pdflatex perf.tex
	latex2html -init_file init.l2h perf.tex

bogomips bogomips.mtex: bogomips.c
	gcc -I$(top_srcdir)/src -L$(top_srcdir)/src bogomips.c -lnana -o bogomips
	./bogomips >bogomips.mtex
	cat bogomips.mtex

uname.mtex:
	uname -m -s -r >uname.mtex
	cat uname.mtex

summary.mtex: summary.tst measure.sh
	./measure.sh -Os <summary.tst >summary.mtex

dcache.mtex: dcache.tst measure.sh
	./measure.sh -Os <dcache.tst >dcache.mtex

others:
	rm -f code.tex
	for f in nop c_ops assert quantifiers log ; \
	do \
	   echo "Testing: $$f" ; \
	   # note -O2/-O3 are problematic code size < 0 due to movement; \
	   ./measure.sh -O0 -Os <$$f.tst >$$f.mtex ; \
        done




