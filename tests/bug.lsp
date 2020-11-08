(defun println (fmt &rest args)
  (apply #'format (standard-output) (string-append fmt "~%") args))

(defun whitespacep (c) (or (char= c #\space) (char= c #\newline)))
(defun digitp (c) (and (char>= c #\0) (char<= c #\9)))
(defun specialp (c) (member c '(#\+ #\- #\* #\/ #\( #\))))

(defun list-to-string (chars)
  (let ((string (create-string (length chars)))
        (i 0))
    (while chars
      (setf (aref string i) (car chars))
      (setq i (+ i 1))
      (setq chars (cdr chars)))
    string))

(defun read-whitespace (in)
  (let ((char nil))
    (while (and (setq char (preview-char in nil))
                (whitespacep char))
      (read-char in))))

(defun read-number (in)
  (let ((chars nil)
        (char nil))
    (while (and (setq char (preview-char in nil))
                (digitp char))
      (setq chars (cons (read-char in) chars)))
    (list-to-string (nreverse chars))))

(defun tokenize (input)
  (let ((in (create-string-input-stream input))
        (tokens nil)
        (char nil))
    (while (setq char (preview-char in nil))
      (cond
       ((whitespacep char)
        (read-whitespace in))
       ((digitp char)
        (setq tokens (cons (read-number in) tokens)))
       ((specialp char)
        (setq tokens (cons (create-string 1 (read-char in)) tokens)))
       (t (close in) (error "unknown char ~S" char))))
    (close in)
    (nreverse tokens)))

(println "Tokens: ~S" (tokenize "1 * (2 * 3) + 4"))

; ; eisl -s bug.lsp