#include <iostream>
#include <cmath>

double f(double x) {
    return 2 * log(x) - 1 / x;
}

double bisection(double a, double b, double tol) {
    if (f(a) * f(b) >= 0) {
        std::cerr << "Знаменатель не удовлетворяет условиям метода дихотомии." << std::endl;
        return NAN;
    }
    double c;
    while ((b - a) >= tol) {
        c = (a + b) / 2;
        if (f(c) == 0.0) {
            break;
        }
        if (f(c) * f(a) < 0) {
            b = c;
        } else {
            a = c;
        }
    }
    return c;
}

int main() {
    double a = 1; // Начальное значение
    double b = 3; // Границы
    double tol = 0.0001; // Точность
    double root = bisection(a, b, tol);
    std::cout << "Корень: " << root << std::endl;
    return 0;
}
