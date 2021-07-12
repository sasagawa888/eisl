# UNIX library wrappers

A lot of people don't know, but there are quite a lot of useful libraries in a standard UNIX system.
Code using them should be portable because they're defined by a vendor-neutral standard, e.g.
[UNIX V7](https://en.wikipedia.org/wiki/Single_UNIX_Specification)
or an
[IETF RFC](https://tools.ietf.org/html/rfc4506).
I wrapped some I personally found useful in the past for use from Lisp code, an overview follows.
The code can also be consulted for more detailed questions.

This library is by no means complete.
For an example of a more-or-less complete wrapper around the UNIX API, see
[scsh](https://scsh.net/docu/html/man-Z-H-1.html#node_toc_start).

## Syslog

[Syslog](https://man.openbsd.org/syslog)
is the standard logging framework, there's no need to write your own.
I actually implemented a higher-level interface following
[OpenLisp](http://www.eligis.com/)
based on the raw C calls.
It's very simple to use:

```lisp
(import "logger")
...
  (log-add 'debug "f: x ~A y ~A x y)
```

## Regular expressions

If you have used UNIX for some time you'll probably be familiar with these.
I implemented the interface from OpenLisp, but used the standard C library functions rather than implement my own engine.
Also, the syntax is 
[POSIX Extended Regular Expressions (ERE)](https://man.openbsd.org/re_format.7#EXTENDED_REGULAR_EXPRESSIONS)
which may be slightly different to what you are used to.

## Virtty

This supports the creation of text-user-interfaces.
It uses the standard
[curses](https://man.openbsd.org/curses)
library, but I adopted an interface that is probably due to Le-Lisp.
At least, the best description of the interface is a chapter in the
[Le-Lisp manual](https://github.com/c-jullien/lelisp/blob/master/manual/lelisp.pdf).

A local extension is some support for menus and forms.
I don't claim to have great aesthetic taste, so feel free to rework screen layouts, interactions, etc. to be friendlier.
An example of use is in *example/crud.lsp*.

## Internationalisation

The support I implemented here is limited to Western European languages
for now.
However, it should be easily adaptable to any single-byte encoding.
Supporting East Asian languages is more challenging, I think it might require EISL to change to wchar\_t characters and strings internally.

### Message catalogues

This is just a thin wrapper around the
[catopen](https://man.openbsd.org/catopen)/
[catgets](https://man.openbsd.org/catgets.3)/
[catclose](https://man.openbsd.org/catclose.3)
calls.
The man pages have more details.

*NB*: annoyingly, Linux "gencat" has a problem with Latin-9 encoding input.
This didn't happen on other platforms.
I guess this is something for future research.

### Iconv support

This supports conversion between a myriad of codepages.
However, I only use it for between
[Latin-9](https://en.wikipedia.org/wiki/ISO/IEC_8859-15)
and UTF-8.
Even then, I tried to make things as transparent as possible.

### Locale support

This was the least satisfactory part for me.
My aim was to support four functions to start, strcoll, toupper, tolower and isspace.
However, OpenBSD have made an (arguably wise) decision to not support the Latin-9 locale, so the code can't work there.
And I think there is a bug in the OS libraries on macOS 11, even my C test code failed there.
Things do work as designed on Linux, for what it's worth.

How things are *supposed to* work is something like

```lisp
(import "i18n")
(defglobal *locname* (safe-setlocale))
(init-locale *locname*)
(toupper #\a)  ; But accented letters now work too
```

At the very least calling `setlocale` is required at the start of curses programs, i.e. virtty programs for eisl.
This is cleaner as a separate call not coupled to virtty.

## Database

It's not as full-featured as an SQL database, but there is a facility for indexed files in the UNIX standards.
*ndbm.lsp* is a thin wrapper around this library.
*persist.lsp* is an attempt at something higher level, something like transparent object persistence but it could probably do some work.
*crud.lsp* is an example of using this feature.

Note that for Linux you'll need to install whatever is the equivalent of the `libgdbm-dev` and `libgdm-compat-dev` Ubuntu packages for your distro.

## Others

Don't forget that there is already a
[TCPIP](TCPIP.md)
module for socket communication.
