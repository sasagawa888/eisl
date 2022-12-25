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
![bit](bit.md)

![compiler](compiler.md)

![csv](csv.md)

![formatter](formatter.md)

![formuta](formula.md)
