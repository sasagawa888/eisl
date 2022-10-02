;; idea memo
;; production system 
;; C + O2  -> CO2
;; 2H2 + O2 -> 2H2O
;; C + 2H2 -> CH4
;; CH4 + 2O2 -> CO2 + 2H2O

;; extend defpattern to handle set 
(defpattern reaction (x)
    ((element 'C 'O2) (reaction (modify x '(- C O2) '(+ CO2))))
    ((element '(2 'H2) 'O2 ) (reaction (modify x '(- (2 H2) O2) '(+ (2 H2O)))))
    ((element 'C  '(2 H2)) (reaction (modify x '(- x C (2 H2)) '(+ CH4))))
    ((element 'CH4 '(2 O2)) (reaction (modify x '(- x CH4 (2 O2)) '(+ CO2 (2 H2O))))))

