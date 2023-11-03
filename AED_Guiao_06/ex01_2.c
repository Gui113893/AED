//
// Created by Gui113893 on 10/23/23.
//

#include <stdio.h>
int adds;

int D(int m, int n) {
    int array[m + 1][n + 1];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                array[i][j] = 1;
            } else {
                adds+=3;
                array[i][j] = array[i - 1][j] + array[i - 1][j - 1] + array[i][j - 1];
            }
        }
    }
    return array[m][n];
}


int main(){
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            adds = 0;
            int d = D(i, j);
            printf("m: %2d n: %2d - %d Adds: %2d\n", i, j, d, adds);
        }
    }
    return 0;
}