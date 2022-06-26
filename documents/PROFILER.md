# Profiler
The interpreter has a profiler for code improvements.

## set profiler for user-defined-function
Give the prof function 'user arguments. After that, the profile data of the activated user-defined function is saved.
```
(prof 'user)
```
## set profiler for built-in-function
Give the prof function 'sys arguments. After that, the profile data of the activated user-defined function is saved.
```
(prof 'sys)
```
## clear profile data
Give the prof function 'cl arguments. The profile data will be cleared.
```
(prof 'cl)
```

## print profile data
Give the prof function 'pr arguments. The profile data will be printed.

```
Easy-ISLisp Ver2.52
> (load "bench/triang.lsp")
T
> (prof 'sys)
T
> (gogogo 22)
NIL
> (prof 'pr)
function-name           elapsed-time      executions
PROF                     0.000000                  0
=                        2.856079           19608148
ELT                      1.888676           16623530
SET-ELT                  0.192065            1133551
+                        0.348184            5973031
MEMBER                   0.000110                774
NOT                      0.000212                774
CONS                     0.000308                775
CDR                      0.000159                774
T
> 
```
## stop profiler
Give the prof function nil arguments. The profiler stops.
```
(prof nil)
```