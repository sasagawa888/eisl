;;; Virtual Character Mode Terminal (virtty) that can be used to build very simple interfaces, e.g. editors or simple games.
;;; Interface (but not implementation) inspired by OpenLisp ( http://www.eligis.com ).
;;;
;;; This has moderate dependencies on ncurses.
;;;
;;; NB: this should be used under "eisl -r", otherwise keyboard echo may end up disabled!

(c-define "NCURSES_OPAQUE" "1")
(c-include "<curses.h>")
(c-include "<locale.h>")
(c-include "<unistd.h>")
(c-option "-lncurses")

(defun typrologue ()
   ;; Enter the terminal into a mode for drawing characters.
   (c-lang "setlocale(LC_ALL, \"\");")  ; TODO: move out of here?
   (c-lang "initscr();")
   (c-lang "start_color();")
   (c-lang "use_default_colors();")
   (c-lang "scrollok(stdscr, TRUE);")
   (c-lang "idlok(stdscr, TRUE);")
   (c-lang "noecho();")
   (c-lang "keypad(stdscr, TRUE);")
   (c-lang "cbreak();")
   (c-lang "nonl();")
   (c-lang "intrflush(stdscr, FALSE);")
   (tyshowcursor t)
   (c-lang "set_tabsize(8);"))

(defun tyepilogue ()
   ;; Reset the terminal to its original mode.
   (c-lang "endwin();"))

(defun tycls ()
   ;; Clears the entire screen.
   (c-lang "clear();"))

(defun tycursor (column row)
   ;; Moves the cursor to position (x, y) on the screen.
   (the <fixnum> column)(the <fixnum> row)
   (c-lang "move(ROW & INT_MASK, COLUMN & INT_MASK);"))

(defun tycleol ()
   ;; Clears the current line to end of line.
   (c-lang "clrtoeol();"))

(defun tyattrib (x)
   ;; Set, if flag is t, or reset, if flag is nil, the reverse-video attribute.
   (if x
       (c-lang "attron(A_REVERSE);")
       (c-lang "attroff(A_REVERSE);")))

(defgeneric tyo (o)
   ;; Output the object o (a character, string or list of characters) at the current position.
   )
(defmethod tyo ((o <character>))
   (the <character> o)
   (tycn o))
(defmethod tyo ((o <string>))
   (the <string> o)
   (tystring o (length o)))
(defmethod tyo ((o <list>))
   (the <list> o)
   (for ((xs o (cdr xs)))
        ((null xs))
        (tyo (car xs))))

(defun tyxmax ()
   ;; The maximum number of characters that can fit on a single line.
   (c-lang "int x, y;")
   (c-lang "getmaxyx(stdscr, y, x);")
   (c-lang "res = x | INT_FLAG;"))

(defun tyymax ()
   ;; The maximum number of character that can fit on a single column.
   (c-lang "int x, y;")
   (c-lang "getmaxyx(stdscr, y, x);")
   (c-lang "res = y | INT_FLAG;"))

(defun tyflush ()
   ;; Flush unsent characters.
   (c-lang "refresh();"))

(defun tybeep ()
   ;; Sounds the bell.
   (c-lang "beep();"))

(defun tyi ()
   ;; Reads a single character without echo.
   (c-lang "res = getch() | INT_FLAG;"))

;; Various ncurses ( https://man.openbsd.org/curses ) constants.
;; I got these from https://github.com/HiTECNOLOGYs/cl-charms/blob/master/src/low-level/curses-bindings.lisp but the header file would have done as well.

(defconstant KEY_UP #o403)
(defconstant KEY_DOWN #o402)
(defconstant KEY_LEFT #o404)
(defconstant KEY_RIGHT #o405)
(defconstant KEY_HOME #o406)
(defconstant KEY_END #o550)
(defconstant KEY_NPAGE #o552)
(defconstant KEY_PPAGE #o553)
(defconstant KEY_F0 #o410)

(defun key_fn (n)
   (the <fixnum> n)
   (+ KEY_F0 n))

(defconstant KEY_IC #o513)

(defconstant ERR -1)

(defun tys ()
   ;; Tests whether or not a character can be read from the keyboard.
   (let ((response 0))
        (setq response (c-lang "getch() | INT_FLAG"))
        (if (= response ERR)
            nil
            (progn (c-lang "ungetch(RESPONSE & INT_MASK);")
                   t))))

(defun tycn (ch)
   ;; Output character ch at the current position.
   (the <character> ch)
   (let ((ch-code (convert ch <integer>)))
        (c-lang "addch(CH_CODE & INT_MASK);")))

(defun tyshowcursor (flag)
   ;; Shows, if flag is t, or hides, if flag is nil, the cursor.
   (if flag
       (c-lang "curs_set(1);")
       (c-lang "curs_set(0);")))

(defun tyco (x y o)
   ;; Output the object o at position (x, y).
   (the <fixnum> x)(the <fixnum> y)
   (tycursor x y)
   (tyo o))

(defun tystring (str n)
   ;; Output the first n characters of string str at the current position.
   (the <string> str)(the <fixnum> n)
   (let ((substr (subseq str 0 n)))
        (c-lang "addstr(Fgetname(SUBSTR));")))

;; Further extensions from curses:

(defun inch ()
   ;; Get a character from the screen.
   (c-lang "res = inch() | INT_FLAG;"))

(defun getyx (pair)
   ;; Get cursor coordinates.
   (the <cons> pair)
   (c-lang "int y, x;")
   (c-lang "getyx(stdscr, y, x);")
   (setf (car pair) (c-lang "y | INT_FLAG"))
   (setf (cdr pair) (c-lang "x | INT_FLAG")))

(defun nodelay ()
   ;; Cause tyi to be a non-blocking call.
   (c-lang "nodelay(stdscr, TRUE);"))

;; From here on is test code

#|
(defglobal *key* nil)
(defglobal *pos* (cons 0 0))

(defun my-test ()
   (typrologue)
   (tycls)
   (tycursor 10 5)
   (tyattrib t)
   (tyo "Hello world")
   (tyattrib nil)
   (tycursor 10 10)
   (let ((str (create-string-output-stream)))
        (format str "~A" (tyxmax))
        (tyo (get-output-stream-string str)))
   (tyflush)
   (tybeep)
   (setq *key* (tyi))
   (getyx *pos*)
   (tyepilogue))
|#
