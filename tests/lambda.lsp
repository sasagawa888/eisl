(import "elixir")
(import "test")

(defun cadr (x)
  (car (cdr x)))

(defun caar (x) 
  (car (car x)))

(defun caddr (x)
  (car (cdr (cdr x))))

(defun repl ()
  (format "Lambda calculus interpreter")
  (format "To quit enter 'end'")
  (repl))


(defun repl ()
  (block repl
    (cond ((catch 'exit
             (for ((s (read*) (read*)))
                  ((equal s 'end) (return-from repl t))
                  (print* (reduce (combinator s)))
                  (prompt))) t)
          (t (prompt)(repl)))))

(defun read* ()
  (format (standard-output) "~%L> ")
  (parse (convert (read-line) <list>) nil))

(defun print* (x)
  (if (eq (car x) '^)
      (print1* x)
      (print2* x)))

(defun print1* (x)
  (format (standard-output) "^")
  (format-object (standard-output) (cadr x))
  (format (standard-output) ".")
  (print* (caddr x)))

(defun print2* (x)
  (print1* (car x))
  (print1* (cadr x)))


(defun to-upper (x)
  (mapcar (lambda (y)
                (let ((code (convert y <integer>)))
                    (if (and (>= code 97) (<= code 122))
                        (convert (- code 32) <character>)
                        y)))
          x))

;; for test
(defun parse* (x)
    (pipe x |> (convert <list>) |> (to-upper) |> (parse nil) ))
 
#|
parse 
 ^x.x -> (^ x x)
 (^x.x)(^y.y) -> ((^ x x)(^ y y))

|#
(defglobal *rest-list* nil)

(defpattern parse
  ((empty _res) _res)
  ;; space skip
  (((#\space :rest _ls) _res) (parse _ls _res))
  (((#\E #\N #\D) _res) 'end)
  (((#\^ _arg #\. :rest _ls) _) (let* ((arg1 (convert _arg <symbol>))
                                       (body (parse _ls nil)))
                                  (parse *rest-list* (list '^ arg1 body))))
  ;; e.g. ^xyz.z shorthand
  (((#\^ _arg :rest _ls) _) (let* ((arg1 (convert _arg <symbol>)))
                               (cons '^ (list arg1 (parse (cons #\^ _ls) nil)))))
  ;; ( )
  (((#\( :rest _ls) _res) (let* ((exp (parse _ls nil)))
                              (parse *rest-list* (append _res (list exp)))))
  (((#\) :rest _ls) _res)
      (setq *rest-list* _ls)
      _res)
  (((_body :rest _ls) _res) (when (variable-p _body))
             (setq *rest-list* _ls)
             (convert _body <symbol>))
  (else (throw 'exit "syntax error")))

(defun newline ()
  (format (standard-output) "~%"))

(defun lambda-p (x)
  (and (consp x) (eq (car x) '^)))

(defun variable-p (x)
  (and (characterp x) (char>= x #\A) (char<= x #\Z)))

(defpattern combinator
  ((I) `(^ x x))
  ((K) '(^ x (^ y x)))
  ((S) '(^ x (^ y (^ z ((^ x z), (^ y z))))))
  ((Y) '(^ y ((^ x (^ y (^ x x))) (^ x (^ y (^ x x))))))
  (((_x _y))  (append (combinator _x) (combinator _y))) 
  ((_x) _x))


(defpattern reduce
    ((end) (throw 'exit "end"))
    ((_x) (when (atom _x)) _x)
    ((_x) (when (lambda-p _x)) _x)
    (((_x _y)) (when (lambda-p _x))(print `(,_x ,_y)) (reduce (beta _x _y)))
    (((_x _y)) (when (and (atom _x)(atom _y))) `(,_x ,_y))
    (else (print "can't reduce") nil)
)
    

    
     
(defpattern cant-reduce
    ((_x) (when _x) t)
    (((_x _)) (when (atom _x)) t)
    (else t))


(defun beta (x y)
    (let ((arg (cadr x))
          (body (caddr x)))
        (replace body arg y)))

(defun replace (body arg y)
    (cond ((null body) nil)
          ((and (atom body) (eq body arg)) y)
          ((atom body) body)
          (t (cons (replace (car body) arg y)
                   (replace (cdr body) arg y)))))


;;--------------tests------------------------


($test (parse* "^x.x") (^ x x))
($test (parse* "^x. x") (^ x x))
($test (parse* "^x.^x.x") (^ x (^ x x)))
($test (parse* "end") end)
($test (parse* "(^x.x)(^y.y)") ((^ x x)(^ y y)))
($test (parse* "^xy.z") (^ x (^ y z)))
($test (parse* "^xyz.z") (^ X (^ Y (^ Z Z))))

($test (reduce 'y) y)
($test (reduce '(x y)) (x y))
($test (reduce '((^ x x) y) ) y)

#|
  test "total test" do
    assert Lambda.test('y\n') == :y
    assert Lambda.test('Iy\n') == :y
    assert Lambda.test('Is\n') == :s
    assert Lambda.test('Ks\n') == {:y, :s}
    assert Lambda.test('SKKa\n') == :a
    assert Lambda.test('(^y.y((^z.xz)(^z.z)))(^a.a)\n') == [:x, {:z, :z}]
  end

  test "reduce test" do
    assert Lambda.reduce(:y) == :y
    assert Lambda.reduce([:x, :y]) == [:x, :y]
    assert Lambda.reduce([{:x, :x}, :y]) == :y
    assert Lambda.reduce([{:x, :a}, :y]) == :a
  end

  test "parse test" do
    assert Lambda.parse('xy\n', []) == [:x, :y]
    assert Lambda.parse('(xy)\n', []) == [:x, :y]
    assert Lambda.parse('^x.y\n', []) == {:x, :y}
    assert Lambda.parse('^x.(^y.y)\n', []) == {:x, {:y, :y}}
    assert Lambda.parse('(^x.x)(^y.y)\n', []) == [{:x, :x}, {:y, :y}]
    assert Lambda.parse('^x.xy\n', []) == {:x, [:x, :y]}
    assert Lambda.parse('^xy.z\n', []) == {:x, {:y, :z}}
    assert Lambda.parse('^xyz.z\n', []) == {:x, {:y, {:z, :z}}}
    assert Lambda.parse('^x.(^y.(^z.z))\n', []) == {:x, {:y, {:z, :z}}}
    assert Lambda.parse('xyz\n', []) == [[:x, :y], :z]
    assert Lambda.parse('abcd\n', []) == [[[:a, :b], :c], :d]
    assert Lambda.parse('(^x.y)\n', []) == {:x, :y}
    assert Lambda.parse('(^xy.x)\n', []) == {:x, {:y, :x}}
    assert Lambda.parse('(^xyz.x)\n', []) == {:x, {:y, {:z, :x}}}
    assert Lambda.parse('(xy)z\n', []) == [[:x, :y], :z]
    assert Lambda.parse('x(yz)\n', []) == [:x, [:y, :z]]
    assert Lambda.parse('a(b(cd))\n', []) == [:a, [:b, [:c, :d]]]
  end


  |#
