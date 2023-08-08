#|
Ramanujan's formula
x[0] = sqrt(1)
x[n+1] = sqrt(1 + 2 * x[n])
lim max=>inifinit rama(max,1) -> 3.0
base is any number. 
> (load "./example/rama.lsp")
> (rama 30 2)
3
> (rama 3 2)
2.50829
> 
|#
(defun rama (max base)
    (labels ((r (n)
               (if (> n max)
                   base
                   (sqrt (+ 1 (* n (r (+ n 1))))) )))
        (r 2)))
