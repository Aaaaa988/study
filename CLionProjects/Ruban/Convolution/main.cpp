#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int convolution(int *a, int A, int *b, int B, int *c, int C){
    cout<<"C = "<<C<<endl;
    for(int i = 0; i < C; i++){
        if (A<B){
            if (i < A){
                for(int j = 0; j <= i; j++) {
                    c[i] += b[j] * a[i-j];
                }
            }else{
                for(int j = i-A+1; j < B; j++) {
                    if(i-j < 0) break;
                    c[i] += b[j] * a[i-j];
                    //cout<<"i:"<<i<<" j:"<<j<<" i-j:"<<i-j<<endl;
                }
            }
        }else{
            if (i < B){
                for(int j = 0; j <= i; j++) {
                    c[i] += a[j] * b[i-j];
                }
            }else{
                for(int j = i-B+1; j < A; j++) {
                    if(i-j < 0) break;
                    c[i] += a[j] * b[i-j];
                    //cout<<"i:"<<i<<" j:"<<j<<" i-j:"<<i-j<<endl;
                }
            }
        }
    }
}


void initMass(int *array, int size){
    for(int i = 0; i<size; i++){
        array[i] = 0;
    }
}

void outMass(int *array, int size){
    for(int i = 0; i<size; i++){
        cout<< array[i] << " ";
    }
    cout<<endl;
}

void fillMass(int *array, int size){
    for(int i = 0; i<size; i++){
        cout<< array[i] << " ";
    }
    cout<<endl;
}

int giveNumByIndex(string str, int index){
    if (index >= str.length()) {
        return -1;
    }else{
        return str[index] - 48;
    }
}

string sumColumn(int *result, int **matrix, int C, int Matrx){
    string resultToString = "";
    int inMind = 0;
    for(int i = Matrx-1; i>=0; i--){
        result[i] = inMind;
        inMind = 0;
        for(int j = 0; j < C; j++){
            result[i] += matrix[j][i];
        }
        if (result[i] >= 10){
            inMind = result[i] / 10;
            result[i] = result[i]%10;
        }
    }

    cout<<endl;
    for(int i = 0; i < Matrx; i++){
        if(result[i] == 0 && i == 0) continue;
        cout << result[i];
        //resultToString += (char)result[i] + '0';
    }

    return resultToString;
}

int main() {
    cout << "Лабараторная по свертке" << endl;

    int A,B;
    string str_A, str_B;
    int index;

    /*cout<<"Укажите длину массива А: ";
    cin>>A;
    cout<<"Укажите длину массива B: ";
    cin>>B;*/
    cout << "Укажите число A: ";
    cin >> str_A;
    cout << "Укажите число B: ";
    cin >> str_B;
    A = str_A.length();
    B = str_B.length();

    int *a = new int[A];
    int *b = new int[B];
    int C = A+B -1;
    int Matrx = A+B;
    int *c = new int[C];
    int *result = new int[Matrx];

    int **matrix = new int*[C];
    for (int i=0; i<C; i++)
        matrix[i] = new int [Matrx];

    for (int i=0; i<C; i++){
        for(int j = 0; j < Matrx; j++){
            matrix[i][j] = 0;
            //cout<< matrix[i][j]<< " ";
        }
        //cout<<endl;
    }

    initMass(a,A);
    initMass(b,B);

    initMass(c,C);
    initMass(result,Matrx);

    for(int i = 0; i<A; i++){
        a[i] = giveNumByIndex(str_A, i);
    }
    for(int i = 0; i<B; i++){
        b[i] = giveNumByIndex(str_B, i);
    }

    cout<<"A: "; outMass(a,A);
    cout<<"B: "; outMass(b,B);

    cout<<endl;
    convolution(a,A,b,B,c,C);

    cout<<endl;
    cout<<"C: "; outMass(c,C);

    for(int i = 0; i < C; i++){
        string str = to_string(c[C-1-i]);

        for(int j = 0; j < str.length(); j++){
            matrix[i][Matrx-1-j-i] =(int) str[ str.length()-1 - j] -48;
        }

    }

    for(int i = 0; i < C; i++){
        for(int j = 0; j < Matrx; j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    string resultStr = sumColumn(result, matrix, C, Matrx);

    cout<<resultStr;

    return 0;
}
