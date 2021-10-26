/*
 * nanafilter.c -  extracts commands delimited by @@...@@ from stdin and
 * 	prints them to stdout. It also handles the special cases caused
 *      by C string and character constants.
 * 
 * Copyright (c) 1997 Phil Maker
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * Id: nanafilter.c,v 1.2 1998/06/10 06:58:55 pjm Exp 
 */

static const char rcs[] ="Id: nanafilter.c,v 1.2 1998/06/10 06:58:55 pjm Exp ";

#include <stdio.h>
#include <stdlib.h>

void do_input(void);
void do_string(void);
void do_charconst(void);
void do_print(void);
void do_destringify(void);
void error(const char *);

/* nanafilter just transforms data from stdin to stdout */
int main(int argc, char **argv) { /*@unused argc@*/ /*@unused argv@*/
     do_input();
     return 0;
}

/* do_input - the main loop */
void do_input(void) {
     int c;

     while((c = getchar()) != EOF) {
	  switch(c) {
	  case '"': /* skip a C string which may contain @@..@@ */
	       do_string();
	       break;
	  case '\'': /* skip a C char constant which may contain @@..@@ */
	       do_charconst();
	       break;
	  case '@': /* a single @ so look at the next char */
	       if((c = getchar()) == '@') { /* @@ so print until final @@ */
		    do_print();
	       } else if(c == '"') { /* @" so process the string constant */
		    do_string();
	       } else if(c == '\'') { /* @' so process the char constant */
		    do_charconst();
	       } else if(c == EOF) { /* @EOF so just echo @ */
		    putchar('@');
	       } else { /* @c so just print it */
		    putchar('@');
		    putchar(c);
	       }
	       break;
	  default: /* just a character */
	       break;
	  }
     }
}

/* do_string - skips a C string include \\ escapes */
void do_string(void) {
     int c;

     for(;;) {
	  switch(c = getchar()) {
	  case '"': /* end of string */
	       return;
	  case '\\': /* escape character */
	       c = getchar();
	       if(c == EOF) { /* \\EOF so error */
		    error("syntax error: unexpected EOF");
	       }
	       break;
	  case EOF:
	       error("syntax error: unexpected EOF");
	       break;
	  default: /* just a character */
	       break;
	  }
     }
}

/* do_charconst - skips character constants */
void do_charconst(void) {
     int c;

     for(;;) {
	  switch(c = getchar()) {
	  case '\'': /* end of char constant */
	       return;
	  case '\\': /* escape character */
	       c = getchar();
	       if(c == EOF) {
		    error("syntax error: unexpected EOF");
	       } /* ignore it */
	       break;
	  default: /* just a character */
	       break;
	  }
     }
}

/* do_print - print the @@...@@ text out */	
void do_print(void) {
     int c;
     
     for(;;) {
	  switch(c = getchar()) {
	  case '@':
	       if((c = getchar()) == '@') { /* @@ so exit */
		    putchar('\n');
		    return;
	       } else if(c == '"') { /* @" so destringify */
		    do_destringify();
	       } else { /* @? so just print it */
		    putchar('@');
		    putchar(c);
	       }
	       break;
	  case EOF:
	       error("syntax error: unexpected EOF after @");
	       break;
	  default:
	       putchar(c);
	       break;
	  }
     }
}

/* do_destringify - translates @"..." to ... */
void do_destringify(void) {
     int c;

     for(;;) {
	  switch(c = getchar()) {
	  case '"':
	       return;
	  case EOF:
	       error("syntax error: EOF inside @\"..\"");
	       break;
	  default:
	       putchar(c);
	  }
     }
}

void error(const char *p) {
     fprintf(stderr, "%s\n", p);
     exit(1);
}


