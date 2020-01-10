#include <iostream>
#include <iomanip>


using namespace std;

void Print( int **jm, int n, int Up, int Down);

int main() {

    int i, j, M;
    int n = 8;
    int StatR[] = {3, 8, 8, 10, 3, 3, 3, 3, 3};
    int *r = new int [n + 1];

    cout<<"M:\n";
    for(int i = 0; i < n; i++){
        cout<<"["<<StatR[i]<<" x "<<StatR[i+1]<<"]";
        cout<<endl;
    }

    for(i = 0; i < n+1; ++i)
        r[i] = StatR[i];

    int **f = new int *[n];

    for(i = 0; i < n; ++i) {
        f[i] = new int [n];
        for(j = 0; j < n; ++j)
            f[i][j] = -1;
    }
    for(i = 0; i < n; ++i)
        f[i][i] = 0;

    int t, k, Temp;
    int **jm = new int *[n];

    for(i = 0; i < n; ++i) {
        jm[i] = new int [n];
        for(j = 0; j < n; ++j)
            jm[i][j] = -1;
    }

    cout << "Трудоёмкости:" << endl;
    for(int i = 0; i < n; i++){
        cout << " f["<<i+1<<","<<i+1<<"] = " << 0 << endl;
    }

    for(t = 1; t < n; ++t) {
        for(k = 0; k < n-t; ++k) {
            jm[k][k+t] = k;
            f[k][k+t] = f[k][k] + f[k+1][k+t] + r[k]*r[k+1]*r[k+t+1];
            for(j = k ; j < k+t; ++j) {
                cout << " f[" << k+1 << "," << k+t+1 << "] = (f[" << k+1 << "," << j+1 << "]+ f[" << j+1+1 << "," << k+t+1 << "] + " << r[k] << " * " << r[j+1] << " * " <<  r[k+t+1] << ") = " << f[k][j]+f[j+1][k+t]+r[k]*r[j+1]*r[k+t+1] << endl;
                Temp = f[k][j] + f[j+1][k+t] + r[k]*r[j+1]*r[k+t+1];
                if(Temp < f[k][k+t]) {
                    jm[k][k+t] = j;

                    f[k][k+t] = Temp;
                }

            }
            cout << " f[" << k+1 << "," << k+t+1 << "] = min = " << f[k][k+t] << endl;
        }

    }

    cout << endl;

    cout << endl;
    for(i = 0; i < n; ++i) {
        for(j = 0; j < n; ++j)
        cout << setw(5) << f[i][j]  << setw(4) << "   ";
        cout << endl;
    }

   /* cout << endl;
    cout << " Определяем приоритетность для наших матриц:" << endl;

    for(i = 0; i < n; ++i) {
        for(j = 0; j < n; ++j)
            cout << setw(3) << jm[i][j] << setw(3) << " ";
        cout << endl;
    }*/

    cout << endl;
    cout << "Скобки:" << endl;
    Print(jm, n, 0, n-1);
    cout << endl;
    return 0;
}

void Print( int **jm, int n, int Up, int Down) {
    switch(Down - Up) {
        case 0: {
            cout << " M[" << Up+1 << "] ";
            return;
        }
        case 1: {
            cout << "( ";
            cout << "M[" << Up+1 << "] x M[" << Down+1 << "]";
            cout << " )";
            return;
        }
        default: {
            cout << "( ";
            Print(jm, n, Up, jm[Up][Down]);
            Print(jm, n, jm[Up][Down] + 1, Down);
            cout << " )";
            return;
        }
    }
}
