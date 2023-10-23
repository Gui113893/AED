//
// Created by Gui113893 on 10/16/23.
//
#include <stdio.h>
int N1, N2, N3;
int f1(int n){
    if (n == 1)
        return 1;
    N1++;
    return n + f1(n/2);
}

int f2(int n){
    if (n == 1)
        return 1;
    N2+=2;
    return n + f2(n/2) + f2((n+1)/2);
}

int f3(int n){
    if (n == 1)
        return 1;
    else{
        if (n % 2 == 0){
            N3++;
            return 2*f3(n/2) + n;
        }
        N3+=2;
        return n + f3(n/2) + f3((n+1)/2);
    }
}

int main(void){
    int F1, F2, F3;
    for (int i = 1; i <= 16; i++) {
        N1 = N2 = N3 = 0;
        F1 = f1(i);
        F2 = f2(i);
        F3 = f3(i);
        printf("N: %2d | F1: %3d N1: %3d | F2: %3d N2: %3d | F3: %3d N3: %3d\n", i, F1, N1, F2, N2, F3, N3);
    }
    return 0;
}