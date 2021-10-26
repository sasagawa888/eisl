/*
 * calls.c - implements a call to lots of procedures.
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
 * Id: calls.c,v 1.1.1.1 1997/11/23 11:45:50 pjm Exp 
 */

#include <nana_error.h>
#include <stdlib.h>

#include <calls.h>

void calls_add(CALL **head, FUNC fp, void *arg) {
  CALL *p;

  if((p = ((CALL *)malloc(sizeof(CALL)))) != 0) {
    p->func = fp;
    p->arg = arg;
    p->next = *head;
    *head = p;
  } else { /* malloc failed - uhm */
    nana_error("calls_add: out of memory");
  }
}

void calls_exec(CALL **head, FUNC fp, void *arg) {
  CALL *p;
  
  for(p = *head; p != 0; p = p->next) {
    if(((fp == 0) || (fp == p->func)) && 
       ((arg == 0) || (arg == p->arg))) {
      (*(p->func))(p->arg);
    }
  }
}

void calls_delete(CALL **head, FUNC fp, void *arg) {
  CALL *p, *q, *prev;

  p = *head;
  prev = 0; 
  while(p != 0) {
    if(((fp == 0) || (fp == p->func)) && 
       ((arg == 0) || (arg == p->arg))) { /* p should be deleted */
      if(prev != 0) { /* we have a defined predecessor (not the first node) */
	prev->next = p->next; /* relink over p */
	q = p; /* save p away so we can free it later */
	p = p->next;
	/* prev = prev; */
	free(q);
      } else { /* first item in the list */
	q = p;
	*head = p->next;
	p = p->next;
	/* prev = prev; */
	free(q);
      }
    } else { /* p should NOT be deleted */
      prev = p;
      p = p->next;
    }
  }
}  


