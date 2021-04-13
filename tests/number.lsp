
(import "number")
;;; test
(defglobal c1 (make-rectangler 3 -4))
(defglobal c2 (make-rectangler 5 -6))
(defglobal r1 (make-rational 3 4))
(defglobal r2 (make-rational 5 8))

(display (e+ c1 c2))
(display (e+ r1 r2))
    
