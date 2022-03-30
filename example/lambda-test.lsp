(load "tests/lambda.lsp")


;;--------------tests------------------------


($test (parse* "^X.X") (^ x x))
($test (parse* "^X. X") (^ x x))
($test (parse* "^X.(^X.X)") (^ x (^ x x)))
($test (parse* "end") end)
($test (parse* "(^X.X)(^Y.Y)") ((^ x x)(^ y y)))
($test (parse* "^XY.Z") (^ x (^ y z)))
($test (parse* "^XYZ.Z") (^ X (^ Y (^ Z Z))))
($test (parse* "(XY)Z") ((x y) z))
($test (parse* "X(YZ)") (x (y z)))
($test (parse* "ABCD") (((a b) c) d))
($test (parse* "A(B(C(D)))") (a (b (c d))))

($test (reduce 'y) y)
($test (reduce '(x y)) (x y))
($test (reduce '((^ x x) y) ) y)
($test (reduce '((^ x a) y) ) a)

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

>SS
((^x.(^y.(^z.(xz(yz)))))(^x.(^y.(^z.(xz(yz))))))
^y.(^z.(^x.(^y.(^z.(xz(yz))))z(yz)))
^z.(^x.(^y.(^z.(xz(yz))))z(yz))
^x.(^y.(^z.(xz(yz))))z(yz)
^x.(^y.(^z.(xz(yz))))z
^y.(^z.(zz(yz)))
^z.(zz(yz))
zz(yz)
^y.(^z.(zz(yz)))
^z.(zz(yz))
zz(yz)
^y.(^z.(zz(yz)))(yz)
^z.(zz(yzz))
zz(yzz)
^z.(zz(yzz))
zz(yzz)
^y.(^z.(^z.(zz(yzz))))
^z.(^z.(zz(yzz)))
^z.(zz(yzz))
zz(yzz)
^y.(^z.(^z.(zz(yzz))))
>
  
  |#
