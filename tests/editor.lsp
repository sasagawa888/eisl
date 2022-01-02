(import "escape")

(defconstant rows 4000)
(defconstant cols 80)
(defconstant ed-start 2)
(defconstant ed-end 24)
(defconstant ed-footer 25)
(defconstant version 0.1)

(defglobal ed-scroll nil)
(defglobal ed-row nil)
(defglobal ed-col nil)
(defglobal ed-ins t)
(defglobal ed-tab 0)
(defglobal ed-indent t)
(defglobal ed-name nil)
(defglobal ed-data (create-array `(,rows ,cols) 0))


(defun ed (fname)
    ;(system "stty raw -echo")
    (file-load fname)
    (setq ed-row 0)
    (setq ed-col 0)
    (esc-clear-screen)
    (display-header fname)
    (display-screen)
    (edit-screen fname)
    (system "stty -raw echo"))


(defun display-header (fname)
    (esc-move-home)
    (esc-reverse)
    (format (standard-output) "editor for learning ver~A       ~A                               " version fname)
    (esc-reset))

(defun display-screen ()
    (esc-move-top)
    (esc-clear-screen-after)
    (for ((r ed-start (+ r 1)))
         ((> r ed-end) t)
         (display-line r))
    (display-footer)
    (esc-move (+ ed-row 2) (+ ed-col 1)))

(defun display-footer ()
    (esc-move ed-footer 1)
    (esc-reverse)
    (format (standard-output) "                                                               ^Z(quit)")
    (esc-reset))

(defun display-line (r)
    (for ((c 0 (+ c 1)))
         ((or (and (numberp (aref ed-data r c))(= (aref ed-data r c) 0)) (> c cols)) t)
         (format-char (standard-output) (aref ed-data r c))))

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
                    ((#\^Z) (return-from loop t))
                    (t (set-aref c ed-data ed-row ed-col)
                       (setq ed-col (+ ed-col 1))
                       (esc-clear-line)
                       (esc-move-left-margin 0)
                       (display-line ed-row)
                       (esc-move (+ ed-row 2) (+ ed-col 1))))))))
    


(defun file-load (fname)
    (block file-load
        (let* ((instream nil)
               (ans (catch 'c-error
                      (with-handler 
                        (lambda (c) (throw 'c-error c))
                        (setq instream (open-input-file fname))))))
         (if (equal (class-of ans) (class <stream-error>))
             (return-from file-load nil))
         (for ((row 0 (+ row 1))
               (c #\^A))
              ((char= c #\^Z) t)
              (for ((col 0 (+ col 1)))
                   ((or (char= c #\newline) (char= c #\^Z)) t)
                   (setq c (read-char instream nil #\^Z))
                   (set-aref c ed-data row col)))))) 