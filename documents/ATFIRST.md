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

If you modify or improve the library, please do the above make again.