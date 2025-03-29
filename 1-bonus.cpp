#include <iostream>
#include <cmath>

using namespace std;

double F(double x) {
    return 1/(0.01 + fabs(x));
}

double simpson(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = F(a) + F(b);

    for (int i = 1; i < n; i++) {
        double k = a + i * h;
        sum += (i % 2 == 0 ? 2 * F(k) : 4 * F(k));
    }

    return sum * h / 3;
}

// Адаптивное интегрирование
double adaptiveSimpson(double a, double b, double epsilon, double whole) {
    int n = 2; // Начинаем с 2 подынтервалов
//делит интервал [a, b] на две части и применяет метод Симпсона к каждой из них.
    double left = simpson(a, (a + b) / 2, n);
    double right = simpson((a + b) / 2, b, n);
    double total = left + right;

    if (fabs(total - whole) < 15 * epsilon) {
        return total + (total - whole) / 15;
    }

    return adaptiveSimpson(a, (a + b) / 2, epsilon / 2, left) +
           adaptiveSimpson((a + b) / 2, b, epsilon / 2, right);
}
//Если разница между текущим и предыдущим значением интеграла меньше, чем ( 15 * epsilon ), то возвращается текущее значение с корректировкой.
//Если нет, функция рекурсивно вызывает себя для каждой половины интервала.

int main() {
    double a = -0.49;       
    double b = 1;      
    double epsilon = 1e-4;

    // Первичное интегрирование для получения начального значения
    double initial = simpson(a, b, 2);
    
    // Адаптивное интегрирование
    double result = adaptiveSimpson(a, b, epsilon, initial);

    cout.precision(10); // Установка точности вывода
    cout << "Результат интегрирования: " << result << endl;

    return 0;
}
