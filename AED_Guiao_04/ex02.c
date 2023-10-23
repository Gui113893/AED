#include <stdio.h>

int NOPS;

int test_Array(int* array, int size){
    double r = array[1] / array[0];
    NOPS++;

    for (int i = 2; i < size; i++)
    {
        NOPS++;
        if (array[i] != r*array[i-1]){
            return 0;
        }
    }
    
    return 1;

}

int main(void){
    int array1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int array2[] = {1, 2, 4, 4, 5, 6, 7, 8, 9, 10};
    int array3[] = {1, 2, 4, 8, 5, 6, 7, 8, 9, 10};
    int array4[] = {1, 2, 4, 8, 16, 6, 7, 8, 9, 10};
    int array5[] = {1, 2, 4, 8, 16, 32, 7, 8, 9, 10};
    int array6[] = {1, 2, 4, 8, 16, 32, 64, 8, 9, 10};
    int array7[] = {1, 2, 4, 8, 16, 32, 64, 128, 9, 10};
    int array8[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 10};
    int array9[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
    int* arrays[] = {array1, array2, array3, array4, array5, array6, array7, array8, array9};

    int res;
    for (int i = 0; i < 9; i++)
    {
        NOPS = 0;
        res = test_Array(arrays[i], 10);
        printf("Array%d : Resultado = %d : %2d Operações\n", i+1, res, NOPS);
    }
    return 0;
}
