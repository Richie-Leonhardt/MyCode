//PTA数据结构与算法题目集:顺序表操作集
//理解函数的接口是十分重要的
//原址https://pintia.cn/problem-sets/15/problems/725

//以下是测试函数，在main之后的才是真正的开始
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 5
#define ERROR -1
typedef enum {false, true} bool;    //论如何在ｃ语言中使用ｔｒｕｅ、ｆａｌｓｅ和ｂｏｏｌ
typedef int ElementType;
typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List MakeEmpty(); 
Position Find( List L, ElementType X );
bool Insert( List L, ElementType X, Position P );
bool Delete( List L, Position P );

int main()
{
    List L;
    ElementType X;
    Position P;
    int N;

    L = MakeEmpty();
    scanf("%d", &N);
    while ( N-- ) {     //读入以空格分割的还能以这种形式，学到了
        scanf("%d", &X);
        if ( Insert(L, X, 0)==false )
            printf(" Insertion Error: %d is not in.\n", X);
    }
    scanf("%d", &N);
    while ( N-- ) {
        scanf("%d", &X);
        P = Find(L, X);
        if ( P == ERROR )
            printf("Finding Error: %d is not in.\n", X);
        else
            printf("%d is at position %d.\n", X, P);
    }
    scanf("%d", &N);
    while ( N-- ) {
        scanf("%d", &P);
        if ( Delete(L, P)==false )
            printf(" Deletion Error.\n");
        if ( Insert(L, 0, P)==false )
            printf(" Insertion Error: 0 is not in.\n");
    }
    return 0;
}

List MakeEmpty(){
	List ptrL = (List)malloc(sizeof(struct LNode));
	ptrL->Last = -1;		//Last是最后一个元素的位置，从0开始数，相当于下标，这里就初始化为-1了
	return ptrL;
}

Position Find( List L, ElementType X ){
	if (L == NULL || L->Last == -1){
		return ERROR;
	}

	Position index = 0;
	while(index <= L->Last){
		if(L->Data[index] == X){
			return index;
		}
		index++;
	}
	return ERROR;
}

/*
insert：首先考虑特殊情况：
            １．插入到第一个、插入到列表尾端    发现插入到第一个可以跟一般情况合并
            ２．插入时列表已满
            ３．插入读入的Ｌ指向NULL
*/
bool Insert( List L, ElementType X, Position P ){
	

	Position tmp = L->Last;   //比较隐蔽的一点是full应该在illegal position前面
	if (tmp == MAXSIZE - 1){
		printf("FULL");
		return false;
	}

	if (P == L->Last + 1){
		L->Data[++L->Last] = X;
		return true;
	}

	if ( P != 0 && (P > L->Last || P < 0)){
		printf("ILLEGAL POSITION");
		return false;
	}

	while(tmp >= P){
		L->Data[tmp + 1] = L->Data[tmp];
		tmp--;	
		//这里也可以一行代码：L->Data[tmp] = L->Data[tmp--];根据优先级，先算tmp--，Data[tmp--]中tmp值没变，再从右往左赋值，左边的tmp这时已经-1了,恰巧是前面的赋给后面的，不过不易理解，也可能出现warning
		//如果设置成 L->Data[--tmp] = L->Data[tmp]; 就不行了，会先算--tmp，之后右边的tmp已经－1了
	}

	L->Data[P] = X;
	L->Last++; 
	return true;
}

bool Delete( List L, Position P ){

	if (L == NULL || L->Last == -1 || P < 0 || P > L->Last){   //P是不能超过尾端
		printf("POSITION %d EMPTY",P);    //存在一个接口的陷阱
		return false;
	}
	
	
	for (int i = P; i < L->Last; ++i){
		L->Data[i] = L->Data[i + 1];
	}
	
	L->Last--;
	return true; 
}