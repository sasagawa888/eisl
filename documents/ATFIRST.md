# At first
Please read this first.
The document folder contains various documents. Mainly explains how to use the library.

# Common
Some libraries need to be compiled. They use a C wrapper and will not work unless compiled. Please do as follows:

```
on REPL
> (compile-file "library/???.lsp") ??? is filename.

on terminal
$ sudo make install

```

## Why?
Libraries are supposed to be saved in a given directory. "sudo make install" saves the compiled code in that directory.