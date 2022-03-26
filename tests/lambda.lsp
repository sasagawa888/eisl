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

input char-list  respons
return (body . rest-list)
|#

(defpattern parse
  ((empty _res) _res)
  ;; space skip
  (((#\space :rest _ls) _res) (parse _ls _res))
  (((#\e #\n #\d) _res) 'end)
  (((#\^ _arg #\. :rest _ls) _) (let* ((arg1 (convert _arg <symbol>))
                                     (dt (parse _ls nil))
                                     (body (car dt))
                                     (ls1 (cdr dt)))
                                  (parse ls1 (cons '^ (list arg1 body)))))
  ;; e.g. ^xyz.z shorthand
  (((#\^ _arg :rest _ls) _) (let* ((arg1 (convert _arg <symbol>)))
                               (cons '^ (list arg1 (parse (cons #\^ _ls) nil)))))
  ;; ( )
  (((#\( :rest _ls) _res) (let* ((dt (parse _ls nil))
                                 (exp (car dt))
                                 (ls1 (cdr dt)))
                            (cond ((null _res) (parse ls1 exp))
                                  (t (parse ls1 (append (list _res) (list exp)))))))
  (((#\) :rest _ls) _res) _res)
  (((_body :rest _ls) _) (cons (convert _body <symbol>) _ls))
  (else (throw 'exit "syntax error")))


#|
# terminal
  def parse('\n', res) do
    res
  end

  def parse('end\n', _) do
    :end
  end

  # ^ arg .
  def parse([94, arg, 46 | ls], _) do
    arg1 = String.to_atom(<<arg>>)
    {body, ls1} = parse1(ls, [])
    parse(ls1, {arg1, body})
  end

  # e.g. ^xyz.z shorthand
  def parse([94, arg | ls], _) do
    arg1 = String.to_atom(<<arg>>)
    {arg1, parse([94 | ls], [])}
  end

  def parse([l | ls], res) when l >= 65 and l <= 122 do
    # IO.inspect binding()
    cond do
      res == [] -> parse(ls, String.to_atom(<<l>>))
      true -> parse(ls, [res] ++ [String.to_atom(<<l>>)])
    end
  end

  # ( )
  def parse([40 | ls], res) do
    # IO.inspect binding()
    {exp, ls1} = parse1([40 | ls], [])

    cond do
      res == [] -> parse(ls1, exp)
      true -> parse(ls1, [res] ++ [exp])
    end
  end

  # space skip
  def parse([32 | ls], res) do
    parse(ls, res)
  end

  def parse(_, _) do
    # IO.inspect binding()
    throw("syntax error")
  end

  # e.g. ^x.y
  def parse1([94, arg, 46 | ls], res) do
    # IO.inspect binding()
    arg1 = String.to_atom(<<arg>>)
    {body, ls1} = parse1(ls, res)
    {{arg1, body}, ls1}
  end

  # e.g. ^xyz.z shorthand
  def parse1([94, arg | ls], _) do
    # IO.inspect binding()
    arg1 = String.to_atom(<<arg>>)
    {body, ls1} = parse1([94 | ls], [])
    {{arg1, body}, ls1}
  end

  def parse1([l | ls], res) when l >= 65 and l <= 122 do
    # IO.inspect binding()
    cond do
      res == [] -> parse1(ls, String.to_atom(<<l>>))
      true -> parse1(ls, [res] ++ [String.to_atom(<<l>>)])
    end
  end

  def parse1([40 | ls], res) do
    # IO.inspect binding()
    {exp, [41 | ls1]} = parse1(ls, [])

    cond do
      res == [] -> parse1(ls1, exp)
      true -> parse1(ls1, [res] ++ [exp])
    end
  end

  def parse1([41 | ls], res) do
    # IO.inspect binding()
    {res, [41 | ls]}
  end

  # space skip
  def parse1([32 | ls], res) do
    parse1(ls, res)
  end

  def parse1('\n', res) do
    # IO.inspect binding()
    {res, '\n'}
  end

  def parse1(_, _) do
    # IO.inspect binding()
    throw("syntax error1")
  end


|#


(defun newline ()
  (format (standard-output) "~%"))

(defun is-lambda (x)
  (and (consp x) (eq (car) '^)))

(defpattern combinator
  ((I) `(^ x x))
  ((K) '(^ x (^ y x)))
  ((S) '(^ x (^ y (^ z ((^ x z), (^ y z))))))
  ((Y) '(^ y ((^ x (^ y (^ x x))) (^ x (^ y (^ x x))))))
  (((_x _y))  (append (combinator _x) (combinator _y))) 
  ((_x) _x))


(defpattern reduce
    ((end) (throw 'exit "end"))
    ((_x) (when _x) _x)
    (((_x _y)) (when (is_lambda _x)) (print `(,_x ,_y)) (newline) (reduce (beta `(,_x ,_y))))
    (((_x _y)) (when (consp _x)(cant-reduce `(,_x ,_y))) (print `(,_x ,_y)) `(,_x ,_y))
    (((_x _y)) (reduce (list (reduce _x) (reduce _y))))
    (((_x _y)) (when (is_lambda ``(,_x ,_y))) (newline) (list '^ _x (reduce _y))))
    
     
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
($test (parse* "^x.(^x.x)") (^ x (^ x x)))