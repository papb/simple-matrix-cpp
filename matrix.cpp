#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include "matrix.h"

// ------------------------------------------------------------------- //

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    if (rows < 1) throw std::invalid_argument("There must be at least one row.");
    if (cols < 1) throw std::invalid_argument("There must be at least one column.");
    matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new double[cols];
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 0;
        }
    }
}

Matrix::Matrix(const Matrix& that) : rows(that.rows), cols(that.cols) {
    matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new double[cols];
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = that.matrix[i][j];
        }
    }
}

void swap(Matrix& a, Matrix& b) {
    std::swap(a.rows, b.rows);
    std::swap(a.cols, b.cols);
    std::swap(a.matrix, b.matrix);
}

Matrix& Matrix::operator=(Matrix that) {
    // Using copy-and-swap idiom
    // https://stackoverflow.com/a/3279550/4135063
    swap(*this, that);
    return *this;
}

Matrix::~Matrix() {
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
double Matrix::get(int row, int col) const {
    if (rows <= row || cols <= col) throw std::invalid_argument("Index out of bounds.");
    return matrix[row][col];
}
double& Matrix::operator()(int row, int col) {
    if (rows <= row || cols <= col) throw std::invalid_argument("Index out of bounds.");
    return matrix[row][col];
}

// ------------------------------------------------------------------- //

std::string Matrix::prettyPrintHelper(double d) {
    std::ostringstream ss1;
    ss1 << std::fixed << std::setprecision(2) << d;
    std::string temp = ss1.str();
    std::ostringstream ss2;
    ss2 << std::setw(8) << temp;
    return ss2.str();
}
void Matrix::prettyPrint() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j > 0) std::cout << " ";
            std::cout << Matrix::prettyPrintHelper(matrix[i][j]);
        }
        std::cout << "\n";
    }
}
std::string Matrix::toJSON() const {
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
std::ostream& operator<<(std::ostream& stream, const Matrix& matrix) {
    return stream << matrix.toJSON();
}

// ------------------------------------------------------------------- //

void Matrix::zeros() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 0;
        }
    }
}
void Matrix::ones() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 1;
        }
    }
}
void Matrix::unit() {
    if (rows != cols) {
        throw std::logic_error("The matrix must be square.");
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i == j ? 1 : 0;
        }
    }
}

// ------------------------------------------------------------------- //

Matrix& Matrix::operator+=(const Matrix& rhs) {
    if (rows != rhs.rows || cols != rhs.cols) {
        throw std::invalid_argument("Matrices must have the same dimensions to be added.");
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
            result.matrix[i][j] = -this->matrix[i][j];
        }
    }
    return result;
}
Matrix& Matrix::operator-=(const Matrix& rhs) {
    *this += -rhs;
    return *this;
}
Matrix operator-(Matrix const& lhs, const Matrix& rhs) {
    Matrix result(lhs);
    result -= rhs;
    return result;
}
Matrix& Matrix::operator*=(const Matrix& rhs) {
    if (this->cols != rhs.rows) {
        throw std::invalid_argument("The matrices do not have compatible dimensions for multiplication.");
    }
    Matrix temp(this->rows, rhs.cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < rhs.cols; j++) {
            temp.matrix[i][j] = 0;
            for (int k = 0; k < cols; k++) {
                temp.matrix[i][j] += this->matrix[i][k] * rhs.matrix[k][j];
            }
        }
    }
    swap(*this, temp);
    return *this;
}
Matrix operator*(Matrix const& lhs, const Matrix& rhs) {
    Matrix result(lhs);
    result *= rhs;
    return result;
}
Matrix Matrix::operator~() const {
    Matrix result(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.matrix[j][i] = this->matrix[i][j];
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
}
bool operator!=(const Matrix& lhs, const Matrix& rhs) {
    return !(lhs == rhs);
}
