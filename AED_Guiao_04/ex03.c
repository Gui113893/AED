#include <stdio.h>

int NCOMPS;

int test_Array(int* array, int size){
    int nTernos = 0;

    for (int i = 0; i < size-2; i++)
    {
        for (int j = i+1; j < size-1; j++) {
            for (int k = j + 1; k < size; k++) {
                NCOMPS++;
                if (array[k] == array[i] + array[j]) {
                    nTernos++;
                }
            }
        }
    }
    return nTernos;
}

int main(void){
    int array1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int array2[] = {1, 2, 1, 4, 5, 6, 7, 8, 9, 10};
    int array3[] = {1, 2, 1, 3, 2, 6, 7, 8, 9, 10};
    int array4[] = {0, 2, 2, 0, 3, 3, 0, 4, 4, 0};
    int array5[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int array6[] = {0, 2, 2, 0, 3, 3, 0, 4, 4, 0, 1, 2, 1, 4, 5, 6, 7, 8, 9, 10};
    int array7[] = {0, 2, 2, 0, 3, 3, 0, 4, 4, 0, 1, 2, 1, 4, 5, 6, 7, 8, 9, 10, 0, 0, 0, 0, 0, 19, 0, 0, 0, 0, 1, 2, 1, 4, 5, 6, 7, 8, 9, 10};
    int* arrays[] = {array1, array2, array3, array4, array5, array6, array7};
    int array_size[] = {10, 10, 10, 10, 10, 20, 40};

    int n;
    for (int i = 0; i < 7; i++)
    {
        NCOMPS = 0;
        n = test_Array(arrays[i], array_size[i]);
        printf("Array%d : Nº Ternos = %4d : %5d Comparações\n", i+1, n, NCOMPS);
    }
    

    return 0;
}