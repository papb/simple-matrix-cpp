#include <iostream>

class Matrix {
    private:

        double** matrix; // Matrix is stored as a pointer to pointers
        int rows;
        int cols;

        static std::string prettyPrintHelper(double d);

    public:

        // Constructor
        Matrix(int rows, int cols);

        // Rule of Three (with copy-and-swap idiom)
        Matrix(const Matrix& that);
        Matrix& operator=(Matrix that);
        ~Matrix();
        friend void swap(Matrix& a, Matrix& b);

        // Basic getters
        int getRows() const;
        int getCols() const;
        double get(int row, int col) const;

        // Print
        void prettyPrint() const;
        std::string toJSON() const;
        friend std::ostream& operator<<(std::ostream& stream, const Matrix& matrix);

        // Utility setters
        void zeros();
        void ones();
        void unit();

        // Arithmetical operators
        Matrix& operator+=(const Matrix& rhs);
        friend Matrix operator+(Matrix const& lhs, Matrix const& rhs);
        Matrix operator-() const;
        Matrix& operator-=(const Matrix& rhs);
        friend Matrix operator-(Matrix const& lhs, Matrix const& rhs);
        Matrix& operator*=(const Matrix& rhs);
        friend Matrix operator*(Matrix const& lhs, Matrix const& rhs);
        Matrix operator~() const;

        // Other operators
        friend bool operator==(const Matrix& lhs, const Matrix& rhs);
        friend bool operator!=(const Matrix& lhs, const Matrix& rhs);
        double& operator()(int row, int col);

};