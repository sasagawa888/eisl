(import "elixir")


(defun cadr (x)
  (cdr (car x)))

(defun caar (x) 
  (car (car x)))

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
  (format (standard-output) "^")
  (format-object (standard-output) (car x))
  (format (standard-output) ".")
  (print* (cadr x)))


  ;; for test
  (defun test (x)
    (pipe (parse x nil) |> (combinator) |> (reduce)))
 
#|
parse 
 ^x.x -> (^ x x)
 (^x.x)(^y.y) -> ((^ x x)(^ y y))

input char-list  respons
return (body . rest-list)
|#

(defpattern parse
  ((empty _res) _res)
  (((#\e #\n #\d) _res) _res)
  (((#\^ _arg #\. :rest ls)) (let* ((arg1 (convert _arg <symbol>))
                                    (dt (parse1 ls nil)
                                    (body (car dt)))
                                    (ls1 (cdr dt)))
                                  (parse ls1 (cons '^ (cons arg1 body)))))
  ;; e.g. ^xyz.z shorthand
  (((#\^ _arg :rest ls) _) (let* ((arg1 (convert _arg <symbol>)))
                               (cons '^ (cons arg1 (parse (cons #\^ ls) nil)))))
  ;; ( )
  (((#\( :rest ls) _res) (let* ((dt (parse (cons #\( ls) nil))
                                (exp (car dt))
                                (ls1 (cdr dt)))
                            (cond ((null _res) (parse ls1 exp))
                                  (t (parse ls1 (append (list _res) (list exp)))))))
  ;; space skip
  (((#\space :rest ls) _res) (parse ls res))
  (else (throw 'exit "syntax error")))

#|
 
  

  def print(x) when is_atom(x) do
    IO.write(x)
  end

  def print([x, y]) when is_tuple(x) and is_tuple(y) do
    # IO.inspect binding()
    IO.write("(")
    print1(x)
    print1(y)
    IO.write(")")
  end

  def print({x, y}) do
    IO.write("^")
    IO.write(x)
    IO.write(".")
    print1(y)
  end

  def print([x, y]) do
    # IO.inspect binding()
    print(x)
    print1(y)
  end

  def print(e) do
    IO.write(e)
  end

  def print1({x, y}) do
    # IO.inspect binding()
    IO.write("(^")
    IO.write(x)
    IO.write(".")
    print1(y)
    IO.write(")")
  end

  def print1([x, y]) when is_tuple(x) and is_tuple(y) do
    # IO.inspect binding()
    IO.write("(")
    print1(x)
    print1(y)
    IO.write(")")
  end

  def print1([x, y]) do
    IO.write("(")
    print(x)
    print1(y)
    IO.write(")")
  end

  def print1(e) do
    # IO.inspect binding()
    IO.write(e)
  end

  def newline() do
    IO.write('\n')
  end

  def is_lambda({_, _}) do
    true
  end

  def is_lambda(_) do
    false
  end

  def combinator(:I) do
    {:x, :x}
  end

  def combinator(:K) do
    {:x, {:y, :x}}
  end

  def combinator(:S) do
    {:x, {:y, {:z, [[:x, :z], [:y, :z]]}}}
  end

  def combinator(:Y) do
    {:y, [{:x, [:y, [:x, :x]]}, {:x, [:y, [:x, :x]]}]}
  end

  def combinator([x, y]) do
    [combinator(x)] ++ [combinator(y)]
  end

  def combinator(x) do
    x
  end

  def reduce(:end) do
    throw("end")
  end

  def reduce(x) when is_atom(x) do
    x
  end

  def reduce([x, y]) when is_atom(x) do
    [x, y]
  end

  def reduce([x, y]) when is_tuple(x) do
    print([x, y])
    newline()
    reduce(beta(x, y))
  end

  def reduce([x, y]) when is_list(x) do
    print([x, y])
    newline()

    if cant_reduce(x) do
      [x, y]
    else
      reduce([reduce(x), y])
    end
  end

  def reduce({a, body}) do
    print({a, body})
    newline()
    exp = reduce(body)
    {a, exp}
  end

  def cant_reduce(x) when is_atom(x) do
    true
  end

  def cant_reduce([x, _]) when is_atom(x) do
    true
  end

  def cant_reduce(_) do
    false
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
end

|#
