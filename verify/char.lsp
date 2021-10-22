(import "test")
;;;
;;;  Character class
;;;

($ap 1 "Character class")

;;;
;;; function (CHARACTERP obj) --> boolean
;;;
($ap 2 "characterp" P.82)
($test (characterp #\a) t)
($test (characterp "a") nil)
($test (characterp 'a) nil)
;;;
($argc characterp 1 0 0)
($predicate characterp $character)
;;;
($test (characterp #\newline) t)
($test (characterp #\space) t)

;;;
;;; function (CHAR= char1 char2) --> boolean
;;;
($ap 2 "char=" P.82)
($test (char= #\a #\a) t)
($test (char= #\a #\b) nil)
($test (char= #\a #\A) nil)
;;;
($argc char= 2 0 0)
($type char= ($character) :target #\a)
($type char= ($character) #\a :target)
;;;
($test (char= #\newline #\newline) t)
($test (char= #\space #\space) t)

;;;
;;; function (CHAR/= char1 char2) --> boolean
;;;
($ap 2 "char/=" P.82)
($test (char/= #\a #\a) nil)
;;;
($argc char/= 2 0 0)
($type char/= ($character) :target #\a)
($type char/= ($character) #\a :target)
;;;
($test (char/= #\newline #\newline) nil)
($test (char/= #\newline #\space) t)
($test (char/= #\a #\A) t)

;;;
;;; function (CHAR< char1 char2) --> boolean
;;;
($ap 2 "char<" P.82)
($test (char< #\a #\a) nil)
($test (char< #\a #\b) t)
($test (char< #\b #\a) nil)
;;($test (char< #\a #\A) nil)					; nil or t (IDEF)
;;($test (char< #\* #\a) t)					; nil or t (IDEF)
;;;
($argc char< 2 0 0)
($type char< ($character) :target #\a)
($type char< ($character) #\a :target)
;;;
($test (char< #\a #\z) t)
($test (char< #\A #\A) nil)
($test (char< #\A #\Z) t)
($test (char< #\0 #\0) nil)
($test (char< #\0 #\9) t)

;;;
;;; function (CHAR> char1 char2) --> boolean
;;;
($ap 2 "char>" P.82)
($test (char> #\b #\a) t)
;;;
($argc char> 2 0 0)
($type char> ($character) :target #\a)
($type char> ($character) #\a :target)
;;;
($test (char> #\a #\a) nil)
($test (char> #\z #\a) t)
($test (char> #\A #\A) nil)
($test (char> #\Z #\A) t)
($test (char> #\0 #\0) nil)
($test (char> #\9 #\0) t)

;;;
;;; function (CHAR<= char1 char2) --> boolean
;;;
($ap 2 "char<=" P.82)
($test (char<= #\a #\a) t)
;;($test (char<= #\a #\A) nil)				; nil or t (IDEF)
;;;
($argc char<= 2 0 0)
($type char<= ($character) :target #\a)
($type char<= ($character) #\a :target)
;;;
($test (char<= #\a #\z) t)
($test (char<= #\A #\A) t)
($test (char<= #\A #\Z) t)
($test (char<= #\0 #\0) t)
($test (char<= #\0 #\9) t)

;;;
;;; function (CHAR>= char1 char2) --> boolean
;;;
($ap 2 "char>=" P.82)
($test (char>= #\b #\a) t)
($test (char>= #\a #\a) t)
;;;
($argc char>= 2 0 0)
($type char>= ($character) :target #\a)
($type char>= ($character) #\a :target)
;;;
($test (char>= #\z #\a) t)
($test (char>= #\A #\A) t)
($test (char>= #\Z #\A) t)
($test (char>= #\0 #\0) t)
($test (char>= #\9 #\0) t)
