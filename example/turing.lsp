(import "elixir")

#|
(tm 'q0 2 '(0 1 1 1 0 1 1 1 1 0))
this calculates 2+3=5
|#



(defpattern tm
    ((q0 _p _t) (when (= (nth _p _t) 1)) (state 'q0 _p _t) (tm 'q0 (+ _p 1) _t))
    ((q0 _p _t) (when (= (nth _p _t) 0)) (state 'q0 _p _t) (set _p _t 1) (tm 'q1 _p _t))
    ((q1 _p _t) (when (= (nth _p _t) 1)) (state 'q1 _p _t) (tm 'q1 (- _p 1) _t))
    ((q1 _p _t) (when (= (nth _p _t) 0)) (state 'q1 _p _t) (tm 'q2 (+ _p 1) _t))
    ((q2 _p _t) (when (= (nth _p _t) 1)) (state 'q2 _p _t) (set _p _t 0) (tm 'q3 _p _t))
    ((q3 _p _t) (when (= (nth _p _t) 0)) (state 'q3 _p _t) (tm 'q4 (+ _p 1) _t))
    ((q4 _p _t) (when (= (nth _p _t) 1)) (state 'q4 _p _t) (set _p _t 0) (tm 'q5 _p _t))
    ((q5 _p _t) (when (= (nth _p _t) 0)) (state 'q5 _p _t) (tm 'qf (+ _p 1) _t))
    ((qf _p _t) (state 'qf _p _t)))


(defun nth (point tape)
    (elt tape (- point 1)))


(defun set (point tape element)
    (setf (elt tape (- point 1)) element))


(defun tab (n)
    (for ((i 1 (+ i 1)))
         ((> i n) t)
         (format (standard-output) " ")))

(defun state (state point tape)
    (tab (+ (* (- point 1) 2) 1))
    (format (standard-output) "~A~%" state)
    (format (standard-output) "~A~%" tape))


