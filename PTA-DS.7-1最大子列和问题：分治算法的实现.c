//PTA数据结构与算法题目集：7-1最大子列和问题：分治算法的实现
//原址https://pintia.cn/problem-sets/15/problems/709

//分治算法通过多重递归，将数组左右两边切分成更小的数组，直到最后基本条件:数组的元素为1为止，如果小于0返回0，否则返回其本身（子列最大值）
//在递归回来的时候，需要看看mid两边的串加起来是否比左边和右边的最大子列大，这个时候只要从中间开始往左右扫描，最后加起来看看就能得出
//通过分治算法，可以将原来的传统的算法的O(N^2)的时间复杂度转变成O(NlogN)
#include <stdio.h>

typedef int Index;
//分治算法
int divideConquer_FindMaxSubSeqSum(int N,int arr[N]){
    if ( N == 1 ){
        if (arr[0] < 0){
            return 0;
        }else{
            return arr[0]; 
        }
    }
    Index mid = N/2;
    int left[mid];
    int right[N - mid];
    for (int i = 0; i < mid; ++i){
        left[i] = arr[i];
    }
    for (int i = 0; i < N - mid; ++i){
        right[i] = arr[i + mid];
    }

    int leftMaxSum = divideConquer_FindMaxSubSeqSum(mid,left);
    int rightMaxSum = divideConquer_FindMaxSubSeqSum(N - mid,right);

    int leftAll = 0,leftAllMax = 0;
    int rightAll = 0,rightAllMax = 0;
    for (int i = mid - 1; i >= 0; --i){
        leftAll += left[i];
        if (leftAll > leftAllMax){
            leftAllMax = leftAll;     
        }
    }

    for (int i = mid; i < N; ++i){
        rightAll += arr[i];
        if (rightAll > rightAllMax){
            rightAllMax = rightAll;     
        } 
    }

    if (leftAllMax < 0)leftAllMax = 0;
    if (rightAllMax < 0)rightAllMax = 0;
    
    if (leftAllMax + rightAllMax >= leftMaxSum && leftAllMax + rightAllMax >= rightMaxSum){
        return leftAllMax + rightAllMax;
    }else if ( leftMaxSum >= rightMaxSum ){
        return leftMaxSum;
    }else{
        return rightMaxSum;
    }
}

int main(){
    int N;
    scanf("%d",&N);
    int arr[N];


    //一般读入方法：一行解决，但是仅能用于数组而不能链表插入
    /*
    int i = 0;
    while(scanf("%d",&arr[i]) != EOF && getchar() != '\n')i++;
    */


    //反序读入数组,或是反序插入链表
    /*
    int i = N; 
    while(i--){
        scanf("%d",&arr[i]);
    }
    */


    //正序读入数组/插入链表 
    int i = 0;
    while(i < N){
        scanf("%d",&arr[i]);
        i++;
    }

    int answer = divideConquer_FindMaxSubSeqSum(N,arr);
    printf("%d",answer );
    return 0;

}