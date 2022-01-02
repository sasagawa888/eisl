(import "escape")

(defconstant rows 4000)
(defconstant cols 100)
(defconstant ed-footer 25)
(defconstant version 0.2)

(defglobal ed-row nil)
(defglobal ed-col nil)
(defglobal ed-start nil)
(defglobal ed-end nil)
(defglobal ed-data (create-array `(,rows ,cols) 0))


(defun ed (fname)
    (system "stty raw -echo")
    (file-load fname)
    (setq ed-row 0)
    (setq ed-col 0)
    (setq ed-start 0)
    (setq ed-end 23)
    (esc-clear-screen)
    (display-header fname)
    (display-screen)
    (edit-screen fname)
    (system "stty -raw echo"))


(defun display-header (fname)
    (esc-move-home)
    (esc-reverse)
    (format (standard-output) "editor for learning ver~A       ~A                                                 " version fname)
    (esc-reset))

(defun display-screen ()
    (esc-move-top)
    (esc-clear-screen-after)
    (for ((row ed-start (+ row 1)))
         ((>= row ed-end) t)
         (display-line row))
    (display-footer)
    (esc-move (+ ed-row 2) (+ ed-col 1)))

(defun display-footer ()
    (esc-move ed-footer 1)
    (esc-reverse)
    (format (standard-output) "                                                                                      ^Z(quit)")
    (esc-reset))

(defun display-line (row)
    (if (characterp (aref ed-data row 0))
        (for ((col 0 (+ col 1)))
             ((or (char= (aref ed-data row col) #\newline)
                  (char= (aref ed-data row col) #\^Z) )
              (format-char (standard-output) #\newline)
              (format-char (standard-output) #\return))
             (format-char (standard-output) (aref ed-data row col)))))

(defun edit-screen (fname)
    (let ((quit nil))
        (while (not quit)
            (setq quit (edit-loop fname)))))


(defun edit-loop (fname)
    (block loop
        (let ((c nil))
            (while t
                (setq c (read-char))
                (case c
                    ((#\^Z) (esc-clear-screen) (return-from loop t))
                    (t (set-aref c ed-data ed-row ed-col)
                       (setq ed-col (+ ed-col 1))
                       (esc-clear-line)
                       (esc-move-left-margin 0)
                       (display-line ed-row)
                       (esc-move (+ ed-row 2) (+ ed-col 1))))))))
    


(defun file-load (fname)
    (if (not (probe-file fname))
        (set-aref #\^Z ed-data 0 0)
        (let ((instream (open-input-file fname))
              (row 0) (col 0) (c nil))
            (setq c (read-char instream nil #\^Z))
            (while (not (char= c #\^Z))
                (set-aref c ed-data row col)
                (setq col (+ col 1))
                (if (char= c #\newline) (progn (setq row (+ row 1)) (setq col 0)))
                (setq c (read-char instream nil #\^Z)))
            (set-aref c ed-data row col))))