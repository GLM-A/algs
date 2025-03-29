import numpy as np
import matplotlib.pyplot as plt

# Функции для генерации сигналов
def generate_signal(signal_type, t):
    if signal_type == "синус":
        return np.sin(2 * np.pi * 5 * t)  # Синусоида с частотой 5 Гц
    elif signal_type == "косинус":
        return np.cos(2 * np.pi * 5 * t)  # Косинусоида с частотой 5 Гц
    elif signal_type == "сумма":
        return np.sin(2 * np.pi * 5 * t) + np.cos(2 * np.pi * 10 * t)  # Сумма синуса и косинуса
    elif signal_type == "шум":
        return np.random.normal(0, 1, len(t))  # Белый шум
    else:
        return np.zeros(len(t))

# Функция для выполнения БПФ и построения графиков
def plot_fft(signal_type):
    # Параметры сигнала
    fs = 100  # Частота дискретизации
    t = np.arange(0, 1, 1/fs)  # Временной вектор
    signal = generate_signal(signal_type, t)  # Генерация сигнала

    # Выполнение БПФ
    fft_result = np.fft.fft(signal)
    fft_freq = np.fft.fftfreq(len(signal), 1/fs)

    # Построение графиков
    plt.figure(figsize=(12, 6))

    # График сигнала
    plt.subplot(2, 1, 1)
    plt.plot(t, signal)
    plt.title(f'Сигнал: {signal_type.capitalize()}')
    plt.xlabel('Время (с)')
    plt.ylabel('Амплитуда')

    # График БПФ
    plt.subplot(2, 1, 2)
    plt.plot(fft_freq[:len(fft_freq)//2], np.abs(fft_result)[:len(fft_result)//2])
    plt.title('Быстрое преобразование Фурье')
    plt.xlabel('Частота (Гц)')
    plt.ylabel('Амплитуда')

    plt.tight_layout()
    plt.show()

# Основной цикл программы
if __name__ == "__main__":
    print("Выберите тип сигнала:")
    print("1. Синус")
    print("2. Косинус")
    print("3. Сумма")
    print("4. Шум")

    choice = input("Введите номер сигнала (1-4): ")

    signal_types = {
        "1": "синус",
        "2": "косинус",
        "3": "сумма",
        "4": "шум"
    }

    if choice in signal_types:
        plot_fft(signal_types[choice])
    else:
        print("Неверный выбор. Пожалуйста, выберите номер от 1 до 4.")
