/*
 * now.c - basic C support for getting the current time.
 *
 * TODO: provide support for other timing routines, changes in headers, etc
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
 * Id: now.c,v 1.2 1998/01/17 11:31:00 pjm Exp 
 */

#ifdef HAVE_GETTIMEOFDAY
#include <sys/time.h>
#else
#include <sys/timeb.h>
#endif

#include <nana_error.h>

#include <now.h>

static double base_time = 0.0;

#ifdef HAVE_GETTIMEOFDAY
double now(void) {
  struct timeval t;

  if(gettimeofday(&t,0)) {
    nana_error("now: gettimeofday failed");
  } else {
    return (((double) t.tv_sec) + (((double) t.tv_usec) * 1e-6)) -
      base_time ;
  }
}
#else
double now(void) {
  struct timeb t;
  
  ftime(&t);
  return (((double) t.time) + (((double) t.millitm) * 1e-3)) - base_time ;
}
#endif /* HAVE_GETTIMEOFDAY */

#ifdef HAVE_GETTIMEOFDAY
void now_reset(void) {
  struct timeval t;

  if(gettimeofday(&t,0)) {
    nana_error("now_reset: gettimeofday failed");
  } else {
    base_time = ((double) t.tv_sec) + (((double) t.tv_usec) * 1e-6);
  }
}
#else
void now_reset(void) {
  struct timeb t;

  ftime(&t);
  base_time = ((double) t.time) + (((double) t.millitm) * 1e-3);
}
#endif /* HAVE_GETTIMEOFDAY */

double now_delta(double *dp) {
  double t = now();
  double d = t - *dp;
  *dp = t;
  return d;
}


    



