//PTA数据结构与算法题目集：7-3 树的同构
//首先需要考虑特殊情况，这边特殊情况只有Null的情况
//在多个数据输入的时候，尤其是有输入%c的情况，scanf()中尤其要注意换行符 '\n'，一个一个匹配进去才行 
#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
#define Null -1
#define ElementType char
#define Tree int

//用静态链表来表示树，本身其实还是数组，但是汲取链表的左右指针的思想来的
//其中Tree代表的都是结构体数组TNode1和TNode2的下标，实际是int
struct TNode{
	ElementType Data;
	Tree Left;
	Tree Right;
}TNode1[MaxSize],TNode2[MaxSize];	//两棵树

Tree CreatTree(struct TNode T[]){	//建立树，尤其注意建立的时候读入数据
	int N;
	char tmp1,tmp2;
	scanf("%d\n",&N);	//
	if ( N ){
		for (int i = 0; i < N; ++i){
			scanf("%c %c %c\n", &T[i].Data, &tmp1, &tmp2);
			if (tmp1 == '-') T[i].Left = Null;
			else T[i].Left = (int)tmp1 - 48;
			if (tmp2 == '-') T[i].Right = Null;
			else T[i].Right = (int)tmp2 - 48;
		}
		Tree deck[N];		//这边需要寻找树根，就是没有下标指向的那个东西，所以我们把所有有下标指向的都标注出来，最后剩下的那个就是树根了
		for (int i = 0; i < N; ++i)deck[i] = 0;
		for (int i = 0; i < N; ++i){
			if(T[i].Left != Null)deck[T[i].Left] = 1;
			if(T[i].Right != Null)deck[T[i].Right] = 1;
		}
		for (int i = 0; i < N; ++i){
			if (deck[i] == 0) return i;
		}
	}
	return Null;
}

int isSimilar(Tree T1,Tree T2){		//判断是否同构，可以用递归的方法来，比较父节点，再分情况递归比较子节点
	if ( T1 == Null && T2 == Null) return 1;	//如果都是空的话应该是同构的，同时也满足子树是空的话是相同符合同构条件的
	if ( T1 == Null || T2 == Null) return 0;
	if ( TNode1[T1].Data != TNode2[T2].Data) return 0;	//比较的父节点数据域必须相同才能满足同构，同时，注意下标不能越界，所以要先上面的Null的先算，当然也可以跟上面一个用||整合，短路解决了问题
	/*子节点同构只有两种情况，左对左和左对右，所以这边直接这样就OK*/
	if ( isSimilar(TNode1[T1].Left, TNode2[T2].Left) && isSimilar(TNode1[T1].Right, TNode2[T2].Right) ){
		return 1;
	}
	if ( isSimilar(TNode1[T1].Right, TNode2[T2].Left) && isSimilar(TNode1[T1].Left, TNode2[T2].Right) ) {
		return 1;
	}
	return 0;
}


int main(int argc, char const *argv[]){
	Tree T1,T2;
	T1 = CreatTree(TNode1);
	T2 = CreatTree(TNode2);
	if (isSimilar(T1,T2)) printf("Yes");
	else printf("No");
	return 0;
}