import matplotlib.pyplot as plt

def lagrange_polynomial(x_vals, y_vals, x):
    # Вычисляет значение многочлена Лагранжа в точке x
    n = len(x_vals)
    total = 0.0
    for i in range(n):
        L_i = 1.0
        for j in range(n):
            if j != i:
                L_i *= (x - x_vals[j]) / (x_vals[i] - x_vals[j])
        total += y_vals[i] * L_i
    return total

def main():
    # Исходные данные
    x_points = [1, 2, 3, 4, 5]
    y_points = [1.1, 1.2, 1.6, 1.2, 1.4]

    # Текстовый вывод значений в ряде точек
    test_values = [1, 2, 3, 4, 5, 2.5, 3.7]
    print("Значения интерполяционного полинома Лагранжа:")
    for x_val in test_values:
        result = lagrange_polynomial(x_points, y_points, x_val)
        print(f"P({x_val}) = {result}")

    # Построение графика: полином и исходные точки
    x_plot = [i/10 for i in range(10, 51)]  # x от 1.0 до 5.0 с шагом 0.1
    y_plot = [lagrange_polynomial(x_points, y_points, x) for x in x_plot]

    plt.plot(x_plot, y_plot, label='Полином Лагранжа')
    plt.scatter(x_points, y_points, color='red', label='Исходные точки')
    plt.xlabel('x')
    plt.ylabel('P(x)')
    plt.title('Интерполяционный многочлен Лагранжа')
    plt.legend()
    plt.grid(True)
    plt.show()

if __name__ == '__main__':
    main()
