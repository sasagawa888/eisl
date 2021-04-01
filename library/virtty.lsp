;;; Virtual Character Mode Terminal (virtty) that can be used to build very simple interfaces, e.g. editors or simple games.
;;; Interface (but not implementation) inspired by OpenLisp ( http://www.eligis.com ) and
;;; Le-Lisp ( https://github.com/c-jullien/lelisp ).
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
   (c-lang "res = set_tabsize(8) | INT_FLAG;"))

(defun tyepilogue ()
   ;; Reset the terminal to its original mode.
   (c-lang "res = endwin() | INT_FLAG;"))

(defun tycls ()
   ;; Clears the entire screen.
   (c-lang "res = clear() | INT_FLAG;"))

(defun tycursor (column row)
   ;; Moves the cursor to position (x, y) on the screen.
   (the <fixnum> column)(the <fixnum> row)
   (c-lang "res = move(ROW & INT_MASK, COLUMN & INT_MASK) | INT_FLAG;"))

(defun tycleol ()
   ;; Clears the current line to end of line.
   (c-lang "res = clrtoeol() | INT_FLAG;"))

(defun tyattrib (x)
   ;; Set, if flag is t, or reset, if flag is nil, the reverse-video attribute.
   (if x
       (c-lang "res = attron(A_REVERSE) | INT_FLAG;")
       (c-lang "res = attroff(A_REVERSE) | INT_FLAG;")))

(defun tyo (&rest objs)
   (for ((xs objs (cdr xs)))
        ((null xs))
        (tyo1 (car xs))))

(defgeneric tyo1 (o)
   ;; Output the object o (a character, string or list of characters) at the current position.
   )
(defmethod tyo1 ((o <character>))
   (the <character> o)
   (tycn o))
(defmethod tyo1 ((o <string>))
   (the <string> o)
   (tystring o (length o)))
(defmethod tyo1 ((o <list>))
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
   (c-lang "res = refresh() | INT_FLAG;"))

(defun tybeep ()
   ;; Sounds the bell.
   (c-lang "res = beep() | INT_FLAG;"))

(defun tyi ()
   ;; Reads a single character without echo.
   (c-lang "res = getch() | INT_FLAG;"))

;; Various ncurses ( https://man.openbsd.org/curses ) constants.
;; I got these from https://github.com/HiTECNOLOGYs/cl-charms/blob/master/src/low-level/curses-bindings.lisp but the header file would have done as well.

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
        (c-lang "res = addch(CH_CODE & INT_MASK) | INT_FLAG;")))

(defun tyshowcursor (flag)
   ;; Shows, if flag is t, or hides, if flag is nil, the cursor.
   (if flag
       (c-lang "res = curs_set(1) | INT_FLAG;")
       (c-lang "res = curs_set(0) | INT_FLAG;")))

(defun tyco (x y &rest os)
   ;; Output the object o at position (x, y).
   (the <fixnum> x)(the <fixnum> y)
   (tycursor x y)
   (apply tyo os))

(defun tystring (str n)
   ;; Output the first n characters of string str at the current position.
   (the <string> str)(the <fixnum> n)
   (let ((substr (subseq str 0 n)))
        (c-lang "res = addstr(Fgetname(SUBSTR)) | INT_FLAG;")))

;; Further functions from Le-Lisp.

(defun tyinstring ()
   ;; Read a line from the keyboard
   (c-lang "static char str[133];")
   (c-lang "res = Fmakestr(getstr(str));")) ; Fmakestr copies its argument

(defun tynewline ()
   ;; Send an end-of-line marker to the screen.
   (tyo #\newline))

(defconstant +bs+ (convert 8 <character>))
(defun tyback (cn)
   ;; Erase the character immediately before the cursor on screen and move the cursor back one space.
   (tyo +bs+)
   (tyo #\space)
   (tyo +bs+))

(defun tyod (n nc)
   ;; Print the base-10 nc-character representation of the number n.
   (the <fixnum> n)(the <fixnum> nc)
   (let ((str (create-string-output-stream)))
        (format str "~D" n)
        (subseq (get-output-stream-string str) 0 nc)))

(defun tybs (cn)
   ;; Moves the cursor position back one space without erasing anything on the screen.
   (tyo +bs+))

(defconstant +cr+ (convert 13 <character>))
(defun tycr ()
   ;; Place the cursor at the beginning of the current line.
   (tyo +cr+))

(defun tyupkey ()
   ;; Returns the key code associated with the up arrow key.
   #o403)
(defun tydownkey ()
   ;; Returns the key code associated with the down arrow key.
   #o402)
(defun tyleftkey ()
   ;; Returns the key code associated with the left arrow key.
   #o404)
(defun tyrightkey ()
   ;; Returns the key code associated with the right arrow key.
   #o405)

(defun tycleos ()
   ;; Erase from the cursor to the end of screen.
   (c-lang "res = clrtobot() | INT_FLAG;"))

(defun tyinsch (ch)
   ;; Insert a character at the current cursor position.
   (the <character> ch)
   (c-lang "res = insch(CH) | INT_FLAG;"))

(defun tyinscn (cn)
   (tyinsch cn))

(defun tydelch ()
   ;; Erase the character at the current cursor position.
   (c-lang "res = delch() | INT_FLAG;"))

(defun tydelcn (cn)
   (tydelch))

(defun tyinsln ()
   ;; Insert a new line at the current cursor position.
   (c-lang "res = insertln() | INT_FLAG;"))

(defun tydelln ()
   ;; Erase the line at the current cursor position.
   (c-lang "res = deleteln() | INT_FLAG;"))

(defun tycot (x y &rest os)
   (the <fixnum> x)(the <fixnum> y)
   (tyattrib t)
   (apply tyco x y os)
   (tyattrib nil))

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
   (c-lang "res = nodelay(stdscr, TRUE) | INT_FLAG;"))

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
