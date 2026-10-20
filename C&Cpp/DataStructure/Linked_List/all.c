// 单链表的节点定义以及所有方法（有待补充和完善）

#include <stdio.h>
#include <stdlib.h>
typedef int Elemtype;

typedef struct node
{
    Elemtype data;
    struct node* next;
}Node;

Node* initList() //头节点的初始化
{
    Node* head = (Node*)malloc(sizeof(Node));
    if(head == NULL)
    {
        printf("Initialization failed.\n");
        exit(1);
    }
    printf("Initialization succeeded.\n");
    head -> data = 0;
    head -> next = NULL;    //循环链表此处的next应赋值为头节点地址
    return head;
}

Node* get_tail(Node* L)  //获取尾节点，为尾插法提供尾节点参数
{
    Node* p = L;
    while(p -> next != NULL)
    {
        p = p -> next;
    }
    return p;
}

void tailInsert(Node* L,Elemtype e)  //尾插法
{
    Node* p = (Node*)malloc(sizeof(Node));
    Node* tail = get_tail(L);
    p -> data = e;
    p -> next = tail -> next;
    tail -> next = p;
}

int get_length(Node* L)    //获取链表节点数（不包括头节点）
{
    int num = 0;
    Node* p = L;
    while(p -> next != NULL)
    {
        p = p -> next;
        num ++;
    }
    return num;
}

void ListDelete(Node* L,int num)    //按序号删除节点
{
    Node* p = L;
    Node* q;
    int i;
    if(num > get_length(L))
    {
        printf("Invalid input\n");
        return;
    }
    for(i = 0;i < num - 1;i++)
    {
        p = p -> next;
    }
    q = p -> next;
    p -> next = q -> next;
    free(q);
}

void printList(Node* L) //遍历链表
{
    Node* p = L -> next;
    while(p != NULL)
    {
        printf("%d\n",p -> data);
        p = p -> next;
    }
}

Elemtype get_data(Node* L,int num)  //读取链表中数据
{   
    Node* p = L;
    if(num > get_length(L))
    {
        printf("Invalid input\n");
        return 0;
    }
    int i;
    for(i = 0;i < num ;i++)
    {
        p = p -> next;
    }
    return p -> data;
}

void freeList(Node* L)  //释放链表空间
{
    Node* p = L;
    Node* q;
    while(p != NULL)
    {
        q = p -> next;
        free(p);
        p = q;
    }
}