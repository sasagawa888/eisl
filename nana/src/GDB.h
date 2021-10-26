/*
 * GDB.h -  basic support macros for putting gdb commands in C.
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
 * Id: GDB.h,v 1.1.1.1 1997/11/23 11:45:50 pjm Exp 
 */

#ifndef _GDB_h_
#define _GDB_h_ 1

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
 * GDB(c) - just puts the command into the output of nana
 *   c should be a single line of text
 */

#ifdef _NANA_FILTER_
#define GDB(command) @@command@@
#else
#define GDB(command) /* nothing */
#endif

/*
 * GDBCALL(c) - calls a gdb command whenever control reaches the
 *      current line.
 */

#ifdef _NANA_FILTER_
#define GDBCALL(comd) \
  @@break @__FILE__:__LINE__@@ \
  @@command@@ \
  @@silent@@ \
  @@comd@@ \
  @@cont@@ \
  @@end@@
#else
#define GDBCALL(c) DI_MAKE_VALID_BREAKPOINT(1)
#endif

#else /* defined(WITHOUT_NANA) */

#define GDB(e) /* empty */
#define GDBCALL(e) /* empty */

#endif /* !defined(WITHOUT_NANA) */

#ifdef __cplusplus
}
#endif

#endif /* _GDB_h_ */

