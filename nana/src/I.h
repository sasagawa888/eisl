/*
 * I.h -  support for invariants (assertions) using C code.
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
 * Id: I.h,v 1.1.1.1 1997/11/23 11:45:50 pjm Exp 
 */


#ifndef _I_h_
#define _I_h_ 1

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
#include <stdlib.h>
#endif

/* 
 * I_LEVEL sets the level of invariant analogously to NDEBUG in assert.h
 *
 *   I_LEVEL == 2: invariants are always evaluated.
 *   I_LEVEL == 1: evaluate invariants iff they have a true GUARD.
 *   I_LEVEL == 0: invariants are never evaluated.
 */

#ifndef I_LEVEL /* define DEFAULT for I_LEVEL */
#define I_LEVEL 1
#endif


/*
 * I_DEFAULT_GUARD - the default guard expression; an invariant is checked
 *     iff the guard is true. By default its always true.
 */

#ifndef I_DEFAULT_GUARD
#define I_DEFAULT_GUARD (1)
#endif

/*
 * I_DEFAULT_PARAMS - the default value to be passed as the second argument
 *       to the handler macro when an invariant fails.
 */


#ifndef I_DEFAULT_PARAMS
#define I_DEFAULT_PARAMS /* nothing */
#endif

/*
 * I_DEFAULT_HANDLER(expr,file,line,param) - called when an error is detected.
 */

#ifndef I_DEFAULT_HANDLER /* define default handler */
void _I_default_handler(char *expr, char *file, int line);

#define I_DEFAULT_HANDLER(expr,file,line,param) \
  _I_default_handler(expr,__FILE__,__LINE__)

#endif /* I_DEFAULT_HANDLER */

/*
 * _IGHPS(e,g,h,p,s) - implements the general case for invariant handling.
 *
 * e - expression to check
 * g - guard, check only if this is true (subject to I_DEFAULT_LEVEL)
 * h - handler, called when a failure is detected
 * p - parameter to pass off to the handler
 * s - string representation of the expression (e.g. "I(x>=i)")
 *
 * _ISD(e) - generates a data declaration for use in postconditions
 * _ISG(e,g) - generates a guarded assignment to a data declaration
 *     for use in postconditions
 *
 *     N.B. The two types are necessary since we cannot guard a C declaration
 *     with an if statement.
 */

#if I_LEVEL == 2 /* always check the assertion */
#define _IGHPS(e,g,h,p,s) \
	do { \
		if(!(e)) { \
			h (s, __FILE__, __LINE__, p); \
		} \
	} while(0)

#define _ID(e) e
#define _ISG(e,g) e
#elif I_LEVEL == 1 /* check it iff g is true */
#define _IGHPS(e,g,h,p,s) \
	do { \
		if(g) { \
			if(!(e)) { \
				h (s, __FILE__, __LINE__, p); \
			} \
		} \
	} while(0)
#define _ID(e) e
#define _ISG(e,g) \
        do { \
		if(g) { \
			e; \
		} \
	} while(0)
#elif I_LEVEL == 0 /* no assertions so just remove them */
#define _IGHPS(e,g,h,p,s) /* nothing */
#define _ID(e) /* nothing */
#define _ISG(e,g) /* nothing */
#endif /* I_LEVEL */

/*
 * And all the user macros; these are used to put in the default arguments.
 * The name is used to determine the arguments; e.g. IGH takes an expression
 * to check; a guard and a handler as parameters. The letters in the names
 * are in ascending order (i.e. IGH(...) not IHG(...)).
 *
 * I[G][H][P] - it must be true (e) with an optional guard, handler and 
 *    parameter for the handler.
 * N[G][H][P] - as for I... except that (e) must never ever be true.
 */

#define I(e) \
  _IGHPS(e,I_DEFAULT_GUARD,I_DEFAULT_HANDLER,I_DEFAULT_PARAMS,"I("#e")")
#define IG(e,g) \
  _IGHPS(e,g,I_DEFAULT_HANDLER,I_DEFAULT_PARAMS,"I("#e")")
#define IH(e,h) \
  _IGHPS(e,I_DEFAULT_GUARD,h,I_DEFAULT_PARAMS,"I("#e")")
#define IP(e,p) \
  _IGHPS(e,I_DEFAULT_GUARD,I_DEFAULT_HANDLER,p,"I("#e")")
#define IGH(e,g,h) \
  _IGHPS(e,g,h,I_DEFAULT_PARAMS,"I("#e")")
#define IGP(e,g,p) \
  _IGHPS(e,g,I_DEFAULT_HANDLER,p,"I("#e")")
#define IHP(e,h,p) \
  _IGHPS(e,I_DEFAULT_GUARD,h,p,"I("#e")")
#define IGHP(e,g,h,p) \
  _IGHPS(e,g,h,p,"I("#e")")

#define N(e) \
  _IGHPS((!(e)),I_DEFAULT_GUARD,I_DEFAULT_HANDLER,I_DEFAULT_PARAMS,"N("#e")")
#define NG(e,g) \
  _IGHPS((!(e)),g,I_DEFAULT_HANDLER,I_DEFAULT_PARAMS,"N("#e")")
#define NH(e,h) \
  _IGHPS((!(e)),I_DEFAULT_GUARD,h,I_DEFAULT_PARAMS,"N("#e")")
#define NP(e,p) \
  _IGHPS((!(e)),I_DEFAULT_GUARD,I_DEFAULT_HANDLER,p,"N("#e")")
#define NGH(e,g,h) \
  _IGHPS((!(e)),g,h,I_DEFAULT_PARAMS,"N("#e")")
#define NGP(e,g,p) \
  _IGHPS((!(e)),g,I_DEFAULT_HANDLER,p,"N("#e")")
#define NHP(e,h,p) \
  _IGHPS((!(e)),I_DEFAULT_GUARD,h,p,"N("#e")")
#define NGHP(e,g,h,p) \
  _IGHPS((!(e)),g,h,p,"N("#e")")

/*
 * ID(e) - declares a variable to be used to store values for a postcondition.
 *        This can include an initialiser. 
 *        Note this declaration is not disabled by I_DEFAULT_GUARD
 * IS(e) - an assignment to a variable. This statement is enabled by 
 *        I_DEFAULT_GUARD
 * ISG(e,g) - the guarded version of IS
 */

#define ID(e) _ID(e)
#define IS(e) _ISG(e,I_DEFAULT_GUARD)
#define ISG(e,g) _ISG(e,g)

#else /* defined(WITHOUT_NANA) */

#define I(e) /* empty */
#define IG(e,g) /* empty */
#define IH(e,h) /* empty */
#define IP(e,p) /* empty */
#define IGH(e,g,h) /* empty */
#define IGP(e,g,p) /* empty */
#define IHP(e,h,p) /* empty */
#define IGHP(e,g,h,p) /* empty */

#define N(e) /* empty */
#define NG(e,g) /* empty */
#define NH(e,h) /* empty */
#define NP(e,p) /* empty */
#define NGH(e,g,h) /* empty */
#define NGP(e,g,p) /* empty */
#define NHP(e,h,p) /* empty */
#define NGHP(e,g,h,p) /* empty */

#define ID(e) /* empty */
#define IS(e) /* empty */
#define ISG(e,g) /* empty */

#endif /* !defined(WITHOUT_NANA) */

#ifdef __cplusplus
}
#endif

#endif /* _I_h_ */



