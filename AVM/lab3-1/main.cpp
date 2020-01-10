/*
#include <iostream>
#include <chrono>
#include <ctime>
#include <math.h>
#include <sys/time.h>

#define NUM_of_test 20
#define COUNT_PI 10000000

using namespace std;

struct timeval tv1, tv2, dtv;
struct timezone tz;

void time_start(){
    gettimeofday(&tv1, &tz);
}

double time_stop(){
    gettimeofday(&tv2, &tz);
    dtv.tv_sec = tv2.tv_sec - tv1.tv_sec;
    dtv.tv_usec = tv2.tv_usec - tv1.tv_usec;
    if(dtv.tv_usec < 0){
        dtv.tv_sec--;
        dtv.tv_usec+=1000000;
    }
    return dtv.tv_sec*1000+dtv.tv_usec/1000;
}

const uint64_t get_time(){
    uint32_t high, low;
    __asm__ __volatile__(
            "rdtsc\n"
            "movl %%edx, %0\n"
            "movl %%eax, %1\n"
            : "=r" (high), "=r" (low)
            :: "%rax", "%rbx", "%rcx", "%rdx"
            );
    return ((uint64_t)high << 32) | low;
}

/// __int64 r, result4;
/// r = __rdtsc();
/// s = __rdtsc();
/// result4 = s-r;

double Pi (long num){
    double result = 4.0;
    for(long i = 1; i < num; i++){
        if(i%2){
            result -= 4/(double)(2*i+1);
        }else{
            result += 4/(double)(2*i+1);
        }
    }
    return result;
}

int main() {
    cout.precision(7);
    cout<<fixed;
    cout << "Лабораторная №3" << std::endl;
    clock_t start2, stop;
    double average_Event1 = 0, average_Event2 = 0, average_Event3 = 0;
    uint64_t t1, t2, average_Event4 = 0;
    size_t  i,j;
    double rez;
    double *Event1 = new double[NUM_of_test];
    double *Event2 = new double[NUM_of_test];
    double *Event3 = new double[NUM_of_test];

    uint64_t *Event4 = new uint64_t[NUM_of_test];

    for(j = 0; j < NUM_of_test; j++){
        auto start = std:: chrono:: system_clock :: now();
        Pi(COUNT_PI);
        chrono::duration<double> dur = std::chrono::system_clock::now() - start;
        Event1[j] = dur.count();
    }
    auto start = std:: chrono:: system_clock :: now();
    Pi(COUNT_PI);
    chrono::duration<double> contr_1 = std::chrono::system_clock::now() - start;

    for(j = 0; j < NUM_of_test; j++){
        start2 = clock();
        Pi(COUNT_PI);
        stop = clock();
        Event2[j] = (double)(stop - start2)/CLOCKS_PER_SEC;
    }
    start2 = clock();
    Pi(COUNT_PI);
    stop = clock();
    double contr_2 = (double)(stop - start2)/CLOCKS_PER_SEC;

    for(j = 0; j < NUM_of_test; j++){
        time_start();
        Pi(COUNT_PI);
        rez = time_stop();
        Event3[j] = rez/1000;
    }
    time_start();
    Pi(COUNT_PI);
    rez = time_stop();
    double contr_3 = rez/1000;

    for(j = 0; j < NUM_of_test; j++){
        t1 = get_time();
        Pi(COUNT_PI);
        t2 = get_time();
        Event4[j] = t2-t1;
    }
    t1 = get_time();
    Pi(COUNT_PI);
    t2 = get_time();
    uint64_t contr_4 = t2-t1;

    for(i = 0; i < NUM_of_test; i++){
        average_Event1 += Event1[i];
        average_Event1 /= NUM_of_test;
    }
    for(i = 0; i < NUM_of_test; i++){
        average_Event2 += Event2[i];
        average_Event2 /= NUM_of_test;
    }
    for(i = 0; i < NUM_of_test; i++){
        average_Event3 += Event3[i];
        average_Event3 /= NUM_of_test;
    }
    for(i = 0; i < NUM_of_test; i++){
        average_Event4 += Event4[i];
        average_Event4 /= NUM_of_test;
    }

    cout<< "PI = " << Pi(COUNT_PI) << endl << endl;

    cout<< "Время через Chrono = " << contr_1.count() << " секунд"<< endl;
    cout<< "Абсолютная погрешность Chrono - " << fabs(average_Event1 - contr_1.count()) << endl;
    cout<< "Относительная погрешность Chrono - " << fabs((average_Event1 - contr_1.count()) / contr_1.count()) << endl;

    cout<< "Время через Clock = " << contr_2 << " секунд"<< endl;
    cout<< "Абсолютная погрешность Clock - " << fabs(average_Event2 - contr_2) << endl;
    cout<< "Относительная погрешность Clock - " << fabs((average_Event2 - contr_2) / contr_2) << endl;

    cout<< "Время через GetTimeOfDay = " << contr_3 << " секунд"<< endl;
    cout<< "Абсолютная погрешность GetTimeOfDay - " << fabs(average_Event3 - contr_3) << endl;
    cout<< "Относительная погрешность GetTimeOfDay - " << fabs((average_Event3 - contr_3) / contr_3) << endl;

    cout<< "Время через TSC = " << contr_4 << " тактов"<< endl;
    cout<< "Абсолютная погрешность TSC - " << fabs(average_Event4 - contr_4) << endl;
    cout<< "Относительная погрешность TSC - " << fabs((average_Event4 - contr_4) / contr_4) << endl;
    return 0;
}*/


#include <chrono>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <sys/time.h>


struct timeval tv1,tv2,dtv;

struct timezone tz;

void time_start() {
    gettimeofday(&tv1, &tz);
}

double time_stop(){ gettimeofday(&tv2, &tz);

    dtv.tv_sec= tv2.tv_sec -tv1.tv_sec;

    dtv.tv_usec=tv2.tv_usec-tv1.tv_usec;

    if(dtv.tv_usec<0) { dtv.tv_sec--; dtv.tv_usec+=1000000; }

    return dtv.tv_sec*1000+dtv.tv_usec/1000;

}

const uint64_t get_time(){
    uint32_t high, low;
    __asm__ __volatile__(
    "rdtsc\n"
    "movl %%edx, %0\n"
    "movl %%eax, %1\n"
    : "=r" (high), "=r" (low)
    :: "%rax", "%rbx", "%rcx", "%rdx"
    );
    return ((uint64_t)high << 32) | low;
}


double sinx(double x)
{
    double n = x;
    double sum = 0.0;
    int i = 1;

    do
    {
        sum += n;
        n *= -1.0 * x * x / ((2 * i) * (2 * i + 1));
        i++;
    }
    while (fabs(n) > 0.000000001);

    return sum;
}



int main(void){
    int x;
    clock_t start1, stop;
    double sum_of_MatO, sum_of_MatO1, sum_of_MatO2;
    uint64_t t1, t2, sum_of_MatO3;
    std::size_t i, j;
    double res;
    std::vector<double> MatO, MatO1, MatO2;
    std::vector<uint64_t> MatO3;

    std::cout << "Inpunt x: " << std::endl;
    x = 1;

    for(j = 0; j < 20; j++){
        t1 = get_time();
        for(i = 0; i < 9000000; i++)
            sinx(x);
        t2 = get_time();
        MatO3.push_back(t2-t1);
    }
    t1 = get_time();
    for(i = 0; i < 9000000; i++)
        sinx(x);
    t2 = get_time();




    for (auto& n : MatO)
        sum_of_MatO += n;
    for (auto& n : MatO1)
        sum_of_MatO1 += n;
    for (auto& n : MatO2)
        sum_of_MatO2 += n;
    for (auto& n : MatO3)
        sum_of_MatO3 += n;




    std::cout << "Sin: " << std::setprecision(30) << sinx(x) << std::endl << std::endl;

    std::cout << "Clock native(TSC): "  << t2 - t1 << " ticks " << std::endl;
    std::cout << "Абсолютная погрешность(TSC): "  << abs(sum_of_MatO3/20 - (t2 - t1))<< std::endl;
    std::cout << "Относительная погрешность(TSC): "  << abs((sum_of_MatO3/20 - (t2 - t1)) / (t2 - t1))<< std::endl << std::endl;
    return 0;
}
