#|
初めての人のためのLISP
竹内郁雄　著　より
|#

(defun atom-count (x)
  (cond ((nullx ) 0)
    ((atom x) 1)
    (t (+ (atom-count (car x))
          (atom-count (cdr x))))))