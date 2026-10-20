//栈的初始化以及部分方法（有待补充和完善）

#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef int Elemtype;

typedef struct stack
{
    Elemtype data[MAXSIZE];
    int top;
}Stack;

Stack* initStack()  //初始化栈
{
    Stack* S = (Stack*)malloc(sizeof(Stack));
    if(S == NULL)
    {
        printf("Initialization Failed.\n");
        exit(1);
    }
    printf("Initialization succeeded.\n");
    S -> top = -1;
    return S;
}

void Push(Stack* S,Elemtype e)  //入栈
{
    if(S -> top >= MAXSIZE - 1)
    {
        printf("The stack is already full.\n");
        return;
    }
    S -> top++;
    S ->data[S -> top] = e;
}

int is_empty(Stack* S)  //弹栈
{
    return S -> top == -1;
}

Elemtype Pop(Stack* S)  //判断是否为空栈
{
    if (is_empty(S))
    {
        printf("The stack is empty.\n");
        return 0;
    }

    Elemtype e = S -> data[S -> top];
    S -> top--;
    return e;
}

void printStack(Stack* S)       //遍历整个栈（按照栈顶 -> 栈底的顺序）
{
    int num = S -> top;
    while(num != -1)
    {
        printf("%d",S -> data[num]);
        num--;
    }
}

void freeStack(Stack* S)    //释放栈
{
    free(S);
}