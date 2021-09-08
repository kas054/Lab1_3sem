//
// Created by PC on 07.09.2021.
//

#ifndef LAB1_3SEM_PROG1_H
#define LAB1_3SEM_PROG1_H
#include <iostream>
namespace Prog1{
// структура строки матрицы
    struct Line{
        int n; // количество элементов в строке
        int *a; // вектор чисел
    };
// Ввод одного значения
    template <class T>
    int getNum(T &a)
    {
        std::cin >> a;
        if (!std::cin.good()) // ошибка ввода или конец файла
            return -1;
        return 1;
    }

    Line* input(int &, int &); // ввод матрицы
    void output(const char *msg, Line a[], int m); // вывод матрицы
    Line *erase(Line *&a, int m); // освобождение памяти
    int *new_list(int *list, int new_size, int x); // изменение размера вектора
    void coordinates(Line *lines, int **string, int *&column, int *&value, int m, int *size); // создание вектора координат (значение)
    void print_coordinates(int *string, int *column, int *value, int size); // вывод полученных векторов
    int get_vector(int **answer, int *string, int *column, int *value, int size, int m, int n); // формирование результата
    void print_result(int *answer, int size);
}
#endif //LAB1_3SEM_PROG1_H
