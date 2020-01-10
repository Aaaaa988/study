#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

const double Pi = 3.14159265359;

int SumC = 0;
int MultC = 0;

struct Complex
{
    double Re;
    double Im;
};


void ComplexMult(Complex *a, int k, Complex *b, int k1,  Complex *rez)
{
    rez->Re = ((a+k)->Re * (b+k1)->Re) - ((a+k)->Im * (b+k1)->Im);
    rez->Im = ((a+k)->Re * (b+k1)->Im) + ((a+k)->Im * (b+k1)->Re);
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

void PrintF(Complex *a, int N)
{
    for(int i = 0; i < N; i++)
    {
        cout << " ( " << (a+i)->Re << " ; " << (a+i)->Im << " ) " << endl;
    }
}

void DFTP(Complex *A, Complex *f, int N)
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
            ComplexMult(f, j, &Exp, 0,  &Mult);
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

void DFTO(Complex *A, Complex *f, int N)
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
            ComplexMult(A, k, &Exp, 0, &Mult);
           // MultC++;
            f[j].Re += Mult.Re;
            f[j].Im += Mult.Im;

            Mult.Im = 0;
            Mult.Re = 0;

            Exp.Im = 0;
            Exp.Re = 0;
        }
    }
}

int main()
{
    string a;
    string b;
    cin >> a;
    cin >> b;

    int N1 = a.size();
    int N2 = b.size();


    int A[N1];
    int B[N2];


    for(int i = N1 - 1; i >= 0; i--)
    {
        A[i] = a[i] - '0';
    }

    for(int i = N2 - 1; i >= 0; i--)
    {
        B[i] = b[i] - '0';
    }

    int Kmax = (N1 - 1) + (N2 - 1);


    int C[Kmax + 1];
    for(int i = 0; i < Kmax+1; i++)
    {
        C[i] = 0;
    }

    cout << "A:  ";
    for(int i = 0; i < N1; i++)
    {
        cout << A[i] << " ";
    }

    cout << endl;
    cout << "B:  ";
    for(int i = 0; i < N2; i++)
    {
        cout << B[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < Kmax + 1; i++)
    {
        for(int j = 0; j < N1; j++)
        {
            for(int z = 0; z < N2; z++)
            {
                if( (j + z) == i)
                {
                    C[i] += A[j] * B[z];
                }
            }
        }
    }
    cout << "Обычная свертка:\n";
    for(int i = 0; i < Kmax+1; i++)
    {
        cout << C[i] << " " << endl;
    }
    cout << endl;

    //Алгоритм быстрой свёртки
    int N = 0;
    if(N1 > N2)
    {
        //N = 2 * N1;
        N = Kmax + 1;
    }
    else
    {
        //N = 2 * N2;
        N = Kmax + 1;
    }

    Complex A1[N];
    Complex B1[N];

    for(int i = N - 1; i>= 0; i--)
    {
        if(i <= N1 - 1)
        {
            A1[i].Re = a[i] - '0';
            A1[i].Im = 0;
        }
        else
        {
            A1[i].Re = 0;
            A1[i].Im = 0;
        }
    }
    //cout << "A1 :\n";
    //PrintF(A1, N);

    for(int i = N - 1; i>= 0; i--)
    {
        if(i <= N2 - 1)
        {
            B1[i].Re = b[i] - '0';
            B1[i].Im = 0;
        }
        else
        {
            B1[i].Re = 0;
            B1[i].Im = 0;
        }
    }
    //cout << "B1 : \n";
    //PrintF(B1, N);

    Complex RA[N];
    for(int i = 0; i < N; i++)
    {
        RA[i].Re = 0;
        RA[i].Im = 0;
    }

    Complex RB[N];
    for(int i = 0; i < N; i++)
    {
        RB[i].Re = 0;
        RB[i].Im = 0;
    }

    DFTP(RA, A1, N);
    DFTP(RB, B1, N);

    //cout << "RA: \n";
    //PrintF(RA, N);
    //cout << "RB: \n";
    //PrintF(RB, N);

    Complex C1[N];
    for(int i = 0; i < N; i++)
    {
        C1[i].Re = 0;
        C1[i].Im = 0;
    }


    Complex Mult;
    Mult.Im = 0.0;
    Mult.Re = 0.0;

    for(int i = 0; i < N; i++)
    {
        ComplexMult(RA, i, RB, i, &Mult);
        //MultC++;
        C1[i].Re = Mult.Re;
        C1[i].Im = Mult.Im;
        Mult.Im = 0.0;
        Mult.Re = 0.0;
    }

    //cout <<"\n";
    //PrintF(C1, N);

    Complex n2;
    n2.Re = N;
    n2.Im = 0;


    Mult.Im = 0.0;
    Mult.Re = 0.0;
    for(int i = 0; i < N; i++)
    {
        ComplexMult(C1, i, &n2, 0, &Mult);
        //MultC++;
        C1[i].Re = Mult.Re;
        C1[i].Im = Mult.Im;
        Mult.Im = 0.0;
        Mult.Re = 0.0;
    }
    //cout << "\n";
    //PrintF(C1, N);

    Complex f[N];
    for(int i = 0; i < N; i++)
    {
        f[i].Re = 0;
        f[i].Im = 0;
    }

    DFTO(C1, f, N);
    cout << "Свертка через Дискретное Фурье:\n";
    PrintF(f, N);
    cout << "Mult =" << MultC << "  Summ = " << SumC << endl;
}
