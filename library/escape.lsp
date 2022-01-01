(c-include "<stdio.h>")

(defun esc-move-home ()
    (c-lang "printf(\"\\33[1;1H\");")
    (c-lang "res = T;"))


(defun esc-move-top ()
    (c-lang  "printf(\"\\33[2;1H\");")
    (c-lang "res = T;"))


(defun esc-clear-screen-after ()
    (c-lang  "printf(\"\\33[0J\");")
    (c-lang "res = T;"))

(defun esc-clear-screen-before ()
    (c-lang  "printf(\"\\33[1J\");")
    (c-lang "res = T;"))

(defun esc-clear-screen ()
    (c-lang  "printf(\"\\33[2J\");")
    (c-lang "res = T;"))

(defun esc-clear-line-after ()
    (c-lang  "printf(\"\\33[0K\");")
    (c-lang "res = T;"))

(defun esc-clear-line-before ()
    (c-lang  "printf(\"\\33[1K\");")
    (c-lang "res = T;"))


(defun esc-clear-line ()
    (c-lang  "printf(\"\\33[2K\");")
    (c-lang "res = T;"))

(defun esc-move-left-margin (x)
    (c-lang  "printf(\"\\33[%dG\", (INT_MASK & X));")
    (c-lang "res = T;"))

(defun esc-move-right ()
    (c-lang  "printf(\"\\33[C\");")
    (c-lang "res = T;"))

(defun esc-move-left ()
    (c-lang  "printf(\"\\33[D\");")
    (c-lang "res = T;"))

(defun esc-move-up ()
    (c-lang  "printf(\"\\33[A\");")
    (c-lang "res = T;"))

(defun esc-move-down ()
    (c-lang  "printf(\"\\33[B\");")
    (c-lang "res = T;"))

(defun esc-scroll ()
    (c-lang  "printf(\"\\33[S\");")
    (c-lang "res = T;"))

(defun esc-move-left-n (x)
    (c-lang  "printf(\"\\33[%dD\", (INT_MASK & X));")
    (c-lang "res = T;"))

(defun esc-move (x y)
    (c-lang  "printf(\"\\33[%d;%df\", (INT_MASK & X),(INT_MASK & Y));")
    (c-lang "res = T;"))

(defun esc-fore-black ()
    (c-lang  "printf(\"\\33[30m\");")
    (c-lang "res = T;"))

(defun esc-fore-red ()
    (c-lang  "printf(\"\\33[31m\");")
    (c-lang "res = T;"))

(defun esc-fore-green ()
    (c-lang  "printf(\"\\33[32m\");")
    (c-lang "res = T;"))

(defun esc-fore-yellow ()
    (c-lang  "printf(\"\\33[33m\");")
    (c-lang "res = T;"))

(defun esc-fore-blue ()
    (c-lang  "printf(\"\\33[34m\");")
    (c-lang "res = T;"))

(defun esc-fore-magenta ()
    (c-lang  "printf(\"\\33[35m\");")
    (c-lang "res = T;"))

(defun esc-fore-cyan ()
    (c-lang  "printf(\"\\33[36m\");")
    (c-lang "res = T;"))

(defun esc-fore-white ()
    (c-lang  "printf(\"\\33[37m\");")
    (c-lang "res = T;"))

(defun esc-fore-origin ()
    (c-lang  "printf(\"\\33[39m\");")
    (c-lang "res = T;"))

(defun esc-back-cyan ()
    (c-lang  "printf(\"\\33[46m\");")
    (c-lang "res = T;"))

(defun esc-back-origin ()
    (c-lang  "printf(\"\\33[49m\");")
    (c-lang "res = T;"))

(defun esc-reverse ()
    (c-lang  "printf(\"\\33[7m\");")
    (c-lang "res = T;"))

(defun esc-reset ()
    (c-lang  "printf(\"\\33[0m\");")
    (c-lang "res = T;"))

(defun esc-bold ()
    (c-lang  "printf(\"\\33[1m\");")
    (c-lang "res = T;"))


