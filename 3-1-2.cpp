#include <iostream>
#include <cmath>

double f(double x) {
    return 2 * log(x) - 1 / x;
}

double f_prime(double x) {
    return 2 / x + 1 / (x * x);
}

double newtonRaphson(double x0, double tolerance, int maxIterations) {
    double x1;
    int iteration = 0;

    do {
        x1 = x0 - f(x0) / f_prime(x0);
        iteration++;

        if (fabs(x1 - x0) < tolerance) {
            break;
        }

        x0 = x1;
    } while (iteration < maxIterations);
    
    return x1;
}

int main() {
    double initialGuess = 2.0; // начальное приближение
    double tolerance = 1e-7; // допустимая точность
    int maxIterations = 100; // максимальное количество итераций

    double root = newtonRaphson(initialGuess, tolerance, maxIterations);

    std::cout << "Корень уравнения: " << root << std::endl;

    return 0;
}
