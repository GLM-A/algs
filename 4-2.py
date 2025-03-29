import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import CubicSpline
# Определяем массивы x и y
x = np.arange(1.00, 1.21, 0.04)  # Значения от 1.00 до 1.20 с шагом 0.01
y = np.exp(x)  # Вычисляем значения e^x
# Создаем кубический сплайн
cs = CubicSpline(x, y)
# Определяем точки, в которых нужно найти значения сплайна
query_points = [1.05, 1.09, 1.13, 1.15, 1.17]
spline_values = cs(query_points)

# Выводим результаты
for point, value in zip(query_points, spline_values):
    print(f"Spline value at {point}: {value:.5f}")
    # Визуализация оригинальных данных и сплайна
# Визуализация оригинальных данных и сплайна
x_dense = np.linspace(1.00, 1.20, 100)  # Более плотное разбиение для графика
y_dense = cs(x_dense)

plt.figure(figsize=(10, 6))
plt.plot(x_dense, y_dense, label='кубический сплайн', color='blue')
plt.scatter(x, y, color='red', label='e^x', zorder=5)
plt.scatter(query_points, spline_values, color='green', label='Интерполированные точки', zorder=5)
plt.title('Кубическая сплайн-интерполяция y = e^x')
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.grid()
plt.show()
