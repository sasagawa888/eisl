/*
 * L_buffer.c -  implements logging to a circular buffer.
 *
 * Improvements: it might be worthwhile to implement a compression 
 *   scheme for the buffer, decompression could be handled by the 
 *   L_buffer_dump routine. 
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
 * Id: L_buffer.c,v 1.2 1998/01/17 11:31:00 pjm Exp 
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

#include <L_buffer.h>

#include <nana_error.h>

/*
 * L_buffer_create - malloc's and initialises a buffer with space for 
 *     size bytes worth of messages. Returns NULL on failure.
 *
 *     The buffer is initialised to '\0' so we know which locations haven't
 *     been written to yet. An alternate implementation would use a
 *     counter for this but this way seems easier and cuts down the overhead
 *     in the working functions (even if only by a couple of instructions).
 */

L_BUFFER *L_buffer_create(size_t size) { 
  L_BUFFER *p = malloc(sizeof(L_BUFFER));
  if(p != 0) {
    p->size = size;
    p->data = malloc(size);
    p->free = 0;
    p->wraparound = 1;
    if(p->data != 0) {
      int i;
      for(i = 0; i < size; i++) {
	p->data[i] = '\0';
      }
      return p;
    } else {
      return 0;
    }
  } else {
    return 0;
  }
}

/*
 * L_buffer_wraparound - turn wraparound on/off for a buffer, note
 *    that wraparound is turned on by default byu L_buffer_create.
 */

void L_buffer_wraparound(L_BUFFER *b, int wraparound) {
  if(b == 0) {
    nana_error("L_buffer_wraparound: arg1 == 0");
  } else {
    b->wraparound = wraparound;
  }
}


/*
 * L_buffer_putchar - copies a single char into the buffer.
 */
  
void L_buffer_putchar(L_BUFFER *b, char c) {
  if(b == 0) {
    nana_error("L_buffer_putchar: buffer == 0?");
  }

  if(b->wraparound) { /* wrapping around so */
    b->data[b->free++] = c; /* write the char */
    if(b->free == b->size) { /* at the end so back to the beginning */
      b->free = 0;
    }
  } else { /* not wrapping around */
    if(b->free < b->size) {
      b->data[b->free++] = c;
    }
  }
}

/*
 * L_buffer_puts - copies the argument into the buffer.
 */

void L_buffer_puts(L_BUFFER *b, char *s) {
  int i;

  if(b == 0) {
    nana_error("L_buffer_puts: buffer == 0");
  }

  /* map 0 pointer to "(null)" - suggested by Phil Blecker */
  if(s == (char *) 0) {
    s = "(null)";
  }

  /* just copy into the buffer with wraparound */
  for(i = 0; s[i] != '\0'; i++) {
    L_buffer_putchar(b, s[i]);
  }
}


/*
 * L_buffer_printf - does a standard printf operation into the buffer.
 *
 * 
 * Currently we use vs[n]printf to write it to a buffer before 
 * before finally copying it off into our L_BUFFER using L_buffer_puts.
 *
 */

void L_buffer_printf(L_BUFFER *b, const char *format, ...) {

  char buffer[512]; 
  int n;
  va_list ap;
     

  if(b == 0) {
    nana_error("L_buffer_printf: buffer == 0?");
  }

  /* printf the arguments into buffer[0...] */
  va_start(ap, format); 
#if HAVE_VSNPRINTF == 1
  n = vsnprintf(&buffer[0], sizeof(buffer), format, ap);
#elif HAVE_VSPRINTF == 1
  n = vsprintf(&buffer[0], format, ap);
#else
#error We need either vsprintf or vsnprintf for this one;
#error Perhaps you should install liberty or some other rational library;
#error Under Solaris 2.5 it has been reported that our autoconf script
#error fails to find vsprintf, if so define HAVE_VSPRINTF in your makefile;
#endif

  va_end(ap);

  L_buffer_puts(b, &buffer[0]);
}

/*
 * L_buffer_dump - dumps the buffer out from the oldest to the
 *      newest; we also check for non-printing characters.
 */

void L_buffer_dump(L_BUFFER *b, FILE *fp) {
  int i;
  char c;

  if(b == 0) {
    nana_error("L_buffer_dump: buffer == 0?");
  }

  /* print the banner */
  fprintf(fp, "* L_buffer_dump =\n");

  /* if not wraparound just print it and be done */
  if(!(b->wraparound)) {
    fprintf(fp, "%s", b->data);
    goto end;
  }

  /* otherwise a bit of searching is in order */
  /* skip '\0' bytes from free upwards to find the oldest message */
  for(i = b->free+1; ; i++) { 
    if(i == b->size) { /* wraparound at end of buffer */ 
      i = 0;
    }
    if(i == b->free) { /* been through the entire buffer of '\0' */
      fprintf(fp, "buffer was empty\n");
      goto end;
    }
    if(b->data[i] != '\0') { /* found oldest one */
      break;
    }
  }
    
  /* now print out in time order */
  do {
    c = b->data[i];
    if(isprint(c) || isspace(c)) {
      fputc(c, fp);
    } else { /* can't be printed so print it in hex */
      fprintf(fp, "* non-printable character 0x%x\n", c);
    }
    i++;
    if(i == b->size) {
      i = 0;
    }
  } while(b->data[i] != '\0' && i != b->free);
end:     
  fprintf(fp, "* end of dump\n");
}

/*
 * L_buffer_clear - reinitialise the buffer.
 */

void L_buffer_clear(L_BUFFER *b) {
  int i;

  if(b == 0) {
    nana_error("L_buffer_clear: buffer == 0?");
  }

  for(i = 0; i < b->size; i++) {
    b->data[i] = '\0';
  }
  b->free = 0;
}

/*
 * L_buffer_delete - free up all the memory.
 */

void L_buffer_delete(L_BUFFER *b) {
  if(b != 0) {
    if(b->data != 0) {
      free(b->data);
    }
    free(b);
  }
}

