(import "elixir")
(import "test")

(defun cadr (x)
  (cdr (car x)))

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
  (((_body :rest _ls) _) (when (and (char>= _body #\A) (char<= _body #\Z)))
      (setq *rest-list* _ls)
      (convert _body <symbol>))
  (else (throw 'exit "syntax error")))

(defun newline ()
  (format (standard-output) "~%"))

(defun is-lambda (x)
  (and (consp x) (eq (car x) '^)))

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
    (((_x _y)) (when (is-lambda _x))(print `(,_x ,_y)) (newline)) ;(reduce (beta `(,_x ,_y))))
    (((_x _y)) (when (consp _x)(cant-reduce `(,_x ,_y))) (print `(,_x ,_y)) `(,_x ,_y))
    ;(((_x _y)) (reduce (list (reduce _x) (reduce _y))))
    (((_x _y)) (when (is-lambda ``(,_x ,_y))) (newline) (list '^ _x (reduce _y))) 
)
    

    
     
(defpattern cant-reduce
    ((_x) (when _x) t)
    (((_x _)) (when (atom _x)) t)
    (else t))
  

(defpattern replace 
    ((_x (_x _ys) _z) (list _z (replace _x _ys _z)))
    ((_x (_y _ys) _z) (when (atom _x)) (list _x (replace _x _ys _z)))
    ((_x (_y _ys) _z) (when (atom _x)) (list _y (replace _x _ys _z)))
    ((_x (_y _ys) _z) (when (is_lambda _y)) (list (replace _x _y _z) (replace _x _ys _z)))
    ((_x (_y _ys) _z) (when (consp _y)) (list (replace _x _y _z (replace _x _ys _z))))
    ((_x (_y _ys) _z)  (reduce (list _y _ys)))
    ((_x (^ _arg _body) _z) (list '^ _arg (replace _x _body _z))) 
    ((_ _y _) y))

;;--------------tests------------------------


($test (parse* "^x.x") (^ x x))
($test (parse* "^x. x") (^ x x))
($test (parse* "^x.^x.x") (^ x (^ x x)))
($test (parse* "end") end)
($test (parse* "(^x.x)(^y.y)") ((^ x x)(^ y y)))
($test (parse* "^xy.z") (^ x (^ y z)))
($test (parse* "^xyz.z") (^ X (^ Y (^ Z Z))))

($test (reduce 'y) y)
;($test (reduce '(x y)) (x y))
;($test (reduce '((^ x x) y) ) y)

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


 def beta({arg, body}, y) do
    # IO.inspect binding()
    reduce(replace(arg, body, y))
  end

  def replace(x, x, z) do
    z
  end

  def replace(x, [x, ys], z) do
    [z, replace(x, ys, z)]
  end

  def replace(x, [x, ys], z) when is_atom(x) do
    [x, replace(x, ys, z)]
  end

  def replace(x, [y, ys], z) when is_atom(y) do
    [y, replace(x, ys, z)]
  end

  def replace(x, [y, ys], z) when is_list(y) do
    [replace(x, y, z), replace(x, ys, z)]
  end

  def replace(x, [y, ys], z) when is_tuple(y) do
    [replace(x, y, z), replace(x, ys, z)]
  end

  def replace(_, [y, ys], _) do
    reduce([y, ys])
  end

  def replace(x, {arg, body}, z) do
    {arg, replace(x, body, z)}
  end

  def replace(_, y, _) do
    y
  end
  |#
