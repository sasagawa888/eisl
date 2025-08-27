# Easy-ISLisp

Easy-ISLisp(EISL) is an interpreter and compiler compatible with the [ISLisp standard](https://minejima.jp/ISLispHyperDraft/islisp-v23.html).
EISL was written by Kenichi Sasagawa

See [ISLisp](https://en.wikipedia.org/wiki/ISLISP)
YouTube [introduction of Easy-ISLisp](https://www.youtube.com/watch?v=RxBPEY5_MKs&t=76s)

![EISL](documents/eisl.png)

# Installation

Change to the git cloned or downloaded Easy-ISLisp directory.

- Type "sudo make install".
- For more advanced hacking on the interpreter itself, you can build a debug-mode executable by supplying a "DEBUG=1" argument to make, but this is unlikely to be needed by someone starting out.

Update Easy-ISlisp
- Type "sudo make clean".
- Type "sudo make install".


You may get an error that the curses.h file cannot be found when compiling EISL & Edlis.
In this case, enter the following from the terminal

```sh
sudo apt install libncurses-dev
```
# Supported OS:

- Raspberry Pi OS
- Ubuntu
- Linux Mint

 Use of other operating systems is at your own discretion."


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

# WiringPi

On paspberry PI, Eisl includes system function of WiringPi. 

```lisp
EISL <==================================> C
(wiringpi-spi-setup ch speed) <===> wiringPiSPISetup (SPI_CH, SPI_SPEED)
(wiringpi-setup-gpio ) <===> wiringPiSetupGpio()
(pin-mode n 'output) <====> pinMode(n, OUTPUT) or 'input -> INPUT 'pwm-output -> PWM-OUTPUT
(digital-write n v) <===> digitalWrite(n, v)
(digital-write-byte v) <===> digitalWriteByte(value)
(digital-read pin) <===> digitalRead(pin)
(delay-seconds howlong) <===> void delay(unsigned int howLong)
(delay-microseconds howlong) <===> void delayMicroseconds(unsigned int howLong)
(pull-up-dn-control pin pud) <===> pullUpDnControl(pin,pud)
(pwm-set-mode 'pwm-mode-ms) <===> pwmSetMode(PWM_MODE_MS); or 'pwm-mode-bal -> PWM_MODE_BAL
(pwm-set-clock n) <===> pwmSetClock(n)
(pwm-set-range n) <===> pwmSetRange(n)
(pwm-write pin value) <===> pwmWrite(pin , value)
```

### Examples.

```lisp
;;LED on/off

(defglobal pin 5)
(defglobal flag nil)

(defun test (n)
   (cond ((null flag) (wiringpi-setup-gpio)(setq flag t)))
   (pin-mode pin 'output)
   (for ((i 0 (+ i 1)))
        ((> i n) t)
        (digital-write pin 1)
        (delay-seconds 1)
        (digital-write pin 0)
        (delay-seconds 1)))


;;control servo moter.
;;SG90 Micro servo Digital 9g

(defun setup ()
  (cond ((null flag) (wiringpi-setup-gpio ) (setq flag t)))
  (pin-mode 18 'pwm-output)
  (pwm-set-mode 'pwm-mode-ms)
  (pwm-set-clock 400)
  (pwm-set-range 1024))

(defun test (n)
   (pwm-write 18 n))
```

# Functions for debug
- (trace fn1 fn2 ... fn)
- (untrace fn1 fn2 ... fn) or (untrace)
- (backtrace)
- (break)
- (macroexpand-1)

# Extended functions

| Function              | Description                                    |
| --------------------- | ---------------------------------------------- |
| (atom x)              | is x not cons? return T or NIL                 |
| (eval x)              | evaluate s-expression x                        |
| (nconc x y)           | append list x and list y  destructively        |
| (random n)            | random-integer from 0 to n                     |
| (random-real)         | random-float-number from 0 to 1                |
| (set-random n)        | set random seed to non-negative number n       |
| (gbc)                 | invoke garbage collection.                     |
| (gbc t)               | display message when invoke GC.                |
| (gbc nil)             | not display message when invoke GC.            |
| (heapdump n)          | display cell dump list from nth address        |
| (instance n)          | display instance of nth address                |
| (defmodule name body) | see tests/module.lsp                           |
| (import x)            | import library. e.g. (import "compiler")       |
| (quit)                | quit from interpreter                          |
| (load filename)       | load code from file e.g. (load "foo.lsp")      |
| (getenv var)          | get environment-var e.g. (getenv "EASY_ISLISP")|
| (line-argument n)     | get nth argument from OS. n is zero base       |
| (line-argument)       | get all arguments from OS.                     |
| (print obj)           | print obj to standard-stream                   |
| (system cmd)          | send bash command e.g. (system "ls")           |
| (funcp x)             | is x user-defined-function? return T or NIL    |
| (subrp x)             | is x subr? return T or NIL                     |
| (macrop x)            | is x macros? return T or NIL                   |
| (fixnump x)           | is x fixnum?(32bit) return T or NIL            |
| (longnump x)          | is x longnum?(64bit) return T or NIL           |
| (bignump x)           | is x bignum? return T or NIL                   |
| (macroexpand-1 x)     | macroexpand x only once                        |
| (macroexpand-all x)   | macroexpand x completely                       |

# Parallel functions

| Function              | Description                                    |
| --------------------- | ---------------------------------------------- |
| (mp-create n)         | create n processes. see PARA.md                |   
| (mp-call fun a1 .. an)| apply fun args with multi-process. see PARA.md |
| (mp-exec s1 ... sn)   | progn with multi-process. see PARA.md          |
| (mp-and s1 ... sn)    | parallel and with multi-process. see PARA.md   |    
| (mp-or s1 ... sn)     | parallel and with multi-process. see PARA.md   | 
| (mp-eval n exp)       | evaluate exp in nth child Lisp                 |
| (mp-close)            | close all process. see PARA.md                 |
| (mt-create n)         | create n threads. see PARA1.md                 |
| (mt-call fun a1 .. an)| apply fun args with multi-thread.see PARA1.md  |
| (mt-exec s1 ... sn)   | progn with multi-thread. see PARA1.md          |
| (mt-lock s1 ... sn)   | progn with mutex multi-thread. see PARA1.md    |
| (mt-close)            | close all threads. see PARA1.md                |
| (dp-create n)         | create n distributions. see PARA2.md           |
| (dp-call fun a1 .. an)| apply fun args with distributed. see PARA2.md  |
| (dp-exec s1 ... sn)   | progn with distributed. see PARA2.md           |
| (dp-and s1 ... sn)    | parallel and with distributed. see PARA2.md    |
| (dp-or s1 ... sn)     | parallel or with distributed. see PARA2.md     |
| (dp-transfer fn)      | transfer file to all child Lisp. see PARA2.md  |
| (dp-compile fn)       | compile file in all child Lisp. see PARA2md    |
| (dp-load fn)          | load file to parent and all child Lisp.PARA2.md|
| (dp-close)            | close all distributions. see PARA2.md          |
| (dp-halt)             | close all childs and shutdown see PARA2.md     |

# TCP/IP functions

| Function                      | Description                                    |
| ----------------------------- | ---------------------------------------------- |
| (create-server-socket port)   | create socket for server see TCPIP.md          |
| (create-client-socket port ip)| create socket for client see TCPIP.md          |
| (send-socket socket str)      | send message to socket                         |
| (recv-socket socket)          | receive message from socket                    |
| (close-socket socket)         | close socket                                   |
  




