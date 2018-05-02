#include "matrix.h"

void test() {
    Matrix m1(3, 2);
    m1.ones();
    Matrix m2 = m1 * ~m1;
    std::cout << m1 << "\n";
    m2.prettyPrint();
    Matrix m3(4, 4);
    m3 = m2;
    m3(1, 1) = 7;
    m3 *= m3;
    std::cout << m3 << "\n";
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