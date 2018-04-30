#include "matrix.h"

void test() {
    Matrix m1(3, 2);
    m1.ones();
    std::cout << m1 << "\n";
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