(defun tokenize (input)
  (let ((in (create-string-input-stream input))
        (char nil))
    (while (setq char (preview-char in nil))
      (read-char in nil))
    (close in)))

(tokenize "123")
(format (standard-output) "This won't be printed~%")

(let* ((input "1 + 1")
       (in (create-string-input-stream input))
       (char nil))
  (while (setq char (preview-char in nil))
    (format (standard-output) "Char: ~S~%" char)
    (read-char in nil))
  (close in))

  ; eisl -s run2.lsp