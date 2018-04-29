#include <iostream>
#include <stdexcept>
#include <sstream>

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

        // Print
        void print();
        std::string toJSON();

        // Arithmetical operators
        Matrix& operator+=(const Matrix& rhs);
        friend Matrix operator+(Matrix const& lhs, Matrix const& rhs);
        Matrix operator-() const;

        // Comparison operators
        friend bool operator==(const Matrix& lhs, const Matrix& rhs);
        friend bool operator!=(const Matrix& lhs, const Matrix& rhs);
};

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
std::string Matrix::toJSON() {
    std::ostringstream oss;
    oss << "[";
    for (int i = 0; i < rows; i++) {
        oss << "[" << matrix[i][0];
        for (int j = 1; j < cols; j++) {
            oss << "," << matrix[i][j];
        }
        oss << "]";
        if (i != rows - 1) {
            oss << ",";
        }
    }
    oss << "]";
    return oss.str();
}

// ------------------------------------------------------------------- //

Matrix& Matrix::operator+=(const Matrix& rhs) {
    if (rows != rhs.rows || cols != rhs.cols) {
        throw std::invalid_argument("Matrixes must have the same dimensions to be added.");
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] += rhs.matrix[i][j];
        }
    }

    return *this;
}
Matrix operator+(Matrix const& lhs, const Matrix& rhs) {
    Matrix result(lhs);
    result += rhs;
    return result;
}
Matrix Matrix::operator-() const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = -this->matrix[i][j];
        }
    }
    return result;
}

// ------------------------------------------------------------------- //

bool operator==(const Matrix& lhs, const Matrix& rhs) {
    if (lhs.rows != rhs.rows || lhs.cols != rhs.cols) return false;
    for (int i = 0; i < lhs.rows; i++) {
        for (int j = 0; j < lhs.cols; j++) {
            if (lhs.matrix[i][j] != rhs.matrix[i][j]) return false;
        }
    }
    return true;
};
bool operator!=(const Matrix& lhs, const Matrix& rhs) {
    return !(lhs == rhs);
}

// ------------------------------------------------------------------- //

void test() {
    Matrix m1(3, 3);
    Matrix m2(3, 3);
    m1(0,0) = 10;
    m2(0,0) = 20;
    m1 += m1;
    std::cout << m1.toJSON() << "\n";
    std::cout << m2.toJSON() << "\n";
    std::cout << (m1 != m2) << "\n";
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