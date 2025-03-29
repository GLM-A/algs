#include <iostream>
#include <cmath>
#include <stdexcept>

class NewtonRaphsonSolver {
public:
    // Определение функций системы уравнений
    static double f1(double x, double y) {
        return sin(x + 1) - y - 1.2; // Первое уравнение
    }

    static double f2(double x, double y) {
        return 2 * x + cos(y) - 2; // Второе уравнение
    }

    // Вычисление элементов матрицы Якоби
    static double J11(double x, double y) {
        return cos(x + 1); // Производная f1 по x
    }

    static double J12(double x, double y) {
        return -1; // Производная f1 по y
    }

    static double J21(double x, double y) {
        return 2; // Производная f2 по x
    }

    static double J22(double x, double y) {
        return -sin(y); // Производная f2 по y
    }

    // Метод для вычисления обратной матрицы 2x2
    static void InvertMatrix(double matrix[2][2], double inverse[2][2]) {
        double det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]; // Определитель
        if (fabs(det) < 1e-10) {
            throw std::invalid_argument("Матрица Якоби вырождена, невозможно найти обратную.");
        }

        inverse[0][0] = matrix[1][1] / det;
        inverse[0][1] = -matrix[0][1] / det;
        inverse[1][0] = -matrix[1][0] / det;
        inverse[1][1] = matrix[0][0] / det;
    }

    // Главный метод решения системы
    static void SolveSystem() {
        // Начальное приближение
        double x = 0.0, y = 0.0;

        // Параметры метода
        double tolerance = 1e-6; // Точность
        int maxIterations = 100; // Максимальное количество итераций
        int iteration = 0;

        // Итерационный процесс
        while (iteration < maxIterations) {
            try {
                // Шаг 1: Вычисляем значения функций
                double f1Value = f1(x, y);
                double f2Value = f2(x, y);

                // Проверка условий выхода
                if (fabs(f1Value) < tolerance && fabs(f2Value) < tolerance) {
                    std::cout << "Решение найдено после " << iteration << " итераций:\n";
                    std::cout << "x = " << x << ", y = " << y << "\n";

                    // Проверяем значения функций
                    double finalF1 = f1(x, y);
                    double finalF2 = f2(x, y);
                    std::cout << "Проверка значений функций:\n";
                    std::cout << "f1(x, y) = " << finalF1 << ", f2(x, y) = " << finalF2 << "\n";

                    return;
                }

                // Шаг 2: Вычисляем матрицу Якоби
                double J[2][2] = {
                    { J11(x, y), J12(x, y) },
                    { J21(x, y), J22(x, y) }
                };

                // Шаг 3: Проверка матрицы Якоби
                double detJ = J[0][0] * J[1][1] - J[0][1] * J[1][0];
                if (fabs(detJ) < 1e-10) {
                    std::cout << "Матрица Якоби вырождена, метод не может продолжать работу.\n";
                    return;
                }

                // Шаг 4: Вычисляем обратную матрицу Якоби
                double JInverse[2][2];
                InvertMatrix(J, JInverse);

                // Шаг 5: Вычисляем вектор правой части
                double F[2] = { -f1Value, -f2Value };

                // Шаг 6: Решаем линейную систему J^{-1} * F
                double deltaX = JInverse[0][0] * F[0] + JInverse[0][1] * F[1];
                double deltaY = JInverse[1][0] * F[0] + JInverse[1][1] * F[1];

                // Шаг 7: Обновляем приближение
                x += deltaX;
                y += deltaY;

                // Проверка резкого изменения приближения
                if (fabs(deltaX) > 1e3 || fabs(deltaY) > 1e3) {
                    std::cout << "Чрезмерные корректировки, возможно, начальное приближение некорректно.\n";
                    return;
                }
                iteration++;
            }
            catch (const std::exception& ex) {
                std::cout << "Ошибка во время вычислений: " << ex.what() << "\n";
                return;
            }
        }

        // Если достигнуто максимальное число итераций
        std::cout << "Метод не сошёлся за заданное количество итераций.\n";
    }
};

int main() {
    NewtonRaphsonSolver::SolveSystem();
    return 0;
}
