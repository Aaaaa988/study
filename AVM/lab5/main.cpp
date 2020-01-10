#include <pthread.h>
#include <cstdio>
#include <cstdlib>
#include <chrono>


typedef struct range_tag {
    int id;
    int A;
    int B;
    int ArraySize;
    int *Vector;
    int *VectorResult;
    int **Matrix;
} range_t;


void *initArray(void *threadRange)
{
    range_t tid;
    tid = *(range_t *)threadRange;
    printf("THREAD #%ld! Range A = %ld! Range B = %ld!\n",tid.id, tid.A, tid.B);

    for(int i = tid.A; i <= tid.B; i++){
        for(int j = 0; j < tid.ArraySize; j++)
            tid.Matrix[j][i] = 1;
        tid.Vector[i] = 1;
    }

    pthread_exit(NULL);
}

void *multiArray(void *threadRange)
{
    range_t tid;
    tid = *(range_t *)threadRange;
    printf("THREAD #%ld multiplaing!\n",tid.id);

    int result = 0;
    for(int i = tid.A; i <= tid.B; i++){
        for(int j = 0; j < tid.ArraySize; j++)
            result+=tid.Vector[j]*tid.Matrix[j][i];
        tid.VectorResult[i] = result;
    }

    pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
    pthread_t *threads = NULL;
    range_t *range = NULL;

    int num_of_threads = 0;
    int size_of_arrays = 0;

    printf("Сколько потоков = ");
    scanf("%d", &num_of_threads);
    printf("Размерность матрицы в тысячах = ");
    scanf("%d", &size_of_arrays);
    size_of_arrays*=1000;
    auto start = std:: chrono:: system_clock :: now();
    int *Vector = (int *)malloc(size_of_arrays*sizeof(int *));
    int *VectorResult = (int *)malloc(size_of_arrays*sizeof(int *));

    int **Matrix = (int **)malloc(size_of_arrays*sizeof(int *));
    for(int i = 0; i < size_of_arrays; i++) {
        Matrix[i] = (int *)malloc(size_of_arrays*sizeof(int));
    }

    threads = (pthread_t*)malloc(sizeof(pthread_t)*num_of_threads);
    range = (range_t*)malloc(sizeof(range_t)*num_of_threads);

    int t;

    if(num_of_threads > size_of_arrays) {
        printf("Количество потоков не может быть больше чем размерность массива, покайся!");
        return -1;
    }

    int ceil = (int)size_of_arrays / num_of_threads;
    int floor = size_of_arrays % num_of_threads;

    range[0].id = 1;
    range[0].A = 0;
    range[0].B = ceil - 1;
    if(floor > 0) {
        range[0].B++;
        floor--;
    }
    range[0].ArraySize = size_of_arrays;
    range[0].Matrix = Matrix;
    range[0].Vector = Vector;
    range[0].VectorResult = VectorResult;



    for(t=1; t<num_of_threads; t++){
        range[t].id = t+1;
        range[t].A = range[t-1].B + 1;
        range[t].B = range[t].A + ceil - 1;
        if(floor > 0) {
            range[t].B++;
            floor--;
        }
        range[t].ArraySize = size_of_arrays;
        range[t].Matrix = Matrix;
        range[t].Vector = Vector;
        range[t].VectorResult = VectorResult;
    }

    int rc;
    for(t=0; t<num_of_threads; t++){
        printf("In main: creating thread for initialisation %ld\n", t);
        rc = pthread_create(&threads[t], NULL, initArray, (void *)&range[t]);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
        }
    }

    for(int i=0; i < num_of_threads; i++)
    pthread_join(threads[i], NULL);

    for(t=0; t<num_of_threads; t++){
        printf("In main: creating thread for multiply %ld\n", t);
        rc = pthread_create(&threads[t], NULL, multiArray, (void *)&range[t]);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
        }
    }

    for(int i=0; i < num_of_threads; i++)
        pthread_join(threads[i], NULL);

    /*printf("\nВектор\n");
    for(int i=0; i < size_of_arrays; i++){
        printf("%d ",Vector[i]);
    }
    printf("\n");
    printf("\nМатрица\n");
    for(int i=0; i < size_of_arrays; i++){
        for(int j=0; j < size_of_arrays; j++)
            printf("%d ",Matrix[i][j]);
        printf("\n");
    }*/

    printf("\nРезультирующий вектор\n");
    for(int i=0; i < size_of_arrays; i++){
        printf("%d ",VectorResult[i]);
        // printf("\n");
    }

    std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
    printf("\nВремя работы = %f", dur.count());
    pthread_exit(NULL);
}