# Debug

- (trace fn1 fn2 ... fn)
- (untrace fn1 fn2 ... fn) or (untrace)
- (backtrace)
- (break)
- (macroexpand-1)


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

```sh
sudo make clean
sudo make install USE_GDB=1

gdb eisl
```


There is also a `heapdmp` function that may be useful if you are still at the REPL.
