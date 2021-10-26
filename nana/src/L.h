/*
 * L.h -  support for logging (printf...) style debugging.
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
 * Id: L.h,v 1.2 1998/01/17 10:57:03 pjm Exp 
 */


#ifndef _L_h_
#define _L_h_ 1

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
 * L_LEVEL sets the level of logging analogously to NDEBUG in assert.h
 *
 *   L_LEVEL == 2: always print.
 *   L_LEVEL == 1: print iff the guard is true.
 *   L_LEVEL == 0: never print.
 */

#ifndef L_LEVEL /* define DEFAULT for L_LEVEL */
#define L_LEVEL 1
#endif

/* 
 * L_DEFAULT_HANDLER - the default print handler; by default we just
 *   use fprintf.
 */

#ifndef L_DEFAULT_HANDLER /* define default handler */
#define L_DEFAULT_HANDLER fprintf
#endif /* L_DEFAULT_HANDLER */

/*
 * L_DEFAULT_GUARD - the default guard expression; a message is printed
 *     iff the guard is true. By default its always true.
 */

#ifndef L_DEFAULT_GUARD
#define L_DEFAULT_GUARD (1)
#endif

/*
 * L_DEFAULT_PARAMS - the default value to be passed as the second argument
 *       to the handler macro when an invariant fails.
 */


#ifndef L_DEFAULT_PARAMS
#define L_DEFAULT_PARAMS stderr
#endif

/* 
 * L_SHOW_TIME_FORMAT - the format string for printing the time.
 */

#ifndef L_SHOW_TIME_FORMAT
#define L_SHOW_TIME_FORMAT "%.6f:\t"
#endif

/*
 * L_SHOW_TIME_NOW - the function to measure the time.
 */

#ifndef L_SHOW_TIME_NOW
#include <now.h> 
#define L_SHOW_TIME_NOW now()
#endif

/*
 * L_SHOW_TIME - if it is defined then we will put time stamps at the
 *    beginning of each message using L_SHOW_TIME_FORMAT and L_SHOW_TIME_NOW.
 */

#ifdef L_SHOW_TIME
#define _L_SHOWTIME(h,p) h (p, L_SHOW_TIME_FORMAT, L_SHOW_TIME_NOW)
#else
#define _L_SHOWTIME(h,p) /* nothing */
#endif /* L_SHOWTIME */

/*
 * LGHP(g,h,p, f...) - print a log message.
 *
 *     g - the guard; print the message iff this is true
 *     h - the handler function that does the actual printing
 *     p - a parameter for the handler function; e.g. a file descriptor.
 *     f - printf style format string; we put this at the end since we
 *         we need to be able have 1 or more arguments (e.g. L("x") and
 *         L("%d",10); we use GNU cccp preprocessor varargs extension
 *         to handle multiple arguments.
 */

#ifndef __GNUC__
error you need gcc for this stuff to work properly
#endif

#if L_LEVEL == 2 /* always log the message */
#define LGHP(g,h,p,f...) \
	do { \
	       _L_SHOWTIME(h,p); \
	       h (p, ##f); \
	} while(0)

#elif L_LEVEL == 1 /* log it iff the guard is true */
#define LGHP(g,h,p,f...) \
	do { \
		  if(g) { \
			       _L_SHOWTIME(h,p); \
			       h (p, ##f); \
		  } \
	} while(0)
#elif L_LEVEL == 0 /* no logging so ignore them */
#define LGHP(g,h,p,f...) /* nothing */
#endif /* L_LEVEL */

/*
 * User routines.
 */

#define L(f...) \
          LGHP(L_DEFAULT_GUARD,L_DEFAULT_HANDLER,L_DEFAULT_PARAMS,##f)
#define LG(g,f...) \
          LGHP(g,L_DEFAULT_HANDLER,L_DEFAULT_PARAMS,##f)
#define LH(h,f...) \
          LGHP(L_DEFAULT_GUARD,h,L_DEFAULT_PARAMS,##f)
#define LP(p,f...) \
          LGHP(L_DEFAULT_GUARD,L_DEFAULT_HANDLER,p,##f)
#define LGP(g,p,f...) \
          LGHP(g,L_DEFAULT_HANDLER,p,##f)
#define LHP(h,p,f...) \
          LGHP(L_DEFAULT_GUARD,h,p,##f)

/*
 * V* - since the L* macros take a variable numbers of arguments we
 *    have problems compiling calls to L with C preprocessors other 
 *    than GNU cccp. The V* macros are called using a bracketed
 *    argument list, e.g. VL((f,x,s)); 
 *
 *    if we are compiling with GNU C then they simpily call the normal
 *    varargs macro. if we are not using GNU CC then they map to empty.
 */

#define VL(a) L a
#define VLG(a) LG a
#define VLH(a) LH a
#define VLP(a) LP a
#define VLGP(a) LGP a
#define VLHP(a) LHP a
#define VLGHP(a) LGHP a

#else /* defined(WITHOUT_NANA) */

#define VL(a) /* empty */
#define VLG(a) /* empty */
#define VLH(a) /* empty */
#define VLP(a) /* empty */
#define VLGP(a) /* empty */
#define VLHP(a) /* empty */
#define VLGHP(a) /* empty */

#endif /* !defined(WITHOUT_NANA) */
 
#ifdef __cplusplus
}
#endif

#endif /* _L_h_ */



