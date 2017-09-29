#include "complex_num.h"
#include <iostream>
#include <vector>
#include <cstdlib>

void read_poly(std::vector<Complex> &coef) {
    std::cout << "Insert coefficients. "
                 "It should be pair of numbers separated by space.\n"
                 "Insert symbol 'x' to finish.\n";

    while (true) {
        Complex t;
        std::cout << "Insert a_" << coef.size() << ": ";
        std::cin >> t;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore();
            break;
        }
        std::cout << t << "\n";
        coef.push_back(t);
    }

    if (coef.empty()) {
      Complex zero;
      coef.push_back(zero);
    }

    std::cout << "Poly is: \n";
    std::cout << coef[0];
    for (size_t i = 1; i < coef.size(); ++i) {
        std::cout << "+ (" << coef[i] << ")*x^" << i;
    }
    std::cout << "\n";
}

Complex evaluate_poly(const std::vector<Complex> &coef, Complex z) {
    Complex res = coef[0];
    for (auto it = coef.begin()+1; it != coef.end(); ++it) {
        res += (*it) * z;
        z *= z;
    }
    return res;
}

int main(int argc, char* argv[]) {
    std::vector<Complex> coef;
    read_poly(coef);

    std::cout << "Insert z: ";
    Complex z;
    std::cin >> z;
    std::cout << z << "\n";
    std::cout << "f(z) = " << evaluate_poly(coef, z) << "\n";

    return EXIT_SUCCESS;
}
