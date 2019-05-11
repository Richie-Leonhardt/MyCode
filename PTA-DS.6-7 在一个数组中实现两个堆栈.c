//PTA:数据结构与算法题目集:6-7 在一个数组中实现两个堆栈
//https://pintia.cn/problem-sets/15/problems/730
//
//很多隐藏的bug一定要调试后才能知道
#include <stdio.h>
#include <stdlib.h>

#define ERROR 1e8
typedef int ElementType;
typedef enum { push, pop, end } Operation;
typedef enum { false, true } bool;
typedef int Position;
struct SNode {
    ElementType *Data;
    Position Top1, Top2;
    int MaxSize;
};
typedef struct SNode *Stack;

Stack CreateStack( int MaxSize );
bool Push( Stack S, ElementType X, int Tag );
ElementType Pop( Stack S, int Tag );

Operation GetOp();  /* details omitted */
void PrintStack( Stack S, int Tag ); /* details omitted */

int main()
{
    int N, Tag, X;
    Stack S;
    int done = 0;

    scanf("%d", &N);
    S = CreateStack(N);
    while ( !done ) {
        switch( GetOp() ) {
        case push: 
            scanf("%d %d", &Tag, &X);
            if (!Push(S, X, Tag)) printf("Stack %d is Full!\n", Tag);
            break;
        case pop:
            scanf("%d", &Tag);
            X = Pop(S, Tag);
            if ( X==ERROR ) printf("Stack %d is Empty!\n", Tag);
            break;
        case end:
            PrintStack(S, 1);
            PrintStack(S, 2);
            done = 1;
            break;
        }
    }
    return 0;
}

/* 你的代码将被嵌在下面 */

//初始化有个陷阱，建立数组要用静态数组，否则函数结束数组就没了，而MaxSize是变动的所以不能用static
//所以这里就必须用malloc的方法来建立数组了
Stack CreateStack( int MaxSize ){
    Stack S = (Stack)malloc(sizeof(struct SNode)); 
    ElementType *a = (ElementType*)malloc(MaxSize * sizeof(ElementType));
    S->Data = a;
    S->Top2 = MaxSize;
    S->Top1 = -1;
    S->MaxSize = MaxSize;
    
    return S;
}


bool Push( Stack S, ElementType X, int Tag ){
    if (S->Top1 == S->Top2 - 1){
        printf("Stack Full\n");				//没有\n会“格式错误”
        return false;
    }
    if (Tag == 1){
        S->Data[++(S->Top1)] = X;
        return true;
    }else if ( Tag == 2 ){
        S->Data[--(S->Top2)] = X;
        return true;
    }
}

ElementType Pop( Stack S, int Tag ){
    if (Tag == 2 && S->Top2 == S->MaxSize){
        printf("Stack %d Empty\n",Tag);
        return ERROR;
    }
    if (Tag == 1 && S->Top1 == -1){
        printf("Stack %d Empty\n",Tag);
        return ERROR;
    }

    if (Tag == 1){
        return S->Data[S->Top1--];
    }else if (Tag == 2){
        return S->Data[S->Top2++];
    }
}