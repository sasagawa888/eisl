(c-include "<stdio.h>")

(defun eschome ()
    (c-lang "printf(\"\\33[1;1H\");")
    (c-lang "res = T;"))


(defun esctop ()
    (c-lang  "printf(\"\\33[2;1H\");")
    (c-lang "res = T;"))

(defun esccls ()
    (c-lang  "printf(\"\\33[2J\");")
    (c-lang "res = T;"))

(defun esccls1 ()
    (c-lang  "printf(\"\\33[0J\");")
    (c-lang "res = T;"))

(defun escclsl ()
    (c-lang  "printf(\"\\33[0K\");")
    (c-lang "res = T;"))

(defun escclsla ()
    (c-lang  "printf(\"\\33[2K\");")
    (c-lang "res = T;"))

(defun escmvleft (x)
    (c-lang  "printf(\"\\33[%dG\", (INT_MASK & X));")
    (c-lang "res = T;"))

(defun escmvr ()
    (c-lang  "printf(\"\\33[C\");")
    (c-lang "res = T;"))

(defun escmvl ()
    (c-lang  "printf(\"\\33[D\");")
    (c-lang "res = T;"))

(defun escmvu ()
    (c-lang  "printf(\"\\33[A\");")
    (c-lang "res = T;"))

(defun escmvd ()
    (c-lang  "printf(\"\\33[B\");")
    (c-lang "res = T;"))

(defun escscr ()
    (c-lang  "printf(\"\\33[S\");")
    (c-lang "res = T;"))

(defun escmvln (x)
    (c-lang  "printf(\"\\33[%dD\", (INT_MASK & X));")
    (c-lang "res = T;"))

(defun escmove (x y)
    (c-lang  "printf(\"\\33[%d;%df\", (INT_MASK & X),(INT_MASK & Y));")
    (c-lang "res = T;"))

(defun escfblack ()
    (c-lang  "printf(\"\\33[30m\");")
    (c-lang "res = T;"))

(defun escfred ()
    (c-lang  "printf(\"\\33[31m\");")
    (c-lang "res = T;"))

(defun escfgreen ()
    (c-lang  "printf(\"\\33[32m\");")
    (c-lang "res = T;"))

(defun escfyellow ()
    (c-lang  "printf(\"\\33[33m\");")
    (c-lang "res = T;"))

(defun escfblue ()
    (c-lang  "printf(\"\\33[34m\");")
    (c-lang "res = T;"))

(defun escfmagenta ()
    (c-lang  "printf(\"\\33[35m\");")
    (c-lang "res = T;"))

(defun escfcyan ()
    (c-lang  "printf(\"\\33[36m\");")
    (c-lang "res = T;"))

(defun escfwhite ()
    (c-lang  "printf(\"\\33[37m\");")
    (c-lang "res = T;"))

(defun escforg ()
    (c-lang  "printf(\"\\33[39m\");")
    (c-lang "res = T;"))

(defun escbcyan ()
    (c-lang  "printf(\"\\33[46m\");")
    (c-lang "res = T;"))

(defun escborg ()
    (c-lang  "printf(\"\\33[49m\");")
    (c-lang "res = T;"))

(defun escrev ()
    (c-lang  "printf(\"\\33[7m\");")
    (c-lang "res = T;"))

(defun escrst ()
    (c-lang  "printf(\"\\33[0m\");")
    (c-lang "res = T;"))

(defun escbold ()
    (c-lang  "printf(\"\\33[1m\");")
    (c-lang "res = T;"))


