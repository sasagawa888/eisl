/*
 * eiffel.h - an assertion checking scheme similar to Eiffel,
 *     see pg 133 of the Eiffel book.
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
 * Id: eiffel.h,v 1.1.1.1 1997/11/23 11:45:50 pjm Exp 
 */

#ifndef _eiffel_h_
#define _eiffel_h_

#ifdef __cplusplus
extern "C" {
#endif

#include <nana.h>

/*
 * EIFFEL_CHECK_LEVEL - this defines the various levels of checking.
 *
 *   See page 133 of "Eiffel: the language" by Bertrand Meyer.
 */

typedef enum { 
  CHECK_NO,        /* no assertion checking */
  CHECK_REQUIRE,   /* only require, i.e. method preconditions */
  CHECK_ENSURE,    /* require+ensure, i.e. method pre/postconditions */
  CHECK_INVARIANT, /* as ensure plus check class invariant on entry/exit */
  CHECK_LOOP,      /* as invariant plus loop invariants + variants */
  CHECK_ALL        /* everything including check statements */
} EIFFEL_CHECK_LEVEL;

/*
 * EIFFEL_CHECK - the level of checking to be done for this compile.
 *   This can be overridden, e.g. by compiling with -DEIFFEL_CHECK=CHECK_ALL
 */

#ifndef EIFFEL_CHECK
#define EIFFEL_CHECK CHECK_REQUIRE 
#endif

/*
 * invariant() - each class using this library should provide a method
 *   called invariant() which returns true if the object is
 *   consistent, false otherwise. This method will be called by the
 *   checking macros below.  Since some classes don't have class
 *   invariants we will define a default one which always succeeds.  
 */

static inline bool invariant() {
  return true;
}

/*
 * EIFFEL_DOEND - if EIFFEL_DOEND is defined then (at the suggestion
 *   of Bertrand Meyer (Eiffel's author)) we define the DO and END 
 *   macros which check the class invariant on method entry/exit. To
 *   use these macros your methods should look something like:
 *
 *   // if EIFFEL_DOEND is defined
 *   void Stack::push(int n) 
 *   DO 
 *      REQUIRE(..) ; // note this is optional
 *      .. 
 *      if(x >= 10) { 
 *        ...
 *	}
 *   END
 *
 *   if EIFFEL_DOEND is not defined then we revert to the old
 *   behaviour where invariants are checked by REQUIRE and ENSURE 
 *   calls. For example:
 *
 *   // if EIFFEL_DOEND is not defined
 *   void Stack::push(int n) 
 *   {
 *      REQUIRE(x <= 10); // note this is required if you 
 *      ...               // wish to check invariants
 *      ENSURE(...);
 *   }
 */

#ifdef EIFFEL_DOEND

#define DO  { IG(invariant(), EIFFEL_CHECK >= CHECK_INVARIANT); 
#define END  IG(invariant(), EIFFEL_CHECK >= CHECK_INVARIANT); }
#define REQUIRE(e) IG(e, EIFFEL_CHECK >= CHECK_REQUIRE)
#define ENSURE(e) IG(e, EIFFEL_CHECK >= CHECK_ENSURE)

#else /*!defined EIFFEL_DOEND */

/*
 * REQUIRE(e) - precondition for a method, this also checks the class
 *   invariant. 
 */

#define REQUIRE(e) \
  do { \
    IG(e, EIFFEL_CHECK >= CHECK_REQUIRE); \
    IG(invariant(), EIFFEL_CHECK >= CHECK_INVARIANT); \
  } while(0)

/*
 * ENSURE(e) - postcondition for a method, this also checks the class
 *   invariant
 */

#define ENSURE(e) \
  do { \
    IG(e, EIFFEL_CHECK >= CHECK_ENSURE); \
    IG(invariant(), EIFFEL_CHECK >= CHECK_INVARIANT); \
  } while(0)

#endif /* defined EIFFEL_DOEND */

/*
 * CHECK(e) - check an assertion in inline code.
 */

#define CHECK(e) \
  IG(e, EIFFEL_CHECK >= CHECK_ALL)

/*
 * INVARIANT(e) - loop invariant.
 */

#define INVARIANT(e) \
  IG(e, EIFFEL_CHECK >= CHECK_LOOP)

/*
 * VARIANT(e) - there is no support for variant checking yet, a syntax
 *   exists buts it too ugly for me. Perhaps if someone is interested 
 *   I'll build it; personally I find termination the least of my problems!
 */

#ifdef __cplusplus
}
#endif

#endif
