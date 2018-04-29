#include <iostream>
#include <stdexcept>

class Matrix {
    private:

        int** matrix;
        int rows;
        int cols;

    public:

        // Constructor
        Matrix(int rows, int cols);

        // Rule of Three
        Matrix(const Matrix& that);
        Matrix& operator=(const Matrix& that);
        ~Matrix();

        // Basic getters
        int getRows() const;
        int getCols() const;
        int get(int row, int col) const;
        int& operator()(int row, int col);

        void print();

        // Matrix& operator+=(const Matrix& rhs);
        // friend Matrix operator+(Matrix const& lhs, Matrix const& rhs);
};

// Matrix& operator+=(const Matrix& rhs) {
//     /* addition of rhs to *this takes place here */
//     return *this; // return the result by reference
// }
// Matrix operator+(Matrix const& lhs, const Matrix& rhs) {
//     Matrix result = lhs;
//     lhs += rhs; // reuse compound assignment
//     return lhs; // return the result by value (uses move constructor)
// }
// Matrix operator+(Matrix const& lhs, Matrix const& rhs) {
//     if (lhs.rows != rhs.rows || lhs.cols != rhs.cols) {
//         throw std::invalid_argument("Matrixes must have the same dimensions to be added.");
//     }
//     Matrix result(lhs.rows, lhs.cols);
//     for (int i = 0; i < lhs.rows; i++) {
//         for (int j = 0; j < lhs.cols; j++) {
//             result(i,j) = lhs.get(i,j) + rhs.get(i,j);
//         }
//     }
//     return result;
// };

// ------------------------------------------------------------------- //

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    std::cout << "Matrix constructor called\n";
    matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 0;
        }
    }
}

Matrix::Matrix(const Matrix& that) : rows(that.rows), cols(that.cols) {
    std::cout << "Matrix copy constructor called\n";
    matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = that.matrix[i][j];
        }
    }
}

Matrix& Matrix::operator=(const Matrix& that) {
    std::cout << "Matrix copy assignment operator called\n";

    // TODO - Known issue: This copy assignment implementation
    // is dangerous because if the attempt to get the new resource
    // throws, this object will be left in an invalid state.

    if (this != &that) {
        // Free the old matrix pointers
        for (int i = 0; i < rows; i++) delete [] matrix[i];
        delete [] matrix;

        // Set the new rows & cols
        rows = that.rows;
        cols = that.cols;

        // Get the new resources
        matrix = new int*[rows];
        for (int i = 0; i < rows; i++) {
            matrix[i] = new int[cols];
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = that.matrix[i][j];
            }
        }
    }
    return *this;
}

Matrix::~Matrix() {
    std::cout << "Matrix destructor called\n";
    for (int i = 0; i < rows; i++) delete [] matrix[i];
    delete [] matrix;
}

// ------------------------------------------------------------------- //

int Matrix::getRows() const {
    return rows;
}
int Matrix::getCols() const {
    return cols;
}
int Matrix::get(int row, int col) const {
    if (rows <= row || cols <= col) throw std::invalid_argument("Index out of bounds.");
    return matrix[row][col];
}
int& Matrix::operator()(int row, int col) {
    if (rows <= row || cols <= col) throw std::invalid_argument("Index out of bounds.");
    return matrix[row][col];
}

// ------------------------------------------------------------------- //

void Matrix::print() {
    for (int i = 0; i < rows; i++) {
        std::cout << matrix[i][0];
        for (int j = 1; j < cols; j++) {
            std::cout << " " << matrix[i][j];
        }
        std::cout << "\n";
    }
}

// ------------------------------------------------------------------- //

void test() {
    Matrix m1(3, 3);
    Matrix m2(3, 3);
    m1(0,0) = 10;
    m2(0,0) = 20;
    m1.print();
    m2.print();
}

int main(int argc, char **argv) {
    try {
        test();
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
}