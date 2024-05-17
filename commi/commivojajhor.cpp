#include<glut.h>
#include <glut.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <string>
#include"Point.h"
#include"GraphFunctions.h"
#include"obhod_v_shirinu.h"
#define PI 3.14159265358979323846


//const int numObjects = 5; // Количество объектов
const float radius = 200; // Радиус окружности
const float center_x = 640; // X-координата центра окружности
const float center_y = 360; // Y-координата центра окружности

//std::vector<std::vector<int>> matr = { //таблица смежности
//        {0,5,6,14,15},
//        {5,0,7,10,6},
//        {6,7,0,8,7},
//        {14,10,8,0,9},
//        {15,6,7,9,0}
//};
std::vector<std::vector<int>> matr;

std::map <int, int> points;
std::vector<Point> text_and_coords; //храним координаты и номер города (по порядку)
std::vector<std::vector<int>> coord_lines; //массив хранит координаты центра узлов (городов), чтобы потом соединять линиями

void drawCircle(float cx, float cy, float r, int num_segments);
void display();
void drawText(float x, float y, std::string text);
void drawLine(float x1, float y1, float x2, float y2);
bool checkXY(int x, int y); //проверка, чтобы не нарисовать лишний раз текст
int MinElement(std::vector<int>&); //нахождение минимального элемента в строке
int MinElementIndex(std::vector<int>&); //индекс минимального элемента строки
void fNull(std::vector<std::vector<int>>&, int, int); //зануляем строку и столбец города, в котором уже были

int main(int argc, char** argv)
{
    system("chcp 1251 > null");
    int n = 10, i = matr.size(); //i - количество городов

    while (n != 3) {
        std::cout << "1. Добавить город\n2. Расчитать дорогу\n3. Печать графа\n4. Вывести матрицу смежности\n5. Удалить город\n";
        std::cout << "6. Удалить расстояние между городами\n7. Изменить расстояние между городами\n";
        std::cout << "8. Обход графа в глубину\n9. Обход графа в ширину\n>";
        std::cin >> n;
        if (n == 1) {
            std::vector<int>add_matr; //массив с расстояними i-го города до остальных городов
            for (int k = 0; k < i; ++k) //заполняем нулями все расстояния нового города
                add_matr.push_back(0);
            for (int k = 0; k < matr.size(); ++k)
                matr[k].push_back(0); //добавление расстояния в существующие города (изначально расстояния = 0)
            matr.push_back(add_matr);
            for (int j = 0; j < matr.size(); ++j) {
                if (i == j) matr[i].push_back(0);
                else {
                    int temp;
                    printf("Введите расстояние от %d города до %d города : ", i + 1, j + 1);
                    std::cin >> temp;
                    matr[i][j] = temp;
                    matr[j][i] = temp;
                }
            }
            i++;
            printf("Добавлен %d город\n", i);
            system("pause");
        }

        if (n == 2) {
            std::vector<std::vector<int>> help_matr = matr; //всопомгательная таблица, где учитывается, какие города мы проходили
            int k = 0;
            std::string str = "";

            for (int i = 0; i < help_matr.size(); ++i) {
                int rem_city = i; //переменная будет запоминать город в котором находимся
                for (int j = 0; j < help_matr[i].size() - 1; ++j) {
                    str += std::to_string(rem_city + 1); str += " -> ";
                    int min_el = MinElement(help_matr[rem_city]);
                    k += min_el;
                    int min_el_index = MinElementIndex(help_matr[rem_city]);
                    fNull(help_matr, rem_city, rem_city);
                    rem_city = min_el_index; //заменяем индекс на тот город, в который перешел комивояжер
                }
                str += std::to_string(rem_city + 1);
                help_matr = matr; //обновляем таблицу смежности для следующей итерации
                if (k < 100000) {
                    std::cout << str << " Расстояние: " << k << std::endl;
                }
                str = "";
                k = 0;
            }
            system("pause");
        }

        if (n == 4) {
            for (int i = 0; i < matr.size(); ++i) {
                for (int j = 0; j < matr[i].size(); ++j)
                    std::cout << matr[i][j] << ' ';
                std::cout << std::endl;
            }
            system("pause");
        }
        if (n == 5) {
            std::cout << "Какой город удалить?\n>";
            int city; std::cin >> city;
            matr.erase(matr.begin() + city - 1);
            for (int i = 0; i < matr.size(); ++i) {
                matr[i].erase(matr[i].begin() + city - 1);
            }
            system("pause");
        }
        if (n == 6) {
            std::cout << "Между какими городами удалить расстояние?\n";
            int num, num2;
            std::cout << "Введите номер первого города: "; std::cin >> num;
            std::cout << "Введите номер второго города: "; std::cin >> num2;
            matr[num - 1][num2 - 1] = 0;
            matr[num2 - 1][num - 1] = 0;
        }
        if (n == 7) {
            std::cout << "Между какими городами поменять расстояние?\n";
            int num, num2, d;
            std::cout << "Введите номер первого города: "; std::cin >> num;
            std::cout << "Введите номер второго города: "; std::cin >> num2;
            std::cout << "Введите новое расстояние: "; std::cin >> d;
            matr[num - 1][num2 - 1] = d;
            matr[num2 - 1][num - 1] = d;
        }
        if (n == 8) {
            obhod_v_glubiny(matr);
            system("pause");
        }
        if (n == 9) {
            obhod_v_shirinu(matr);
            system("pause");
        }
        system("cls");
    }
    glutInit(&argc, argv);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Комивояжер");

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1280.0, 0.0, 720.0);

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}

void drawCircle(float cx, float cy, float r, int num_segments) {
    glColor3ub(0, 255, 0);
    glLineWidth(1.5);

    int k = 0;

    glBegin(GL_LINE_LOOP); // начинаем рисовать линии
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * PI * float(i) / float(num_segments); // угол текущего сегмента
        float x = r * cosf(theta); // x координата точки на окружности
        float y = r * sinf(theta); // y координата точки на окружности
        glVertex2f(x + cx, y + cy); // координаты точки с учетом смещения центра окружности
    }
    glEnd(); // заканчиваем рисование
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // очищаем буфер цвета
    Point pos;
    std::vector<int>cords_line;
    glColor3f(0.0, 0.0, 0.0);
    bool print_graph = true;
    while (print_graph) {
        Point pos;
        glClearColor(1.0, 1.0, 1.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
        int n = 10, i = matr.size(); //i - количество городов

        while (n != 3) {
            std::cout << "1. Добавить город\n2. Расчитать дорогу\n3. Печать графа\n4. Вывести матрицу смежности\n5. Удалить город\n";
            std::cout << "6. Удалить расстояние между городами\n7. Изменить расстояние между городами\n";
            std::cout << "8. Обход графа в глубину\n9. Обход графа в ширину\n>";
            std::cin >> n;
            if (n == 1) {
                std::vector<int>add_matr; //массив с расстояними i-го города до остальных городов
                for (int k = 0; k < i; ++k) //заполняем нулями все расстояния нового города
                    add_matr.push_back(0);
                for (int k = 0; k < matr.size(); ++k)
                    matr[k].push_back(0); //добавление расстояния в существующие города (изначально расстояния = 0)
                matr.push_back(add_matr);
                for (int j = 0; j < matr.size(); ++j) {
                    if (i == j) matr[i].push_back(0);
                    else {
                        int temp;
                        printf("Введите расстояние от %d города до %d города : ", i + 1, j + 1);
                        std::cin >> temp;
                        matr[i][j] = temp;
                        matr[j][i] = temp;
                    }
                }
                i++;
                printf("Добавлен %d город\n", i);
                system("pause");
            }

            if (n == 2) {
                std::vector<std::vector<int>> help_matr = matr; //всопомгательная таблица, где учитывается, какие города мы проходили
                int k = 0;
                std::string str = "";

                for (int i = 0; i < help_matr.size(); ++i) {
                    int rem_city = i; //переменная будет запоминать город в котором находимся
                    for (int j = 0; j < help_matr[i].size() - 1; ++j) {
                        str += std::to_string(rem_city + 1); str += " -> ";
                        int min_el = MinElement(help_matr[rem_city]);
                        k += min_el;
                        int min_el_index = MinElementIndex(help_matr[rem_city]);
                        fNull(help_matr, rem_city, rem_city);
                        rem_city = min_el_index; //заменяем индекс на тот город, в который перешел комивояжер
                    }
                    str += std::to_string(rem_city + 1);
                    help_matr = matr; //обновляем таблицу смежности для следующей итерации
                    if (k < 100000) {
                        std::cout << str << " Расстояние: " << k << std::endl;
                    }
                    str = "";
                    k = 0;
                }
                system("pause");
            }

            if (n == 4) {
                for (int i = 0; i < matr.size(); ++i) {
                    for (int j = 0; j < matr[i].size(); ++j)
                        std::cout << matr[i][j] << ' ';
                    std::cout << std::endl;
                }
                system("pause");
            }
            if (n == 5) {
                std::cout << "Какой город удалить?\n>";
                int city; std::cin >> city;
                matr.erase(matr.begin() + city - 1);
                for (int i = 0; i < matr.size(); ++i) {
                    matr[i].erase(matr[i].begin() + city - 1);
                }
                system("pause");
            }
            if (n == 6) {
                std::cout << "Между какими городами удалить расстояние?\n";
                int num, num2;
                std::cout << "Введите номер первого города: "; std::cin >> num;
                std::cout << "Введите номер второго города: "; std::cin >> num2;
                matr[num - 1][num2 - 1] = 0;
                matr[num2 - 1][num - 1] = 0;
            }
            if (n == 7) {
                std::cout << "Между какими городами поменять расстояние?\n";
                int num, num2, d;
                std::cout << "Введите номер первого города: "; std::cin >> num;
                std::cout << "Введите номер второго города: "; std::cin >> num2;
                std::cout << "Введите новое расстояние: "; std::cin >> d;
                matr[num - 1][num2 - 1] = d;
                matr[num2 - 1][num - 1] = d;
            }
            if (n == 8) {
                obhod_v_glubiny(matr);
                system("pause");
            }
            if (n == 9) {
                obhod_v_shirinu(matr);
                system("pause");
            }
            system("cls");
        }
        for (int i = 0; i < matr.size(); ++i) {
            float angle = 2.0f * 3.1415926f * float(i) / float(matr.size());
            float x = center_x + radius * cosf(angle);
            float y = center_y + radius * sinf(angle);
            pos.x = x; pos.y = y; pos.value = std::to_string(i + 1);
            cords_line.push_back(x); cords_line.push_back(y);
            coord_lines.push_back(cords_line);
            cords_line.clear();
            text_and_coords.push_back(pos);

            drawCircle(x, y, 30, 100);
        }
        for (int i = 0; i < text_and_coords.size(); ++i) {
            drawText(text_and_coords[i].x, text_and_coords[i].y, text_and_coords[i].value);
        }
        for (int i = 0; i < coord_lines.size() - 1; ++i) {
            for (int j = 1; j <= coord_lines.size() - 1; ++j) {
                if (matr[i][j] != 0)
                    drawLine(coord_lines[i][0], coord_lines[i][1], coord_lines[j][0], coord_lines[j][1]);
            }
        }
        for (int i = 0; i < coord_lines.size() - 1; ++i) {
            for (int j = 0; j < coord_lines.size(); ++j) {
                if (checkXY((coord_lines[i][0] + coord_lines[j][0]) / 2, (coord_lines[i][1] + coord_lines[j][1]) / 2) && i != j && matr[i][j] != 0)
                    drawText((coord_lines[i][0] + coord_lines[j][0]) / 2, (coord_lines[i][1] + coord_lines[j][1]) / 2, std::to_string(matr[i][j]));
            }
        }
        glFlush(); // принудительно выводим все команды нарисовать
        system("pause");
        cords_line.clear();
        coord_lines.clear();
        text_and_coords.clear();
        std::cout << "Завершить печать графа?\n1. Завершить\n2. Продолжить\n>";
        std::cin >> n;
        if (n == 1) print_graph = false;
        if (!print_graph) return;
    }
}

// Функция для вывода текста по координатам (x, y)
void drawText(float x, float y, std::string text) {
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2f(x-5, y-5); // Устанавливаем позицию для вывода текста

    // Проходимся по каждому символу текста и выводим его
    for (char& c : text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}
void drawLine(float x1, float y1, float x2, float y2) {
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(1.5);
    glBegin(GL_LINES); // Начинаем рисовать линию
    glVertex2f(x1, y1); // Устанавливаем первую точку
    glVertex2f(x2, y2); // Устанавливаем вторую точку
    glEnd(); // Завершаем рисование линии
}
bool checkXY(int x, int y) {
    bool flag = false;
    for (int i = 0; i < coord_lines.size() && !flag; ++i) {
        if (x == coord_lines[i][0] && y == coord_lines[i][1]) {
            flag = true;
        }
    }
    return !flag;
}



int MinElement(std::vector<int>& arr) {
    int min_el = 100000;
    for (auto i = 0; i < arr.size(); ++i) {
        if (arr[i] < min_el && arr[i] != 0)
            min_el = arr[i];
    }
    return min_el;
}
int MinElementIndex(std::vector<int>& arr) {
    int min_el = 100000;
    int index = 0;
    for (auto i = 0; i < arr.size(); ++i) {
        if (arr[i] < min_el && arr[i] != 0) {
            min_el = arr[i];
            index = i;
        }
    }
    return index;
}
void fNull(std::vector<std::vector<int>>& a, int cur_column, int cur_str) {
    for (int i = 0; i < a.size(); ++i) {
        a[cur_str][i] = 0;
    }
    for (int i = 0; i < a.size(); ++i) {
        a[i][cur_column] = 0;
    }
}