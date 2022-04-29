(import "elixir")

#|
(tm 'q0 2 '(0 1 1 1 0 1 1 1 1 0))
this calculates 2+3=5
|#



(defpattern tm
    ((q0 _p _t) (when (= (nth _p _t) 1)) (state 'q0 _p _t) (tm 'q0 (+ _p 1) _t))
    ((q0 _p _t) (when (= (nth _p _t) 0)) (state 'q0 _p _t) (tm 'q1 _p (set _p _t 1)))
    ((q1 _p _t) (when (= (nth _p _t) 1)) (state 'q1 _p _t) (tm 'q1 (- _p 1) _t))
    ((q1 _p _t) (when (= (nth _p _t) 0)) (state 'q1 _p _t) (tm 'q2 (+ _p 1) _t))
    ((q2 _p _t) (when (= (nth _p _t) 1)) (state 'q2 _p _t) (tm 'q3 _p (set _p _t 0)))
    ((q3 _p _t) (when (= (nth _p _t) 0)) (state 'q3 _p _t) (tm 'q4 (+ _p 1) _t))
    ((q4 _p _t) (when (= (nth _p _t) 1)) (state 'q4 _p _t) (tm 'q5 _p (set _p _t 0)))
    ((q5 _p _t) (when (= (nth _p _t) 0)) (state 'q5 _p _t) (tm 'qf (+ _p 1) _t))
    ((qf _p _t) (state 'qf _p _t)))

#|

tm(q0,P,T) :-
    nth(P,T,1),
    state(q0,P,T),
    P1 is P+1,
    tm(q0,P1,T).
tm(q0,P,T) :-
    nth(P,T,0),
    state(q0,P,T),
    set(P,T,1,T1),
    tm(q1,P,T1).
tm(q1,P,T) :-
    nth(P,T,1),
    state(q1,P,T),
    P1 is P-1,
    tm(q1,P1,T).
tm(q1,P,T) :-
    nth(P,T,0),
    state(q1,P,T),
    P1 is P+1,
    tm(q2,P1,T).
tm(q2,P,T) :-
    nth(P,T,1),
    state(q2,P,T),
    set(P,T,0,T1),
    tm(q3,P,T1).
tm(q3,P,T) :-
    nth(P,T,0),
    state(q3,P,T),
    P1 is P+1,
    tm(q4,P1,T).
tm(q4,P,T) :-
    nth(P,T,1),
    state(q4,P,T),
    set(P,T,0,T1),
    tm(q5,P,T1).
tm(q5,P,T) :-
    nth(P,T,0),
    state(q5,P,T),
    P1 is P+1,
    tm(qf,P1,T).
tm(qf,P,T) :-
    state(qf,P,T).

|#

(defun nth (point tape)
    (elt tape (- point 1)))


(defun set (point tape element)
    (cond ((= point 1) (cons element (cdr tape)))
          (t (cons (car tape ) (set (- point 1) (cdr tape) element)))))


(defun tab (n)
    (for ((i 1 (+ i 1)))
         ((> i n) t)
         (format (standard-output) " ")))

(defun state (state point tape)
    (tab (+ (* (- point 1) 2) 1))
    (format (standard-output) "~A~%" state)
    (format (standard-output) "~A~%" tape))


