/**
 * 双向链表的实现：
 * - 初始化链表
 * - 添加测试数据
 * - 添加头节点
 * - 在指定位置插入元素
 * - 删除指定位置元素
 * - 查找某一数据是否存在
 * - 删除链表
 * */

#include <stdio.h>
#include <malloc.h>

//链表中所保存的数据类型，使用结构体定义，可存放不同类型的数据，且当数据类型改变时，便于修改
typedef struct {
    int elem;
} ElemType;

typedef enum {
    OK = -200, Error, Underflow
} Status;

typedef struct Link {
    struct Link *prev;
    ElemType data;
    struct Link *next;
} Node;

Node info;
Node *LinkList;

//初始化测试数据
Status TestData(Node *List, int size) {
    int i;
    Node *p;
    p = List;
    for (i = 0; i < size; ++i) {
        //分配内存
        Node *temp = (Node *) malloc(sizeof(Node));
        if (!temp) {
            return Underflow;
        }
        ElemType d;
        d.elem = (i + 1);
        temp->data = d;
        p->next = temp;
        temp->prev = p;
        p = temp;
    }
    p->next = NULL;
    return OK;
}

//删除指定位置数据并返回该数据
Status Delete(Node *head, int i, Node *delete) {
    int j = 1;

    Node *ne = head->next;
    while (ne && j < (i - 1)) {
        ne = ne->next;
        j++;
    }


    if (!ne || j > (i - 1))return Error;
    (*delete) = *(ne->next);
    if (delete->next) {
        ne->next = delete->next;
        delete->next->prev = ne;
        delete->prev = NULL;
        delete->next = NULL;
    } else {
        delete->prev = NULL;
        ne->next = NULL;
    }
    return OK;
}

//删除链表，释放内存（释放每一个节点的内存）
Status DeleteAll(Node *head) {

    Node *temp;
    Node *L = head; //L为头节点
    temp = L->next;
    while (temp->next) {
        L->next = temp->next;
        temp->next->prev=L;
        temp->prev = NULL;
        temp->next = NULL;
        free(temp);
        temp = L->next;
    }
    L->next = NULL;
    return OK;
}

//在指定位置添加元素
Status Add(Node *L, int i, ElemType add) {
    int j = 0;
    while (L && j < (i - 1)) {
        L = L->next;
        j++;
    }
    if (!L || j > (i - 1))return Error;
    Node *p = (Node *) malloc(sizeof(Node));
    p->data = add;
    p->next = L->next;
    L->next->prev = p;
    L->next = p;
    p->prev = L;
    return OK;
}


//初始化链表，返回头指针
Node *InitListWithHead() {
    LinkList = &info;
    info.data.elem = -5;
    info.next = NULL;
    info.prev = NULL;
    return LinkList;
}


//查找第i个元素
Status Find(Node *L, int i, Node *find) {
    int j = 0;
    //当L为NULL或J=i时退出循环
    while (L && j < i) {
        L = L->next;
        j++;
    }
    if (!L || i < j)return Error;
    *find = *L;
    return OK;
}


void Put(Node *head) {
    int i = 0;
    Node *p = head;
    while (p->next) {
        printf("[%d]->next = %d\t", i, p->next->data);
        if(p->prev)
            printf("[%d]->prev = %d\n", i, p->prev->data);
        p = p->next;
        i++;
    }
}

int main(){
   Node *head = InitListWithHead();
   TestData(head,8);
   Put(head);
   Node delete;
   Delete(head,5,&delete);
   printf("\ndelete: %d\n",delete.data);
   Put(head);
   Add(head,5,delete.data);
    printf("\nadd: %d\n",delete.data);

    Put(head);
    return 0;
}