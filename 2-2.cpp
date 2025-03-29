#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

const double EPSILON = 1e-6; // Точность
const int MAX_ITERATIONS = 100; // Максимальное количество итераций

// Функция для выполнения одной итерации метода Зейделя
vector<double> seidel(const vector<vector<double>>& A, const vector<double>& b, vector<double>& x) {
    int n = A.size();
    vector<double> x_new = x; // Создаем новый вектор
    for (int i = 0; i < n; ++i) {
        double sum = 0.0;
        for (int j = 0; j < n; ++j) {
            if (j != i) {
                sum += A[i][j] * x_new[j];
            }
        }
        x_new[i] = (b[i] - sum) / A[i][i]; // Обновляем x
    }
    return x_new;
}

// Основная функция
int main() {
    vector<vector<double>> A = {
        {5, 1, -1},
        {-1, 3, -1},
        {1, -2, 4}
    };
    vector<double> b = {-5, 5, 1};
    vector<double> x(3, 0); // Начальное приближение, по умолчанию 0

    int iterations = 0;
    while (iterations < MAX_ITERATIONS) {
        vector<double> x_new = seidel(A, b, x);
        
        // Проверка сходимости
        double norm = 0.0;
        for (int i = 0; i < x.size(); ++i) {
            norm += pow(x_new[i] - x[i], 2);
        }
        if (sqrt(norm) < EPSILON) {
            break;
        }
        x = x_new; // Обновляем вектор
        iterations++;
    }

    // Вывод результатов
    cout << "Решение:" << endl;
    for (double xi : x) {
        cout << setw(10) << xi << endl;
    }
    
    return 0;
}
