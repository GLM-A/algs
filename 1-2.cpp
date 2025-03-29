#include <iostream>
#include <cmath>
#include <random>
#include <functional>
using namespace std;

// Функция для вычисления интеграла методом Монте-Карло
double monteCarloIntegration(const function<double(double)>& f, double a, double b, int numSamples) {
    // Инициализация генератора случайных чисел
    mt19937 rng;
    rng.seed(random_device()());
    uniform_real_distribution<double> distribution(a, b);

    double sum = 0.0;
    for (int i = 0; i < numSamples; i++) {
        double x = distribution(rng); // случайная точка в [a, b]
        sum += f(x);
    }
    // Приближённое значение интеграла:
    double integral = (b - a) * sum / numSamples;
    return integral;
}

int main() {
    // Определяем функцию f(x) = cos3x /(1+ 0,7cos x)
    auto f = [](double x) -> double {
        return pow(cos(x), 3) * cos(3 * x);
    };
    const int k=10;
    double sum[k];
    double integral;
    for (int i=0;i<k;i++){
        double a = 0.0;
        double b = 5;
        int numSamples = 150000; // Количество случайных точек, можно увеличить для повышения точности
        double integral = monteCarloIntegration(f, a, b, numSamples);
        cout << "pribl znach po Monte-Carlo " << integral << endl;
        sum[i]+=integral;
    }
    double s,s2,q;
    s=(sum[0]+sum[1]+sum[2])/3;
    s2=(pow(sum[0],2)+pow(sum[1],2)+pow(sum[2],2))/k;
    q=sqrt(abs(s2-pow(s,2)));
    cout<<"q "<<q<<endl;
    cout<<"otvet "<<s<<endl;

    
    return 0;
}
