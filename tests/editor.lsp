(defglobal ed-scroll nil)
(defglobal ed-footer nil)
(defglobal ed-row nil)
(defglobal ed-col nil)
(defglobal ed-start nil)
(defglobal ed-end nil)
(defglobal ed-ins t)
(defglobal ed-tab 0)
(defglobal ed-indent t)
(defglobal ed-name nil)
(defglobal ed-data (create-array '(4000 80)))


(defun editor ()
    (system "stty raw -echo")
    (setq ed-row 0)
    (setq ed-col 0)
    (setq ed-start 0)
    (setq ed-end 0)
    (setq ed-scroll 21)
    (setq ed-footer 24)
    (esc-cls)
    (display-command fname)
    (display-screen)
    (edit-screen fname)
    (system "stty -raw echo"))


(defun esc-move (r c)
    (progn 
        (format-char (standard-output) #\escape)
        (format-char (standard-output) #\[)
        (format-object (standard-output) r)
        (format-char (standard-output) #\;)
        (format-char (standard-output) c)
        (format-char (standard-output) #\newline)))


(defun esc-cls () )

(defun esc-clear-line () )

