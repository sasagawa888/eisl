/*
 * showconfig.c - used to display the autoconf generated configure
 *   variables used by nana.
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
 * Id: showconfig.c,v 1.3 1998/01/17 22:15:23 pjm Exp 
 */

#include <nana.h>

"NANA_NAME ==>" NANA_NAME

"DI_MAKE_VALID_BREAKPOINT(e) ==> " DI_MAKE_VALID_BREAKPOINT(e)
"DL_MAKE_VALID_BREAKPOINT() ==> " DL_MAKE_VALID_BREAKPOINT()

"I_DEFAULT_HANDLER(e,f,l,p) ==> " I_DEFAULT_HANDLER(e,f,l,p)
"ALWAYS_INCLUDE_MALLOC ==> " ALWAYS_INCLUDE_MALLOC

#if HAVE_VSNPRINTF == 1
"HAVE_VSNPRINTF defined   ==> good, we will use it for logging."
#elif HAVE_VSPRINTF == 1
"HAVE_VSNPRINTF undefined ==> no vsnprintf means we use vsprintf"
"                         ==> which of course may open a security hole"
"                         ==> similar to gets(3), i.e. size of buffer"
"                         ==> is not passed to vsprintf."
"                         ==> Solution: get a new library"
#else
"HAVE_VSN?PRINTF undefined ==> oops, get a new library"
"                          ==> configure hasn't found vsprintf or vsnprintf"
"                          ==> if you really have it"
"                          ==> define it yourself in nana-config.h"
#endif

