// Быстрое умножение чисел

#include <iomanip>
#include "FastAlgoritmh.h"

int p[1000] {}, r[3][1000] {};

void output();
void input(string&, string&);
void prints(string, string);

int main() {

    string a, b;

    output();
    input(a, b);

    string result = mult(a, b);
    while (result[0] == '0' && result.length() > 1) {
        result = result.substr(1, result.length());
    }

    cout << endl << result << endl;

    cout<<"Cчетчик разрядных умножений и переполнений:"<<endl;
    cout << " N  -  + ++"<< endl;
    for (int i = 1; i < a.length() + 1; i++) {
        if(r[1][i] == 0 && r[2][i] == 0 && p[i] == 0) continue;
        cout <<setw(2)<<  i  << " " <<setw(2)<< p[i] << " " <<setw(2)<< r[1][i+1] << " " <<setw(2)<< r[2][i+1] << endl;
    } cout << endl;

    return 0;
}

void output() {
    cout << endl
    << endl
    << "Введите два числа" << endl;
}

void input(string &a, string &b) {
    cout << "Первое число = "; cin >> a;
    cout << "Второе число = "; cin >> b;
}

void prints(string a, string b) {
    cout << endl
    << a << endl
    << b << endl;
}
