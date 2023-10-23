#include <stdio.h>
#include <math.h>

int printTabela(int n)
{
    printf("%-4s|%-8s|%-5s\n", "N", "Square", "SquareRoot");
    printf("============================\n");

    for (int i = 1; i <= n; i++)
    {
        printf("%-4d|%-8d|%3.2f\n", i, i*i, sqrt(i));
    }
    
    printf("============================\n");
    return 0;
}

int main(void)
{
    int n;

    do{
        printf("Insira o limite de linhas: ");
        scanf("%d", &n);
    } while (n < 1);

    printTabela(n);

    return 0;

    
}
