;; M-expression samples

foo[x] <= x+1

fact[n] <= 
    [n=0->1;t->times[n;fact[n-1]]]

fib[n] <=
    [n=0->0;
     n=1->1;
     t->plus[fib[n-1];fib[n-2]]]