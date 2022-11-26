;; Toy production system 
;; C + O2  -> CO2
;; 2H2 + O2 -> 2H2O
;; C + 2H2 -> CH4
;; CH4 + 2O2 -> CO2 + 2H2O

;; (reaction '(c h2 h2 o2 o2))
(import "elixir")

;; if you exchange rule1&rule2  rule3&rule4 , you will get same result.
(defpattern reaction 
    (((element _x C O2)) (print 'rule1) (pipe (modify _x '(- C) '(- O2) '(+ CO2)) |> (reaction)))
    (((element _x (2 H2) O2)) (print 'rule2) (pipe (modify _x '(- (2 H2))  '(- O2) '(+ (2 H2O))) |> (reaction)))
    (((element _x C (2 H2))) (print 'rule3) (pipe (modify _x '(- C) '(- (2 H2)) '(+ CH4))) |> (reaction))
    (((element _x CH4 (2 O2))) (print 'rule4) (pipe (modify _x '(- CH4) '(- (2 O2)) '(+ CO2) '(+ (2 H2O))) |> (reaction)))
    ((_x) _x))

