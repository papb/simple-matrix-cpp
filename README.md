# Matrix.h

Simple library for manipulating matrices of `double` values in C++.

## Quick Start

Obtain the files `matrix.cpp` and `matrix.h`, and use:

```c++
#include "matrix.h"

int main(int argc, char **argv) {
    Matrix m1(3, 3);
    m1.ones();
    std::cout << m1 << "\n";

    Matrix m2(3, 3);
    m2.unit();
    std::cout << m2 << "\n";

    Matrix m3 = m1 * m2;
    std::cout << (m1 == m3) << "\n"; // true

    return EXIT_SUCCESS;
}
```

## Complete documentation

### Construtor

The only available constructor receives two int parameters, the number of lines and the number of columns (in this order). If one of them is less than 1, an `std::invalid_argument` exception will be thrown. The resulting matrix automatically has all its entries initialized to zero.

If there is not enough memory space for the initialization, an `std::bad_alloc` will be thrown (as usual).

### Copy constructor, copy assignment, destructor and swap

Internally, the matrix is stored using a pointer to an array of pointers to `double`. The implementation follows the pattern of the [Rule of Three](https://en.wikipedia.org/wiki/Rule_of_three_(C%2B%2B_programming)), therefore the user can rest assured that there is no nmemory leak happening.

Therefore, both the copy constructor and the copy assignment operator (`operator=`) are available normally. The destructor is also implemented and guarantees that there are no memory leaks.

Besides, for the adequate implementation of these methods, the [copy-and-swap idiom](https://stackoverflow.com/questions/3279543) was used. Thus, yet another method is also available for the user: the `void swap(Matrix& a, Matrix& b)`, to swap two matrices.

### Basic getters and setters

The following basic getters are available:

* `int Matrix::getRows() const;` which returns the amount of rows of the matrix.
* `int Matrix::getCols() const;` which returns the amount of columns of the matrix.
* `double get(int row, int col) const;` which returns the value present int the cell at row `row` and column `col`.

The operator `()` is also overloaded for cell value inspection, just like in the `get()` method, with the only difference being that it is not `const`, since the same `operator() can also be used as a setter for the content of a cell, as in the following example:

```c++
Matrix m(3, 4);
std::cout << m.getRows() << "\n"; // 3
std::cout << m.getCols() << "\n"; // 4
std::cout << m.get(1, 2) << "\n"; // 0
m(1, 2) = 5;
std::cout << m.get(1, 2) << "\n"; // 5
std::cout << m(1, 2) << "\n"; // 5
```

The following setters are also available:

* `void zeros()`: sets all cells of the matrix to 0.
* `void ones()`: sets all cells of the matrix to 1.
* `void unit()`: if it is a square matrix, it is set to the unit matrix, i.e., every cell in the main diagonal is set to 1 and the other cells are set to 0. If the matrix is not square, a `std::logic_error` is thrown.

### String conversion and printing

To convert a matrix to a string format, the method `std::string toJSON() const` is provided, which returns the representation of the matrix as a JSON string.

Also, the appropriate overloading of the operator `<<` is provided as usual, which automatically converts the matrix to string using the `toJSON()` method mentioned above.

```c++
Matrix m(2, 2);
m.unit();
std::cout << m; // "[[1,0],[0,1]]"
```

Another method, `void prettyPrint() const`, is also provided, which prints to `std::cout` the contents of the matrix in a readable manner, line per line, with the values rounded to two decimal places.

### Comparison operators

The operators `==` and `!=` were overloaded and are available. Two matrices are considered equal if and only if they have equal dimensions and equal contents on each cell.

### Arithmetic operators

The addition (`+`, `+=`), subtraction (unary `-`, binary `-`, `-=`) and matrix multiplication (`*`, `*=`) operators are available. Any attempt to operate with matrices in an invalid way (e.g. adding matrices of different dimensions) will cause an `std::invalid_argument` exception to be thrown.

Also, the unary operator `~` is also available to obtain the transpose of the given matrix.

### License

MIT © Pedro Augusto de Paula Barbosa