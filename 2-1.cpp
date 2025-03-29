#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Функция для обмена строк в матрице
void swapRows(vector<vector<double>>& A, vector<double>& b, int i, int j) {
    swap(A[i], A[j]);
    swap(b[i], b[j]);
}
//меняет местами строки матрицы A и вектора b

// Функция для метода Гаусса с выборкой ведущего элемента
vector<double> gaussElimination(vector<vector<double>> A, vector<double> b) {
    int n = A.size();
    for (int i = 0; i < n; i++) {
        //Для каждой строки i выбирается максимальный элемент в столбце i (от строки i до n). 
        //Если найденный элемент не на месте i, строки меняются местами.
        double maxElem = abs(A[i][i]);
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (abs(A[k][i]) > maxElem) {
                maxElem = abs(A[k][i]);
                maxRow = k;
            }
        }
        // Обмен строк
        //Для каждой строки ниже текущей i вычисляется коэффициент, который используется
        // для вычитания из текущей строки, чтобы обнулить элементы под ведущим элементом.
        if (maxRow != i) {
            swapRows(A, b, i, maxRow);
        }

        // Нормализация и исключение
        for (int k = i + 1; k < n; k++) {
            double coeff = A[k][i] / A[i][i];
            for (int j = i; j < n; j++) {
                A[k][j] -= coeff * A[i][j];
            }
            b[k] -= coeff * b[i];
        }
    }

    //происходит обратная подстановка для нахождения значений переменных.
    vector<double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
    return x;
}

int main() {
    // Исходные данные
    vector<vector<double>> A = {
        {5, 0, 1},
        {1, 3, -1},
        {-20, 2, 10}
    };
    vector<double> b = {11, 4, 6};

    // Решение системы
    vector<double> solution = gaussElimination(A, b);

    // Вывод результата
    cout << "Решение системы: " << endl;
    for (size_t i = 0; i < solution.size(); i++) {
        cout << "x" << i+1 << " = " << setprecision(10) << solution[i] << endl;
    }

    return 0;
}
