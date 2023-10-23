#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "elapsed_time.h"

int algarismos(int n){
    int algarismos = 0;

    while (n > 0)
    {
        algarismos++;
        n/=10;
    }
    return algarismos;
    
}

int soma_exp(int n, int alg){
    if (n == 0){
        return 1;
    }
    int soma = 0;
    while (n>0)
    {
        int digit = n%10;
        soma += pow(digit, alg);
        n /= 10;
    }
    return soma;
    
}

int main(){
    unsigned int start_n = 1;
    unsigned int end_n = 1000000;
    double start_time;
    double finish_time;
    double exec_time;

    start_time = cpu_time();
    

    printf("Números de Armstrong:\n");
    for (int i = start_n; i < end_n; i++)
    {
        int alg = algarismos(i);
        if (i == soma_exp(i, alg)){
            printf("%6d\n", i);
        }
    }
    finish_time = cpu_time();
    exec_time = finish_time - start_time;
    printf("Tempo = %5.5e\n", exec_time);

    return 0;
    
}


