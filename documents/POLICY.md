# Policy 

I want to keep Easy-ISLisp as small and simple as possible.

I was a fan of Scheme. It was around R3RS ~ R5RS. I fell in love with Scheme's simple and elegant design philosophy. 
However, after R6RS, Scheme changed its policy to become huge.
I hated the recent huge Scheme.

Around that time, I learned about the ISLisp standard. It is very simple and compact. I fell in love with this.
For this reason I want to keep Easy-IS Lisp as small and simple as possible.

## Hints for C Coding

Although we'd all love to write Lisp, a lot of the interpreter had to be written in C.
This section contains some hints on how to write more robust C code.
In a corporation it would form a mandatory "coding standard", but this project aims to accept help from a wide range of people so it's much more permissive.
Although there's no need to follow it, the OpenBSD style guide is some nice background reading.

First, try to write idiomatic C.
C17 is ok, because we're assuming the compiler is a recent release of gcc or clang anyway.
C++ was evaluated, but the decision was made to not use it.

Use of standard UNIX libraries is ok, e.g. defined by the UNIX07, X-Open and IETF standards.
Please don't write Linux-specific code.

If at some point it seems that a C++ feature would be really useful, it may actually be available as a C library.
Two libraries I'd recommend are cii and Nana, but we probably don't want to go there quite yet.
