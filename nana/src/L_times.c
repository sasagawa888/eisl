/*
 * L_times.c - implements a circular buffer of timed events with 
 *    names.
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
 * Id: L_times.c,v 1.1.1.1 1997/11/23 11:45:50 pjm Exp 
 */

#include <L_times.h>

#include <stdio.h>
#include <nana_error.h>

L_TIMES *L_times_create(unsigned long n) {
  L_TIMES *p = malloc(sizeof(L_TIMES));
  if(p != 0) {
    p->ncalls = 0;
    p->freeslot = 0;
    p->maxsamples = n;
    p->times = calloc(n, sizeof(NANA_TIME));
    p->names = calloc(n, sizeof(char *));
    p->wraparound = 1;
    if(p->times == 0 || p->names == 0) {
      return 0;
    } else {
      return p;
    }
  } else {
    return 0;
  }
}

void L_times_delete(L_TIMES *l) {
  if(l != 0) {
    if(l->times != 0) {
      free(l->times);
    }
    if(l->names != 0) {
      free(l->names);
    }
    free(l);
  }
}

void L_times_wraparound(L_TIMES *l, int wrap) {
  if(l == 0) {
    nana_error("L_times_wraparound: arg1 == 0");
  } else {
    l->wraparound = wrap;
  }
}

void L_times_add(L_TIMES *l, char *n, NANA_TIME t) {
  if(l->wraparound) { /* only keep latest data */
    l->times[l->freeslot] = t;
    l->names[l->freeslot] = n;
    l->freeslot++;
    if(l->freeslot == l->maxsamples) {
      l->freeslot = 0;
    }
    l->ncalls++;
  } else { /* ignore data once full */
    if(l->freeslot < l->maxsamples) {
      l->times[l->freeslot] = t;
      l->names[l->freeslot] = n;
      l->freeslot++;
    } /* else full so ignore it */
    l->ncalls++;
  }
}

void L_times_clear(L_TIMES *l) {
  if(l == 0) {
    nana_error("L_times_clear: arg1 == 0");
  } else {
    l->freeslot = 0;
    l->ncalls = 0;
  }
}

void L_times_dump(L_TIMES *l, FILE *f) {
  unsigned long i;
  if(l == 0) {
    nana_error("L_times_dump: arg1 == 0");
  }

  fprintf(f, "L_times_dump = %ld calls\n", l->ncalls);
  if(l->wraparound) { /* wraparound */
    if(l->ncalls > l->maxsamples) {
      for(i = l->freeslot; i < l->maxsamples; i++) {
	fprintf(f, "%f\t%s\n", l->times[i], l->names[i]);
      }
    }
    for(i = 0; i < l->freeslot; i++) {
      fprintf(f, "%f\t%s\n", l->times[i], l->names[i]);
    }
  } else { /* no wraparound so just [0..nsamples-1] */
    for(i = 0; i < l->freeslot; i++) {
      fprintf(f, "%f\t%s\n", l->times[i], l->names[i]);
    }
  }
}
    




