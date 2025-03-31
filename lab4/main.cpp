#include <iostream>
#include <cstring>
using namespace std;

int main() {
    char str1[] = "Hello";
    char str2[] = "World";
    char str3[20];

    // Использование strlen()
    cout << "Длина str1: " << strlen(str1) << endl;

    // Использование strcpy()
    strcpy(str3, str1);
    cout << "После копирования str3: " << str3 << endl;

    // Использование strcat()
    strcat(str3, " ");
    strcat(str3, str2);
    cout << "После конкатенации str3: " << str3 << endl;

    // Использование strcmp()
    int result = strcmp(str1, str2);
    if (result < 0)
        cout << str1 << " меньше " << str2 << endl;
    else if (result > 0)
        cout << str1 << " больше " << str2 << endl;
    else
        cout << "Строки равны" << endl;

    return 0;
}

// Способ 1: с использованием индексации массива
int clina1(char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Способ 2: с использованием указателей
int clina2(char* str) {
    char* ptr = str;
    while (*ptr != '\0') {
        ptr++;
    }
    return ptr - str;
}

// Способ 3: рекурсивный способ
int clina3(char* str) {
    if (*str == '\0') {
        return 0;
    }
    return 1 + clina3(str + 1);
}

void kopir(char* dest, char* src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

void srawn(char* str1, char* str2) {
    while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2) {
        str1++;
        str2++;
    }
    if (*str1 == *str2) {
        cout << "Строки равны" << endl;
    } else if (*str1 < *str2) {
        cout << "Первая строка меньше" << endl;
    } else {
        cout << "Первая строка больше" << endl;
    }
}


void konkat(char* dest, char* src) {
    // Находим конец первой строки
    while (*dest != '\0') {
        dest++;
    }
    // Копируем вторую строку в конец первой
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

int withMalloc() {
    char *str1, *str2;
    str1 = (char*)malloc(100 * sizeof(char));
    str2 = (char*)malloc(100 * sizeof(char));

    strcpy(str1, "Dynamic");
    strcpy(str2, "Memory");

    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl;

    konkat(str1, str2);
    cout << "После конкатенации: " << str1 << endl;

    free(str1);
    free(str2);

    return 0;
}

int withCalloc() {
    char *str1, *str2;
    str1 = (char*)calloc(100, sizeof(char));
    str2 = (char*)calloc(100, sizeof(char));

    strcpy(str1, "Calloc");
    strcpy(str2, "Example");

    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl;

    free(str1);
    free(str2);

    return 0;
}


int arrayOfStrings() {
    const int N = 3;
    char** strings = (char**)malloc(N * sizeof(char*));
    
    for (int i = 0; i < N; i++) {
        strings[i] = (char*)malloc(100 * sizeof(char));
        cout << "Введите строку " << i+1 << ": ";
        cin.getline(strings[i], 100);
    }

    // Применяем наши функции к массиву строк
    for (int i = 0; i < N; i++) {
        cout << "Длина строки " << i+1 << ": " << clina1(strings[i]) << endl;
    }

    kopir(strings[0], strings[1]);
    cout << "После копирования: " << strings[0] << endl;

    // Освобождаем память
    for (int i = 0; i < N; i++) {
        free(strings[i]);
    }
    free(strings);

    return 0;
}