/*
 * cycles.h - measures CPU cycles using architecture specific extensions.
 * 
 * Currently only setup for the pentuim using the RDTSC instruction
 *
 * Copyright (c) 1998 Phil Maker <pjm@gnu.org>
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
 * $Id: cycles.h,v 1.1.1.1 1999/09/12 03:26:50 pjm Exp $
 */

#ifndef _cycles_h_
#define _cycles_h_ 1

#ifdef __cplusplus
extern "C" {
#endif

#include <nana-config.h>

#if HAVE_CYCLES 

#if HAVE_RDTSC /* enabled by configure --enable-rdtsc instruction */

/* 
 * Pentium RDTSC instruction - 
 *
 * 0. 64 bit counter running at clock speed so 
 *    (2^64)/(1000*1000*1000*60*60*24*365) = 584 years @ 1GHz
 * 1. reset to 0 on power on (is it)
 * 2. on pentium or later CPUs
 */ 
 
typedef unsigned long long CYCLES;

#define cycles() \
({ \
     CYCLES __t; \
     asm volatile ("rdtsc ; movl %%edx,%1; movl %%eax,%0" \
	 : "=m" (__t), "=m" (*(((char *)&__t) + 4)) \
	 : /* no input */ \
	 : "eax", "edx", "cc", "memory" \
       ); \
    __t; \
})

#endif /* HAVE_RDTSC */

/* 
 * Calibration routines which should be available for all platforms
 *
 * cycles_per_second(t,n) - performs n measurements using a spin loop 
 *    using the now() function to wait for t or more seconds. It returns
 *    the max number of cycles per second that it measures. As a side
 *    effect (gasp) it also sets the values return by cycles_per_second_min()
 *    and cycles_per_second_max().
 *
 * Notes:
 * 
 *    1. each call to cycles_per_second() resets our min/max values.
 *    2. overflows are always possible if t gets too large.
 *
 */

CYCLES cycles_per_second(double t, int n); 
CYCLES cycles_per_second_min();
CYCLES cycles_per_second_max();

/* 
 * cycles_diff - returns the time in second between two cycle measurement
 *
 * Note: start <= stop
 *       stop - start should be representable in a double.
 * !No overflow detection
 */

double cycles_diff(CYCLES start, CYCLES stop);

#endif /* HAVE_CYCLES */
#ifdef _cplusplus
};
#endif

#endif /* _cycles_h_ */

