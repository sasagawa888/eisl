;;Doctor 

(defun string->list (str)
    (string->list1 (convert str <list>) "" nil))

(defun string->list1 (ls word result)
    (cond ((null ls) (reverse (cons (convert word <symbol>) result)))
          ((char= (car ls) #\space) (string->list1 (cdr ls) "" (cons (convert word <symbol>) result)))
          (t (string->list1 (cdr ls) (string-append word (convert (car ls) <string>)) result))))

(defun list->string (ls)
    (if (null ls)
        ""
        (string-append (convert (car ls) <string>) " " (list->string (cdr ls)))))

(defpattern rule)

#|
flag(dummy). % to avoid existence error

doctor :-
	write('Hi!,I am a doctor'),
    nl,tab(3),write('Speak up'),
    nl,prog.

prog :-
    reader(X),!,rule(X),assertz((rule(X))),prog.


reader(X) :- nl,input(X),nl.

printer([]).
printer([X|Y]) :- write(X),tab(1),printer(Y).


rule([i,am,worried|L]) :-
    write('How long have you been worried'),
    tab(1),printer(L),tab(1),write('.').

rule([stop]) :-
    write('I am sorry our time is up.'),
    nl,write('Good bye !'),nl,clear,abort.
rule([X]) :-
    member(mother,x),!,
    write('Tell me more about your family.'),
    assert((flag(on))),nl.


rule(X) :-
    member(computer,X),write('Do machines frighten you.').
rule([yes]) :- message.
rule([no]) :- message.
rule(X) :- count(X,4),
        write('Please do not use Words like that.').

rule(X) :- flag(on),
        write('Earlier you spoke of your mother'),retract(flag).
rule(X) :- 
        write('You say so before, too?').
rule(X) :- member(remember,X),!,
        write('you spoke me next, ok!'),stem(Y),
        printlist(Y).
rule(X) :- write('I see,tell me more.'),nl.

message :- write('Please do not be so short with me').

count([X|[]],Y) :- name(X,Z),counter(Z,Y).
counter([],0).
counter([X|Y],M) :- counter(Y,N),M is N+1.

clear :- flag(on),retract((flag(on))).
clear.

stm(S) :- findall(X,rules(X),S).

printlist([A|B]) :- write(A),nl,printlist(B).
printlist([]).

input(X) :- in0(X,[],[]).
in0(X,Y,Z) :- get0(C),test(C,X,Y,Z).

test(31,X,Y,Z) :- in0(X,[],[]).
test(32,X,Y,[]) :- in0(X,Y,[]).
test(32,X,Y,Z) :- name(X1,Z),append(Y,[X1],Y1),in0(X,Y1,[]).
test(46,X,Y,[]).
test(46,X,Y,Z) :- name(X1,Z),append(Y,[X1],X).
test(C,X,Y,Z) :- append(Z,[C],X1),in0(X,Y,X1).


|#