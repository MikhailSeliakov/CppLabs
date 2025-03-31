#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cctype>

using namespace std;

// Класс Stroka из лабораторной работы 6
class Stroka {
private:
    string str;
public:
    Stroka() : str("") {}
    Stroka(const string& s) : str(s) {}
    
    // Перегрузка оператора ввода
    friend istream& operator>>(istream& is, Stroka& s) {
        getline(is, s.str);
        return is;
    }
    
    // Перегрузка оператора вывода
    friend ostream& operator<<(ostream& os, const Stroka& s) {
        os << s.str;
        return os;
    }
    
    // Дополнительные методы для работы со строкой
    int length() const { return str.length(); }
    void toUpper() {
        for (char &c : str) {
            c = toupper(c);
        }
    }
    void toLower() {
        for (char &c : str) {
            c = tolower(c);
        }
    }
};

// Функция-цифратор с использованием классов потоков
void digitizer(const string& inputFile, const string& outputFile) {
    ifstream in(inputFile);
    ofstream out(outputFile);
    
    if (!in.is_open()) {
        cerr << "Ошибка открытия входного файла!" << endl;
        return;
    }
    
    if (!out.is_open()) {
        cerr << "Ошибка открытия выходного файла!" << endl;
        return;
    }
    
    char ch;
    int digitCount = 0;
    
    while (in.get(ch)) {
        if (isdigit(ch)) {
            out << ch;
            digitCount++;
        }
    }
    
    in.close();
    out.close();
    
    cout << "Найдено и записано " << digitCount << " цифр." << endl;
}

// Демонстрация методов управления состоянием потоков
void streamStateDemo() {
    // Примеры из методических указаний (стр. 22-24)
    
    // 1. Установка флагов формата
    cout << "\nДемонстрация флагов формата:" << endl;
    int num = 255;
    cout << "Десятичное: " << num << endl;
    cout << "Шестнадцатеричное: " << hex << num << endl;
    cout << "Восьмеричное: " << oct << num << endl;
    
    // Возврат к десятичной системе
    cout << dec;
    
    // 2. Управление точностью для чисел с плавающей точкой
    double pi = 3.141592653589793;
    cout << "\nДемонстрация точности (по умолчанию 6): " << pi << endl;
    cout << "Точность 9: " << setprecision(9) << pi << endl;
    
    // 3. Заполнение и выравнивание
    cout << "\nДемонстрация заполнения:" << endl;
    cout << setw(20) << left << "Выравнивание слева" << "|" << endl;
    cout << setw(20) << right << "Выравнивание справа" << "|" << endl;
    cout << setfill('*') << setw(20) << "Заполнение" << "|" << endl;
    
    // Возврат к стандартному заполнению пробелами
    cout << setfill(' ');
    
    // 4. Работа с флагами состояния потока
    cout << "\nДемонстрация состояния потока:" << endl;
    ifstream testFile("nonexistent_file.txt");
    if (testFile.fail()) {
        cerr << "Ошибка открытия файла!" << endl;
        cout << "Состояние потока: failbit установлен" << endl;
    }
    
    // Очистка состояния потока
    testFile.clear();
}

int main() {
    // Демонстрация работы с классом Stroka
    cout << "Демонстрация класса Stroka:" << endl;
    Stroka s;
    cout << "Введите строку: ";
    cin >> s;
    cout << "Вы ввели: " << s << endl;
    
    // Демонстрация цифратора
    cout << "\nДемонстрация цифратора:" << endl;
    digitizer("input.txt", "output.txt");
    
    // Демонстрация методов управления состоянием потоков
    streamStateDemo();
    
    return 0;
}