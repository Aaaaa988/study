#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

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
        for(int i = 0; i < 2; i++){
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
            if(M[i][j] != -1){
                cout<<setw(2)<< M[i][j] <<" ";
            }else{
                cout<< " ∞" <<" ";
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

struct Edge{
    int A;
    int B;
    int Way;
};


/*void printEdge(Edge* A, int N){
    cout<<endl;
    for(int j = 0; j < N; j++){
        cout<< A[j].Way <<" ";
    }
    cout<<endl;
}*/

void printEdge(Edge* A, int N){

    for(int i = 0; i<N; i++){
            cout<<"("<<A[i].A+1<<";"<<A[i].B+1<<") = "<< A[i].Way<<endl;
    }
    cout<<endl;
}



int summ(int N){
    int sum = 0;
    for(int i = 1; i <= N; i++){
        sum += i;
    }
    return sum;
}

void SelectSort(Edge* array, int N){
    for(int min = 0; min < N; min ++){
        int max = min;
        for(int j = min + 1; j < N; j++){
            if(array[j].Way < array[max].Way){
                max = j;
            }
        }
        Edge tmp = array[min];
        array[min] = array[max];
        array[max] = tmp;
    }
}

int numOfInf(int **M, int N){
    int num = 0;
    for(int i = 1; i<N; i++){
        for(int j = 0; j<i; j++){
            if(M[i][j] == -1)
            num++;
        }
    }
    return num;
}

bool minOstovReady(int *D, int N){
    for (int i = 0; i < N; i++) {
        if (D[i] == 0)
            return false;
    }
    return true;
}

void Kraskal(int **M, int N){
    int downDiagNum = N*N - summ(N);
    downDiagNum -= numOfInf(M,N);
    Edge *Vertex = new Edge[downDiagNum];
    Edge *MinOstov = new Edge[N-1];
    int *Esc = new int[N-1];
    for(int i = 0; i < N-1; i++) Esc[0] = 0;
    int index = 0;
    for(int i = 1; i<N; i++){
        for(int j = 0; j<i; j++) {
            if (M[i][j] != -1) {
                Vertex[index].A = i;
                Vertex[index].B = j;
                Vertex[index].Way = M[i][j];
                index++;
            }
        }
    }

    cout<<"Все ребра графа"<<endl;
    printEdge(Vertex,downDiagNum);
    SelectSort(Vertex,downDiagNum);
    cout<<"Отсортированные ребра графа"<<endl;
    printEdge(Vertex,downDiagNum);

    cout<<"Процесс построения дерева"<<endl;
    index=0;
    for(int i = 0; i<18; i++){
        if(Esc[Vertex[i].A] == 1 && Esc[Vertex[i].B] == 1){
            cout<<"//("<<Vertex[i].A+1<<";"<<Vertex[i].B+1<<") = "<< Vertex[i].Way <<" - не подходит"<<endl;
        }else{
            MinOstov[index] = Vertex[i];
            cout<<"("<<Vertex[i].A+1<<";"<<Vertex[i].B+1<<") = "<< Vertex[i].Way <<" - подходит"<<endl;
            index++;
            Esc[Vertex[i].A] = 1;
            Esc[Vertex[i].B] = 1;
        }

    }
    int Weight = 0;
    for(int i = 0; i<N-1; i++)
        Weight += MinOstov[i].Way;
    cout<<"Вес минимального Остовного дерева = "<< Weight <<endl;

+++++++}

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
    }
    fin.close();

    cout<<"Размерность N = "<<N<<endl<<endl;

    int **Matrix=nullptr;
    initMatrix(Matrix,N);
    readToMatrix(Matrix,N);

    cout<<"Исходная матрица";
    printMatrix(Matrix,N);

    Kraskal(Matrix,N);

    return 0;
}