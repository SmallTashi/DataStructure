#include <stdio.h>

/*
 * 斐波那契数列
 * 1.非递归
 * 2.递归实现
 * * */
void FibWithoutRec(int count);

void Fib(int count);

int Recursion(int count);

int main() {
    FibWithoutRec(100);
    printf("\n");
    Fib(100);
    return 0;
}

void FibWithoutRec(int count) {
    int a, b, c;
    a = 1;
    b = 1;
    printf("%d %d ", a, b);
    count-=2;
    int i;
    for (i = 0; i < count; ++i) {
        c = a + b;
        printf("%d ", c);
        if (i % 2 == 0)
            a = c;
        else
            b = c;
    }
}

void Fib(int count) {
    int i;
    for (i = 0; i < count; ++i) {
        printf("%d ",Recursion(i+1));
    }
}

int Recursion(int count){
    if(count<=2)
        return 1;
    return Recursion(count-1)+Recursion(count-2);
}
