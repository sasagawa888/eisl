(import "test")
;;;
;;; (CHARACTERP obj) --> boolean
;;;
(test (characterp #\a) t)
(test (characterp "a") nil)
(test (characterp 'a) nil)
;;;
;;;
(test (characterp #\newline) t)
(test (characterp #\space) t)

;;;
;;; (CHAR= char1 char2) --> boolean
;;;
(test (char= #\a #\a) t)
(test (char= #\a #\b) nil)
(test (char= #\a #\A) nil)
;;;
;;;
(test (char= #\newline #\newline) t)
(test (char= #\space #\space) t)

;;;
;;; (CHAR/= char1 char2) --> boolean
;;;
(test (char/= #\a #\a) nil)
;;;
;;;
(test (char/= #\newline #\newline) nil)
(test (char/= #\newline #\space) t)
(test (char/= #\a #\A) t)

;;;
;;; (CHAR< char1 char2) --> boolean
;;;
(test (char< #\a #\a) nil)
(test (char< #\a #\b) t)
(test (char< #\b #\a) nil)
;;((char< #\a #\A) nil)					; nil or t (IDEF)
;;((char< #\* #\a) t)					; nil or t (IDEF)
;;;
;;;
(test (char< #\a #\z) t)
(test (char< #\A #\A) nil)
(test (char< #\A #\Z) t)
(test (char< #\0 #\0) nil)
(test (char< #\0 #\9) t)

;;;
;;; (CHAR> char1 char2) --> boolean
;;;
(test (char> #\b #\a) t)
;;;
;;;
(test (char> #\a #\a) nil)
(test (char> #\z #\a) t)
(test (char> #\A #\A) nil)
(test (char> #\Z #\A) t)
(test (char> #\0 #\0) nil)
(test (char> #\9 #\0) t)

;;;
;;; (CHAR<= char1 char2) --> boolean
;;;
(test (char<= #\a #\a) t)
;;((char<= #\a #\A) nil)				; nil or t (IDEF)
;;;
;;;
(test (char<= #\a #\z) t)
(test (char<= #\A #\A) t)
(test (char<= #\A #\Z) t)
(test (char<= #\0 #\0) t)
(test (char<= #\0 #\9) t)

;;;
;;; (CHAR>= char1 char2) --> boolean
;;;
(test (char>= #\b #\a) t)
(test (char>= #\a #\a) t)
;;;
;;;
(test (char>= #\z #\a) t)
(test (char>= #\A #\A) t)
(test (char>= #\Z #\A) t)
(test (char>= #\0 #\0) t)
(test (char>= #\9 #\0) t)

