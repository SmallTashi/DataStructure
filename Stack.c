#include <stdio.h>
#include <malloc.h>
#include <time.h>
/**
 * 栈的实现：
 * - 初始化栈
 * - 添加测试数据
 * - 压栈
 * - 出栈
 * - 判空
 * - 销毁
 * - 清除
 * */

#define MAX_SIZE 10

//栈中所保存的数据类型，使用结构体定义，可存放不同类型的数据，且当数据类型改变时，便于修改
typedef struct {
    int elem;
} ElemType;

typedef enum {
    OK = -200, Error, Underflow
} Status;

typedef struct Stack {
    ElemType data;
    struct Stack *next;
} Node;

Node info;
Node *Stack;
Node *top;

//出栈
Status Pop(Node *head, int i, Node *delete);

//清空（释放每一个节点的内存）
Status Clean(Node *head);

//入栈
Status Push(Node *L, int i, ElemType add);

//创建栈,返回头指针
Node *InitStackWithHead();

//查找第i个元素
Status GetTop(Node top);

//初始化测试数据
Status TestData(Node *List, int size);

//输出栈元素
void Put(Node head);

//int main() {
//    Node *head = InitStackWithHead();
//    TestData(head, 5);
//    Put(head);
//    printf("The length is: %d \n",getLength(head));
//    ElemType max ={0};
//    findMax(head,&max);
//    printf("The max number is: %d \n",max.elem);
//    printf("The average is: %d \n", aver(head, 0, 0));
//
//    int n,m,o,h;
//    //删除操作
//    Node delete;
//    Node *del = &delete;
//    n = Delete(head, 3, del);
//
//    if (OK == n) {
//        printf("--------------------After deleting------------------------\n");
//        printf("delete: %d\n",delete.data.elem);
//        Put(head);
//    } else
//        printf("\nError!");
//
//    //添加元素
//    ElemType add;
//    add.elem = 50;
//    m = Push(head, 3, add);
//    if (OK == m) {
//        printf("--------------------After adding------------------------\n");
//        Put(head);
//    } else
//        printf("\nError!");
//
//    //查找
//    Node find;
//    o = GetTop(head,3,&find);
//    if (OK == o) {
//        printf("--------------------Finding------------------------\n");
//
//        printf("find: %d\n",find.data.elem);
//    } else
//        printf("\nError!");
//
//    //清空链表
//    h= Clean(head);
//
//    if (OK == h) {
//        printf("--------------------Destroy------------------------\n");
//        Put(head);
//    } else
//        printf("\nError!");
//    return 0;
//}

Status Pop(Node *head, int i, Node *delete) {
    int j = 1;
    Node *L = head->next;
    while (L && j < (i - 1)) {
        L = L->next;
        j++;
    }
    if (!L || j > (i - 1))return Error;
    (*delete) = *(L->next);
    if (delete->next) {
        L->next = delete->next;
        delete->next = NULL;
    } else {
        L->next = NULL;
    }
    return OK;
}

Status Clean(Node *head) {

    Node *temp;
    Node *L = head;
    temp = L->next;
    while(temp->next){
        L->next = temp->next;
        temp->next = NULL;
        free(temp);
        temp = L->next;
    }
    L->next = NULL;
    return OK;
}

Status Push(Node *L, int i, ElemType add) {
    int j = 0;
    while (L && j < (i - 1)) {
        L = L->next;
        j++;
    }
    if (!L || j > (i - 1))return Error;
    Node *p = (Node *) malloc(sizeof(Node));
    p->data = add;
    p->next = L->next;
    L->next = p;
    return OK;
}
//TODO OK
Node *InitStackWithHead() {
    Stack = &info;
    info.data.elem = -5;
    top = &info;
    info.next = NULL;
    return Stack;
}

Status GetTop(Node t) {
    t = *top;
    return OK;
}

Status TestData(Node *List, int size) {
    int i;
    Node *p;
    p = List;
    srand((unsigned int)(time(NULL)));
    for (i = 0; i < size; ++i) {
        //分配内存
        Node *temp = (Node *) malloc(sizeof(Node));
        if (!temp) {
            return Underflow;
        }
        ElemType d;
        d.elem = (rand()%100+1);
        temp->data = d;
        p->next = temp;
        p = temp;
    }
    p->next = NULL;
    return OK;
}

//TODO OK
void Put(Node head) {
    int i = 0;
    Node *p = &head;
    while (p) {
        printf("List[%d] = %d\n", i, p->data);
        p = p->next;
        i++;
    }
}

int main() {
    printf("Hello, World!\n");
    return 0;
}
