;; M-expression samples

foo[x] = x+1

fact[n] = 
    [eq[n;0]->1;t->*[n;fact[n-1]]]

