#include <iostream>
#include "Prog1.h"
using namespace Prog1;

int main()
{
    Line *arr = nullptr; // исходный массив
    int m, size = 0; // количество строк в матрице
    int *string, *column, *value, *answer;
    arr = input(m); // ввод матрицы
    if (!arr){
        std::cout << "incorrect data" << std::endl;
        return 1;
    }

    coordinates(arr, &string, column, value, m, &size);
    //print_coordinates(string, column, value, size);

    if (get_vector(arr, &answer, string, value, size, m)){
        std::cout << "Error in allocate memory" << std::endl;
        erase(arr, m);
        return 1;
    }
    output("Input matrix", arr, m);
    print_result(answer, m);
    erase(arr, m);
    delete [] answer;
    return 0;
}