//
// Created by Gui113893 on 11/3/23.
//
#include <stdio.h>

#define SIZE 100

int globalArray[SIZE];

void initializeArray(void){
    for (int i = 0; i < SIZE; i++) {
        globalArray[i] = 0;
    }
}


int max(int a, int b){
    if (a == b) return a;
    return a > b ? a : b;
}


int recursiveV(int n, int* array){
    if (n == 0) return 0;
    else if (n == 1) return array[1];
    else return max(array[n] + recursiveV(n-2, array), recursiveV(n-1, array));
}

int iterativeV(int n, int* array){
    int localArray[n+1];
    for (int i = 0; i <= n; i++) {
        if (i == 0) localArray[0] = 0;
        else if (i == 1) localArray[1] = array[1];
        else localArray[i] = max(array[i] + localArray[i-2], localArray[i-1]);
    }
    return localArray[n];
}

int memoizationV(int n, int* array){
    if (globalArray[n] != 0) return globalArray[n];
    int r;
    if (n == 0) r = 0;
    else if (n == 1) r = array[1];
    else r = max(array[n] + recursiveV(n-2, array), recursiveV(n-1, array));
    globalArray[n] = r;
    return r;
}


int main() {
    initializeArray();
    int array[] = {5, 1, 2, 10, 6, 2, 5, 1, 2, 10, 6, 2,
                   5, 1, 2, 10, 6, 2, 5, 1, 2, 10, 6, 2,
            5, 1, 2, 10, 6, 2, 5, 1, 2, 10, 6, 2,
            5, 1, 2, 10, 6};
    int recursive_V = recursiveV(40, array);
    int iterative_V = iterativeV(40, array);
    int memoization_V = memoizationV(40, array);

    printf("Recursive: V(%d) = %d\n", 40, recursive_V);
    printf("Iterative: V(%d) = %d\n", 40, iterative_V);
    printf("Memoization: V(%d) = %d\n", 40, memoization_V);

    return 0;
}