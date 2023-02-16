#include <iostream>
#include<windows.h>
using namespace std;

void enter(double** A, int N) {
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << A[i][j] << " ";			//Вывод матрицы 			
        }
        cout << "\n";
    }
    cout << "\n";
}

void inversion(double** A, int N)
{
    double temp;
   
    double** E = new double* [N];

    for (int i = 0; i < N; i++)
        E[i] = new double[N];

    for (int i = 0; i < N; i++)            //создаем еденичную матрицу
        for (int j = 0; j < N; j++)
        {
            E[i][j] = 0.0;

            if (i == j)
                E[i][j] = 1.0;
        }

    for (int k = 0; k < N; k++)
    {
        temp = A[k][k];

        for (int j = 0; j < N; j++)
        {
            A[k][j] /= temp;
            E[k][j] /= temp;
        }

        for (int i = k + 1; i < N; i++)
        {
            temp = A[i][k];

            for (int j = 0; j < N; j++)
            {
                A[i][j] -= A[k][j] * temp;
                E[i][j] -= E[k][j] * temp;
            }
        }
    }
    //cout << "\n" << "E" << "\n";
    enter(E, N);
    for (int k = N - 1; k > 0; k--)
    {
        for (int i = k - 1; i >= 0; i--)
        {
            temp = A[i][k];

            for (int j = 0; j < N; j++)
            {
                A[i][j] -= A[k][j] * temp;
                E[i][j] -= E[k][j] * temp;
            }
        }
    }
    //cout << "\n" << "E" << "\n";
    enter(E, N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            A[i][j] = E[i][j];

    for (int i = 0; i < N; i++)
        delete[] E[i];

    delete[] E;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int N;
    cout << "ВВедите размерность: ";
    cin >> N;
    double** nev = new double* [N];
    double** first = new double* [N];;
    double** matrix = new double* [N];
        
    for (int i = 0; i < N; i++)                                                      //Заполнеие 0
    {
        first[i] = new double[N];
    }

    for (int i = 0; i < N; i++) 
    {
        nev[i] = new double[N];
    }

    for (int i = 0; i < N; i++)
    {
        matrix[i] = new double[N];
    }

    for (int i = 0; i < N; i++)                                                     //Заполнение матрицы                       
        for (int j = 0; j < N; j++)
        {
            cout << "Ведите матрицу[" << i << "][" << j << "] = ";
            cin >> matrix[i][j];
        }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            first[i][j] = matrix[i][j];
        }
    }

    enter(matrix, N);                                                              //Обратная матрица
    inversion(matrix, N);

    cout << "Обратная матрица" << "\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout << matrix[i][j] << "  ";

        cout << endl;
    }

    cout << "\n";
    cout << "Невязка" << "\n";

    for (int i = 0; i < N; i++)                                                  //Выполенние проверки 
    {
        for (int j = 0; j < N; j++)
        {
           nev[i][j] = 0;
            for (int k = 0; k < N; k++)
                nev[i][j] += first[i][k] * matrix[k][j];
                nev[i][j] = round(nev[i][j] * 10) / 10;
            cout << nev[i][j] << " ";
        }
        cout << "\n";
    }
    for (int i = 0; i < N; i++)
        delete[] matrix[i];

    delete[] matrix;

    cin.get();
    return 0;
}