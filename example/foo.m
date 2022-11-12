;; M-expression samples

foo[x] <= x+1

fact[n] <= 
    [eq[n;0]->1;t->*[n;fact[n-1]]]

fib[n] <=
    [eq[n;0]->0;
     eq[n;1]->1;
     t->plus[fib[n-1];fib[n-2]]]