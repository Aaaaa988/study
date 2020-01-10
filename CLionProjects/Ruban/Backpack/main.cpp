

#include <iostream>
#include <vector>

using namespace std;

const int M = 30;

const int COL = 3;
const int N = COL + 2;

int f(int Result[][N], int i)
{
    int mInf = -10000;
    int rez = 0;

    if( i < 0)
    {
        rez = mInf;
    }
    else
    {
        rez = Result[i][1];
    }
    return rez;
}


int main()
{
    int MC[COL][2];

    MC[0][0] = 3;
    MC[0][1] = 8;

    MC[1][0] = 6;
    MC[1][1] = 17;

    MC[2][0] = 8;
    MC[2][1] = 23;

    //MC[3][0] = 10;
    //MC[3][1] = 28;



    int Result[M][N];

    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(j == 0)
            {
                Result[i][j] = i;
            }
            else
            {
                Result[i][j] = 0;
            }
        }
    }



    int Max = -10000;
    int iTemp = 0;
    int temp = 0;

    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            temp = f( Result, i - MC[j][0]) + MC[j][1];
            if( temp > Max)
            {
                Max = temp;
                iTemp = j;
            }
        }

        if(Max < 0)
        {
            Result[i][1] = 0;
        }
        else
        {
            Result[i][1] = Max;

            for(int j = 0; j < COL; j++)
            {
                if( j == iTemp)
                {
                    Result[i][j + 2] = Result[i - MC[j][0]][j + 2] + 1;
                }
                else if (i - MC[j][0] < 0)
                {
                    Result[i][j + 2] = 0;
                }
                else
                {
                    Result[i][j + 2] = Result[i - MC[iTemp][0]][j + 2];
                }
            }
        }

        Max = -10000;
        iTemp = 0;
    }

    cout << "m\tC\n";
    for(int i = 0; i < COL; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            cout << MC[i][j] <<"\t";
        }
        cout << endl;
    }

    cout << "\nM = " << M - 1<< endl;

    cout << "\nX \tSum 1\t2 \t3\t\n";

    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cout << Result[i][j] << "\t";
        }
        cout << endl;
    }
}
