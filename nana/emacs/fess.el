;;
;; This code is not copyrighted, in fact don't even blame me for it.
;; No Warranty....
;;
;; If you write a proper version I'd be obliged if you could send
;; me a copy.
;; 
;; Phil Maker <pjm@gnu.org>

(defun fess-mode() 
  "..."
  (interactive)
  (setq selective-display t)
  (setq select-display-ellipses t)
  (setq case-fold-search nil)
  (local-set-key "\C-C\C-h" 'fess-hide)
  (local-set-key "\C-C\C-s" 'fess-show)
  (local-set-key "\C-C*" 'fess-show-all))

(defun fess-debug ()
  "..."
  (interactive)
  (setq selective-display nil))

(defun fess-hide (re)
  "Hide all the lines which contain REGEXP"
  (interactive "sRegular expression to hide: ") 
  (save-excursion
    (goto-char (point-min))
    (while (re-search-forward 
	    (concat "\\(\\`\\|\n\\)\\([^\C-m\n]*" re "[^\C-m\n]*\\)") nil t)
      (replace-match "\C-m\\2" nil nil))))

(defun fess-show (re)
  "Show all the lines which contain REGEXP"
  (interactive "sRegular expression to show: ")
  (save-excursion
    (goto-char (point-min))
    (setq s (concat "\\(\\`\\|[\C-M\n]\\)\\([^\C-M\n]*" re "[^\C-M]*\\)"))
    (while (re-search-forward s nil t)
      (replace-match "\n\\1" nil nil))))

(defun fess-show-all ()
  "Make everything visible"
  (interactive)
  (save-excursion
    (subst-char-in-region (point-min) (point-max) ?\C-m ?\n nil)))

(defun fess-new-view (prog buffer)
  "Show all the lines output'ed by PROG in BUFFER"
  (interactive "sProgram to run
BBuffer for output")
  (call-process-region (point-min) (point-max) prog t buffer t))


