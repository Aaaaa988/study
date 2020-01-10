#include <iostream>

#define DEBUG_MODE 0
using namespace std;

int T1, T2, T = 0;
int i, j, k, n;

int T11,T12;

long **addsub(long **A, long **B, int n, int k)
{
    long **C = new long *[n];
    for (i = 0; i < n; i++)
    {
        C[i] = new long [n];
        for (j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + k * B[i][j];
            T1++;
        }
    }
    return C;
}

long **FastMM(long **A, long **B,  int n)
{
    int hn = n / 2;

    long **C = new long *[n];
    for (i = 0; i < n; i++)
        C[i] = new long [n];

    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        T2++;
        return C;
    }
    else
    {
        long ***Ak = new long **[4];
        long ***Bk = new long **[4];
        long ***Ck = new long **[4];

        long **rA = new long *[n];
        long **rB = new long *[n];

        for (i = 0; i < n; i++)
        {
            rA[i] = A[i] + hn;
            rB[i] = B[i] + hn;
        }

        for (i = 0; i < 4; i++)
        {
            if (!(i % 2))
            {
                Ak[i] = A;
                Bk[i] = B;
            }
            else
            {
                Ak[i] = rA;
                Bk[i] = rB;
            }

            if (i >= 2)
            {
                Ak[i] += hn;
                Bk[i] += hn;
            }
        }



        if(DEBUG_MODE){
        for (k = 0; k < 4; k++)
        {
            cout << "A" << k << endl;
            for (i = 0; i < hn; i++)
            {
                for (j = 0; j < hn; j++)
                {
                    cout.width(5);
                    cout << Ak[k][i][j];
                }
                cout << endl;
            }
            cout << endl;
        }
        cout << endl;

        for (k = 0; k < 4; k++)
        {
            cout << "B" << k << endl;
            for (i = 0; i < hn; i++)
            {
                for (j = 0; j < hn; j++)
                {
                    cout.width(5);
                    cout << Bk[k][i][j];
                }
                cout << endl;
            }
            cout << endl;
        }
        }
        long ***M = new long **[7];
        M[0] = FastMM(addsub(Ak[1], Ak[3], hn, -1), addsub(Bk[2], Bk[3], hn, 1), hn);
        M[1] = FastMM(addsub(Ak[0], Ak[3], hn, 1), addsub(Bk[0], Bk[3], hn, 1), hn);
        M[2] = FastMM(addsub(Ak[0], Ak[2], hn, -1), addsub(Bk[0], Bk[1], hn, 1), hn);
        M[3] = FastMM(addsub(Ak[0], Ak[1], hn, 1), Bk[3], hn);
        M[4] = FastMM(Ak[0], addsub(Bk[1], Bk[3], hn, -1), hn);
        M[5] = FastMM(Ak[3], addsub(Bk[2], Bk[0], hn, -1), hn);
        M[6] = FastMM(addsub(Ak[2], Ak[3], hn, 1), Bk[0], hn);
        Ck[0] = addsub(addsub(addsub(M[0], M[1], hn, 1), M[3], hn, -1), M[5], hn, 1);
        Ck[1] = addsub(M[3], M[4], hn, 1);
        Ck[2] = addsub(M[5], M[6], hn, 1);
        Ck[3] = addsub(addsub(addsub(M[1], M[2], hn, -1), M[4], hn, 1), M[6], hn, -1);

        for (i = 0; i < hn; i++)
        {
            for (j = 0; j < hn; j++)
            {
                C[i][j] = Ck[0][i][j];
                C[i][j + hn] = Ck[1][i][j];
                C[i + hn][j] = Ck[2][i][j];
                C[i + hn][j + hn] = Ck[3][i][j];
            }
        }
        return C;
    }
}

long **SlowlyMM(long **A, long **B, int n)
{
    long **C = new long *[n];
    for (i = 0; i < n; i++)
    {
        C[i] = new long [n];
        for (j = 0; j < n; j++)
            C[i][j] = 0;
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            for (k = 0; k < n; k++)
            {
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
                T11++;
                T12++;
            }
    }
    return C;
}

int Init(long **A, long **B, int nn, int bufn, int flag) {
    for (i = 0; i < bufn; i++) {
        A[i] = new long[100000];
        B[i] = new long[100000];
    }
    for (i = 0; i < nn; i++) {
        for (j = 0; j < nn; j++) {
            A[i][j] = -1 * j;
            B[i][j] = i + j;
        }
    }
    if (flag == 1)
    {
        for (i = 0; i < n; i++)
        {
            for (j = n; j < bufn; j++)
            {
                A[i][j] = 0;
                B[i][j] = 0;
            }
        }
        for (i = n; i < bufn; i++)
        {
            for (j = 0; j < bufn; j++)
            {
                A[i][j] = 0;
                B[i][j] = 0;
            }
        }
        n = bufn;
    }

    if(DEBUG_MODE){
        cout << "Матрица A: " << endl;
        for (i = 0; i < n; i++) {
        cout.width(5);
        cout << "| " << A[i][0];
        for (j = 1; j < n - 1; j++) {
            cout.width(5);
            cout << A[i][j];
        }
        cout.width(5);
        cout << A[i][n - 1] << " |";
        cout << endl;
         }
        cout << endl;

        cout << "Матрица B: " << endl;
        for (i = 0; i < n; i++) {
        cout.width(5);
        cout << "| " << B[i][0];
        for (j = 1; j < n - 1; j++) {
            cout.width(5);
            cout << B[i][j];
        }
        cout.width(5);
        cout << B[i][n - 1] << " |";
        cout << endl;
        }
        cout << endl;
    }
}

int Output(long **C)
{
    cout << "Матрица C:" << endl;
    if (n < 16)
    {
        for (i = 0; i < n; i++)
        {
            cout.width(5);
            cout << "| " << C[i][0];
            for (j = 1; j < n - 1; j++)
            {
                cout.width(5);
                cout << C[i][j];
            }
            cout.width(5);
            cout << C[i][n - 1] << " |";
            cout << endl;
        }
    }
    else
    {
        for (i = 0; i < 4; i++)
        {
            cout.width(5);
            cout << "| " << C[i][0];
            for (j = 1; j < 4; j++)
            {
                cout.width(8);
                cout << C[i][j];
            }
            cout << "    ...";
            cout.width(8);
            cout << C[i][n - 1] << " |";
            cout << endl;
        }

        cout << "   |  ...";
        for (i = 1; i < 5; i++)
            cout << "     ...";
        cout << "     ... |";
        cout << endl;

        cout.width(5);
        cout << "| " << C[i][0];
        for (j = 1; j < 4; j++)
        {
            cout.width(8);
            cout << C[n - 1][j];
        }
        cout << "    ...";
        cout.width(8);
        cout << C[n - 1][n - 1] << " |";
        cout << endl;
    }
    cout << endl;
}

int main()
{
    cout << "Введите размер матриц n = ";
    cin >> n;
    long **A = new long *[10000];
    long **B = new long *[10000];
    long **C = new long *[10000];
    Init(A, B, n, n, 0);

    C = SlowlyMM(A, B, n);
    cout << "Количество сложений: " << T11 << endl;
    cout << "Количество умножений: " << T12 << endl;
    T = T11 + T12;
    cout << "Трудоёмкость T (по формуле обычного умножения) = " << T << endl;
    Output(C);

    int bufn = 1;
    while (bufn < n)
        bufn <<= 1;
    Init(A, B, n, bufn, 0);
    T = 0;
    C = FastMM(A, B, bufn);
    cout << "Количество сложений: " << T1 << endl;
    cout << "Количество умножений: " << T2 << endl;
    T = T1 + T2;
    cout << "Трудоёмкость T (по формуле быстрого умножения) = " << T << endl;
    Output(C);
    return 0;
}
