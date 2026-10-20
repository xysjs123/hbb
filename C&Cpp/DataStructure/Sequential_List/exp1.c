#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef int elemtype;

typedef struct
{
    elemtype data[MAXSIZE];
    int length;
}Seqlist;

Seqlist* initList()
{
    Seqlist* L = (Seqlist*)malloc(sizeof(Seqlist));
    if(L == NULL)
    {
        printf("Initialization Failed!\n");
        exit(1);
    }
    printf("Initialization Succeeded!\n");
    L -> length = 0;
    return L;
}

void tailInsert(Seqlist* L,elemtype e)
{
    if(L -> length >= MAXSIZE)
    {
        printf("The list is full!\n");
        exit(1);
    }
    L -> data[L -> length] = e;
    L -> length++;
}

void tailDelete(Seqlist* L)
{
    if(L -> length == 0)
    {
        printf("There is no data in the list.\n");
        exit(1);
    }
    L -> length--;
}

void numDelete(Seqlist* L,int num)
{
    if(num > L -> length || num < 1)
    {
        printf("The number is illegal.\n");
        exit(1);
    }
    while(num < L -> length)
    {
        L -> data[num - 1] = L -> data[num];
        num ++;
    }
    L -> length --;
}

void getdata(Seqlist* L,int num)
{
    if(num > L -> length || num < 1)
    {
        printf("The number is illegal.\n");
        exit(1);
    }
    printf("The data in %d is %d\n",num,L -> data[num - 1]);
}

void printList(Seqlist* L)
{
    int i = 0;
    printf("The data of the List is:\n");
    while(i !=  L -> length)
    {
        printf("%d\n",L -> data[i]);
        i++;
    }
}

void freeList(Seqlist* L)
{
    free(L);
}

int main()
{
    Seqlist* L = initList();
    printList(L);
    int i = 1;
    for(; i <= 3;i++)
    {
        tailInsert(L,i);
    }
    printList(L);
    getdata(L,3);
    numDelete(L,2);
    printList(L);
    tailDelete(L);
    printList(L);
    freeList(L);

    return 0;
}