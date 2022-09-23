#|
Deterministic finite automaton
Using defpattern macro in elixir lib
dfa(_state,_input)
_state symbol that means state
_input list of char

automaton function transforms string to list of char. and call dfa

example
    num & not num
      -> b <-
not  /       \ not
num /         \ num
--> a -------> c
       num      num

K={a,b,c}
Σ={0~9,a~z}
q0=a
F={c}
> (automaton "123")
ACCEPT
> (automaton "1x3")
REJECT
> (automaton "xxy")
REJECT
|#

(import "elixir")

(defun automaton (str)
    (dfa 'a (convert str <list>)))

;;Deterministic finite automaton
(defpattern dfa
    ((a (_input . _rest)) (when (number-char _input)) (dfa 'c _rest))
    ((a (_input . _rest)) (when (not (number-char _input))) (dfa 'b _rest))
    ((b empty) (print 'reject))
    ((b (_input . _rest)) (dfa 'b _rest))
    ((c empty) (print 'accept))
    ((c (_input . _rest)) (when (number-char _input)) (dfa 'c _rest))
    ((c (_input . _rest)) (when (not (number-char _input))) (dfa 'b _rest)))


(defun number-char (x)
    (member x '(#\0 #\1 #\2 #\3 #\4 #\5 #\6 #\7 #\8 #\9)))