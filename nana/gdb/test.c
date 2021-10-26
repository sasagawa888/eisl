/*
 * test.c - used for testing our macros
 *
 *    nana - improved support for invariant checking and logging
 *    Copyright (C) 1996  P.J.Maker <pjm@gnu.org>
 * 
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Library General Public
 *    License as published by the Free Software Foundation; either
 *    version 2 of the License, or (at your option) any later version.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Library General Public License for more details.
 * 
 *    You should have received a copy of the GNU Library General Public
 *    License along with this library; if not, write to the Free
 *    Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Header: /home/pjm/cvs/nana/gdb/test.c,v 1.3 1998/06/22 07:06:03 pjm Exp  
 */


#include <stdio.h>
#include <math.h>

int twice(int i) {
     i = i * 2;
     
     return i ;
}

int abs(int i) {
     if(i >= 0) {
	  return i;
     } else {
	  return -i;
     }
}

int distance(int i, int j) {
     return abs(i - j);
}

main() {
     setbuf(stdout, NULL); /* disable buffering */

     printf("** main()\n");
     printf("** 1: %d\n", distance(1,-5));
     printf("** 2: %d\n", distance(twice(1),-5));
     printf("** 3: %d\n", distance(3,-5));
}



     

	  
