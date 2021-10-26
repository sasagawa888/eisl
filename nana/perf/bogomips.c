/*
 * bogomips.c - measure Linus's bogo mips using now.h.
 *
 * See also:
 *
 * 0. Linux kernel
 * 1. bogomips-1.2.tar.gz written by Jeff Tranter (Jeff_Tranter@Mitel.COM)
 *    which is available from the sunsite linux archive
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
 */

#include <stdio.h>

#include <now.h>

/*
 * delay - used for the delay loop.
 */

inline void delay(long l) {
  volatile register long i;

  for(i = l; i >= 0; i--) 
    ;
}

double measure() {
  double begin, end, duration;
  long loops = 1;
  
  for(;;) {
    begin = now();
    delay(loops);
    end = now();
    duration = end - begin;
    if(duration >= 1.0) {
      return 2.0*((double) loops)/(((double)duration))/1.0e6;
    }
    loops = loops * 2;
  }
}

#define NMEASURE 10 /* total number of measurements to make */

main() {
  int n;
  double min, max;
  double t;

  min = max = measure();
  
  for(n = 1; n < NMEASURE; n++) {
    t = measure();
    if(t < min) {
      min = t;
    } 
    if(t > max) {
      max = t;
    }
  }
  if(min == max) {
    printf("%.1f BogMips\n", max);
  } else {
    printf("%.1f..%.1f BogMips\n", min, max);
  }
  return 0;
}

    
    


