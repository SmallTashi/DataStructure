#include <stdio.h>
#include <malloc.h>
#include <time.h>
/**
 * 单向链表的实现：
 * - 初始化链表
 * - 添加测试数据
 * - 添加头节点
 * - 在指定位置插入元素
 * - 删除指定位置元素
 * - 删除链表
 *
 * 10.12
 * 使用递归算法实现下列运算
 * - 求链表中的最大整数
 * - 求链表的节点个数
 * - 求所有整数的平均值
 * */

//链表中所保存的数据类型，使用结构体定义，可存放不同类型的数据，且当数据类型改变时，便于修改
typedef struct {
    int elem;
} ElemType;

typedef enum {
    OK = -200, Error, Underflow
} Status;

typedef struct Link {
    ElemType data;
    struct Link *next;
} Node;

Node info;
Node *LinkList;

//删除指定位置数据并返回该数据
Status Delete(Node *head, int i, Node *delete);

//删除链表，释放内存（释放每一个节点的内存）
Status DeleteAll(Node *head);

//在指定位置添加元素
Status Add(Node *L, int i, ElemType add);

//初始化链表，返回头指针
Node *InitListWithHead();

//查找第i个元素
Status Find(Node *L, int i, Node *find);

//初始化测试数据
Status TestData(Node *List, int size);

//输出链表元素
void Put(Node *head);

//10.12

//查找最大整数
Status findMax(Node *head, ElemType *max);

ElemType toNextTwo(Node *now, ElemType max);

int toNext(Node *now,int len);

//平均数
int aver(Node *now, int len, int sum);

//获取链表长度
int getLength(Node *head);

int main() {
    Node *head = InitListWithHead();
    TestData(head, 10);
    Put(head);
    printf("The length is: %d \n",getLength(head));
    ElemType max ={0};
    findMax(head,&max);
    printf("The max number is: %d \n",max.elem);
    printf("The average is: %d", aver(head, 0, 0));

//    int n,m,o,h;
//     //删除操作
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
//    m = Add(head, 3, add);
//    if (OK == m) {
//        printf("--------------------After adding------------------------\n");
//        Put(head);
//    } else
//        printf("\nError!");
//
//    //查找
//    Node find;
//    o = Find(head,3,&find);
//    if (OK == o) {
//        printf("--------------------Finding------------------------\n");
//
//        printf("find: %d\n",find.data.elem);
//    } else
//        printf("\nError!");
//
//    //清空链表
//   h= DeleteAll(head);
//
//    if (OK == h) {
//        printf("--------------------Destroy------------------------\n");
//        Put(head);
//    } else
//        printf("\nError!");
    return 0;
}

Status Delete(Node *head, int i, Node *delete) {
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

Status DeleteAll(Node *head) {

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
    L->next = p;
    return OK;
}

Node *InitListWithHead() {
    LinkList = &info;
    info.data.elem = -5;
    info.next = NULL;
    return LinkList;
}

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

void Put(Node *head) {
    int i = 0;
    Node *p = head;
    while (p) {
        printf("List[%d] = %d\n", i, p->data);
        p = p->next;
        i++;
    }
}

int getLength(Node *head){
    Node *p = head;
    return toNext(p,0);
}

int toNext(Node *now, int len){
    if(!now->next){
        return len;
    }
    len++;
    now = now->next;
    return toNext(now,len);
}

Status findMax(Node *head, ElemType *max){
    Node *p = head;
    if(!p->next)
        return Error;
    (*max)= toNextTwo(p,*max);
    return OK;
}

ElemType toNextTwo(Node *now, ElemType max){
    if(!now->next){
        return now->data.elem>max.elem?now->data:max;
    }
    if(now->data.elem>max.elem)
        max = now->data;
    now = now->next;
    return toNextTwo(now,max);
}

int aver(Node *now, int len, int sum){
    len++;
    if(!now->next) {
        return sum/len;
    }
    sum+=now->data.elem;
    now = now->next;
    return aver(now, len, sum);
}
