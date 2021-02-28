;;;
;;;  ‘æ‚P‚QÍ  Character class
;;;

($ap 1 "Character class")

;;;
;;; ŠÖ” (CHARACTERP obj) --> boolean
;;;
($ap 2 "characterp" P.82)
((characterp #\a) t)
((characterp "a") nil)
((characterp 'a) nil)
;;;
($argc characterp 1 0 0)
($predicate characterp $character)
;;;
((characterp #\newline) t)
((characterp #\space) t)

;;;
;;; ŠÖ” (CHAR= char1 char2) --> boolean
;;;
($ap 2 "char=" P.82)
((char= #\a #\a) t)
((char= #\a #\b) nil)
((char= #\a #\A) nil)
;;;
($argc char= 2 0 0)
($type char= ($character) :target #\a)
($type char= ($character) #\a :target)
;;;
((char= #\newline #\newline) t)
((char= #\space #\space) t)

;;;
;;; ŠÖ” (CHAR/= char1 char2) --> boolean
;;;
($ap 2 "char/=" P.82)
((char/= #\a #\a) nil)
;;;
($argc char/= 2 0 0)
($type char/= ($character) :target #\a)
($type char/= ($character) #\a :target)
;;;
((char/= #\newline #\newline) nil)
((char/= #\newline #\space) t)
((char/= #\a #\A) t)

;;;
;;; ŠÖ” (CHAR< char1 char2) --> boolean
;;;
($ap 2 "char<" P.82)
((char< #\a #\a) nil)
((char< #\a #\b) t)
((char< #\b #\a) nil)
;;((char< #\a #\A) nil)					; nil or t (IDEF)
;;((char< #\* #\a) t)					; nil or t (IDEF)
;;;
($argc char< 2 0 0)
($type char< ($character) :target #\a)
($type char< ($character) #\a :target)
;;;
((char< #\a #\z) t)
((char< #\A #\A) nil)
((char< #\A #\Z) t)
((char< #\0 #\0) nil)
((char< #\0 #\9) t)

;;;
;;; ŠÖ” (CHAR> char1 char2) --> boolean
;;;
($ap 2 "char>" P.82)
((char> #\b #\a) t)
;;;
($argc char> 2 0 0)
($type char> ($character) :target #\a)
($type char> ($character) #\a :target)
;;;
((char> #\a #\a) nil)
((char> #\z #\a) t)
((char> #\A #\A) nil)
((char> #\Z #\A) t)
((char> #\0 #\0) nil)
((char> #\9 #\0) t)

;;;
;;; ŠÖ” (CHAR<= char1 char2) --> boolean
;;;
($ap 2 "char<=" P.82)
((char<= #\a #\a) t)
;;((char<= #\a #\A) nil)				; nil or t (IDEF)
;;;
($argc char<= 2 0 0)
($type char<= ($character) :target #\a)
($type char<= ($character) #\a :target)
;;;
((char<= #\a #\z) t)
((char<= #\A #\A) t)
((char<= #\A #\Z) t)
((char<= #\0 #\0) t)
((char<= #\0 #\9) t)

;;;
;;; ŠÖ” (CHAR>= char1 char2) --> boolean
;;;
($ap 2 "char>=" P.82)
((char>= #\b #\a) t)
((char>= #\a #\a) t)
;;;
($argc char>= 2 0 0)
($type char>= ($character) :target #\a)
($type char>= ($character) #\a :target)
;;;
((char>= #\z #\a) t)
((char>= #\A #\A) t)
((char>= #\Z #\A) t)
((char>= #\0 #\0) t)
((char>= #\9 #\0) t)
