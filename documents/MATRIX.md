# Matrix
A library for working with vectors and matrices

## Usage

```lisp
(import "matrix")
```

## Specification

### Functions

#### (**matrix::rows** *matrix*)
Returns the row vectors of matrix `matrix`

#### (**matrix::rows->matrix** *rows*)
Converts a vector of row vectors into a matrix

#### (**matrix::columns** *matrix*)
Returns the column vectors of matrix `matrix`

#### (**matrix::colmuns->matrix** *columns*)
Converts a vector of column vectors into a matrix

#### (**matrix::transpose** *x*)
Transposes a vector or matrix `x`

#### (**matrix::add** *operand* *operand+*)
Adds the operands `operand` together

#### (**matrix::sub** *operand* *operand+*)
Subtracts the operands `operand` from left to right

#### (**matrix::element-wise-product** *operand* *operand+*)`
Performs the element-wise product on operands `operand`.
This is also known as the Hadamard product

#### (**matrix::mult** *operands* *operand+*)
Multiplies operands `operand` together from left to right

#### (**matrix::negate** *x*)
Negates `x`

#### (**matrix::dot** *x* *y*)
Calculates the dot product of `x` and `y`

#### (**matrix::cross** *x* *y*)
Calculates the cross product of `x` and `y`

#### (**matrix::norm** *x*)
Calculates the Euclidean norm of vector `x`

#### (**matrix::normalize** *x*)
Normalizes vector `x`

#### (**matrix::cartesian-product** *vector+*)
Returns the cartesian product of the vectors `vector`