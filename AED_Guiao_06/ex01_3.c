//
// Created by Gui113893 on 10/23/23.
//

#include <stdio.h>
#define SIZE 100
int adds;

int array[SIZE][SIZE];

void initializeArray(void){
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            array[i][j] = -1;
        }
    }
}

int D(int m, int n){
    if (array[m][n] != -1){
        return array[m][n];
    }
    int r;
    if (m == 0 || n == 0) {
        r = 1;
    }else{
        adds+=3;
        r = D(m - 1, n) + D(m - 1, n - 1) + D(m, n - 1);
    }
    array[m][n] = r;
    return r;
}
int main(){
    initializeArray();
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            adds = 0;
            int d = D(i, j);
            printf("m: %2d n: %2d - %d - Adds:%2d\n", i, j, d, adds);
        }
    }
}