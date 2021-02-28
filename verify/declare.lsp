(import "test")
;;;
;;;  Declarations and Coercions
;;;

($ap 1 "Declarations and Coercions")

;;;
;;; (THE class-name form) --> <object>
;;;
($ap 2 "the" P.61)
(test (the <integer> 10) 10 eql)
(test (the <number> 10) 10 eql)
;;(test (the <float> 10) 10 eql)	; the consequences are undefined
;;;
($argc the 2 0 0)
($error (the . 1) <error>)
($error (the <integer> 10 . 2) <error>)

;;;
;;; (ASSURE class-name form) --> <object>
;;;
($ap 2 "assure" P.61)
(test (assure <integer> 10) 10 eql)
(test (assure <number> 10) 10 eql)
($error (assure <float> 10) <domain-error>)
;;;
($argc assure 2 0 0)
($error (assure . 1) <error>)
($error (assure <integer> 10 . 2) <error>)

;;;
;;; (CONVERT obj class-name) --> <object>
;;;
($ap 2 "convert" P.62)
(test (convert 3 <float>) 3.0 eql)
(test (convert "abc" <general-vector>) #(#\a #\b #\c) equal)
(test (convert #(a b) <list>) (a b) equal)
;;;
($argc convert 2 0 0)
($error (convert . 1) <error>)
($error (convert 3 <float> . 2) <error>)
;;;
(test (convert #\a <character>) #\a eql)
(test (convert #\a <integer>) 97 eql)
($error (convert #\a <float>) <domain-error>)
(test (let ((x (convert #\a <symbol>)))
   (and (symbolp x) (string= (convert x <string>) "a"))) t)
(test (let ((x (convert #\A <symbol>)))
   (and (symbolp x) (string= (convert x <string>) "A"))) t)
(test (let ((x (convert #\space <symbol>)))
   (and (symbolp x) (string= (convert x <string>) " "))) t)
(test (let ((x (convert #\1 <symbol>)))
   (and (symbolp x) (string= (convert x <string>) "1"))) t)
($error (convert #\a <string>) <domain-error>)
($error (convert #\a <general-vector>) <domain-error>)
($error (convert #\a <list>) <domain-error>)
;;;
(test (convert 100 <character>) #\d eql)
(test (convert 100 <integer>) 100 eql)
(test (convert 100 <float>) 100.0 eql)
($error (convert 100 <symbol>) <domain-error>)
(test (convert 100 <string>) "100" string=)
($error (convert 100 <general-vector>) <domain-error>)
($error (convert 100 <list>) <domain-error>)
;;;
($error (convert 1234567890 <character>) <domain-error>)
(test (convert 1234567890 <integer>) 1234567890 eql)
(test (convert 1234567890 <float>) 1234567890.0 eql)
($error (convert 1234567890 <symbol>) <domain-error>)
(test (convert 1234567890 <string>) "1234567890" string=)
($error (convert 1234567890 <general-vector>) <domain-error>)
($error (convert 1234567890 <list>) <domain-error>)
;;;
($error (convert 1.23 <character>) <domain-error>)
($error (convert 1.23 <integer>) <domain-error>)
(test (convert 1.23 <float>) 1.23 eql)
($error (convert 1.23 <symbol>) <domain-error>)
(test (convert 1.23 <string>) "1.23" string=)
($error (convert 1.23 <general-vector>) <domain-error>)
($error (convert 1.23 <list>) <domain-error>)
;;;
($error (convert 'abc <character>) <domain-error>)
($error (convert 'abc <integer>) <domain-error>)
($error (convert 'abc <float>) <domain-error>)
(test (convert 'abc <symbol>) abc)
(test (stringp (convert 'abc <string>)) t)
($error (convert 'abc <general-vector>) <domain-error>)
($error (convert 'abc <list>) <domain-error>)
;;;
($error (convert "" <character>) <domain-error>)
($error (convert "" <integer>) <domain-error>)
($error (convert "" <float>) <domain-error>)
(test (let ((x (convert "" <symbol>)))
   (and (symbolp x) (string= (convert x <string>) ""))) t)
(test (convert "" <general-vector>) #() equal)
(test (convert "" <list>) ())
;;;
($error (convert "abc" <character>) <domain-error>)
($error (convert "abc" <integer>) <domain-error>)
(test (convert "100" <integer>) 100 eql)
(test (convert "1234567890" <integer>) 1234567890 eql)
($error (convert "abc" <float>) <domain-error>)
(test (convert "1.23" <float>) 1.23 eql)
(test (let ((x (convert "abc" <symbol>)))
   (and (symbolp x) (string= (convert x <string>) "abc"))) t)
(test (let ((x (convert "ABC" <symbol>)))
   (and (symbolp x) (string= (convert x <string>) "ABC"))) t)
(test (let ((x (convert "1" <symbol>)))
   (and (symbolp x) (string= (convert x <string>) "1"))) t)
(test (let ((x (convert "123" <symbol>)))
   (and (symbolp x) (string= (convert x <string>) "123"))) t)
(test (convert "abc" <string>) "abc" string=)
(test (convert "abc" <list>) (#\a #\b #\c) equal)
;;;
($error (convert "ab c" <character>) <domain-error>)
($error (convert "ab c" <integer>) <domain-error>)
($error (convert "10 0" <integer>) <domain-error>)
($error (convert "123456789 0" <integer>) <domain-error>)
($error (convert "ab c" <float>) <domain-error>)
($error (convert "1.2 3" <float>) <domain-error>)
(test (let ((x (convert "ab c" <symbol>)))
   (and (symbolp x) (string= (convert x <string>) "ab c"))) t)
(test (let ((x (convert "1 " <symbol>)))
   (and (symbolp x) (string= (convert x <string>) "1 "))) t)
(test (convert "ab c" <string>) "ab c" string=)
(test (convert "ab c" <list>) (#\a #\b #\space #\c) equal)
;;;
(test (let ((x (convert "()" <symbol>)))
   (and (symbolp x) (string= (convert x <string>) "()"))) t)
(test (let ((x (convert "nil" <symbol>)))
   (and (symbolp x) (string= (convert x <string>) "nil"))) t)
(test (let ((x (convert "NIL" <symbol>)))
   (and (symbolp x) (string= (convert x <string>) "NIL"))) t)
(test (convert "()" <list>) (#\( #\)) equal)
(test (let ((x (convert "t" <symbol>)))
   (and (symbolp x) (string= (convert x <string>) "t"))) t)
(test (let ((x (convert "T" <symbol>)))
   (and (symbolp x) (string= (convert x <string>) "T"))) t)
;;;
($error (convert #() <character>) <domain-error>)
($error (convert #() <integer>) <domain-error>)
($error (convert #() <float>) <domain-error>)
($error (convert #() <symbol>) <domain-error>)
($error (convert #() <string>) <domain-error>)
(test (convert #() <general-vector>) #() equal)
(test (convert #() <list>) ())
;;;
($error (convert #(a b c) <character>) <domain-error>)
($error (convert #(a b c) <integer>) <domain-error>)
($error (convert #(a b c) <float>) <domain-error>)
($error (convert #(a b c) <symbol>) <domain-error>)
($error (convert #(a b c) <string>) <domain-error>)
(test (convert #(a b c) <general-vector>) #(a b c) equal)
(test (convert #(a b c) <list>) (a b c) equal)
;;;
($error (convert () <character>) <domain-error>)
($error (convert () <integer>) <domain-error>)
($error (convert () <float>) <domain-error>)
;;; 
;($error (convert () <symbol>) <domain-error>)
;($error (convert () <string>) <domain-error>)
(test (convert () <symbol>) nil)
(test (convert () <string>) "NIL" string=)
;;;
(test (convert () <general-vector>) #() equal)
(test (convert () <list>) ())
;;;
($error (convert '(a b c) <character>) <domain-error>)
($error (convert '(a b c) <integer>) <domain-error>)
($error (convert '(a b c) <float>) <domain-error>)
($error (convert '(a b c) <symbol>) <domain-error>)
($error (convert '(a b c) <string>) <domain-error>)
(test (convert '(a b c) <general-vector>) #(a b c) equal)
(test (convert '(a b c) <list>) (a b c) equal)
