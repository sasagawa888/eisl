/*
 * DL.h -  support for logging (printf...) style debugging using gdb.
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
 * Id: DL.h,v 1.1.1.1 1997/11/23 11:45:50 pjm Exp 
 */

#ifndef _DL_h_
#define _DL_h_ 1

#ifdef __cplusplus
extern "C" {
#endif

#ifndef WITHOUT_NANA 

/*
 * nana-config.h - the system wide configuration file; we put the ifndef
 *   around it to avoid the file 5 million times during a compile.
 */

#ifndef _nana_config_h_
#include <nana-config.h>
#endif

/*
 * DL_MAKE_VALID_BREAKPOINT() - used to make sure that we can put a
 *   breakpoint at this location. We default to a portable C expression
 *   which simply does an assignment. The configure script may override
 *   this (on an architecture basis) and replace it with something
 *   like asm("nop");
 */

#ifndef DL_MAKE_VALID_BREAKPOINT
static volatile int _dl_target;

#define DL_MAKE_VALID_BREAKPOINT() _dl_target = 0
#endif

/* 
 * DL_LEVEL sets the level of logging analogously to NDEBUG in assert.h
 *
 *   DL_LEVEL == 2: always print.
 *   DL_LEVEL == 1: print iff the guard is true.
 *   DL_LEVEL == 0: never print.
 */

#ifndef DL_LEVEL /* define DEFAULT for DL_LEVEL */
#define DL_LEVEL 1
#endif

/* 
 * DL_DEFAULT_HANDLER - the default print handler; by default we just
 *   the debugger printf.
 *
 * @@call (void) printf(f)@@
 */

#ifndef DL_DEFAULT_HANDLER /* define default handler */
#define DL_DEFAULT_HANDLER(g,h,p,f...) @@printf f@@
#endif /* DL_DEFAULT_HANDLER */

/*
 * DL_DEFAULT_GUARD - the default guard expression; a message is printed
 *     iff the guard is true. By default its always true.
 */

#ifndef DL_DEFAULT_GUARD
#define DL_DEFAULT_GUARD (1)
#endif

/*
 * DL_DEFAULT_PARAMS - the default value to be passed as the second argument
 *       to the handler macro when an invariant fails.
 */


#ifndef DL_DEFAULT_PARAMS
#define DL_DEFAULT_PARAMS stderr
#endif

/*
 * DL_SHOW_TIME - if its defined then each message gets a timestamp in front.
 */

#ifdef DL_SHOW_TIME

unsigned long _L_gettime(void); /* returns the current time */

#define _DL_SHOWTIME(h,p) @@call (void) h (p, "%-8ld ", _L_gettime())@@
#else

#define _DL_SHOWTIME(h,p) /* nothing */

#endif /* DL_SHOWTIME */

/*
 * DLGHP(g,h,p,f...) - print a log message.
 *
 *     g - the guard; print the message iff this is true
 *     h - the handler function that does the actual printing
 *     p - a parameter for the handler function; e.g. a file descriptor.
 *     f - the format and the data...
 */

#if DL_LEVEL == 2 /* always log the message */
#ifdef _NANA_FILTER_
#define DLGHP(g,h,p,f...) \
	do { \
		  @@break @__FILE__:__LINE__@@ \
		  @@command $bpnum@@ \
		  @@silent@@ \
  		  _DL_SHOWTIME(h,p); \
                  DL_DEFAULT_HANDLER(g,h,p,##f); \
		  @@cont@@ \
		  @@end@@ \
	} while(0)
#else
#define DLGHP(g,h,p,f...) DL_MAKE_VALID_BREAKPOINT()
#endif

#elif DL_LEVEL == 1 /* log it iff the guard is true */

#ifdef _NANA_FILTER_
#define DLGHP(g,h,p,f...) \
	do { \
		  if(g) { \
			       @@break @__FILE__:__LINE__@@ \
			       @@condition $bpnum g@@ \
			       @@command $bpnum@@ \
			       @@silent@@ \
			       _DL_SHOWTIME(h,p); \
			       DL_DEFAULT_HANDLER(g,h,p,##f); \
			       @@cont@@ \
			       @@end@@ \
		  } \
	} while(0)
#else
#define DLGHP(g,h,p,f...) DL_MAKE_VALID_BREAKPOINT()
#endif

#elif DL_LEVEL == 0 /* no logging so ignore them */
#define DLGHP(g,h,p,f...) /* nothing */
#endif /* DL_LEVEL */

/*
 * And the user routines.
 */

#define DL(f...) \
          DLGHP(DL_DEFAULT_GUARD,DL_DEFAULT_HANDLER,DL_DEFAULT_PARAMS,##f)
#define DLG(g,f...) \
          DLGHP(g,DL_DEFAULT_HANDLER,DL_DEFAULT_PARAMS,##f)
#define DLH(h,f...) \
          DLGHP(DL_DEFAULT_GUARD,h,DL_DEFAULT_PARAMS,##f)
#define DLP(p,f...) \
          DLGHP(DL_DEFAULT_GUARD,DL_DEFAULT_HANDLER,p,##f)
#define DLGP(g,p,f...) \
          DLGHP(g,DL_DEFAULT_HANDLER,p,##f)
#define DLHP(h,p,f...) \
          DLGHP(DL_DEFAULT_GUARD,h,p,##f)


/*
 * V* - since the DL* macros take a variable numbers of arguments we
 *    have problems compiling calls to L with C preprocessors other 
 *    than GNU cccp. The V* macros are called using a bracketed arglist, e.g.
 *    VDL((s,x,y))
 *
 *    if we are compiling with GNU C then they simply call the normal
 *    varargs macros. if we are not using GNU C then they map to empty.
 */

#define VDL(a) DL a
#define VDLG(a) DLG a
#define VDLH(a) DLH a
#define VDLP(a) DLP a
#define VDLGP(a) DLGP a
#define VDLHP(a) DLHP a
#define VDLGHP(a) DLGHP a

#else /* defined(WITHOUT_NANA) */

#define VDL(a) /* empty */
#define VDLG(a) /* empty */
#define VDLH(a) /* empty */
#define VDLP(a) /* empty */
#define VDLGP(a) /* empty */
#define VDLHP(a) /* empty */
#define VDLGHP(a) /* empty */

#endif /* !defined(WITHOUT_NANA) */
 

#ifdef __cplusplus
}
#endif
    
#endif /* _DL_h_ */





