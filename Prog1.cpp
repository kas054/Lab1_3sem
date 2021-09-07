//
// Created by PC on 07.09.2021.
//

#include "Prog1.h"
#include <iostream>
namespace Prog1{
// Функция ввода
    Line* input(int &rm)
    {
        const char *pr = ""; // сообщение об ошибке
        Line *lines = nullptr; // динамический массив строк матрицы
        int m; //количество строк матрицы
// ввод количества строк
        do{
            std::cout << pr << std::endl;
            std::cout << "Enter number of lines: --> ";
            pr = "You are wrong; repeat please!";
            if (getNum(m) < 0) // ошибка ввода или конец файла
                return nullptr;
        } while (m < 1);
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
// для каждой строки матрицы вводим количество столбцов
            pr = "";
            do{
                std::cout << pr << std::endl;
                std::cout << "Enter number of items in line #" << (i + 1) << " --> ";
                pr = "You are wrong; repeat please!";
                if (getNum(lines[i].n) < 0){
                    erase(lines, i); // освобождение памяти, занятой ранее введёными строками
                    return nullptr;
                }
            } while (lines[i].n < 1);

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
            for (int j = 0; j < lines[i].n; j++){
                if (getNum(lines[i].a[j]) < 0){
                    erase(lines, i + 1);
                    return nullptr;
                }
            }
        }

        rm = m;
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
    int get_vector(Line *matrix, int **answer, int *string, int *value, int size, int m)
    {
        try{
            *answer = new int[m]();
        }
        catch (std::bad_alloc &ba)
        {
            std::cout << ba.what() << std::endl;
            return 1;
        }
        int prev_string = -1;
        for (int i = 0; i < size; i ++){
            if (string[i] != prev_string) // перешли к элементам новой строки
            {
                prev_string = string[i];
                (*answer)[string[i]] = (matrix[string[i]]).a[0]; // записываем значение первого ненулевого элемента
            }
            if (value[i] < 0) // если значение отрицательное, то записываем последний элемент
                {
                    int n = (matrix[string[i]]).n - 1;
                    (*answer)[string[i]] = (matrix[string[i]]).a[n];
                }
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
}
