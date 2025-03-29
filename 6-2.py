import numpy as np
import matplotlib.pyplot as plt


# Определяем функцию и её производную
def f(x):
    return (x - 3) ** 2 + 4


def df(x):
    return 2 * (x - 3)


# Метод градиентного спуска
def gradient_descent(starting_point, learning_rate, num_iterations):
    x = starting_point
    history = [x]

    for _ in range(num_iterations):
        x = x - learning_rate * df(x)
        history.append(x)

    return x, history


# Параметры метода
starting_point = 0.0  # Начальная точка
learning_rate = 0.1  # Скорость обучения
num_iterations = 50  # Количество итераций

# Запуск градиентного спуска
minimum, history = gradient_descent(starting_point, learning_rate, num_iterations)

# Вывод результатов
print(f"Найденный минимум: x = {minimum}, f(x) = {f(minimum)}")

# Визуализация
x_values = np.linspace(-1, 7, 100)
y_values = f(x_values)

plt.plot(x_values, y_values, label='f(x)')
plt.scatter(history, f(np.array(history)), color='red', label='Итерации')
plt.title('Градиентный спуск')
plt.xlabel('x')
plt.ylabel('f(x)')
plt.legend()
plt.grid()
plt.show()
