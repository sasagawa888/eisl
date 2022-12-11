;; data for PL/0 instant compiler
(program gcd
     (const (x = 10)(y = 45))
     (var z)
     (procedure gcd1 
        ((var a b)
         (a := x) (b := y)
         (while (a /= b) do
            (if (a < b) then (b := (b - a)) else (a := (a - b))))
         (z := a)))
     ((call gcd1)
      (write z)))


