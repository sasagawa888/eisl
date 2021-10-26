/*
 * L_times.h - log measurements of time to a circular buffer.
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
 * Id: L_times.h,v 1.2 1998/01/17 10:57:03 pjm Exp 
 */

#ifndef _L_times_h_
#define _L_times_h_ 1

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _nana_config_h_
#include <nana-config.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#ifndef NANA_TIME 
#define NANA_TIME double
#endif

typedef struct {
  unsigned long ncalls; /* total number of calls */
  unsigned long freeslot; /* current freeslot in times, names */
  unsigned long maxsamples; /* max samples to keep */
  int wraparound; /* wraparound (throw away old data) */
  NANA_TIME *times; /* the time for each event */
  char **names; /* the name for each event */
} L_TIMES; 

L_TIMES *L_times_create(unsigned long n);
void L_times_delete(L_TIMES *l);
void L_times_wraparound(L_TIMES *l, int wrap);
void L_times_add(L_TIMES *l, char *n, NANA_TIME t);
void L_times_clear(L_TIMES *l);
void L_times_dump(L_TIMES *l, FILE *f);

#ifdef __cplusplus
}
#endif

#endif /* _L_times_h_ */

