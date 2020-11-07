(defun tokenize (input)
  (let ((in (create-string-input-stream input))
        (char nil))
    (while (setq char (preview-char in nil))
      (read-char in nil))
    (close in)))


(tokenize "123")
(format (standard-output) "This won't be printed~%")

  ; eisl -s tests/run2.lsp