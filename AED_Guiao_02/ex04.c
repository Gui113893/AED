#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void DisplayArray(double* a, size_t n){
    assert(a != NULL && n > 0);

    printf("\nArray = [ ");
    for (size_t i = 0; i < n-1; i++)
    {
        printf("%3.2f, ", a[i]);
    }
    printf("%3.2f ]\n", a[n-1]);
    
}

double* ReadArray(size_t* size_p){
    assert(size_p != NULL);

    size_t size;
    printf("Digite o número de elementos: ");
    if (scanf("%zu", &size) != 1 || size <= 0){
        *size_p = 0;
        return NULL;
    }

    double* array = (double*)malloc(size * sizeof(double));
    if (array == NULL){
        *size_p = 0;
        return NULL;
    }

    *size_p = size;

    printf("Digite os elementos da array:\n");
    for (size_t i = 0; i < size; i++)
    {
        if (scanf("%lf", &array[i]) != 1){
            free(array);
            *size_p = 0;
            return NULL;
        }
    }
    return array;
    
}

double* Append(double* array_1, size_t size_1, double* array_2, size_t size_2){
    assert(array_1 != NULL && array_2 != NULL);
    assert(size_1 > 0 && size_2 > 0);

    size_t size = size_1 + size_2;
    double* NewArray = (double*)malloc(size * sizeof(double));
    if (NewArray == NULL){
        return NULL;
    }

    for (size_t i = 0; i < size_1; i++)
    {
        NewArray[i] = array_1[i];
    }

    for (size_t j = 0; j < size_2; j++)
    {
        NewArray[j + size_1] = array_2[j];
    }
  
    return NewArray;
    
}

int main(void){
    size_t size1;

    double* Array1 = ReadArray(&size1);
    
    size_t size2;
    double* Array2 = ReadArray(&size2);
    
    size_t size = size1 + size2;

    double* Array = Append(Array1, size1, Array2, size2);
    DisplayArray(Array1, size1);
    DisplayArray(Array2, size2);
    DisplayArray(Array, size);
    
    free(Array1);
    free(Array2);
    free(Array);
    return 0;
}

