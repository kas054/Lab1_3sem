//
// Created by PC on 07.09.2021.
//

#include "Prog1.h"
#include <iostream>
namespace Prog1{
// Функция ввода
    Line* input(int &rm, int &rn)
    {
        const char *pr = ""; // сообщение об ошибке
        Line *lines = nullptr; // динамический массив строк матрицы
        int m, n; //количество строк матрицы
// ввод количества строк
        do{
            std::cout << pr << std::endl;
            std::cout << "Enter number of lines: --> ";
            pr = "You are wrong; repeat please!";
            if (getNum(m) < 0) // ошибка ввода или конец файла
                return nullptr;
        } while (m < 1);

        pr = "";
// ввод количества столбцов
        do{
            std::cout << pr << std::endl;
            std::cout << "Enter number of items in line: --> ";
            pr = "You are wrong; repeat please!";
            if (getNum(n) < 0) // ошибка ввода или конец файла
                return nullptr;
        } while (n < 1);
// выделяем память под массив структур
        try{
            lines = new Line[m];
        }
        catch (std::bad_alloc &ba)
        {
            std::cout << "------ too many rows in matrix: " << ba.what() << std::endl;
            return nullptr;
        }
        for (int i = 0; i < m; i++){
            pr = "";
            lines[i].n = n;
// выделяем память под элементы строки
            try{
                lines[i].a = new int[lines[i].n];
            }
            catch (std::bad_alloc &ba)
            {
                std::cout << "------ too many items in matrix: " << ba.what() << std::endl;
                erase(lines, i);
                return nullptr;
            }
// введение элементов строки матрицы
            std::cout << "Enter items for matrix line #" << (i + 1) << ":" << std::endl;
            for (int j = 0; j < n; j++){
                if (getNum(lines[i].a[j]) < 0){
                    erase(lines, i + 1);
                    return nullptr;
                }
            }
        }

        rm = m;
        rn = n;
        return lines;
    }
// функция вывода
    void output(const char *msg, Line *a, int m)
    {
        int i, j;
        std::cout << msg << ":\n";
        for (i = 0; i < m; ++i){
            for (j = 0; j < a[i].n; ++j)
                std::cout << a[i].a[j] << " ";
            std::cout << std::endl;
        }
    }
// Освобождение занятой памяти
    Line *erase(Line *&lines, int m)
    {
        int i;
        for (i = 0; i < m; i++)
            delete[] lines[i].a;
        delete[] lines;
        return nullptr;
    }
    int *new_list(int *list, int new_size, int x)
    {
        int *new_list = new int[new_size];
        for (int i = 0; i < new_size - 1; i++) new_list[i] = list[i];
        new_list[new_size - 1] = x;
        if (new_size != 1) delete[] list;
        return new_list;
    }
    void coordinates(Line *lines, int **string, int *&column, int *&value, int m, int *size)
    {
        for (int i = 0; i < m; i ++)
        {
            for (int j = 0; j < (lines[i]).n ; j ++)
            {
                if ( ((lines[i]).a)[j] != 0 )
                {
                    *size += 1;
                    *string = new_list(*string, *size, i);
                    column = new_list(column, *size, j);
                    value = new_list(value, *size, ((lines[i]).a)[j]);
                }
            }
        }
    }
    void print_coordinates(int *string, int *column, int *value, int size){
        for (int k = 0; k < size; k ++){
            std::cout << string[k] << "  ";
        }
        std::cout << "" << std::endl;
        for (int k = 0; k < size; k ++){
            std::cout << column[k] <<  "  ";
        }
        std::cout << "" << std::endl;
        for (int k = 0; k < size; k ++){
            std::cout << value[k] <<  "  ";
        }
        std::cout << "" << std::endl;
    }
    int get_vector(int **answer, int *string, int *column, int *value, int size, int m, int n)
    {
        try{
            *answer = new int[m]();
        }
        catch (std::bad_alloc &ba)
        {
            std::cout << ba.what() << std::endl;
            return 1;
        }
        int prev_string = -1, negative_number = 0;
        for (int i = 0; i < size; i ++){
            if (string[i] != prev_string) // перешли к элементам новой строки
            {
                if (negative_number) // в предыдущей строке было отрицательное число
                {
                    if (column[i - 1] == n - 1) (*answer)[prev_string] = value[i - 1]; // последнее число в строке не 0
                    else (*answer)[prev_string] = 0;
                }
                negative_number = 0;
                prev_string = string[i];
                if (column[i] == 0) (*answer)[string[i]] = value[i]; // записываем значение первого ненулевого элемента
                else (*answer)[string[i]] = 0;
            }
            if (value[i] < 0 || negative_number)
            {
                negative_number = 1;// если значение отрицательное, то записываем последний элемент
                (*answer)[string[i]] = value[i];
            }
        }
        if (negative_number) // в последней строке было отрицательное число
        {
            if (column[size - 1] == n - 1) (*answer)[prev_string] = value[size - 1]; // последнее число в строке не 0
            else (*answer)[prev_string] = 0;
        }
        return 0;
    }
    void print_result(int *answer, int size)
    {
        std::cout << "Result: ";
        for (int i = 0; i < size; i ++)
        {
            std::cout << answer[i] << " ";

        }
        std::cout << "" << std::endl;
    }
    void print_matrix(int *string, int *column, int *value, int size, int m, int n)
    {
        std::cout << "Input matrix: " << std::endl;
        int k = 0, flag = size;
        for (int i = 0; i < m; i ++ )
        {
            for (int j = 0; j < n; j ++)
            {
                if (flag) { // пока есть ненулевые значения
                    if (string[k] == i && column[k] == j) // если индексы совпали, то печатаем значение
                    {
                        std::cout << value[k] << " ";
                        k++;
                        if (k == size) flag = 0; // перебрали все ненулевые значение
                    }
                    else std::cout << "0 ";
                }
                else std::cout << "0 ";
            }
            std::cout << "" << std::endl;
        }
    }
}