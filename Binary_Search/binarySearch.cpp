#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

void crearArrayLineal(int n, int *A, int epsilon)
{
    A[0] = rand() % 50;
    for (int i = 1; i < n; i++)
    {
        A[i] = A[i - 1] + rand() % epsilon;
    }
}

void crearArrayNormal(int n, int *A, double mean, double stddev)
{
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> d(mean, stddev);

    for (int i = 0; i < n; i++)
    {
        A[i] = static_cast<int>(d(gen));
    }
    sort(A, A + n);
}

void printArray(int n, int *A)
{
    for (int i = 0; i < n; i++)
    {
        cout << A[i] << " ";
    }
    cout << endl;
}

int binarySearch(int *A, int l, int r, int x)
{
    if (l > r)
        return -1;

    int m = (l + r) / 2;
    if (x == A[m])
        return m;
    if (x < A[m])
        return binarySearch(A, l, m - 1, x);
    else
        return binarySearch(A, m + 1, r, x);
}

void validarM(int b, int m)
{
    if (b == -1)
    {
        cout << "El valor " << m << " no se encuentra en el arreglo." << endl;
    }
    else
    {
        cout << "El valor " << m << " se encuentra en la posición " << b + 1 << " del arreglo." << endl;
    }
}

void medirTiempoBusqueda(int n, int *A, int m)
{
    auto start = chrono::high_resolution_clock::now();
    int b = binarySearch(A, 0, n - 1, m);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;

    validarM(b, m);
    cout << "Tiempo de búsqueda: " << duration.count() << " ms" << endl;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Entrada debe ser ./binaryS n m" << endl;
        exit(1);
    }
    srand(time(nullptr));

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    int *A_lineal = new int[n];
    int *A_normal = new int[n];

    int epsilon = 10;
    crearArrayLineal(n, A_lineal, epsilon);
    double mean = 25.0;
    double stddev = 5.0;
    crearArrayNormal(n, A_normal, mean, stddev);

    cout << "Arreglo Lineal: ";
    printArray(n, A_lineal);
    cout << "Arreglo Normal: ";
    printArray(n, A_normal);

    cout << "Búsqueda en Arreglo Lineal:" << endl;
    medirTiempoBusqueda(n, A_lineal, m);

    cout << "Búsqueda en Arreglo Normal:" << endl;
    medirTiempoBusqueda(n, A_normal, m);

    delete[] A_lineal;
    delete[] A_normal;

    return 0;
}
