# At first
Please read this first.
The document folder contains various documents. Mainly explains how to use the library.

# Common
Some libraries need to be compiled. They use a C wrapper and will not work unless compiled. Please do as follows:

```
on terminal
$ sudo make install

```
Any lisp library that needs to be compiled will be automatically compiled and saved in the given directory.

## Why?
Libraries are supposed to be saved in a given directory. "sudo make install" saves the compiled code in that directory.

## Note
Each library has a dependent C library. If it is not installed, it will not compile. The makefile contains the Lisp files for the library. Please delete Lisp file names that you don't need for the time being. they will not be compiled.

makefile
```
# Files in library/ that need to be compiled
SRC_LISP := library/bit.lsp \
	    library/escape.lsp \
	    library/i18n.lsp \
	    library/logger.lsp \
	    library/ndbm.lsp \
	    library/opengl.lsp \
	    library/regex.lsp \
	    library/tcltk.lsp \
	    library/tcpip.lsp \
	    library/virtty.lsp

```

If you modify or improve the library, please do the above make again.


# Documents

## Library
![bit](BIT.md)

![combination](COMBINATION.md)

![compiler](COMPILER.md)

![complex](COMPLEX.md)

![csv](CSV.md)

![datetime](DATETIME.md)

![elixir](ELIXIR.md)

![escape](ESCAPE.md)

![formatter](FORMATTER.md)

![formula](FORMULA.md)

![functions](FUNCTIONS.md)

![functionsJ](FUNCTIONSJ.md)

![hash](HASH.md)

![lazy](LAZY.md)

![list](LIST.md)

![math](MATH.md)

![macro](MACRO.md)

![matrix](MATRIX.md)

![mexp](MEXP.md)

![opengl](OPENGL.md)

![prolog](PROLOG.md)

![seq](SEQ.md)

![sort](SORT.md)

![tcltk](TCLTK.md)

![tcpip](TCPIP.md)

![unixlibs](UNIXLIBS.md)

# Development
![debug](DEBUG.md)

![cross](CROSS.md)

![profiler](PROFILER.md)

![test](TEST.md)

![Edlis](EDLIS.md)

# Extension

![module](MODULE.md)

![unicode](UNICODE.md)

![ctrlchar](CTRLCHAR.md)

![chaitin](CHAITIN.md)


# Specification

![summary](SUMMARY.md)

![ISLisp](ISLISP.md)

![ISLisp(Japanese)](ISLISP-ja.md)

![verification](VERIFICATION.md)


# Other

![policy](POLICY.md)

![bench](BENCH.md)

