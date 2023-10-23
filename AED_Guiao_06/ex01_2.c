//
// Created by Gui113893 on 10/23/23.
//

#include <stdio.h>
int D(int m, int n) {
    int array[m + 1][n + 1];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                array[i][j] = 1;
            } else {
                array[i][j] = D(i - 1, j) + D(i - 1, j - 1) + D(i, j - 1);
            }
        }
    }
    return array[m][n];
}


int main(){
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 15; j++) {
            int d = D(i, j);
            printf("m - %2d n - %2d- %d\n", i, j, d);
        }
    }
    return 0;
}