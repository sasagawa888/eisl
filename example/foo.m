;; M-expression samples

foo[x] <= x+1

bar[x;y;z] <= x^3+y^3+z^3

boo[x;y] <= sin[x]+cos[x]

fact[n] <= 
    [n=0->1;t->n*fact[n-1]]

fib[n] <=
    [n=0 -> 0;
     n=1 -> 1;
     t -> fib[n-1]+fib[n-2]]

tarai[x;y;z] <=
    [x<=y -> y;
     t->tarai[tarai[x-1;y;z];
              tarai[y-1;z;x];
              tarai[z-1;x;y]]]

ack[m;n] <=
    [m=0 -> n+1;
     n=0 -> ack[m-1;1];
     t -> ack[m-1;ack[m;n-1]]]

