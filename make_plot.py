import matplotlib.pyplot as plt

# Загрузка данных
processes = []
times = []

with open('results.txt', 'r') as file:
    for line in file:
        if line.strip():  # Пропустить пустые строки
            # Проверка, содержит ли строка информацию о времени
            if "Time" in line:
                # Извлечение времени выполнения из строки
                parts = line.split()
                # Ищем общее время (предпоследний элемент строки, если он является числом)
                for part in parts:
                    try:
                        if part == parts[-1]:  # Убедимся, что это последнее значение
                            processes.append(len(times) + 1)
                            total_time = part
                            times.append(float(total_time))
                    except ValueError:
                        continue  # Игнорировать, если не можем преобразовать

# Расчет ускорения
if len(times) > 0:  # Проверка на случай, если times пуст
    speedup = [times[0] / t for t in times]

    # Построение графика
    plt.plot(processes, speedup, marker='o')
    plt.xlabel('Number of Processes')
    plt.ylabel('Speedup')
    plt.title('Speedup of Parallel Integration')
    plt.grid()
    plt.show()
else:
    print("No valid time data found.")
