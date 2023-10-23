#include <stdio.h>
#include <math.h>


int printTabela(int menor, int maior, int incremento)
{
    FILE *ptr;
    ptr = fopen("out.txt", "w");


    fprintf(ptr, " %-3s|%-8s|%-8s\n", "ang", "sin(ang)", "cos(ang)");
    fprintf(ptr, "============================\n");

    for (int i = menor; i <= maior; i+= incremento)
    {
        double radian = i * (M_PI / 180);
        fprintf(ptr, "%4d|%8.5f|%8.5f\n", i, sin(radian), cos(radian));
    }
    
    fprintf(ptr, "============================\n");
    fclose(ptr);
    return 0;
}

int main(void)
{
    int menor;
    int maior;
    int incremento;

    printf("Insira o menor ângulo: ");
    scanf("%d", &menor);

    do
    {
        printf("Insira o maior ângulo: ");
        scanf("%d", &maior);
    } while (menor > maior);

    do
    {
        printf("Insira o incremento: ");
        scanf("%d", &incremento);
    } while (incremento <= 0);
    

    printTabela(menor, maior, incremento);

    return 0;
}
