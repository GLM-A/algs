#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Вычисляет скалярное произведение двух векторов. Это используется для 
// нахождения величины, необходимой для обновления направления в методе 
// сопряженных градиентов.
double dotProduct(const vector<double> &a, const vector<double> &b) {
    double result = 0;
    for (size_t i = 0; i < a.size(); i++) {
        result += a[i] * b[i];
    }
    return result;
}

// Умножает матрицу (A) на вектор (x). Это необходимо для вычисления 
//вектора (Ap) в процессе итераций.
vector<double> matVecMult(const vector<vector<double>> &A, const vector<double> &x) {
    vector<double> result(A.size(), 0);
    for (size_t i = 0; i < A.size(); i++) {
        for (size_t j = 0; j < A[i].size(); j++) {
            result[i] += A[i][j] * x[j];
        }
    }
    return result;
}

// Вычисляет норму (длину) вектора. Это используется для проверки, достигнута 
// ли заданная точность (толерантность) в процессе итераций.
double vecNorm(const vector<double> &v) {
    double sum = 0;
    for (double val : v) {
        sum += val * val;
    }
    return sqrt(sum);
}

// Основная функция, реализующая метод сопряженных градиентов. Она принимает 
// матрицу (A), вектор (b) и опциональную толерантность. Внутри функции происходит 
//итеративное обновление вектора (x) до тех пор, пока остаток (разность между (b) 
// и (Ax)) не станет меньше заданной толерантности.
vector<double> conjugateGradient(const vector<vector<double>> &A, const vector<double> &b, double tolerance = 1e-10) {
    int n = A.size();
    vector<double> x(n, 0); // Начальное приближение
    vector<double> r = b;    // Остаток
    vector<double> p = r;    // Направление

    double rNorm = vecNorm(r);

    while (rNorm > tolerance) {
        vector<double> Ap = matVecMult(A, p);
        double alpha = rNorm * rNorm / dotProduct(r, Ap);

        // Обновление x
        for (int i = 0; i < n; i++) {
            x[i] += alpha * p[i];
        }

        // Обновление остатков
        vector<double> r_new = r;
        for (int i = 0; i < n; i++) {
            r_new[i] -= alpha * Ap[i];
        }

        double beta = vecNorm(r_new) * vecNorm(r_new) / (rNorm * rNorm);
        
        // Обновление направления
        for (int i = 0; i < n; i++) {
            p[i] = r_new[i] + beta * p[i];
        }

        r = r_new;
        rNorm = vecNorm(r);
    }

    return x;
}

int main() {
    vector<vector<double>> A = {
        {5, 0, 1},
        {1, 3, -1},
        {-30, 2, 10}
    };
    vector<double> b = {11, 4, 6};

    vector<double> result = conjugateGradient(A, b);

    cout << "Решение системы: " << endl;
    for (double x : result) {
        cout << x << endl;
    }
    
    return 0;
}
