//
// Created by Gui113893 on 10/23/23.
//

#include <stdio.h>

int adds;

int Delannoy(int m, int n){
    if (m == 0 || n == 0){
        return 1;
    }else{
        adds+=3;
        return Delannoy(m - 1, n) + Delannoy(m - 1, n - 1) + Delannoy(m, n - 1);
    }

}

int main(){
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            adds = 0;
            int d = Delannoy(i, j);
            printf("m:%2d n:%2d - %d - Adds:%2d\n", i, j, d, adds);
        }
    }
    return 0;
}