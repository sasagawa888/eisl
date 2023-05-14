# Matrix
A library for working with vectors and matrices

## Usage

```lisp
(import "matrix")
```

## Specification


### data type

#### matrix
e.g. #2a((1 2)(3 4))
#### vector
e.g. #(1 2 3)
#### rows
Matrix it's elements are row vectors
#### columns
Matrix it's elements are column vectors

### Functions

#### (matrixp x)
If x is matrix data return t, else nil.

#### (matrix-convert x class)
- (matrix-convert x <rows>)  convert from matrix to row-vector matrix.
- (matrix-convert x <columns>) convert from matrix to colmun-vector matrix.
- (matrix-convert x <general-array*>) convert from row(or column)-vector to matrix. 

#### (matrix-transpose x)
Transposes a vector or matrix `x`

#### (matrix-add *operand* *operand+*)
Adds the operands `operand` together

#### (matrix-sub *operand* *operand+*)
Subtracts the operands `operand` from left to right

#### (matrix-hadamard *operand* *operand+*)`
Performs the element-wise product on operands `operand`.
This is also known as the Hadamard product

#### (matrix-mult *operands* *operand+*)
Multiplies operands `operand` together from left to right

#### (matrix-negate x)
Negates `x`

#### (vector-dot x y)
Calculates the dot product of `x` and `y`

#### (vector-cross *x* *y*)
Calculates the cross product of `x` and `y`

#### (matrix-norm x)
Calculates the Euclidean norm of vector `x`

#### (matrix-normalize x)
Normalizes vector `x`

#### (matrix-cartesian *vector+*)
Returns the cartesian product of the vectors `vector`

#### (matrix-det matrix)
Returns matrix determinant of matrix