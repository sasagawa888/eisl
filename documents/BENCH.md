# Benchmark
I applied the benchmark test written by Mr. Jullien to Easy-ISLisp. 
see bench folder.


# Hardware
Intel(R) Core(TM) i5-6500 CPU @ 3.20GHz

# EISL Compiler
before run, please compile with cpbench.lsp
$ eisl -s bench/runbench.lsp

```
Test 01: Fib     -> ok, time =   0.000495s.
Test 02: Tak     -> ok, time =   0.00258s.
Test 03: Stak    -> 12, time =   0.009302s.
Test 04: Ctak    -> ok, time =   0.005628s.
Test 05: Takl    -> ok, time =   0.004742s.
Test 06: Takr    -> ok, time =   0.002637s.
Test 07: Boyer   -> T, time =   0.058689s.
Test 08: Browse  -> ok, time =   0.259957s.
Test 09: Destru  -> ok, time =   0.006001s.
Test 10: Travini -> ok, time =   0.033001s.
Test 11: Travrun -> ok, time =   0.503954s.
Test 12: Deriv   -> ok, time =   0.045395s.
Test 13: Dderiv  -> ok, time =   0.045697s.
Test 14: Divit   -> ok, time =   0.008829s.
Test 15: Divrec  -> ok, time =   0.002772s.
Test 16: FFT     -> ok, time =   0.064474s.
Test 17: Puzzle  -> ok, time =   0.102663s.
Test 18: Triang  -> ok, time =   1.819389s.
Test 19: Fprint  -> ok, time =   0.000406s.
Test 20: Fread   -> ok, time =   0.000601s.
Test 21: Tprint  -> ok, time = 4e-0600s.
Test 22: Frpoly  -> ok, time =   0.047611s.

Total   3.024827s.


```

# OpenLisp

```
;; OpenLisp v11.1.0 (Build: 6652) by C. Jullien [Oct 30 2020 - 13:48:51]
;; Copyright (c) Eligis - 1988-2020.
;; System 'win64' (64bit, 6 CPU) on 'DESKTOP-0D0L6O5', ASCII.
;; Reading startup ..
;; God thank you, OpenLisp is back again!
? (load "bench/runbench.lsp")

Test 01: Fib -> ok, time = 0.001s.
Test 02: Tak -> ok, time = 0.003s.
Test 03: Stak -> ok, time = 0.015s.
Test 04: Ctak -> ok, time = 0.066s.
Test 05: Takl -> ok, time = 0.006s.
Test 06: Takr -> ok, time = 0.004s.
Test 07: Boyer -> ok, time = 0.048s.
Test 08: Browse -> ok, time = 0.055s.
Test 09: Destru -> ok, time = 0.010s.
Test 10: Travini -> ok, time = 0.050s.
Test 11: Travrun -> ok, time = 0.245s.
Test 12: Deriv -> ok, time = 0.010s.
Test 13: Dderiv -> ok, time = 0.013s.
Test 14: Divit -> ok, time = 0.005s.
Test 15: Divrec -> ok, time = 0.009s.
Test 16: FFT -> ok, time = 0.045s.
Test 17: Puzzle -> ok, time = 0.056s.
Test 18: Triang -> ok, time = 0.744s.
Test 19: Fprint -> ok, time = 0.005s.
Test 20: Fread -> ok, time = 0.001s.
Test 21: Tprint -> ok, time = 0.000s.
Test 22: Frpoly -> ok, time = 0.096s.

Total 1.487s.

;; elapsed time = 1.6486s, (8 gc).
= t
?

```