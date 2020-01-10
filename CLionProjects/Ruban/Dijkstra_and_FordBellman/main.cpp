#include <iostream>
#include <fstream>
#include <iomanip>

#define inf 2147483647

using namespace std;

int chToInt(char ch){
    return (int)ch-48;
}

void initMatrix(int** &M, int N){
    M = new int *[N];
    for(int i = 0; i<N; i++){
        M[i] = new int[N];
    }
    for(int i = 0; i<N; i++)
        for(int j = 0; j<N; j++)
            M[i][j] = 0;
}

void readToMatrix(int** &M, int N){
    ifstream fin;
    fin.open("../matrix.txt");
    string str;
    if(!fin.is_open()){
        cout<<"Проблемка с файлом";
    }else{
        for(int i = 0; i < 4; i++){
            fin.get();
        }
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                fin >> str;
                M[i][j] = atoi(str.c_str());
            }
        }
    }
    fin.close();
}

void printMatrix(int** &M, int N){
    cout<<endl;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(M[i][j] != -666){
                cout<<setw(2)<< M[i][j] <<" ";
            }else{
                cout<< " -" <<" ";
            }

        }
        cout<<endl;
    }
}

void printArray(int* &A, int N){
    cout<<endl;
    for(int j = 0; j < N; j++){
        cout<< A[j] <<" ";
    }
    cout<<endl;
}

void printTablet(int* Way, int W, int* &D, int N){
    for(int i=0; i<N; i++){

        if(Way[i] != -1) {
            cout << "{" << Way[i] << "}";
        }else{
            cout<<"   ";
        }
    }
    if(W != -1){
        cout<<"| "<< W <<" |"; cout <<" "<<setw(2)<<D[W]<< " | ";
    }else{
        cout<<"| - |"; cout <<"  - | ";
    }
    for(int j = 0; j < N; j++){
        cout<<setw(2)<< D[j] <<" | ";
    }
    cout<<endl;
}

int indexOfMinEl(int* &D,int N,int *Esc){
    int min = inf;
    int index = -1;
    for(int i = 0; i < N; i++) {
        if(Esc[i] == 1) continue;
        if (min > D[i]) {
            min = D[i];
            index = i;
        }
    }
    Esc[index] = 1;
    return index;
}

int min(int a, int b){
    if (a<b){
        return a;
    }else{
        return b;
    }
}

void Dijkstra(int** M, int N, int Start){
    int *D = new int[N];
    int *Esc = new int[N];
    int *Way = new int[N];
    int W;
    for(int i = 0; i < N; i++) Way[i] = -1;
    for(int j = 0; j < N; j++){
        D[j] = M[Start][j];
    }
    cout<<"Исходный массив";
    printArray(D,N);
    Esc[Start] = 1;
    Way[0] = Start;
    cout<<"Таблица"<<endl;
    cout<<"|      S       | W |D(w)|"; for(int i = 0; i<N; i++) cout<<"D("<<i<<")|";
    cout<<endl;
    printTablet(Way,-1,D,N);
   for(int j = 1; j < N; j ++){
        W = indexOfMinEl(D,N,Esc);
        Way[j] = W;
        for(int i = 0; i < N; i++) {
            if(Esc[i] == 1) continue;
            if(M[W][i] == -666){
                D[i] = D[i];
            }else{
                D[i] = min(D[i],D[W]+M[W][i]);
            }
        }
       printTablet(Way,W,D,N);
    }
    cout<<"Итоговый массив";
    printArray(D,N);
}

bool compareArrays(int *D1, int* D, int N){
    for (int i = 0; i < N; i++) {
        if (D1[i] != D[i])
            return false;
    }
    return true;
}

void FordBellman(int** M, int N, int Start){
    int *D = new int[N];
    int *D1 = new int[N];
    int min = 0;

    for(int j = 0; j < N; j++){
        D[j] = M[Start][j];
        D1[j] = 0;
    }
    cout<<"D(0)"<<endl;
    for(int i = 0; i<N; i++){
        if(D[i] != 0){
            cout <<"∞ ";
        }else{
            cout<< "0 ";
        }
    }
    cout<<endl;
    cout<<"D(1)";
    printArray(D,N);
    for(int o = 2; 1; o++) {
        for (int j = 0; j < N; j++) {
            min = inf;
            for (int i = 0; i < N; i++) {
                if ( M[i][j] == -666) continue;
                if (min > D[i] + M[i][j])
                    min = D[i] + M[i][j];
            }
            if (j == Start) continue;
            D1[j] = min;
        }
        cout<<"D("<<o<<")";
        printArray(D1,N);
        if(compareArrays(D1,D,N)) break;
        for (int i = 0; i < N; i++) {
            D[i] = D1[i];
        }
    }

}

int main() {
    int a = inf;
    char ch;
    int N, Start;
    std::cout << a << std::endl;
    ifstream fin;
    fin.open("../matrix.txt");

    if(!fin.is_open()){
        cout<<"Здесь открытие файлов запрещенна, программу вырубай!";
        return -1;
    }else{
        cout<<"Открыт файл\n";
            fin.get(ch);
        N = chToInt(ch);
            fin.get(ch);
            fin.get(ch);
        Start = chToInt(ch) - 1;
    }
    fin.close();

    cout<<"Размерность N = "<<N<<endl;
    cout<<"Стартовая точка  = "<< Start<<endl;

    int **Matrix=nullptr;
    initMatrix(Matrix,N);
    readToMatrix(Matrix,N);

    cout<<"Исходная матрица"<<endl;
    printMatrix(Matrix,N);

   // cout<<"Метод Дейкстры"<<endl;
    //Dijkstra(Matrix,N,Start);
    //cout<<endl<<endl;
    cout<<"Метод Форд-Беллмана"<<endl;
    FordBellman(Matrix,N,Start);

    return 0;
}

/*
 *
5
1
0 25 15 3 2
25 0 8 -666 -666
15 8 0 4 -666
3 -666 4 0 3
2 -666 -666 3 0
 */