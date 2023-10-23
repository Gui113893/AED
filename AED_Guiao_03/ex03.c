#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "elapsed_time.h"

int fatorial(int n){
    if (n <= 1){
        return 1;
    }else{
        return n * fatorial(n-1);
    }
}

int soma_fat(int n, int* array){
    if (n == 0){
        return 1;
    }
    int soma = 0;
    while (n>0)
    {
        int digit = n%10;
        soma += array[digit];
        n /= 10;
    }
    return soma;
    
}

int main(){
    unsigned int start_n = 1;
    unsigned int end_n = 100000;
    double start_time;
    double finish_time;
    double exec_time;

    start_time = cpu_time();
    int* array = (int*)malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++)
    {
        array[i] = fatorial(i);
    }
    
    printf("Fatoriões:\n");
    for (int i = start_n; i < end_n; i++)
    {
        if (i == soma_fat(i, array)){
            printf("%10d\n", i);
        }
    }
    finish_time = cpu_time();
    exec_time = finish_time - start_time;
    printf("Tempo = %5.5e\n", exec_time);
    free(array);

    return 0;
    
}

