# UNIX library wrappers

A lot of people don't know, but there are quite a lot of useful libraries in a standard UNIX system.
Code using them should be portable because they're defined by a vendor-neutral standard, e.g. UNIXV7 or some IETF RFCs.
I wrapped some I personally found useful in the past for use from Lisp code, an overview follows:

## Syslog

This is the standard logging framework, there's no need to write your own.
I actually implemented a higher-level interface following OpenLisp based on the raw C calls.
It's very simple to use:

```lisp
(import "logger")
...
  (log-add 'debug "f: x ~A y ~A x y)
```

## Regular expressions

If you have used UNIX for some time you'll probably be familiar with these.
I implemented the interface from OpenLisp, but used the standard C library functions rather than implement my own engine.
Also, the syntax is POSIX Extended Regular Expressions (ERE) which may be slightly different to what you are used to.

## Virtty

This supports the creation of text-user-interfaces.
It uses the standard curses library, but I adopted an interface that is probably due to Le-Lisp.
At least, the best description of the interface is a chapter in the Le-Lisp manual.

## Internationalisation

The support I implemented here is limited to Western European languages for now.
However, it should be easily adaptable to any single-byte encoding.
Supporting East Asian languages is more challenging, I think it might require EISL to change to wchar\_t characters and strings internally.

### Message catalogues

This is just a thin wrapper around the catopen/catgets/catclose calls.
The man pages have more details.

### Iconv support

This supports conversion between a myriad of codepages.
However, I only use it for between Latin-9 and UTF-8.
Even then, I tried to make things as transparent as possible.

### Locale support

This was the least satisfactory part for me.
My aim was to support four functions, strcoll, toupper, tolower and isspace.
However, OpenBSD have made an (arguably wise) decision to not support the Latin-9 locale, so the code can't work there.
And I think there is a bug in the OS libraries on macOS 11, even my C test code failed there.
Things do work as designed on Linux, for what it's worth.

At the very least calling `setlocale` is required at the start of curses programs, i.e. virtty programs for eisl.
This is cleaner as a separate call not coupled to virtty.

## Miscellaneous

It may not be ideal, but I put calls that didn't belong in an obvious category in the "unix" module.
For now, only the `getenv` function and `perror` are defined here (but I'm not sure if perror is that useful to call from Lisp, perhaps it should really be called from C code).

## Others


