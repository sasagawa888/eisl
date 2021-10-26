/*
 * cycles.c - measures CPU cycles using architecture specific extensions.
 * 
 * Currently just for the pentium using the RDTSC instruction
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
 * $Id: cycles.c,v 1.1.1.1 1999/09/12 03:26:50 pjm Exp $
 */

#include <nana-config.h>

#if HAVE_CYCLES /* only compile this file if we can measure CPU cycles */

#include <now.h>
#include <cycles.h>

/*
 * measure - does a single measurement using a spin loop running for
 *   duration. Sets min/max appropriately (note: min is the smallest
 *   number of the cps which is the LONGEST time!)
 *
 * Assumptions: 
 *
 *   1. We can be preempted by another process at any time;
 *      hence the min..max return values.
 *   2. We use doubles for some of the calculations and this
 *      should be allright since the number of cycles occurring
 *      during a single measurement should be representable in 
 *      in a double (I hope).
 */

static void measure(double duration, CYCLES *min, CYCLES *max) {
  double start_min, start_max, end_min, end_max;
  CYCLES start, end;

  start_min = now();
  start = cycles();
  start_max = now();

  do {
    end_min = now();
  } while((end_min - start_min) < duration);

  end = cycles();
  end_max = now();

  *max = (CYCLES) (((double)(end - start))/(end_min - start_max));
  *min = (CYCLES) (((double)(end - start))/(end_max - start_min));
}

static CYCLES min_cps, max_cps;

/*
 * cycles_per_second - performs n measurements of duration d and returns
 *   the maximum value which should be fairly close to the correct
 *   value (and pigs fly). The values min_cps and max_cps are reset
 *   upon every call to this routine.
 */

CYCLES cycles_per_second(double d, int n) {
  int i;
  CYCLES min, max;

  measure(d, &min_cps, &max_cps);
  for(i = 1; i < n; i++) {
    measure(d, &min, &max);
    if(min < min_cps) {
      min_cps = min;
    }
    if(max > max_cps) {
      max_cps = max;
    }
  }
  return max_cps;
}

CYCLES cycles_per_second_min() {
  return min_cps;
}

CYCLES cycles_per_second_max() {
  return max_cps;
}

double cycles_diff(CYCLES start, CYCLES stop) {
  return ((double)(stop - start))/((double) max_cps);
  
}

#endif /* HAVE_CYCLES */

