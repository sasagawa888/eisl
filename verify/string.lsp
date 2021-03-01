(import "test")
;;;
;;;  chapter16 String class
;;;

($ap 1 "String class")

;;;
;;; function (STRINGP obj) --> boolean
;;;
($ap 2 "stringp" P.95)
(test (stringp "abc") t)
(test (stringp 'abc) nil)
;;;
($argc stringp 1 0 0)
($predicate stringp $string)

;;;
;;; function (CREATE-STRING i [initial-element]) --> <string>
;;;
($ap 2 "create-string" P.95)
(test (create-string 3 #\a) "aaa" string=)
(test (create-string 0 #\a) "" string=)
;;;
($argc create-string 1 1 0)
($type create-string ($integer) :target)
;;;
(test (create-string 0) "" string=)
(test (create-string 1) " " string=)
(test (length (create-string 1000)) 1000 eql)
($error (create-string -1) <domain-error>)
($error (create-string -1234567890) <domain-error>)
($error (create-string 1234567890) <storage-exhausted>)

;;;
;;; function (STRING= string1 string2) --> quasi-boolean
;;;
($ap 2 "string=" P.96)
(test (if (string= "abcd" "abcd") t nil) t)
(test (if (string= "abcd" "wxyz") t nil) nil)
(test (if (string= "abcd" "abcde") t nil) nil)
(test (if (string= "abcde" "abcd") t nil) nil)
;;;
($argc string= 2 0 0)
($type string= ($string) :target "a")
($type string= ($string) "a" :target)
;;;
(test (string= "" "") t)
(test (string= "" "a") nil)
(test (string= "a" "") nil)
(test (string= "abcd" "Abcd") nil)
(test (string= "abcd" "abcD") nil)
(test (string= (create-string 1000 #\a) (create-string 1000 #\a)) t)
(test (string= (create-string 1000 #\a) (create-string 1000 #\b)) nil)

;;;
;;; function (STRING/= string1 string2) --> quasi-boolean
;;;
($ap 2 "string/=" P.96)
(test (if (string/= "abcd" "wxyz") t nil) t)
;;;
($argc string/= 2 0 0)
($type string/= ($string) :target "a")
($type string/= ($string) "a" :target)
;;;
(test (string/= "" "") nil)
(test (string/= "" "a") t)
(test (string/= "a" "") t)
(test (string/= "abcd" "Abcd") t)
(test (string/= "abcd" "abcD") t)
(test (string/= (create-string 1000 #\a) (create-string 1000 #\a)) nil)
(test (string/= (create-string 1000 #\a) (create-string 1000 #\b)) t)

;;;
;;; function (STRING< string1 string2) --> quasi-boolean
;;;
($ap 2 "string<" P.96)
(test (if (string< "abcd" "abcd") t nil) nil)
(test (if (string< "abcd" "wxyz") t nil) t)
(test (if (string< "abcd" "abcde") t nil) t)
(test (if (string< "abcde" "abcd") t nil) nil)
;;;
($argc string< 2 0 0)
($type string< ($string) :target "a")
($type string< ($string) "a" :target)
;;;
(test (string< "" "") nil)
(test (string< "" "a") t)
(test (string< "a" "") nil)
(test (string< (create-string 1000 #\a) (create-string 1000 #\a)) nil)
(test (string< (create-string 1000 #\a) (create-string 1000 #\b)) t)
(test (string< (create-string 1000 #\b) (create-string 1000 #\a)) nil)

;;;
;;; function (STRING> string1 string2) --> quasi-boolean
;;;
($ap 2 "string>" P.96)
(test (if (string> "abcd" "wxyz") t nil) nil)
;;;
($argc string> 2 0 0)
($type string> ($string) :target "a")
($type string> ($string) "a" :target)
;;;
(test (string> "" "") nil)
(test (string> "" "a") nil)
(test (string> "a" "") t)
(test (string> (create-string 1000 #\a) (create-string 1000 #\a)) nil)
(test (string> (create-string 1000 #\a) (create-string 1000 #\b)) nil)
(test (string> (create-string 1000 #\b) (create-string 1000 #\a)) t)

;;;
;;; function (STRING>= string1 string2) --> quasi-boolean
;;;
($ap 2 "string>=" P.96)
(test (if (string>= "abcd" "abcd") t nil) t)
;;;
($argc string>= 2 0 0)
($type string>= ($string) :target "a")
($type string>= ($string) "a" :target)
;;;
(test (string>= "" "") t)
(test (string>= "" "a") nil)
(test (string>= "a" "") t)
(test (string>= (create-string 1000 #\a) (create-string 1000 #\a)) t)
(test (string>= (create-string 1000 #\a) (create-string 1000 #\b)) nil)
(test (string>= (create-string 1000 #\b) (create-string 1000 #\a)) t)

;;;
;;; function (STRING<= string1 string2) --> quasi-boolean
;;;
($ap 2 "string<=" P.96)
(test (if (string<= "abcd" "abcd") t nil) t)
(test (if (string<= "abcd" "wxyz") t nil) t)
(test (if (string<= "abcd" "abcde") t nil) t)
(test (if (string<= "abcde" "abcd") t nil) nil)
;;;
($argc string<= 2 0 0)
($type string<= ($string) :target "a")
($type string<= ($string) "a" :target)
;;;
(test (string<= "" "") t)
(test (string<= "" "a") t)
(test (string<= "a" "") nil)
(test (string<= (create-string 1000 #\a) (create-string 1000 #\a)) t)
(test (string<= (create-string 1000 #\a) (create-string 1000 #\b)) t)
(test (string<= (create-string 1000 #\b) (create-string 1000 #\a)) nil)

;;;
;;; function (CHAR-INDEX character string [start-position]) --> <object>
;;;
($ap 2 "char-index" P.97)
(test (char-index #\b "abcab") 1 eql)
(test (char-index #\B "abcab") nil)
(test (char-index #\b "abcab" 2) 4 eql)
(test (char-index #\d "abcab") nil)
(test (char-index #\a "abcab" 4) nil)
;;;
($argc char-index 2 1 0)
($type char-index ($character) :target "abc")
($type char-index ($string) #\a :target)
($type char-index ($integer) #\a "abc" :target)
;;;
(test (char-index #\space " ") 0 eql)
(test (char-index #\a "") nil)
(test (char-index #\a (create-string 1000 #\a)) 0 eql)
(test (char-index #\a (create-string 1000 #\b)) nil)
($error (char-index #\a "" 0) <program-error>)
($error (char-index #\a "" -1) <domain-error>)
($error (char-index #\a "" -1234567890) <domain-error>)
($error (char-index #\a "" 1234567890) <program-error>)
($error (char-index #\a "abc" 3) <program-error>)
($error (char-index #\a "abc" -1) <domain-error>)
($error (char-index #\a "abc" -1234567890) <domain-error>)
($error (char-index #\a "abc" 1234567890) <program-error>)

;;;
;;; function (STRING-INDEX substring string [start-position]) --> <object>
;;;
($ap 2 "string-index" P.97)
(test (string-index "foo" "foobar") 0 eql)
(test (string-index "bar" "foobar") 3 eql)
(test (string-index "FOO" "foobar") nil)
(test (string-index "foo" "foobar" 1) nil)
(test (string-index "bar" "foobar" 1) 3 eql)
(test (string-index "foo" "") nil)
(test (string-index "" "foo") 0 eql)
;;;
($argc string-index 2 1 0)
($type string-index ($string) :target "abc")
($type string-index ($string) "abc" :target)
($type string-index ($integer) "abc" "abc" :target)
;;;
(test (string-index " " "a b") 1 eql)
(test (string-index "" "") 0 eql)
(test (string-index "abc" "abc") 0 eql)
(test (string-index "aaa" (create-string 1000 #\a)) 0 eql)
(test (string-index "aaa" (create-string 1000 #\b)) nil)
($error (string-index "abc" "" 0) <program-error>)
($error (string-index "abc" "" -1) <domain-error>)
($error (string-index "abc" "" -1234567890) <domain-error>)
($error (string-index "abc" "" 1234567890) <program-error>)
($error (string-index "a" "abc" 3) <program-error>)
($error (string-index "a" "abc" -1) <domain-error>)
($error (string-index "a" "abc" -1234567890) <domain-error>)
($error (string-index "a" "abc" 1234567890) <program-error>)

;;;
;;; function (STRING-APPEND string*) --> <string>
;;;
($ap 2 "string-append" P.98)
(test (string-append "abc" "def") "abcdef" string=)
(test (string-append "abc" "abc") "abcabc" string=)
(test (string-append "abc" "") "abc" string=)
(test (string-append "" "abc") "abc" string=)
(test (string-append "abc" "" "def") "abcdef" string=)
;;;
($argc string-append 0 0 1)
($type string-append ($string) :target)
($type string-append ($string) :target "abc")
($type string-append ($string) "abc" :target)
($type string-append ($string) :target "abc" "def")
($type string-append ($string) "abc" "def" :target)
;;;
(test (string-append) "" string=)
(test (string-append "" "" "") "" string=)
(test (string-append "abc" "def" "ghi") "abcdefghi" string=)
(test (length (string-append (create-string 1000))) 1000 eql)
(test (length (string-append (create-string 1000) (create-string 1000))) 2000 eql)
