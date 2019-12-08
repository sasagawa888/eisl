# Easy-ISLisp

Easy-ISLisp(EISL) is an interpreter and compiler compatible with ISLisp standard.
EISL was written by Kenichi Sasagawa
https://qiita.com/sym_num/items/793adfe118514668e5b0


# Installation
On Linux  type "make" on terminal.

On Windows rename winmakefile -> makefile. and type "make" on terminal.
Require MINGW gcc

We confirmed the operation in the following environment.
- Ubuntu 16.04 GCC 5.4
- Ubuntu 18.04 GCC 7.3
- Raspberry Pi3 Raspbian GCC 6.3
- openSUSE Leap 42.3 GCC 4.8.5
- Debian GNU/Linux GCC 6.3 GCC 7.3
- Windows10 MINGW GCC 5.3


# Invoke
- eisl (Windows)
- ./eisl (Linux)

Linux version, REPL is editable. If you not use editable REPL, invoke with -r option.

```
./eisl -r
```
# Goal
I hope that Lisp will become more popular. I hope many people enjoy Lisp. EISL aims at easy handling.

# Compiler
EISL has compiler. it generate GCC code and generate object code.

```
Invoke with -c option
./eisl -c compiler.lsp

or (load "compiler.lsp")

(compile-file "foo.lsp")

(load "foo.o")

example
./eisl -c compiler.lsp
Easy-ISLisp Ver0.91
> (compile-file "tarai.lsp")
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
> (load "tarai.o")
T
> (time (tarai 12 6 0))
Elapsed Time(second)=0.024106
<undef>
> (time (ack 4 1))
Elapsed Time(second)=3.728262
<undef>
>
```
You can compile the compiler itself. Compilation is faster.

# Builtin editor
EISL(Linux version) has builtin editor.

### Invoke editor
(edit file-name-string) example (edit "foo.lsp")

(edit nil) edit recent file again.

### Command
- CTR+O save file.
- CTRL+X quit editor.
- CTRL+K delete selection.
- CTRL+U paste from clip board.
### Editing
move cursol
- ESC A mark current row position. After this operation, cursol up or down reverse selected rows. ESC A again, unmark. Similer to nano editor
- Enter key insert tab for Lisp automatic
- Insert key switch insert/overwrite
- Tab key insert tab for Lisp
- BackSpace key delete backword char
- Delete key delete forwaord char
- Home key display top page
- ESC |(SSH)
- End key display end page
- ESC /(SSH)
- PageUp key PageUp
- Ctrl+Y(SSH)
- PageDown PageDown
- Ctrl+V(SSH)
- ESC TAB completion.

### Setting
- (set-editor 'indent 'auto) set auto indent mode.
- (set-editor 'indent 'manual) set manual indet mode. To indent tab key.
- (set-editor 'tab 'lisp) set tab for Lisp style.
- (set-editor 'tab 2) set tab 2.
- (set-editor 'tab 4) set tab 4.
- (set-editor 'tab 8) set tab 8.

### syntax highlighting.
- n = 0-7
0=Black, 1=Red, 2 =Green, 4=Blue, 5=Maggenta, 6=Syan, 7=White.
- (set-editor 'syntax-color n)
- (set-editor 'builtin-color n)
- (set-editor 'extended-color n)
- (set-editor 'string-color n)
- (set-editor 'comment-color n)


# WiringPi
Version for Raspberry include library for wiringPi.

In order to use wiringPi, you need to compile wiringpi.lsp(in example folder) and invoke EISL with super user.

```
sudo ./eisl
```
and 

```
(load "wiringpi.o")
```
please see exsample code "led.lsp"

"wiringpi.lsp" is source code of wiringpi.o.

```
EISL <==================================> C
(wiringpi-spi-setup ch speed) <===> wiringPiSPISetup (SPI_CH, SPI_SPEED)
(wiringpi-setup-gpio ) <===> wiringPiSetupGpio()
(pin-mode n 'output) <====> pinMode(n, OUTPUT) or 'input -> INPUT 'pwm-output -> PWM-OUTPUT
(digital-write n v) <===> digitalWrite(n, v)
(digital-write-byte v) <===> digitalWriteByte(value)
(digital-read pin) <===> digitalRead(pin)
(delay howlong) <===> void delay(unsigned int howLong)
(pull-up-dn-control pin pud) <===> pullUpDnControl(pin,pud)
(pwm-set-mode 'pwm-mode-ms) <===> pwmSetMode(PWM_MODE_MS); or 'pwm-mode-bal -> PWM_MODE_BAL
(pwm-set-clock n) <===> pwmSetClock(n)
(pwm-set-range n) <===> pwmSetRange(n)
(pwm-write pin value) <===> pwmWrite(pin , value)
```

### Examples.

```
;;LED on/off

(defglobal pin 5)
(defglobal flag nil)

(defun test (n)
   (cond ((null flag) (wiringpi-setup-gpio)(setq flag t)))
   (pin-mode pin 'output)
   (for ((i 0 (+ i 1)))
        ((> i n) t)
        (digital-write pin 1)
        (delay 1000)
        (digital-write pin 0)
        (delay 1000)))


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
- (random n) random-integer from 0 to n
- (random-real) random-float-number from 0 to 1
- (gbc) invoke garbage collection.
- (gbc t) display message when invoke GC.
- (gbc nil) not display message when invoke GC.
