#include <iostream>
#include <cmath>
#include <cstdlib>
#include <time.h>

using namespace std;

const int N = 100;
const double Pi = 3.1415926536;
int SumC = 0;
int MultC  = 0;

struct Complex
{
    double Re;
    double Im;
}A[N], f[N];


void ComplexMult(Complex *a, int k, Complex *b, Complex *rez)
{
    rez->Re = ((a+k)->Re * b->Re) - ((a+k)->Im * b->Im);
    rez->Im = ((a+k)->Re * b->Im) + ((a+k)->Im * b->Re);
}

void ComplexExp(double arg, Complex *rez)
{
    if(arg < 0)
    {
        rez->Re = cos( -1 * arg );
        rez->Im = -1 * sin( -1 * arg );
    }
    else
    {
        rez->Re = cos( arg );
        rez->Im = sin( arg );
    }
}

void ComplexDivide(Complex *a, int k, int p)
{
    Complex Temp;
    Temp.Re = 0;
    Temp.Im = 0;
    Complex n;
    n.Re = p;
    n.Im = 0;

    Temp.Re = ((a+k)->Re * n.Re + (a+k)->Im * n.Im) / (n.Re * n.Re + n.Im  * n.Im);
    Temp.Im = ((a+k)->Im * n.Re - (a+k)->Re * n.Im) / (n.Re * n.Re + n.Im * n.Im);

    (a+k)->Re = Temp.Re;
    (a+k)->Im = Temp.Im;
}

void PrintF(Complex *a)
{
    for(int i = 0; i < N; i++)
    {
        cout << " ( " << (a+i)->Re << " ; " << (a+i)->Im << " ) " << endl;
    }
}

void DFTP(Complex *A, Complex *f)
{
    Complex Mult;
    Mult.Im = 0.0;
    Mult.Re = 0.0;

    //Временная переменная для експоненты
    Complex Exp;
    Exp.Re = 0.0;
    Exp.Im = 0.0;

    //Дискретное преобразование Фурье, прямой ход
    for(int k = 0; k < N; k++)
    {
        for(int j = 0; j < N; j++)
        {
            ComplexExp( -1 * (2 * Pi * j * k) / N, &Exp );
            ComplexMult(f, j, &Exp, &Mult);
            MultC++;

            A[k].Re += Mult.Re;
            A[k].Im += Mult.Im;
            SumC++;

            Mult.Im = 0;
            Mult.Re = 0;

            Exp.Im = 0;
            Exp.Re = 0;
        }
        ComplexDivide(A, k, N);
    }
}

void DFTO(Complex *A, Complex *f)
{
    Complex Mult;
    Mult.Im = 0.0;
    Mult.Re = 0.0;

    //Временная переменная для експоненты
    Complex Exp;
    Exp.Re = 0.0;
    Exp.Im = 0.0;

    //Дискретное преобразование Фурье, обратный ход
    for(int j = 0; j < N; j++)
    {
        for(int k = 0; k < N; k++)
        {
            ComplexExp((2 * Pi * j * k) / N, &Exp);
            ComplexMult(A, k, &Exp, &Mult);

            f[j].Re += Mult.Re;
            f[j].Im += Mult.Im;

            Mult.Im = 0;
            Mult.Re = 0;

            Exp.Im = 0;
            Exp.Re = 0;
        }
    }
}

int GetP()
{
    int p = (int)sqrt(N);
    while(true)
    {
        if(N % p == 0)
        {
            break;
        }
        else
        {
            p++;
        }
    }
    return p;
}

void SFFT(Complex *A, Complex *f)
{
    Complex Mult;
    Mult.Im = 0;
    Mult.Re = 0;

    //Временная переменная для экспоненты
    Complex Exp;
    Exp.Re = 0;
    Exp.Im = 0;


    int p1 = GetP();
    int p2 = N / p1;

    Complex A1[N];
    for(int i = 0; i < N; i++)
    {
        A1[i].Re = 0;
        A1[i].Im = 0;
    }

    for(int k1 = 0; k1 < p1; k1++)
    {
        for(int j2 = 0; j2 < p2; j2++)
        {
            for(int j1 = 0; j1 < p1; j1++)
            {
                double z = (-1 * 2 * Pi * j1 * k1) / p1;
                ComplexExp( z, &Exp );
                ComplexMult(f, j2 + p2 * j1, &Exp, &Mult);

                A1[k1 + p1 * j2].Re += Mult.Re;
                A1[k1 + p1 * j2].Im += Mult.Im;

                Mult.Im = 0;
                Mult.Re = 0;

                SumC++;
                MultC++;

                Exp.Im = 0;
                Exp.Re = 0;
            }
            ComplexDivide(A1, k1 + p1 * j2, p1);
        }
    }

    Mult.Im = 0;
    Mult.Re = 0;

    Exp.Im = 0;
    Exp.Re = 0;

    Complex A2[N];
    for(int i = 0; i < N; i++)
    {
        A2[i].Re = 0;
        A2[i].Im = 0;
    }

    for(int k1 = 0; k1 < p1; k1++)
    {
        for(int k2 = 0; k2 < p2; k2++)
        {
            for(int j2 = 0; j2 < p2; j2++)
            {
                double z = -1 * 2 * Pi * j2 * (k1 + p1 * k2) / (p1 * p2);
                ComplexExp(   z, &Exp);
                ComplexMult(A1, k1 + p1 * j2, &Exp, &Mult);

                A2[k1 + p1 * k2].Re += Mult.Re;
                A2[k1 + p1 * k2].Im += Mult.Im;

                Mult.Im = 0;
                Mult.Re = 0;

                //SumC++;
               // MultC++;

                Exp.Im = 0;
                Exp.Re = 0;
            }
            ComplexDivide(A2, k1 + p1 * k2, p2);
        }
    }

    for(int i = 0; i < N; i++)
    {
        A[i].Re = A2[i].Re ;
        A[i].Im = A2[i].Im ;
    }
}

void SFFTO(Complex *A, Complex *f)
{
    Complex Mult;
    Mult.Im = 0;
    Mult.Re = 0;

    //Временная переменная для экспоненты
    Complex Exp;
    Exp.Re = 0;
    Exp.Im = 0;


    int p1 = GetP();
    int p2 = N / p1;

    Complex f1[N];
    for(int i = 0; i < N; i++)
    {
        f1[i].Re = 0;
        f1[i].Im = 0;
    }

    for(int k1 = 0; k1 < p1; k1++)
    {
        for(int j2 = 0; j2 < p2; j2++)
        {
            for(int j1 = 0; j1 < p1; j1++)
            {
                double z = (1 * 2 * Pi * j1 * k1) / p1;
                ComplexExp( z, &Exp );
                ComplexMult(A, j2 + p2 * j1, &Exp, &Mult);

                f1[k1 + p1 * j2].Re += Mult.Re;
                f1[k1 + p1 * j2].Im += Mult.Im;

                Mult.Im = 0;
                Mult.Re = 0;

                //SumC++;
                //MultC++;

                Exp.Im = 0;
                Exp.Re = 0;
            }
        }
    }

    Mult.Im = 0;
    Mult.Re = 0;

    Exp.Im = 0;
    Exp.Re = 0;

    Complex f2[N];
    for(int i = 0; i < N; i++)
    {
        f2[i].Re = 0;
        f2[i].Im = 0;
    }

    for(int k1 = 0; k1 < p1; k1++)
    {
        for(int k2 = 0; k2 < p2; k2++)
        {
            for(int j2 = 0; j2 < p2; j2++)
            {
                double z = 1 * 2 * Pi * j2 * (k1 + p1 * k2) / (p1 * p2);
                ComplexExp(   z, &Exp);
                ComplexMult(f1, k1 + p1 * j2, &Exp, &Mult);

                f2[k1 + p1 * k2].Re += Mult.Re;
                f2[k1 + p1 * k2].Im += Mult.Im;

                Mult.Im = 0;
                Mult.Re = 0;

                //SumC++;
                //MultC++;

                Exp.Im = 0;
                Exp.Re = 0;
            }
        }
    }

    for(int i = 0; i < N; i++)
    {
        f[i].Re = f2[i].Re ;
        f[i].Im = f2[i].Im ;
    }
}

int main()
{
    //Массив обработаннго сигнала
    for(int i = 0; i < N; i++)
    {
        A[i].Re = 0;
        A[i].Im = 0;
    }

    cout<<fixed;

    srand(time(NULL));
    //Исходный массив сигналов
    cout << "Исходные значения :" << endl;
    for(int i = 0; i < N; i++)
    {
        f[i].Re = rand()%20;
        f[i].Im = rand()%5;
    }

    Complex TempM[N];
    for(int i = 0; i < N; i++)
    {
        TempM[i].Re = f[i].Re;
        TempM[i].Im = f[i].Im;
    }

    PrintF(f);
    cout << endl << endl;
    DFTP(A, f);

    for(int i = 0; i < N; i++)
    {
        f[i].Re = 0;
        f[i].Im = 0;
    }

    DFTO(A, f);

    cout << "Дискретное преобразование Фурье прямой ход: \n";
    PrintF(A);
    cout << "\nДПФ: " << SumC << "(Sum) + " << MultC << "(Mult)" << " = " << SumC + MultC <<  endl;
    cout << endl << endl;

    cout << "Обратное дискретное фурье: \n";
    PrintF(f);
    cout << endl << endl;

    for(int i = 0; i < N; i++)
    {
        A[i].Re = 0;
        A[i].Im = 0;
    }

    SumC = 0;
    MultC = 0;

    SFFT(A, TempM);
    cout << "Полу-быстрое преобразование фурье: \n";
    PrintF(A);
    cout << "\nПБПФ: " << SumC << "(Sum) + " << MultC << "(Mult)" << " = " << SumC + MultC <<  endl;

    for(int i = 0; i < N; i++)
    {
        f[i].Re = 0;
        f[i].Im = 0;
    }

    SFFTO(A, f);
    cout << "\nОбратное полу-быстрое преобразование фурье:\n";
    PrintF(f);

    return 0;
}
