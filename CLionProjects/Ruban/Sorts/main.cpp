#include <iostream>
#include "lib.h"

int main() {
    HelloWorld();

    int* array = new int[N];
    /*-------Bubble-------*/
    cout<<"Начальный массив"<<endl;
    resetArray(array);
    outPutArray(array);
    BubbleSort(array, N);
    cout<<"Отсортированный массив"<<endl;
    outPutArray(array);
    /*-------Select-------*/
    cout<<endl;
    cout<<"Начальный массив"<<endl;
    resetArray(array);
    outPutArray(array);
    SelectSort(array, N);
    cout<<"Отсортированный массив"<<endl;
    outPutArray(array);
    /*-------Merge--------*/
    cout<<endl;
    cout<<"Начальный массив"<<endl;
    resetArray(array);
    outPutArray(array);
    MergeSort(array, N);
    cout<<"Отсортированный массив"<<endl;
    outPutArray(array);
    return 0;
}