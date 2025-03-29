import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Button
from scipy.integrate import quad

# Определяем функции, которые будем разлагать в ряд Фурье
def f_sin(x):
    return np.sin(x)

def f_cos(x):
    return np.cos(x)

def f_square_wave(x):
    return 1 if (0 <= x % (2 * np.pi) < np.pi) else -1

def f_triangle_wave(x):
    return (2 / np.pi) * (x % (2 * np.pi)) - 1 if (0 <= x % (2 * np.pi) < np.pi) else (2 / np.pi) * (
                2 * np.pi - (x % (2 * np.pi))) - 1

def f_complex(x):
    return np.sin(2 * x) + np.cos(3 * x)

# Новые сложные функции
def f_exp(x):
    return np.exp(x) * np.sin(x)

def f_log(x):
    return np.log(np.abs(x)) if x != 0 else 0

def f_gaussian(x):
    return np.exp(-x**2)

def f_sawtooth(x):
    return (x % (2 * np.pi)) / (2 * np.pi) * 2 - 1

def f_combined(x):
    return np.sin(x) + 0.5 * np.cos(2 * x) + 0.3 * np.sin(3 * x)

# Параметры ряда Фурье
L = np.pi  # Период функции
N = 10  # Количество гармоник

# Вычисление коэффициентов a0, an, bn
def a0(func):
    return (1 / (2 * L)) * quad(func, -L, L)[0]

def an(func, n):
    return (1 / L) * quad(lambda x: func(x) * np.cos(n * np.pi * x / L), -L, L)[0]

def bn(func, n):
    return (1 / L) * quad(lambda x: func(x) * np.sin(n * np.pi * x / L), -L, L)[0]

# Формирование ряда Фурье
def fourier_series(func, x, N):
    result = a0(func)
    for n in range(1, N + 1):
        result += an(func, n) * np.cos(n * np.pi * x / L) + bn(func, n) * np.sin(n * np.pi * x / L)
    return result

# Генерация значений для графика
x_values = np.linspace(-L, L, 1000)

# Функция для обновления графика
def update_plot(func):
    f_values = np.vectorize(func)(x_values)  # Применяем функцию к массиву
    fourier_values = fourier_series(func, x_values, N)

    ax.clear()
    ax.plot(x_values, f_values, label='Исходная функция', color='blue')
    ax.plot(x_values, fourier_values, label='Ряд Фурье', color='red', linestyle='--')
    ax.set_title('Разложение функции в ряд Фурье')
    ax.set_xlabel('x')
    ax.set_ylabel('f(x)')
    ax.axhline(0, color='black', lw=0.5, ls='--')
    ax.axvline(0, color='black', lw=0.5, ls='--')
    ax.legend()
    ax.grid()
    plt.draw()

# Создание графика
fig, ax = plt.subplots(figsize=(10, 6))
plt.subplots_adjust(bottom=0.2)

# Кнопки для выбора функции
ax_sin = plt.axes([0.1, 0.05, 0.1, 0.075])
btn_sin = Button(ax_sin, 'sin(x)')

ax_cos = plt.axes([0.22, 0.05, 0.1, 0.075])
btn_cos = Button(ax_cos, 'cos(x)')

ax_square = plt.axes([0.34, 0.05, 0.1, 0.075])
btn_square = Button(ax_square, 'Square Wave')

ax_triangle = plt.axes([0.46, 0.05, 0.1, 0.075])
btn_triangle = Button(ax_triangle, 'Triangle Wave')

ax_complex = plt.axes([0.58, 0.05, 0.1, 0.075])
btn_complex = Button(ax_complex , 'Complex Function')

ax_exp = plt.axes([0.7, 0.05, 0.1, 0.075])
btn_exp = Button(ax_exp, 'exp(x) * sin(x)')

ax_log = plt.axes([0.82, 0.05, 0.1, 0.075])
btn_log = Button(ax_log, 'log(|x|)')

ax_gaussian = plt.axes([0.94, 0.05, 0.1, 0.075])
btn_gaussian = Button(ax_gaussian, 'Gaussian')

ax_sawtooth = plt.axes([1.06, 0.05, 0.1, 0.075])
btn_sawtooth = Button(ax_sawtooth, 'Sawtooth')

ax_combined = plt.axes([1.18, 0.05, 0.1, 0.075])
btn_combined = Button(ax_combined, 'Combined')

# Привязка кнопок к функциям
btn_sin.on_clicked(lambda event: update_plot(f_sin))
btn_cos.on_clicked(lambda event: update_plot(f_cos))
btn_square.on_clicked(lambda event: update_plot(f_square_wave))
btn_triangle.on_clicked(lambda event: update_plot(f_triangle_wave))
btn_complex.on_clicked(lambda event: update_plot(f_complex))
btn_exp.on_clicked(lambda event: update_plot(f_exp))
btn_log.on_clicked(lambda event: update_plot(f_log))
btn_gaussian.on_clicked(lambda event: update_plot(f_gaussian))
btn_sawtooth.on_clicked(lambda event: update_plot(f_sawtooth))
btn_combined.on_clicked(lambda event: update_plot(f_combined))

# Изначальный график
update_plot(f_sin)

plt.show()
