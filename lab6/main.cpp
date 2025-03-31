#include <iostream>
#include <cstring>

using namespace std;

class Stroka {
    char* str;  // Указатель на строку (теперь используем динамическую память)
    int size;   // Размер выделенной памяти

    // Вспомогательная функция для копирования строки
    void copyString(const char* source) {
        int length = myStrlen(source);
        if (length + 1 > size) {
            // Если не хватает места, перевыделяем память
            delete[] str;
            size = length + 1;
            str = new char[size];
        }
        myStrcpy(str, source);
    }

    // Собственная реализация strlen
    int myStrlen(const char* s) const {
        int len = 0;
        while (s[len] != '\0') len++;
        return len;
    }

    // Собственная реализация strcpy
    void myStrcpy(char* dest, const char* src) {
        int i = 0;
        while ((dest[i] = src[i]) != '\0') i++;
    }

    // Собственная реализация strcmp
    int myStrcmp(const char* s1, const char* s2) const {
        while (*s1 && (*s1 == *s2)) {
            s1++;
            s2++;
        }
        return *(const unsigned char*)s1 - *(const unsigned char*)s2;
    }

    // Собственная реализация strcat
    void myStrcat(char* dest, const char* src) {
        int dest_len = myStrlen(dest);
        int src_len = myStrlen(src);
        
        if (dest_len + src_len + 1 > size) {
            // Если не хватает места, перевыделяем память
            char* new_str = new char[dest_len + src_len + 1];
            myStrcpy(new_str, dest);
            delete[] str;
            str = new_str;
            size = dest_len + src_len + 1;
        }
        
        int i = 0;
        while (src[i] != '\0') {
            dest[dest_len + i] = src[i];
            i++;
        }
        dest[dest_len + i] = '\0';
    }

public:
    // Конструктор по умолчанию (создает пустую строку с размером 80)
    Stroka() : size(80) {
        str = new char[size];
        str[0] = '\0';
    }

    // Конструктор из C-строки
    Stroka(const char* string) : size(myStrlen(string) + 1) {
        str = new char[size];
        myStrcpy(str, string);
    }

    // Конструктор с заданным размером буфера
    Stroka(int bufferSize) : size(bufferSize) {
        str = new char[size];
        str[0] = '\0';
    }

    // Конструктор копирования
    Stroka(const Stroka& s) : size(s.size) {
        str = new char[size];
        myStrcpy(str, s.str);
    }

    // Деструктор (теперь необходим, так как используем динамическую память)
    ~Stroka() {
        delete[] str;
    }

    // Оператор присваивания
    Stroka& operator=(const Stroka& s) {
        if (this != &s) {
            copyString(s.str);
        }
        return *this;
    }

    // Оператор сложения (конкатенации)
    Stroka operator+(const Stroka& s) {
        Stroka result(*this);  // Создаем копию текущей строки
        result.myStrcat(result.str, s.str);
        return result;
    }

    // Оператор сравнения
    bool operator==(const Stroka& s) const {
        return myStrcmp(str, s.str) == 0;
    }

    // Метод для определения длины строки
    int dlina() const {
        return myStrlen(str);
    }

    // Метод ввода строки
    void vvod() {
        cin.getline(str, size);
    }

    // Метод вывода строки
    void vyvod() const {
        cout << str;
    }
};

int main() {
    // Тестирование конструкторов
    Stroka s1("qwerty");  // Конструктор из C-строки
    Stroka s2(100);       // Конструктор с заданным размером буфера
    Stroka s3;            // Конструктор по умолчанию (размер 80)
    Stroka s4(s1);        // Конструктор копирования

    // Тестирование ввода/вывода
    cout << "Введите строку для s2: ";
    s2.vvod();
    cout << "s2: ";
    s2.vyvod();
    cout << endl;

    // Тестирование оператора присваивания
    s3 = "Привет";
    cout << "s3 после присваивания: ";
    s3.vyvod();
    cout << endl;

    // Тестирование оператора сложения
    Stroka s5 = s1 + s3;
    cout << "s5 (s1 + s3): ";
    s5.vyvod();
    cout << endl;

    // Тестирование длины строки
    cout << "Длина s5: " << s5.dlina() << endl;

    // Тестирование оператора сравнения
    if (s1 == s4) {
        cout << "s1 и s4 равны" << endl;
    } else {
        cout << "s1 и s4 различны" << endl;
    }

    if (s1 == s5) {
        cout << "s1 и s5 равны" << endl;
    } else {
        cout << "s1 и s5 различны" << endl;
    }

    return 0;
}