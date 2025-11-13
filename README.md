**“This software is a technology created for peace and freedom.  
It does not wish to serve, in any way, as a tool for oppression, suppression, human rights violations, or dictatorship.”**


# Easy-ISLisp

Easy-ISLisp(EISL) is an interpreter and compiler compatible with the [ISLisp standard](https://minejima.jp/ISLispHyperDraft/islisp-v23.html).
EISL was written by Kenichi Sasagawa

See [ISLisp](https://en.wikipedia.org/wiki/ISLISP)
YouTube [introduction of Easy-ISLisp](https://www.youtube.com/watch?v=RxBPEY5_MKs&t=76s)

![EISL](documents/eisl.png)

# Installation

Change to the git cloned or downloaded Easy-ISLisp directory.

- Type "sudo make install".

Update Easy-ISlisp
- Type "sudo make clean".
- Type "sudo make install".

see document ATFRIST.md

Easy-ISLisp requires ncurses library. Please install ncurses.

```sh
sudo apt install libncurses-dev
```
# Supported OS:

- Raspberry Pi OS
- Ubuntu
- Linux Mint

- Use of other operating systems is at your own discretion.
Unsupported Operating Systems
Operating systems other than the officially supported ones (Raspberry Pi OS, Ubuntu, Mint) are not officially supported, as I do not have the hardware or sufficient experience to properly test them.
If you wish to run this project on an unsupported OS, please feel free to adapt the code on your own.
If your modifications are successful, we encourage you to publish a branch so that others can benefit from your work.

### GNU Emacs support
ISLisp-mode of Emacs is developed by Mr. sasanidas.
Watch the video to see how to use it. https://vimeo.com/614514131

Repository URL:  https://gitlab.com/sasanidas/islisp-mode


# Invoke

```sh
eisl 
```

In the Linux version,the REPL is editable. If you do not want to use the editable REPL, invoke with the -r option.

```sh
eisl -r
```


If you want to start after reading a file, use the -l command-line option.
e.g.

```sh
eisl -l foo.lsp 
```

For other options, see `eisl -h`:

```
$ eisl -h
List of options:
-c           -- EISL starts after reading compiler.lsp.
-f           -- EISL starts after reading formatter.lsp.
-h           -- display help.
-l filename  -- EISL starts after reading the file.
-m N(mega)   -- EISL starts with N*1000000(>=10mega) cells.
-n           -- EISL starts as network child mode.
-r           -- EISL does not use editable REPL.
-s filename  -- EISL runs the file with script mode.
-v           -- dislplay version number.
```

You can also write ISLisp scripts,
following the usual UNIX convention of pointing to the interpreter with the first line, e.g.
```lisp
#!/Users/me/bin/eisl -s
(format (standard-output) "Hello world~%")
```

# Quit

In the REPL type (quit) or Esc+Q.

In the non-editable REPL type (quit) or CTRL+D.

# Introductory article
Mr. Hiroi has published introductory articles about ISLisp. It's written in plain Japanese, so you can easily translate it into your native language with google translator. http://www.nct9.ne.jp/m_hiroi/clisp/islisp.html

# Editable REPL
When entering a line in the REPL, syntax highlighting, completion, and text editing are available.
Key bindings are as follows:

| Key         | Description           |
| ----------- | --------------------- |
| ctrl+F or → | move right            |
| ctrl+B or ← | move left             |
| ctrl+P or ↑ | recall history older  |
| ctrl+N or ↓ | recall history newer  |
| ctrl+A      | move to begin of line |
| strl+E      | move to end of line   |
| ctrl+J ctrl+M or return | send S-exp to Lisp             |
| ctrl+H or back-space    | backspace                      |
| ctrl+D                  | delete one char                |
| Esc Tab                 | completion                     |

# Goal

I hope that Lisp will become more popular.
I hope many people enjoy it.
EISL aims to be user-friendly.

# Compiler

EISL has a compiler.
It generates C code that can be compiled using gcc or clang to object code.

Invoke with the -c option,
`eisl -c`
or `(import "compiler")` in the REPL.
Then you can
```lisp
(compile-file "foo.lsp")
(load "foo.o")
```

For example:

```
eisl -c
Easy-ISLisp Ver1.6
> (compile-file "tests/tarai.lsp")
type inference
initialize
pass1
pass2
compiling PACK
compiling TARAI
compiling FIB
compiling FIB*
compiling ACK
compiling GFIB
compiling TAK
compiling LISTN
compiling TAKL
compiling CTAK
compiling CTAK-AUX

finalize
invoke GCC
T
> (load "tests/tarai.o")
T
> (time (tarai 12 6 0))
Elapsed Time(second)=0.024106
<undef>
> (time (ack 4 1))
Elapsed Time(second)=3.728262
<undef>
>
```

# Invoke editor

By default the `edit` function invokes the
[Edlis](documents/EDLIS.md)
editor.
But note that it respects the UNIX convention of the `VISUAL` and `EDITOR` environment variables, so if either of those is defined it will be used instead.

(edit file-name-string) example (edit "foo.lsp")

# Functions for debug
see documents/DEBUG/md

# Extended functions
see documents/EXTENDED.md

# Parallel functions
see documents/PARA.md

# TCP/IP functions
see documents/TCPIP.md
