# Benchmark
I applied the benchmark test written by Julian to Easy-ISLisp. 
see bench folder.

# Constraint 
The compiled code of frpoly.lsp does not work properly due to GCC compiler optimization.
Therefore, the compiler version excludes frpoly. 

# Hardware
Intel(R) Core(TM) i5-6500 CPU @ 3.20GHz

# Interpreter
$ eisl -s bench/runbench.lsp

```

Test 01: Fib     -> ok, time =   0.006509s.
Test 02: Tak     -> ok, time =   0.025662s.
Test 03: Stak    -> ok, time =   0.07359s.
Test 04: Ctak    -> ok, time =   0.037173s.
Test 05: Takl    -> ok, time =   0.146051s.
Test 06: Takr    -> ok, time =   0.027699s.
Test 07: Boyer   -> T, time =   0.371107s.
Test 08: Browse  -> ok, time =   0.409977s.
Test 09: Destru  -> ok, time =   0.05987s.
Test 10: Travini -> ok, time =   0.494095s.
Test 11: Travrun -> ok, time =   6.826968s.
Test 12: Deriv   -> ok, time =   0.054394s.
Test 13: Dderiv  -> ok, time =   0.061663s.
Test 14: Divit   -> ok, time =   0.049307s.
Test 15: Divrec  -> ok, time =   0.060932s.
Test 16: FFT     -> ok, time =   0.200734s.
Test 17: Puzzle  -> ok, time =   0.540896s.
Test 18: Triang  -> ok, time =   7.674351s.
Test 19: Fprint  -> ok, time =   0.00048s.
Test 20: Fread   -> ok, time =   0.000454s.
Test 21: Tprint  -> ok, time = 5e-0600s.
Test 22: Frpoly  -> ok, time =   0.022222s.

Total  17.144139s.


```


# Compiler
$ eisl -c -s bench/runcpbench.lsp

```

Test 01: Fib     -> ok, time =   0.000543s.
Test 02: Tak     -> ok, time =   0.002199s.
Test 03: Stak    -> ok, time =   0.029045s.
Test 04: Ctak    -> ok, time =   0.008656s.
Test 05: Takl    -> ok, time =   0.00407s.
Test 06: Takr    -> ok, time =   0.002256s.
Test 07: Boyer   -> T, time =   0.114025s.
Test 08: Browse  -> ok, time =   0.369166s.
Test 09: Destru  -> ok, time =   0.008481000000000001s.
Test 10: Travini -> ok, time =   0.04743s.
Test 11: Travrun -> ok, time =   1.147392s.
Test 12: Deriv   -> ok, time =   0.08071399999999999s.
Test 13: Dderiv  -> ok, time =   0.084243s.
Test 14: Divit   -> ok, time =   0.015301s.
Test 15: Divrec  -> ok, time =   0.003099s.
Test 16: FFT     -> ok, time =   0.118119s.
Test 17: Puzzle  -> ok, time =   0.321164s.
Test 18: Triang  -> ok, time =   3.010385s.
Test 19: Fprint  -> ok, time =   0.00039s.
Test 20: Fread   -> ok, time =   0.000675s.
Test 21: Tprint  -> ok, time = 3e-0600s.

Total   5.367356000000001s.


```
