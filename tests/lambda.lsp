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
  (parse (convert (read-line) <list>)))


(defun parse (x)
  (let ((1st (elt x 0))
        (2nd (elt x 1))
        (3rd (elt x 2)))
      (cond ((and (char= 1st #\^) (char= 3rd #\.))) 
      

(defun print* (x)
  (format (standard-output) "^")
  (format-object (standard-output) (car x))
  (format (standard-output) ".")
  (print* (cadr x)))

#|
I will port Lambda interpreter from Elixir

defmodule Lambda do
  @moduledoc """
  This code is Lambda interpreter
  """

  @doc """
  Invoke interpreter

  ## Examples

      #iex> Lambda.repl()
      #for halt >end

  """
  def lambda() do
    IO.puts("Lambda calculus interpreter")
    IO.puts("To quit enter 'end'")
    repl()
  end

  def repl() do
    try do
      read() |> combinator |> reduce |> print
      repl()
    catch
      x ->
        IO.write(x)

        if x != "end" do
          repl()
        end
    end
  end

  def read() do
    IO.gets("\n>") |> String.to_charlist() |> parse([])
  end

  # for test
  def test(x) do
    parse(x, []) |> combinator |> reduce
  end

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
