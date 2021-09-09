#include <iostream>
#include "Prog1.h"
using namespace Prog1;

int main()
{
    Line *arr = nullptr; // исходный массив
    int m, n, size = 0; // количество строк в матрице
    int *string, *column, *value, *answer;
    arr = input(m, n); // ввод матрицы
    if (!arr){
        std::cout << "incorrect data" << std::endl;
        return 1;
    }

    coordinates(arr, &string, column, value, m, &size); // создание массивов с координатами и значениями ненулевых элементов матрицы
    erase(arr, m); // удаление введённой матрицы
    //print_coordinates(string, column, value, size);

    if (get_vector(&answer, string, column, value, size, m, n)){
        std::cout << "Error in allocate memory" << std::endl;
        delete [] string;
        delete [] column;
        delete [] value;
        return 1;
    }
    //output("Input matrix", arr, m);
    print_matrix(string, column, value, size, m, n);
    print_result(answer, m);
    //erase(arr, m);
    delete [] answer;
    delete [] string;
    delete [] column;
    delete [] value;
    return 0;
}