#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Базовый класс Point (Точка)
class Point {
protected:
    int x, y;          // Координаты точки
    int color;         // Цвет точки
public:
    // Инициализация точки
    void init(int xn, int yn, int c) {
        x = xn;
        y = yn;
        color = c;
    }
    
    // Виртуальные методы (будут переопределены в производных классах)
    virtual void show() {}
    virtual void hide() {}
    
    // Получение текущих координат
    void locate(int &xl, int &yl) {
        xl = x;
        yl = y;
    }
    
    // Метод для перемещения объекта
    void fly(int cost) {
        int xx, yy;
        show(); // Показать объект
        
        // Инициализация генератора случайных чисел
        srand(time(NULL));
        
        while (!kbhit()) { // Пока не нажата клавиша
            locate(xx, yy); // Получить текущие координаты
            
            // Случайное перемещение по X
            do {
                xx += (int)((rand()/(float)RAND_MAX - 0.5) * cost);
            } while (xx <= 0 || xx >= getmaxx());
            
            // Случайное перемещение по Y
            do {
                yy += (int)((rand()/(float)RAND_MAX - 0.5) * cost);
            } while (yy <= 0 || yy >= getmaxy());
            
            hide(); // Скрыть объект
            x = xx; // Обновить координаты
            y = yy;
            show(); // Показать объект на новом месте
            
            delay(300); // Задержка для анимации
        }
        getch(); // Ожидание нажатия клавиши
    }
};

// Класс Krug (Круг), наследуется от Point
class Krug : public Point {
protected:
    int radius; // Радиус круга
public:
    // Конструктор для инициализации круга
    void init(int xn, int yn, int r, int c) {
        Point::init(xn, yn, c); // Инициализация базового класса
        radius = r;
        show(); // Показать круг
    }
    
    // Показать круг
    void show() override {
        setcolor(color);
        setfillstyle(SOLID_FILL, color);
        pieslice(x, y, 0, 360, radius);
    }
    
    // Скрыть круг (закрасить цветом фона)
    void hide() override {
        setcolor(getbkcolor());
        setfillstyle(SOLID_FILL, getbkcolor());
        pieslice(x, y, 0, 360, radius);
    }
    
    // Дополнительный метод для изменения размера круга
    void changeSize(int delta) {
        hide();     // Скрыть текущий круг
        radius += delta; // Изменить радиус
        if (radius < 5) radius = 5; // Минимальный радиус
        show();     // Показать с новым радиусом
    }
    
    // Дополнительный метод для изменения цвета
    void changeColor(int newColor) {
        hide();     // Скрыть текущий круг
        color = newColor; // Изменить цвет
        show();     // Показать с новым цветом
    }
};

// Класс Ring (Кольцо), наследуется от Krug
class Ring : public Krug {
protected:
    int width; // Ширина кольца
public:
    // Конструктор по умолчанию
    Ring() {}
    
    // Инициализация кольца
    void init(int xn, int yn, int r, int c, int w) {
        width = w;
        Krug::init(xn, yn, r, c); // Инициализация базового класса
    }
    
    // Показать кольцо
    void show() override {
        Krug::show(); // Показать внешний круг
        
        // "Вырезать" внутренний круг для создания кольца
        setfillstyle(EMPTY_FILL, getbkcolor());
        pieslice(x, y, 0, 360, radius - width);
    }
    
    // Дополнительный метод для изменения ширины кольца
    void changeWidth(int delta) {
        hide();     // Скрыть текущее кольцо
        width += delta; // Изменить ширину
        if (width < 1) width = 1; // Минимальная ширина
        if (width >= radius) width = radius - 1; // Максимальная ширина
        show();     // Показать с новой шириной
    }
    
    // Дополнительный метод для анимированного изменения размера и цвета
    void animate(int cost) {
        int xx, yy;
        show();
        
        srand(time(NULL));
        
        while (!kbhit()) {
            locate(xx, yy);
            
            // Случайное перемещение по X
            do {
                xx += (int)((rand()/(float)RAND_MAX - 0.5) * cost);
            } while (xx <= 0 || xx >= getmaxx());
            
            // Случайное перемещение по Y
            do {
                yy += (int)((rand()/(float)RAND_MAX - 0.5) * cost);
            } while (yy <= 0 || yy >= getmaxy());
            
            hide();
            x = xx;
            y = yy;
            
            // Изменение размера и цвета во время движения
            changeWidth(rand() % 5 - 2); // Случайное изменение ширины
            changeColor(1 + rand() % 15); // Случайный цвет
            
            show();
            delay(300);
        }
        getch();
    }
};

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI"); // Инициализация графики
    
    setbkcolor(BLUE); // Установка цвета фона
    
    // Создание и тестирование круга
    Krug testKrug;
    testKrug.init(150, 40, 50, RED);
    testKrug.fly(100);
    
    // Создание и тестирование кольца
    Ring testRing;
    testRing.init(450, 80, 90, GREEN, 10);
    testRing.animate(60); // Анимация с изменением размера и цвета
    
    // Еще одно перемещение круга
    testKrug.fly(60);
    
    getch();
    
    // Скрыть объекты перед выходом
    testKrug.hide();
    testRing.hide();
    
    getch();
    closegraph(); // Закрытие графического режима
    return 0;
}