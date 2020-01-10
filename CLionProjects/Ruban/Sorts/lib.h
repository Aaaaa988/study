//
// Created by vladimir on 03.09.2019.
//

#ifndef SORTS_LIB_H
#define SORTS_LIB_H

#include <iostream>
#include <string>

using namespace std;

const int N = 8;

void resetArray(int* array){
    for(int i = 0; i < N; i++){
        array[i] = N-i;
    }
}

void outPutArray(int* array){
    for(int i = 0; i < N; i++){
        cout<<array[i]<<" ";
    }
    cout<<endl;
}

void outPutArray(int* array, int N){
    for(int i = 0; i < N; i++){
        cout<<array[i]<<" ";
    }
    cout<<endl;
}

void outPutArray(int* array, string str){
    cout<<"/-";
    for(int i = 0; i < N; i++){
        cout<<array[i]<<" ";
    }
    cout<<endl;
}

void outPutArray(int* array1,  int N1, int* array2,  int N2){
    cout<<"( ";
    for(int i = 0; i < N1; i++){
        cout<<array1[i]<<" ";
    }
    cout<<")";
    cout<<"( ";
    for(int i = 0; i < N2; i++){
        cout<<array2[i]<<" ";
    }
    cout<<")";
   // cout<<endl;
}

void BubbleSort(int* array, int N){
    int C = 0;
    int flag = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N-i; j++){
            C++;
            if(array[j] > array[j+1]){
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
                flag = 1;
            }
            if(!flag) break;
            outPutArray(array, "Debug");
        }
        flag = 0;
    }
    cout<<"Compare by Bubble = "<< C <<endl;
}

void SelectSort(int* array, int N){
    int C = 0;
    int flag = 0;
    for(int min = 0; min < N; min ++){
        int max = min;
        for(int j = min + 1; j < N; j++){
            C++;
            if(array[j] < array[max]){
                max = j;
                flag = 1;
            }
            if(!flag) break;
            outPutArray(array, "Debug");
        }
        flag = 0;
        int tmp = array[min];
        array[min] = array[max];
        array[max] = tmp;
    }
    cout<<"Cpmpare by Select = "<< C <<endl;
}

int* merge(int *m1, int* m2, int len_1, int len_2, int &C)
{
    outPutArray(m1, len_1, m2, len_2);
    int* ret = new int[len_1+len_2];
    int n = 0;
    // Сливаем массивы, пока один не закончится
    while (len_1 && len_2) {
        C++;
        if (*m1 < *m2) {
            ret[n] = *m1;
            m1++;
            --len_1;
        } else {
            ret[n] = *m2;
            ++m2;
            --len_2;
        }
        ++n;
    }
    // Если закончился первый массив
    if (len_1 == 0) {
        for (int i = 0; i < len_2; ++i) {
            ret[n++] = *m2++;
        }
    } else { // Если закончился второй массив
        for (int i = 0; i < len_1; ++i) {
            ret[n++] = *m1++;
        }
    }
    return ret;
}

// Функция восходящего слияния
void MergeSort(int* array, int len)
{
    int n = 1, k, ost;
    int C = 0;
    int* array1;
    int verstka = 0;
    while (n < len) {
        k = 0;
        while (k < len) {
            if (k + n >= len) break;
            if(verstka<n) {cout<<"\n"; verstka = n;}
            ost = (k + n * 2 > len) ? (len - (k + n)) : n;
            array1 = merge(array + k, array + k + n, n, ost,C);
            for (int i = 0; i < n + ost; ++i)
                array[k+i] = array1[i];
            delete [] array1;
            k += n * 2;
        }
        n *= 2;
    }
    cout<<endl<<"Compare by Merge "<<C<<endl;
}

void HelloWorld(){
    cout<<"Hello World!"<<endl;
}

#endif //SORTS_LIB_H
