#include <iostream>
#include <limits.h>
#include <iomanip>

using namespace std;


void matrixDoSomething(int(*)[10], int, int);
void matrixDoSomething(int(*)[10], int);
void matrixDoSomething(int(*)[10], int, int, int);
void matrixDoSomething(int(*)[10]);

int main()
{
    int const massivDimention = 10;
    int massiv[massivDimention][massivDimention] = { 0 };
    int limitNumber = 100;
    int max = INT_MIN;
    int min = INT_MAX;
    int input;

    cout << "This program do something with matrix" << endl;
    do
    {
        cout << "Select what you want to do: " << endl <<
            "0 = Exit" << endl << "1 = Initialize matrix" << endl <<
            "2 = Print matrix" << endl << "3 = Find min and max elements" << endl <<
            "4 = Sorting rows" << endl;
        cin >> input;

        switch (input)
        {
        case 0:
            cout << "You want to exit" << endl;
            break;
        case 1:
            matrixDoSomething(massiv, massivDimention, limitNumber);
            break;
        case 2:
            matrixDoSomething(massiv, massivDimention);
            break;
        case 3:
            matrixDoSomething(massiv, massivDimention, min, max);
            break;
        case 4:
            matrixDoSomething(massiv);
            break;
        default:
            cout << "Error. Uncorrect choice!" << endl;
            return 1;
        }
    } while (input != 0);
    return 0;
}
//Инициализация квадратной матрицы;
void matrixDoSomething(int arr[][10], int size, int limitNumber)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            arr[i][j] = rand() % limitNumber;
        }
    }
    cout << "An array initialized" << endl;
}
//Вывод матрицы на экран;
void matrixDoSomething(int arr[][10], int arSize)
{
    cout << "Start massiv: " << endl;
    for (int i = 0; i < arSize; i++)
    {
        for (int j = 0; j < arSize; j++)
        {
            cout << fixed << setw(3) << arr[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}
//Определение максимального и минимального элемента на главной диагонали матрицы;
void matrixDoSomething(int arr[][10], int arSize, int minElement, int maxElement)
{
    for (int i = 0; i < arSize; i++)
    {
        if (arr[i][i] > maxElement)
        {
            maxElement = arr[i][i];
        }
        if (arr[i][i] < minElement)
        {
            minElement = arr[i][i];
        }
    }
    cout << "Min element = " << minElement << endl <<
        "Max element = " << maxElement << endl;
}
//Сортировка элементов по возрастанию отдельно для каждой строки матрицы.
void matrixDoSomething(int arr[][10])
{
    int arraySize = 10;
    int bufer;
    cout << "Sort Ascending elements of each line separately" << endl;
    for (int k = 0; k < arraySize; k++)
    {
        for (int j = 0; j < arraySize - 1; j++)
        {
            for (int i = 1; i < arraySize - j; i++)
            {
                if (arr[k][i] < arr[k][i - 1])
                {
                    bufer = arr[k][i - 1];
                    arr[k][i - 1] = arr[k][i];
                    arr[k][i] = bufer;
                }
            }
        }
    }
}