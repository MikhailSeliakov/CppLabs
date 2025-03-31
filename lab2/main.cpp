#include <iostream>
#include <iomanip>  // Для форматированного вывода
#include <cstdlib>  // Для функции rand()
#define N 5         // Размер квадратной матрицы

using namespace std;

// Объявления функций (прототипы)
// Минимум матрицы
float matrix_min(float m[N][N]);
// Максимум матрицы
float matrix_max(float m[N][N]);
// Максимум нижнетреугольной части (включая диагональ)
float lower_triangle_max(float m[N][N]);
// Максимум верхнетреугольной части (включая диагональ)
float upper_triangle_max(float m[N][N]);
// Минимум нижнетреугольной части (включая диагональ)
float lower_triangle_min(float m[N][N]);
// Минимум верхнетреугольной части (включая диагональ)
float upper_triangle_min(float m[N][N]);
// Минимум главной диагонали
float main_diagonal_min(float m[N][N]);
// Максимум главной диагонали
float main_diagonal_max(float m[N][N]);
// Минимум побочной диагонали
float secondary_diagonal_min(float m[N][N]);
// Максимум побочной диагонали
float secondary_diagonal_max(float m[N][N]);
// Среднее арифметическое всех элементов матрицы
float matrix_average(float m[N][N]);
// Среднее арифметическое нижнетреугольной части
float lower_triangle_average(float m[N][N]);
// Среднее арифметическое верхнетреугольной части
float upper_triangle_average(float m[N][N]);
// Суммы элементов каждой строки (результат в массиве sums)
void row_sums(float m[N][N], float sums[N]);
// Суммы элементов каждого столбца (результат в массиве sums)
void column_sums(float m[N][N], float sums[N]);
// Минимальные элементы каждой строки (результат в массиве minima)
void row_minima(float m[N][N], float minima[N]);
// Минимальные элементы каждого столбца (результат в массиве minima)
void column_minima(float m[N][N], float minima[N]);
void row_maxima(float m[N][N], float maxima[N]);
void column_maxima(float m[N][N], float maxima[N]);
void row_averages(float m[N][N], float averages[N]);
void column_averages(float m[N][N], float averages[N]);
void triangle_sums(float m[N][N], float& lower_sum, float& upper_sum);
float closest_to_average(float m[N][N]);


int main()
{
    float m[N][N];  // Объявление матрицы N x N
    int i, j;       // Индексы для циклов
    
    // Инициализация матрицы случайными значениями
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            m[i][j] = rand() / 10.;  // Генерация случайного числа и деление на 10 для получения дробной части
        }
    }
    
    // Вывод матрицы на экран
    cout << "Matrix:" << endl;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            // Форматированный вывод: ширина поля 8 символов, 5 знаков после запятой
            cout << setw(8) << setprecision(5) << m[i][j];
        }
        cout << endl;  // Переход на новую строку после вывода строки матрицы
    }
    cout << endl;  // Пустая строка после вывода матрицы
    
    // Вызов и вывод результатов всех функций
    cout << "Matrix min: " << matrix_min(m) << endl;
    cout << "Matrix max: " << matrix_max(m) << endl;
    cout << "Lower triangle max: " << lower_triangle_max(m) << endl;
    cout << "Upper triangle max: " << upper_triangle_max(m) << endl;
    cout << "Lower triangle min: " << lower_triangle_min(m) << endl;
    cout << "Upper triangle min: " << upper_triangle_min(m) << endl;
    cout << "Main diagonal min: " << main_diagonal_min(m) << endl;
    cout << "Main diagonal max: " << main_diagonal_max(m) << endl;
    cout << "Secondary diagonal min: " << secondary_diagonal_min(m) << endl;
    cout << "Secondary diagonal max: " << secondary_diagonal_max(m) << endl;
    cout << "Matrix average: " << matrix_average(m) << endl;
    cout << "Lower triangle average: " << lower_triangle_average(m) << endl;
    cout << "Upper triangle average: " << upper_triangle_average(m) << endl;
    
    float sums[N];  // Массив для хранения сумм строк или столбцов
    
    // Вычисление и вывод сумм строк
    row_sums(m, sums);
    cout << "Row sums: ";
    for (i = 0; i < N; i++) cout << sums[i] << " ";
    cout << endl;
    
    // Вычисление и вывод сумм столбцов
    column_sums(m, sums);
    cout << "Column sums: ";
    for (i = 0; i < N; i++) cout << sums[i] << " ";
    cout << endl;
    
    float minima[N];  // Массив для хранения минимальных значений строк или столбцов
    
    // Вычисление и вывод минимумов строк
    row_minima(m, minima);
    cout << "Row minima: ";
    for (i = 0; i < N; i++) cout << minima[i] << " ";
    cout << endl;
    
    // Вычисление и вывод минимумов столбцов
    column_minima(m, minima);
    cout << "Column minima: ";
    for (i = 0; i < N; i++) cout << minima[i] << " ";
    cout << endl;
    float maxima[N];  // Массив для хранения максимальных значений
    
    // Вычисление и вывод максимумов строк
    row_maxima(m, maxima);
    cout << "Row maxima: ";
    for (i = 0; i < N; i++) cout << maxima[i] << " ";
    cout << endl;
    
    // Вычисление и вывод максимумов столбцов
    column_maxima(m, maxima);
    cout << "Column maxima: ";
    for (i = 0; i < N; i++) cout << maxima[i] << " ";
    cout << endl;
    
    float averages[N];  // Массив для хранения средних значений
    
    // Вычисление и вывод средних значений строк
    row_averages(m, averages);
    cout << "Row averages: ";
    for (i = 0; i < N; i++) cout << averages[i] << " ";
    cout << endl;
    
    // Вычисление и вывод средних значений столбцов
    column_averages(m, averages);
    cout << "Column averages: ";
    for (i = 0; i < N; i++) cout << averages[i] << " ";
    cout << endl;
    
    float lower_sum, upper_sum;
    // Вычисление и вывод сумм треугольных частей
    triangle_sums(m, lower_sum, upper_sum);
    cout << "Lower triangle sum: " << lower_sum << endl;
    cout << "Upper triangle sum: " << upper_sum << endl;
    
    // Вычисление и вывод элемента, ближайшего к среднему
    cout << "Element closest to average: " << closest_to_average(m) << endl;
    
    return 0;  // Завершение программы
}

// Функция поиска минимального значения в матрице
float matrix_min(float m[N][N]) {
    float min_val = m[0][0];  // Начальное значение - первый элемент
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (m[i][j] < min_val) min_val = m[i][j];  // Если найден меньший элемент, обновляем min_val
        }
    }
    return min_val;
}

// Функция поиска максимального значения в матрице
float matrix_max(float m[N][N]) {
    float max_val = m[0][0];  // Начальное значение - первый элемент
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (m[i][j] > max_val) max_val = m[i][j];  // Если найден больший элемент, обновляем max_val
        }
    }
    return max_val;
}

// Функция поиска максимума в нижнетреугольной части матрицы (включая диагональ)
float lower_triangle_max(float m[N][N]) {
    float max_val = m[0][0];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {  // Для нижнего треугольника j <= i
            if (m[i][j] > max_val) max_val = m[i][j];
        }
    }
    return max_val;
}

// Функция поиска максимума в верхнетреугольной части матрицы (включая диагональ)
float upper_triangle_max(float m[N][N]) {
    float max_val = m[0][0];
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {  // Для верхнего треугольника j >= i
            if (m[i][j] > max_val) max_val = m[i][j];
        }
    }
    return max_val;
}

// Функция поиска минимума в нижнетреугольной части матрицы (включая диагональ)
float lower_triangle_min(float m[N][N]) {
    float min_val = m[0][0];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {  // Для нижнего треугольника j <= i
            if (m[i][j] < min_val) min_val = m[i][j];
        }
    }
    return min_val;
}

// Функция поиска минимума в верхнетреугольной части матрицы (включая диагональ)
float upper_triangle_min(float m[N][N]) {
    float min_val = m[0][0];
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {  // Для верхнего треугольника j >= i
            if (m[i][j] < min_val) min_val = m[i][j];
        }
    }
    return min_val;
}

// Функция поиска минимума на главной диагонали
float main_diagonal_min(float m[N][N]) {
    float min_val = m[0][0];
    for (int i = 1; i < N; i++) {
        if (m[i][i] < min_val) min_val = m[i][i];  // Главная диагональ - элементы с i == j
    }
    return min_val;
}

// Функция поиска максимума на главной диагонали
float main_diagonal_max(float m[N][N]) {
    float max_val = m[0][0];
    for (int i = 1; i < N; i++) {
        if (m[i][i] > max_val) max_val = m[i][i];  // Главная диагональ - элементы с i == j
    }
    return max_val;
}

// Функция поиска минимума на побочной диагонали
float secondary_diagonal_min(float m[N][N]) {
    float min_val = m[0][N-1];  // Первый элемент побочной диагонали (0, N-1)
    for (int i = 1; i < N; i++) {
        if (m[i][N-1-i] < min_val) min_val = m[i][N-1-i];  // Побочная диагональ - элементы с j = N-1-i
    }
    return min_val;
}

// Функция поиска максимума на побочной диагонали
float secondary_diagonal_max(float m[N][N]) {
    float max_val = m[0][N-1];
    for (int i = 1; i < N; i++) {
        if (m[i][N-1-i] > max_val) max_val = m[i][N-1-i];
    }
    return max_val;
}

// Функция вычисления среднего арифметического всех элементов матрицы
float matrix_average(float m[N][N]) {
    float sum = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sum += m[i][j];  // Суммируем все элементы
        }
    }
    return sum / (N * N);  // Делим сумму на количество элементов
}

// Функция вычисления среднего арифметического нижнетреугольной части
float lower_triangle_average(float m[N][N]) {
    float sum = 0;
    int count = 0;  // Счетчик элементов
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            sum += m[i][j];
            count++;
        }
    }
    return sum / count;  // Делим сумму на количество элементов
}

// Функция вычисления среднего арифметического верхнетреугольной части
float upper_triangle_average(float m[N][N]) {
    float sum = 0;
    int count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            sum += m[i][j];
            count++;
        }
    }
    return sum / count;
}

// Функция вычисления сумм элементов каждой строки
void row_sums(float m[N][N], float sums[N]) {
    for (int i = 0; i < N; i++) {
        sums[i] = 0;  // Инициализация суммы для текущей строки
        for (int j = 0; j < N; j++) {
            sums[i] += m[i][j];  // Суммируем элементы строки
        }
    }
}

// Функция вычисления сумм элементов каждого столбца
void column_sums(float m[N][N], float sums[N]) {
    for (int j = 0; j < N; j++) {
        sums[j] = 0;  // Инициализация суммы для текущего столбца
        for (int i = 0; i < N; i++) {
            sums[j] += m[i][j];  // Суммируем элементы столбца
        }
    }
}

// Функция поиска минимальных элементов в каждой строке
void row_minima(float m[N][N], float minima[N]) {
    for (int i = 0; i < N; i++) {
        minima[i] = m[i][0];  // Начальное значение - первый элемент строки
        for (int j = 1; j < N; j++) {
            if (m[i][j] < minima[i]) minima[i] = m[i][j];  // Поиск минимума в строке
        }
    }
}

// Функция поиска минимальных элементов в каждом столбце
void column_minima(float m[N][N], float minima[N]) {
    for (int j = 0; j < N; j++) {
        minima[j] = m[0][j];  // Начальное значение - первый элемент столбца
        for (int i = 1; i < N; i++) {
            if (m[i][j] < minima[j]) minima[j] = m[i][j];  // Поиск минимума в столбце
        }
    }
}

// Функция поиска максимальных значений в каждой строке
void row_maxima(float m[N][N], float maxima[N]) {
    for (int i = 0; i < N; i++) {
        maxima[i] = m[i][0];  // Начальное значение - первый элемент строки
        for (int j = 1; j < N; j++) {
            if (m[i][j] > maxima[i]) maxima[i] = m[i][j];  // Поиск максимума в строке
        }
    }
}

// Функция поиска максимальных значений в каждом столбце
void column_maxima(float m[N][N], float maxima[N]) {
    for (int j = 0; j < N; j++) {
        maxima[j] = m[0][j];  // Начальное значение - первый элемент столбца
        for (int i = 1; i < N; i++) {
            if (m[i][j] > maxima[j]) maxima[j] = m[i][j];  // Поиск максимума в столбце
        }
    }
}

// Функция вычисления средних арифметических значений для каждой строки
void row_averages(float m[N][N], float averages[N]) {
    for (int i = 0; i < N; i++) {
        float sum = 0;
        for (int j = 0; j < N; j++) {
            sum += m[i][j];  // Суммируем элементы строки
        }
        averages[i] = sum / N;  // Делим на количество элементов в строке
    }
}

// Функция вычисления средних арифметических значений для каждого столбца
void column_averages(float m[N][N], float averages[N]) {
    for (int j = 0; j < N; j++) {
        float sum = 0;
        for (int i = 0; i < N; i++) {
            sum += m[i][j];  // Суммируем элементы столбца
        }
        averages[j] = sum / N;  // Делим на количество элементов в столбце
    }
}

// Функция вычисления сумм нижней и верхней треугольных частей
void triangle_sums(float m[N][N], float& lower_sum, float& upper_sum) {
    lower_sum = 0;
    upper_sum = 0;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            lower_sum += m[i][j];  // Суммируем нижний треугольник (j <= i)
        }
        for (int j = i; j < N; j++) {
            upper_sum += m[i][j];  // Суммируем верхний треугольник (j >= i)
        }
    }
}

// Функция поиска элемента, наиболее близкого к среднеарифметическому всей матрицы
float closest_to_average(float m[N][N]) {
    float avg = matrix_average(m);  // Получаем среднее значение матрицы
    float closest = m[0][0];        // Начальное значение - первый элемент
    float min_diff = abs(m[0][0] - avg);  // Начальная разница
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            float current_diff = abs(m[i][j] - avg);  // Разница текущего элемента
            if (current_diff < min_diff) {
                min_diff = current_diff;
                closest = m[i][j];  // Обновляем ближайший элемент
            }
        }
    }
    return closest;
}