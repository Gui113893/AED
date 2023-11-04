//
// TO DO : desenvolva um algoritmo para verificar se um numero inteiro positivo
//         e uma capicua
//         Exemplos: 12321 e uma capiacua, mas 123456 nao e
//         USE uma PILHA DE INTEIROS (STACK) e uma FILA DE INTEIROS (QUEUE)
//
// TO DO : design an algorithm to check if the digits of a positive decimal
//         integer number constitue a palindrome
//         Examples: 12321 is a palindrome, but 123456 is not
//         USE a STACK of integers and a QUEUE of integers
//

#include <stdio.h>
#include "IntegersQueue.c"
#include "IntegersStack.c"

int IsCapicuaQueue(int n){
    int isCapicua = 1;
    int digit, head, tail;
    Queue* q = QueueCreate(11);
    while (n > 0){
        digit = n % 10;
        QueueEnqueue(q, digit);
        n = n / 10;
    }
    for (int i = 0; i < (q->cur_size)/2; i++) {
        tail = q->data[q->cur_size];
        head = QueueDequeue(q);
        if (head != tail) {
            isCapicua = 0;
            break;
        }
    }
    QueueDestroy(&q);
    return isCapicua;
}

int IsCapicuaStack(int n){
    int digit, powTen, newN, size;
    int tempN = n;
    Stack* s = StackCreate(11);
    while (tempN > 0){
        digit = tempN % 10;
        StackPush(s, digit);
        tempN = tempN / 10;
    }
    newN = 0;
    size = s->cur_size;
    for (int i = 0; i < size; i++) {
        if (i == 0) powTen = 1;
        newN += StackPop(s) * powTen;
        powTen*=10;

    }
    StackDestroy(&s);
    if (newN == n) return 1;
    else return 0;
}

int main(void) {
    int n;
    printf("n: ");
    scanf("%d", &n);

    if (IsCapicuaQueue(n)) printf("Queue Method: Is a Capicua\n");
    else printf("Queue Method: Is Not a Capicua\n");

    if (IsCapicuaStack(n)) printf("Stack Method: Is a Capicua\n");
    else printf("Stack Method: Is Not a Capicua\n");

    return 0;
}
