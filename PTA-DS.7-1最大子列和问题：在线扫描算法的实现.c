//PTA数据结构与算法题目集：7-1最大子列和问题：在线扫描算法的实现
//原址https://pintia.cn/problem-sets/15/problems/709

//在线扫描算法是从做到右依次扫描，不停更新最大子列和，如果扫描的子列和小于0则更新为0再往右扫描
//可以用逻辑推演得出是正确的，相当于从0开始找每段的子列和，最大的子列和放在MaxSum变量中

#include<stdio.h>

int maxSubseqSum(int A[], int N){
    int thisSum,MaxSum;
    thisSum = MaxSum = 0;
    for ( int i = 0; i < N; ++i ){
        thisSum += A[i];
        
        if ( thisSum > MaxSum ){
            MaxSum = thisSum;
        }
        else if ( thisSum < 0 ){
            thisSum = 0;
        }
    }
    return MaxSum;
}

int main(int argc, char const *argv[])
{
    int N;
    int i = 0;
    int maxsum;
    scanf("%d",&N);
    int A[N];
    while(scanf("%d",&A[i]) != EOF && getchar() != '\n'){
        i++;
    }
    maxsum = maxSubseqSum(A,N);
    if ( maxsum < 0 ){
        maxsum = 0;
    }
    printf("%d",maxsum);
    return 0;
}