(import "elixir")

#|
(tm q0 2 '(0 1 1 1 0 1 1 1 1 0))
this calculates 2+3=5
|#

(defpattern tm
    ((q0 _p _t) (when (= (nth _p _t) 1)) (state q0 _p _t) (tm q0 (+ _p 1) _t))
    ((q0 _p _t) (when (= (nth _p _t) 0)) (state q0 _p _t) (tm q1 _p (set _p _t 1)))
    ((q1 _p _t) (when (= (nth _p _t) 1)) (state q1 _p _t) (tm q2 (+ _p 1)) _t))



#|
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



nth(1,[X|_],X).
nth(N,[_|Xs],Y) :-
    N>1,
    N1 is N-1,
    nth(N1,Xs,Y).

set(1,[_|Ls],X,[X|Ls]).
set(N,[L|Ls],X,[L|Y]) :-
    N>1,
    N1 is N-1,
    set(N1,Ls,X,Y).

state(S,P,T) :-
    P1 is P*2,
    tab(P1),
    write(S),nl,
    write(T),nl.
    
|#
