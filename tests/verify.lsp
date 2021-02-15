;; load all test code ./test
(gbc)
(format (standard-output) "object-test~%")
(load "tests/object-test.lsp")

(format (standard-output) "arithemetic-test~%")
(load "tests/arithmetic-test.lsp")

(format (standard-output) "array-test~%")
(load "tests/array-test.lsp")

(format (standard-output) "controle-test~%")
(load "tests/controle-test.lsp")

(format (standard-output) "convert-test~%")
(load "tests/convert-test.lsp")

(format (standard-output) "list-test~%")
(load "tests/list-test.lsp")

(format (standard-output) "predicate-test~%")
(load "tests/predicate-test.lsp")

(format (standard-output) "symbol-test~%")
(load "tests/symbol-test.lsp")

(format (standard-output) "All tests are done!~%")
