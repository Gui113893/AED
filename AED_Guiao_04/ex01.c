#include <stdio.h>

int NCOMPS;

int test_Array(int* array, int size){
    int nElem = 0;

    for (int i = 1; i < size - 1; i++)
    {
        NCOMPS++;
        if (array[i] == array[i-1] + array[i+1]){
            nElem++;
        }
    }

    return nElem;
}

int main(void){
    int array1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int array2[] = {1, 2, 1, 4, 5, 6, 7, 8, 9, 10};
    int array3[] = {1, 2, 1, 3, 2, 6, 7, 8, 9, 10};
    int array4[] = {0, 2, 2, 0, 3, 3, 0, 4, 4, 0};
    int array5[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int* arrays[] = {array1, array2, array3, array4, array5};

    int n;
    for (int i = 0; i < 5; i++)
    {
        NCOMPS = 0;
        n = test_Array(arrays[i], 10);
        printf("Array%d : %d Elementos : %d Comparações\n", i+1, n, NCOMPS);
    }
}