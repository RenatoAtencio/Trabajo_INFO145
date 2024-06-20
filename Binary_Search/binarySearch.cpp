#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

void crearArray(int n, int *A)
{
    for (int i = 0; i < n; i++)
    {
        A[i] = rand() % 50;
    }
}

void sortArray(int n, int *A)
{
    sort(A, A + n);
    cout << "arreglo ordenado A = ";
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
        cout << "el valor " << m << " no se encuentra en el arreglo " << endl;
    }
    else
    {
        cout << "el valor " << m << "  se encuentra en la posicion " << b + 1 << " del arreglo" << endl;
    }
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Entrada debe ser ./binaryS n m " << endl;
        exit(1);
    }
    srand(time(nullptr));

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    int *A = new int[n];
    int left = 0;
    int right = n - 1;

    crearArray(n, A);
    sortArray(n, A);

    int b = binarySearch(A, left, right, m);

    validarM(b, m);

    delete[] A;

    return 0;
}