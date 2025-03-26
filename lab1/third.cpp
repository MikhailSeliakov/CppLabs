#include <iostream>

// Объявления функций обмена
void obmen1(int, int);       // Обмен по значению (не будет работать)
void obmen2(int*, int*);     // Обмен по указателям
void obmen3(int&, int&);     // Обмен по ссылкам

int main()
{
    int a = 2, b = 5;  // Исходные значения переменных

    // Вывод значений до обмена
    std::cout << "до обмена: a = " << a << ", b = " << b << std::endl;
    
    // Попытка обмена через передачу по значению (не сработает)
    obmen1(a, b);
    std::cout << "после обмена 1: a = " << a << ", b = " << b << std::endl;
    
    // Обмен через указатели (работает)
    obmen2(&a, &b);  // Передаем адреса переменных
    std::cout << "после обмена 2: a = " << a << ", b = " << b << std::endl;
    
    // Обмен через ссылки (работает)
    obmen3(a, b);    // Передаем сами переменные
    std::cout << "после обмена 3: a = " << a << ", b = " << b << std::endl;

    return 0;
}

// Реализация функций обмена:

// 1. Обмен по значению - НЕ РАБОТАЕТ (передаются копии значений)
void obmen1(int x, int y)
{
    int temp = x;
    x = y;
    y = temp;
    // Изменения остаются локальными в этой функции
}

// 2. Обмен через указатели - работает
void obmen2(int* x, int* y)
{
    int temp = *x;  // Получаем значение по адресу x
    *x = *y;       // Записываем значение y по адресу x
    *y = temp;     // Записываем сохраненное значение по адресу y
}

// 3. Обмен через ссылки - работает (только в C++)
void obmen3(int& x, int& y)
{
    int temp = x;
    x = y;
    y = temp;
    // Работаем напрямую с оригинальными переменными
}