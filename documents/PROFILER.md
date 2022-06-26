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

## print prifile data
Give the prof function 'pr arguments. The profile data will be printed.

```
> (load "bench/triang.lsp")
T
> (prof 'sys)
T
> (gogogo 22)
NIL
> (prof 'pr)
function-name             elapsed-time  executions
TARAI                  381.765326           12604859
NIL                      0.000000                  0
PROF                     0.000000                  0
=                        3.034068           19608148
ELT                      2.000991           16623530
AND                      3.406498            5801796
SET-ELT                  0.201269            1133551
SETF                     0.457731            1134327
+                        0.363931            5973031
COND                   104.652676            5802571
OR                      97.439175            5973806
FOR                     99.043868             162710
IF                       0.000509               1549
DYNAMIC                  0.000068               1550
MEMBER                   0.000154                774
NOT                      0.000247                774
CONS                     0.000402                775
SET-DYNAMIC              0.000511                775
LET                      0.006949                774
CONVERT                  0.000114                774
CDR                      0.000203                774
DYNAMIC-LET              0.000000                  0
T
> 

```
## stop profiler
Give the prof function nil arguments. The profiler stops.
```
(prof nil)
```