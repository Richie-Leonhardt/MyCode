//PTA数据结构与算法题目集：6-5 链式表操作集
//地址https://pintia.cn/problem-sets/15/problems/728


#include <stdio.h>
#include <stdlib.h>

#define ERROR NULL
typedef int ElementType;
typedef struct LNode *PtrToLNode;
struct LNode {
    ElementType Data;
    PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;

Position Find( List L, ElementType X );
List Insert( List L, ElementType X, Position P );
List Delete( List L, Position P );

int main()
{
    List L;
    ElementType X;
    Position P, tmp;
    int N;

    L = NULL;
    scanf("%d", &N);
    while ( N-- ) {
        scanf("%d", &X);
        L = Insert(L, X, L);
        if ( L==ERROR ) printf("Wrong Answer\n");
    }
    scanf("%d", &N);
    while ( N-- ) {
        scanf("%d", &X);
        P = Find(L, X);
        if ( P == ERROR )
            printf("Finding Error: %d is not in.\n", X);
        else {
            L = Delete(L, P);
            printf("%d is found and deleted.\n", X);
            if ( L==ERROR )
                printf("Wrong Answer or Empty List.\n");
        }
    }
    L = Insert(L, X, NULL);
    if ( L==ERROR ) printf("Wrong Answer\n");
    else
        printf("%d is inserted as the last element.\n", X);
    P = (Position)malloc(sizeof(struct LNode));
    tmp = Insert(L, X, P);
    if ( tmp!=ERROR ) printf("Wrong Answer\n");
    tmp = Delete(L, P);
    if ( tmp!=ERROR ) printf("Wrong Answer\n");
    for ( P=L; P; P = P->Next ) printf("%d ", P->Data);
    return 0;
}




/*以下为实际代码*/

//find先考虑L是null的情况，其次是找到首尾和一般情况，发现首尾和一般情况可以合起来
Position Find( List L, ElementType X ){
	if ( L == NULL ){
		return ERROR;
	}

	Position p = L;
	while(p != NULL && p->Data != X ){
		p = p->Next;
	}
	if (p != NULL) return p;
	return ERROR;	

}

/*
要求插入到P位置的前面，P是一个指针
传入的参数：L是NULL的情况：P只能是NULL
P是NULL的情况：在最后一位插入
在最前插入：返回头节点
中间插入：一般情况
可以再做优化，由于P是NULL的关系，插入到最后一个可以跟一般情况合起来
 */
List Insert( List L, ElementType X, Position P ){
	List tmp;
	List head = L;

	if ( L == NULL && P != NULL ){
		printf("Wrong Position for Insertion\n");
		return ERROR;
	}

	tmp = (List)malloc(sizeof(struct LNode));
	tmp -> Data = X;

	if (L == NULL){
		tmp->Next = NULL;
		return tmp;
	}

	if (P == L){
		tmp->Next = L;
		return tmp; 
	}

	//下面一块可以再作优化
	if (P == NULL){
		tmp->Next = NULL;
		if(L->Next != NULL){
			while(L->Next != NULL){
				L = L->Next;
			}
			L->Next = tmp;
			return head;
		}else{
			L->Next = tmp;
			return head;
		}
	}

	//while中在使用->的时候千万要注意是否越界了
	//下面是错误示例：

//	while ( L->Next = NULL && L->Next != P ){	//后面一个-> 存在越界问题！
//		L = L->Next;	
//	}

	while ( L->Next != NULL && L->Next != P ){
		L = L->Next;	
	}
	if (L->Next == P){
		tmp->Next = L->Next;
		L->Next = tmp;
		return head;
	}else{
		free(tmp);
		printf("Wrong Position for Insertion\n");
		return ERROR;
	}
}

List Delete( List L, Position P ){
	List head = L;

	if ( L == NULL || P == NULL ){
		printf("Wrong Position for Deletion\n");
		return ERROR;
	}

	if ( L == P ){
		head = head->Next;
		free(L);
		return head;
	}

	while ( L->Next != NULL && L->Next != P ){
		L = L->Next;	
	}
	if (L->Next == P){
		L->Next = P->Next;
		free(P);
		return head;
	}else{
		printf("Wrong Position for Deletion\n");
		return ERROR;
	}

}