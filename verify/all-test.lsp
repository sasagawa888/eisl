;; load all test code ./test
(gbc)
(format (standard-output) "object-test~%")
(load "verify/object-test.lsp")

(format (standard-output) "arithemetic-test~%")
(load "verify/arithmetic-test.lsp")

(format (standard-output) "array-test~%")
(load "verify/array-test.lsp")

(format (standard-output) "controle-test~%")
(load "verify/controle-test.lsp")

(format (standard-output) "convert-test~%")
(load "verify/convert-test.lsp")

(format (standard-output) "list-test~%")
(load "verify/list-test.lsp")

(format (standard-output) "predicate-test~%")
(load "verify/predicate-test.lsp")

(format (standard-output) "symbol-test~%")
(load "verify/symbol-test.lsp")

(format (standard-output) "char-test~%")
(load "verify/char-test.lsp")

(format (standard-output) "string-test~%")
(load "verify/string-test.lsp")

(format (standard-output) "vector-test~%")
(load "verify/vector-test.lsp")

(format (standard-output) "seq-test~%")
(load "verify/seq-test.lsp")

(format (standard-output) "All tests are done!~%")
