# Debug

## trace

Puts the user-defined function in the trace state.
Once in the trace state, the arguments and their return values will be displayed when the function is executed.

```
> (trace fact)
T
> (fact 3)
ENTERING: FACT(3)
 ENTERING: FACT(2)
  ENTERING: FACT(1)
   ENTERING: FACT(0)
   EXITING: FACT 1
  EXITING: FACT 1
 EXITING: FACT 2
EXITING: FACT 6
6
> 
```

When called with no arguments, the name of the function currently being traced is displayed. 

```
> (trace)
(FACT)
> 
```

## untrace

Cancels the trace state.

```lisp
(untrace fact)
```

If no arguments are given, all functions in the trace state are cleared. 

## backtrace

Display the most recently executed built-in functions, with arguments.

```
> (fact 5)
120
> (backtrace)
(FACT (- N 1))
(- N 1)
(IF (= N 0) 1 (* N (FACT (- N 1))))
(= N 0)
(BACKTRACE)
T
```

## break

The `break` function aborts execution and enters the debugger (see below).

```
(defun fact (n)
  (if (= n 0)
      (break)
      (* n (fact (- n 1)))))

> (fact 3)
break
> 
```

## macroexpand-1

This can be used to see if a macro expands correctly. 

```
> (defmacro when (x y) `(if ,x ,y))
T
> (macroexpand-1 '(when (= 1 2) 3))
(IF (= 1 2) 3)
> 
```

## Debugger

The `break` function and errors interrupt execution and launch the debugger.
When you enter the debugger, the prompt changes to ">>".
"?" brings up the help screen.

```
> (break)
break
debug mode ?(help)
>> ?
?  help
:b backtrace
:d dynamic environment
:e environment
:i identify examining symbol
:q quit
:r room
:s stepper ON/OFF
other S exps eval
>> 
```

## Debugging C Code

This is a very different task to the above. Most users should never need to do it, but the procedure is written down here just in case.

An important tool here is the special "DEBUG" build of the interpreter. But this requires some setup. First, you need to get the full version of the Nana library instead of the trivial stubs that are checked in:

```sh
cd eisl
rm -r nana
git clone https://github.com/pjmaker/nana.git
cd nana
make distclean
```

*NB*: Be careful not to check in changes that would require ordinary users to install Nana.

Now you should be able to create a debug build. Note that this will run `autoreconf`, so you must have the automake and autoconf packages installed for your OS.

```sh
make clean
make 'DEBUG=1'
```

(You can supply `OPSYS=` if necessary too.)

### Sample Debugger Usage

This is taken from 
[issue #131](https://github.com/sasagawa888/eisl/issues/131).

```
$ lldb ./eisl
(lldb) break set --name abort
(lldb) run
...
Easy-ISLisp Ver2.12
> (standard-input)
./eisl.h:233: I(res != ((void*)0)) failed; dumping core
Process 25048 stopped
...
(lldb) bt
* thread #1, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
  * frame #0: 0x0000000180a8f3d8 libsystem_c.dylib`abort
    frame #1: 0x0000000100079c3c eisl`_I_default_handler(exprn="I(res != ((void*)0))", file="./eisl.h", line=233) at I.c:51:6
    frame #2: 0x00000001000045f4 eisl`GET_NAME(addr=980) at eisl.h:233:5
    frame #3: 0x000000010000ab20 eisl`printstream(addr=980) at main.c:1436:53
    frame #4: 0x0000000100002e24 eisl`print(addr=980) at main.c:1249:2
    frame #5: 0x0000000100002794 eisl`main(argc=1, argv=0x000000016fdff730) at main.c:307:6
    frame #6: 0x0000000180b65430 libdyld.dylib`start + 4
(lldb) 
```

The conclusion is that, at least for this function, the problem is trying to print the result. Previous testing often called `(standard-output)`, but always as an argument to `(format)`, not printing to the REPL. What it is trying to print is cell 980 in the heap, which can be nicely printed as follows:

```
(lldb) print heap[980]
(cell) $0 = {
  val = {
    fltnum = 4.0780135404262676E-314
    lngnum = 8253991296
     = {
      car = {
        intnum = -335943296
        subr = 0x00000001ebf9e980 (__sF)
        port = 0x00000001ebf9e980
        dyna_vec = 0x00000001ebf9e980
        dyna_fvec = 0x00000001ebf9e980
      }
      cdr = (intnum = 0)
    }
  }
  aux = 53
  prop = 0
  name = 0x0000000000000000
  tag = STREAM
  flag = FRE
  option = '\x0e'
  trace = '\0'
}
(lldb)
```

Now it's clear. It's an intentional crash (actually, a call to `abort()`) in the DEBUG build. The reason is that a postcondition (i.e `ENSURE` assertion) is violated, `GET_NAME()` should return a non-NULL string. However, some streams like `(standard-input)` have a NULL name in the heap. Now is a good time to jump into "solution space".

You can substitute gdb for lldb above, but you'll need to change the [command syntax](https://kapeli.com/cheat_sheets/LLDB_to_GDB_Command_Map.docset/Contents/Resources/Documents/index) slightly.
