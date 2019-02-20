(defmacro test(form1 form2 :rest pred)
  (if (null pred)
      `(if (equal ,form1 ',form2)
           (format (standard-output) "~S is ok~%" ',form1)
           (format (standard-output) "~S is bad~%" ',form1))
      `(if (,@pred ,form1 ',form2)
           (format (standard-output) "~S is ok~%" ',form1)
           (format (standard-output) "~S is bad~%" ',form1))))


;;;
;;; “ÁŽêŒ`Ž® (THE class-name form) --> <object>
;;;
(test (the <integer> 10) 10 eql)
(test (the <number> 10) 10 eql)
;;((the <float> 10) 10 eql) ; the consequences are undefined
;;;

;;;
;;; “ÁŽêŒ`Ž® (ASSURE class-name form) --> <object>
;;;
(test (assure <integer> 10) 10 eql)
(test (assure <number> 10) 10 eql)


;;;
;;; “ÁŽêŒ`Ž® (CONVERT obj class-name) --> <object>
;;;
(test (convert 3 <float>) 3.0 eql)
(test (convert "abc" <general-vector>) #(#\a #\b #\c) equal)
(test (convert #(a b) <list>) (a b) equal)


(test (convert #\a <character>) #\a eql)
(test (convert #\a <integer>) 97 eql)

(test (let ((x (convert #\a <symbol>)))
   (and (symbolp x) (string= (convert x <string>) "a"))) t)
(test (let ((x (convert #\A <symbol>)))
   (and (symbolp x) (string= (convert x <string>) "A"))) t)
(test (let ((x (convert #\space <symbol>)))
   (and (symbolp x) (string= (convert x <string>) " "))) t)
(test (let ((x (convert #\1 <symbol>)))
   (and (symbolp x) (string= (convert x <string>) "1"))) t)


(test (convert 100 <character>) #\d eql)
(test (convert 100 <integer>) 100 eql)
(test (convert 100 <float>) 100.0 eql)

(test (convert 100 <string>) "100" string=)

(test (convert 1234567890 <integer>) 1234567890 eql)
(test (convert 1234567890 <float>) 1234567890.0 eql)

(test (convert 1234567890 <string>) "1234567890" string=)

(test (convert 1.23 <float>) 1.23 eql)
(test (convert 1.23 <string>) "1.23" string=)

(test (convert 'abc <symbol>) abc)
(test (stringp (convert 'abc <string>)) t)

(test (let ((x (convert "" <symbol>)))
   (and (symbolp x) (string= (convert x <string>) ""))) t)
(test (convert "" <general-vector>) #() equal)
(test (convert "" <list>) ())
;;;

(test (convert "100" <integer>) 100 eql)
(test (convert "1234567890" <integer>) 1234567890 eql)

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

(test (convert #() <general-vector>) #() equal)
(test (convert #() <list>) ())

(test (convert #(a b c) <general-vector>) #(a b c) equal)
(test (convert #(a b c) <list>) (a b c) equal)

(test (convert () <symbol>) nil)
(test (convert () <string>) "NIL" string=)
;;;
(test (convert () <general-vector>) #() equal)
(test (convert () <list>) ())

(test (convert '(a b c) <general-vector>) #(a b c) equal)
(test (convert '(a b c) <list>) (a b c) equal)
