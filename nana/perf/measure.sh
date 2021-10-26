#!/bin/sh
#
# measure.sh - measure the performance of some single line code fragments
#   in space/time using a variety of compile time options.
# 
# Copyright (c) 1998 Phil Maker <pjm@gnu.org>
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


# the read -r hack is to avoid \n being expand to n
while read -r code
do
    (cat prelude.c 
    /bin/echo -E    "#ifndef NT"
    /bin/echo -E    "#define NT 1024"
    /bin/echo -E    "#endif"
    /bin/echo -E    "  printf(STR($code) \"\\n\");" 
    /bin/echo -E    "  if(false) goto s; /* avoid optimising labels away */"
    /bin/echo -E    "  if(false) goto t; /* avoid optimising labels away */"
    /bin/echo -E    "  if(false) {"
    /bin/echo -E    "  s:" 
# warning: gcc optimises printf to puts if its a string
    /bin/echo -E    "  __asm volatile (\"scode:\");"
    /bin/echo  -E  "$code /*codelet*/"
    /bin/echo -E    "  __asm volatile (\"ecode:\");"
    /bin/echo -E    "  t:;"
    /bin/echo -E    "  }"
#    /bin/echo -E    "  printf(\"s=%pb\\n\", &&s);"
#    /bin/echo -E    "  printf(\"t=%pb\\n\", &&t);"
    /bin/echo -E    "  printf(\"%ldb\\n\", &&t - &&s);"
    /bin/echo -E    "  s = now();"
    /bin/echo -E    "  for(n = 0; n != NT; n++) {"
    /bin/echo -E    "    C256($code);"
    /bin/echo -E    "  }"
    /bin/echo -E    "  e = now();"
    /bin/echo -E    "  te = ((e - s) * 1.0e9)/(NT * 256.0);"
    /bin/echo -E    "  if(te < 1000.0) {"
    /bin/echo -E    "    printf(\"%.2lfns\\n\", te);"
    /bin/echo -E    "  } else {"
    /bin/echo -E    "    printf(\"%.2lfus\\n\", te/1000.0);"
    /bin/echo -E    "  }"

    cat postlude.c
    ) >tmp.c
    grep codelet tmp.c >/dev/tty

    for args in $*
    do
	if gcc -fno-defer-pop -g -I. -I../src -L/usr/local/lib $args tmp.c -lnana -lm
	then
	    ../src/nana -I. -I../src tmp.c >nana.gdb
	    ../src/nana-run ./a.out -x nana.gdb | grep -v "^Breakpoint" |
	      grep -v "^Program" | grep -v "^helloworld" | grep -v "^\$"
            /bin/echo -E   $args
	    gcc -fno-defer-pop -g $args -I. -I../src -S tmp.c
	    # size a.out >/dev/tty
	    (
	    /bin/echo -E   "\\item \\verb@$code@ with \verb@gcc -g $args@ produces:\\par"
	    /bin/echo -E   "\\begin{verbatim}"
	    awk '/scode:/,/ecode:/' tmp.s | 
	     awk ' { x[NR] = $0 } 
                   END { for(i = 3; i < NR -2; i++) print x[i]; }' | 
		  expand
	      
	    /bin/echo -E   "\\end{verbatim}"
	    /bin/echo -E   "\\par"
	    ) >> code.mtex

	else
	    /bin/echo -E   "compile error: giving up"
	    exit 1
	fi
	/bin/echo -E  
    done
done |
awk '
BEGIN {
    RS = ""
    FS = "\n"
    OFS = "&"
    print "\\begin{tabular}{|l|l|l|l|}"
    print "\\hline"
    print "Code & Size & Time & Options \\\\"
    print "\\hline"
}

{
    print "\\verb@" $1 "@", $2, $3, $4 "\\\\"
}

END {
    print "\\hline"
    print "\\end{tabular}"
}'




