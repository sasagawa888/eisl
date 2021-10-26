/*
 * example.c - a small example for the nana shortform generator.
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
 * $Id: example.c,v 1.1.1.1 1999/09/12 03:26:49 pjm Exp $
 */

#include <stdio.h>
#include <ctype.h>

typedef int myint;
typedef char myvector[80];
typedef struct {
  int a, b;
} mypair;

typedef struct s
{
  int a;
  union b {
    float f;
    char s[3];
  } a;
} xray;

class xray {
  int a ;
public:
  float f();
};


void f() {
  more code;
}

void
f() {
  code;
}

void
f(int a, int b) {
  code;
}

void
f(int a, 
  int b) {
  code;
  cpde;
  cde;
}

void
f(int a, 
  int b,
  int c) {
  test();
}

void
f(int a, 
  int b,
  int c) 
{
  REQUIRE(a > b);
  code;
  ENSURE(a > b && 
	 b > c);
}

int g(a,b,c) 
int a, b;
float c;
{
  REQUIRE(a == c);
  printf("hello world");
}

