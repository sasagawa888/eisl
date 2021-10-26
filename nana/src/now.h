/*
 * now.h - some simple minded time measurement support for nana.
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
 * Id: now.h,v 1.2 1998/07/08 10:56:12 pjm Exp 
 */


#ifndef _now_h_
#define _now_h_ 1

#ifdef __cplusplus
extern "C" {
#endif

/*
 * now() - returns the current real time in seconds from the wallclock
 *   using gettimeofday(2). Accuracy (quoted from IPM documentation) is:
 *
 *   SUNOS 4 and 5, HPUX           approx 1us
 *   Linux                         approx 100us
 *   SGI, AIX                      approx 10ms
 *
 *   If you need something a bit faster try either the cycles.h library 
 *   or use $cycles in the simulator.
 */

double now(void); 

/*
 * now_reset() - resets the values returned by now() back to 0 so that
 *   the values are a little smaller. You might use this as part of your
 *   initialisation sequence to make time values easier to read (e.g. 
 *   123.4566 rather than 81828282.8888)
 */

void now_reset(void);

/*
 * now_delta(t) - used to make a delta time counter, the argument is the
 *   used to record the last event we are measuring the time from.
 *
 * t = now(); ...; now_delta(&t); ...; now_delta(&t); ...
 *
 */

double now_delta(double *t);

#ifdef __cplusplus
}
#endif

#endif /* _now_h_ */

