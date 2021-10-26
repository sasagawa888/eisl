/*
 * L_buffer.h -  interface to the circular buffer logging routines.
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
 * Id: L_buffer.h,v 1.1.1.1 1997/11/23 11:45:50 pjm Exp 
 */


#ifndef _L_buffer_h_
#define _L_buffer_h_ 1

#ifdef __cplusplus
extern "C" {
#endif


#ifndef _nana_config_h_
#include <nana-config.h>
#endif

#include <stddef.h>

/*
 * L_BUFFER - the user must use L_buffer_create() to make one
 *    of these for each log buffer you require.
 */

typedef struct {
  size_t size;       /* number of bytes allocated */
  char *data;        /* the actual data[] to write into */
  size_t free;       /* the current location we are writing into */
  int wraparound;    /* true if buffer should wraparond */
} L_BUFFER;

/*
 * L_buffer_create - malloc's the log buffer and initialises it.
 *
 * L_buffer_wraparound - set the wraparound option for the log buffer.
 *     Note: L_buffer_create sets wraparound on by default.
 *
 * L_buffer_printf - does printf style formatting to a log buffer.
 *
 * L_buffer_puts - copies a string to a log buffer. Note that no trialing
 *      newline is added. This be a fair bit faster than the L_buffer_printf
 *      routine since we don't scan the string more than once.
 *
 * L_buffer_putchar - adds a single character to the buffer. The fastest
 *      way to get data into the buffer.
 *
 * L_buffer_dump - print to standard error the contents of the log buffer
 *      in time order (oldest first).
 *
 * L_buffer_clear - clear the log buffer as if its just been created. This
 *      operation is seperate from L_buffer_dump since you want to make 
 *      sure you've captured the dump'ed data before clearing it.
 *
 * L_buffer_free - free the memory malloc'ed for the buffer.
 */

L_BUFFER *L_buffer_create(size_t size);

void L_buffer_wraparound(L_BUFFER *b, int wraparound);

#ifdef __GNUC__
void L_buffer_printf(L_BUFFER *b, const char *format, ...) 
  __attribute__((format (printf, 2, 3)));
#else
void L_buffer_printf(L_BUFFER *b, const char *format, ...);
#endif

void L_buffer_puts(L_BUFFER *b, char *str);

void L_buffer_putchar(L_BUFFER *b, char c);

#ifdef stdin 
void L_buffer_dump(L_BUFFER *b, FILE *fp);
#endif

void L_buffer_clear(L_BUFFER *b);

void L_buffer_delete(L_BUFFER *);

#ifdef __cplusplus
}
#endif

#endif /* _L_buffer_h_ */

