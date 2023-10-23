//
// Created by Gui113893 on 10/23/23.
//

#include <stdio.h>

int Delannoy(int m, int n){
    if (m == 0 || n == 0){
        return 1;
    }else{
        return Delannoy(m - 1, n) + Delannoy(m - 1, n - 1) + Delannoy(m, n - 1);
    }

}



int main(){
    for (int i = 0; i < 15; i++) {
        int d = Delannoy(i, i);
        printf("%2d - %d\n", i, d);
    }
    return 0;
}