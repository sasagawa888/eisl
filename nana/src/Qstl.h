/*
 * Qstl.h - support for quantifers when using STL under C++.
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
 * Id: Qstl.h,v 1.1.1.1 1997/11/23 11:45:50 pjm Exp 
 */

#ifndef _Qstl_h_
#define _Qstl_h_ 1

#ifndef __cplusplus
This header file should only ever be included by a C++ program!
Better luck next time. 
#error 10
#endif

#include <Q.h>

/*
 * Warning: You might be tempted to remove the typedef from the
 *   following code but it seems to be required by g++. Scoping
 *   of type declarations allows us to us a fixed name.
 */

#define AO(name,container,predicate) \
  ({ \
    typedef typeof(container) _Qstl_type_; \
    A(_Qstl_type_::iterator name = container.begin(), \
	name != container.end(), \
	++name, \
	predicate); \
  })

#define EO(name,container,predicate) \
  ({ \
    typedef typeof(container) _Qstl_type_; \
    E(_Qstl_type_::iterator name = container.begin(), \
	name != container.end(), \
	++name, \
	predicate); \
  })

#define E1O(name,container,predicate) \
  ({ \
    typedef typeof(container) _Qstl_type_; \
    E1(_Qstl_type_::iterator name = container.begin(), \
	name != container.end(), \
	++name, \
	predicate); \
  })

#define CO(name,container,predicate) \
  ({ \
    typedef typeof(container) _Qstl_type_; \
    C(_Qstl_type_::iterator name = container.begin(), \
	name != container.end(), \
	++name, \
	predicate); \
  })

#define SO(name,container,exprn) \
  ({ \
    typedef typeof(container) _Qstl_type_; \
    S(_Qstl_type_::iterator name = container.begin(), \
	name != container.end(), \
	++name, \
	exprn); \
  })

#define PO(name,container,exprn) \
  ({ \
    typedef typeof(container) _Qstl_type_; \
    P(_Qstl_type_::iterator name = container.begin(), \
	name != container.end(), \
	++name, \
	exprn); \
  })

#endif
