#include <stdio.h> 
#include <string.h>

int main(void)
{
    char nome[50];
    printf("Digita o teu nome: ");
    fgets(nome, sizeof(nome), stdin);

    nome[strlen(nome)-1] = '\0';

    printf("Hello %s!", nome);
    return 0;
}