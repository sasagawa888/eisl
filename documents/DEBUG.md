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

```
(untrace fact)
```

If no arguments are given, all functions in the trace are cleared. 

## backtrace

Displays the execution status of the built-in function. 

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

Breaks execution by embedding the break function. 

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

It can be used to see if the macro is well expanded. 

```
> (defmacro when (x y) `(if ,x ,y))
T
> (macroexpand-1 '(when (= 1 2) 3))
(IF (= 1 2) 3)
> 
```

## debugger

The break function or error interrupts launches the debugger.
When you enter the debugger, the prompt changes to >>. 
? Will bring up the help screen. 

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
