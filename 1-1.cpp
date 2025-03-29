#include <iostream>
#include <cmath>
#include <iomanip>

double f(double x) {
    return pow(cos(x), 3) * cos(3 * x); 
}

double simpson(double a, double b, int n) {
    double h = (b - a) / n;
    double s = f(a) + f(b);

    for (int i = 1; i < n; ++i) {
        double x = a + i * h;
        s += (i % 2 == 0 ? 2 : 4) * f(x);
    }

    return s * h / 3;
}

// Функция для контроля погрешности методом Рунге
double rungeControl(double I1, double I2) {
    return std::abs(I1 - I2) / 15;
}

int main() {
    double a = 0;
    double b = 5;
    double epsilon = 1e-5;

    int n = 2; // Начальное число разбиений
    double I1, I2;
    double error = epsilon + 1; // Инициализируем погрешность

    // Основной цикл для удвоения разбиений
    while (error > epsilon) {
        I1 = simpson(a, b, n); // Результат с n разбиениями
        I2 = simpson(a, b, 2 * n); // Результат с 2n разбиениями
        error = rungeControl(I1, I2); // Погрешность по Рунге

        n *= 2; // Удвоение числа разбиений
    }

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Фактическое количество разбиений: " << n / 2 << std::endl;
    std::cout << "Фактическая погрешность по методу Рунге: " << error << std::endl;
    std::cout << "Приближенное значение интеграла: " << I2 << std::endl;

    return 0;
}
