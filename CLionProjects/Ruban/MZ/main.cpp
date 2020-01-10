#include "pch.h"

void input(double &eps)
{
    cout << "Приближенные метода решения СЛАУ" << endl;
    cout << "	Метод простых итераций" << endl;
    cout << "	Метод Зейделя" << endl << endl;
    cout << "Введите точность вычислений(0.0001) [eps] = "; cin >> eps;
    cout << endl;
}

int funcMSI(double**, double*, double**, double*&, int, int, double);
int funcZeidel(double**, double*, double**, double*&, int, int, double);
int funcFill(double**, double*&, double**&, double*&, double*&, double*&, int, int);
int multMatrix(double**, double*, double*, int);
int subMatrix(double*, double*, double*, int);
int equalMatrix(double*, double*, int);

int main()
{
    setlocale(0, "");

    string filename = "Matrix.txt";
    int n, m;
    double	**matrix = nullptr, **c = nullptr, *b = nullptr, *x = nullptr, eps = 0.01;

    input(eps);

    countNM(filename, n, m);
    fillMatrix(filename, matrix, b, n, m);
    printm(matrix, n, m);

    funcMSI(matrix, b, c, x, n, m, eps);
    cout << "Первый метод"; printm(x, n);

    funcZeidel(matrix, b, c, x, n, m, eps);
    cout << "Метод Зейделя";  printm(x, n);

    system("pause");
    return 0;
}

int funcMSI(double **matrix, double *b, double **c, double *&x, int n, int m, double eps)
{
    double *x_prev = new double[n];
    double *cx = new double[n];
    funcFill(matrix, b, c, x, cx, x_prev, n, m);

    do {
        equalMatrix(x, x_prev, n);
        multMatrix(c, x, cx, n);
        subMatrix(b, cx, x, n);

        printm(x, n);

    } while (fabs(x[0] - x_prev[0]) > eps);

    return 0.0;
}

int funcZeidel(double **matrix, double *b, double **c, double *&x, int n, int m, double eps)
{
    double *x_prev = new double[n];
    double *cx = new double[n];
    funcFill(matrix, b, c, x, cx, x_prev, n, m);

    do {
        equalMatrix(x, x_prev, n);
        for (int i = 0; i < n; i++) {
            x_prev[i] = x[i]; x[i] = 0;
            for (int j = 0; j < n; j++) {
                x[i] += c[i][j] * x_prev[j];
            }
            x[i] = b[i] - x[i];
        }
    } while (fabs(x[0] - x_prev[0]) > eps);

    return 0;
}

int funcFill(double **matrix, double *&b, double **&c, double *&x, double *&cx, double *&x_prev, int n, int m)
{
    /*Приводим к единичной*/
    double k;
    double **tmp_matrix = new double*[n];
    for (int i = 0; i < n; i++) {
        tmp_matrix[i] = new double[m];
    }
    for (int i = 0; i < n; i++) {
        k = 1 / matrix[i][i];
        for (int j = 0; j < m; j++) {
            tmp_matrix[i][j] = matrix[i][j];
            tmp_matrix[i][j] *= k;
        }
    }
    /*Заполняем С матрицу*/
    c = new double*[n];
    for (int i = 0; i < n; i++) c[i] = new double[n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) c[i][j] = tmp_matrix[i][j];
            c[i][i] = 0;
        }
    }
    /*Заполняем b матрицу и инициализируем вспомогательные матрицы*/
    x = new double[n];
    for (int i = 0; i < n; i++) {
        b[i] = tmp_matrix[i][m - 1];
        x_prev[i] = 0;
        x[i] = 0;
        cx[i] = 0;
    }
    return 0;
}

int multMatrix(double **c, double *x, double *cx, int n)
{
    for (int i = 0; i < n; i++) cx[i] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cx[i] += c[i][j] * x[j];
        }
    } return 0;
}

int subMatrix(double *b, double *cx, double *x, int n)
{
    for (int i = 0; i < n; i++) {
        x[i] = b[i] - cx[i];
    } return 0;
}

int equalMatrix(double *x, double *x_prev, int n)
{
    for (int i = 0; i < n; i++) {
        x_prev[i] = x[i];
    } return 0;
}
