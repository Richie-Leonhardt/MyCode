//PTA数据结构与算法题目集:6-8 求二叉树高度
//聪明的我直接用十一行代码递归实现求二叉树高度的问题，一遍过嘎嘎嘎
//二叉树的构建是我自己写的，能在PTA上学到很多，比如说在在C中如何用true和false：用一个enum共用体就OK了
#include <stdio.h>
#include <stdlib.h>

typedef enum {true,false} bool;
typedef char ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

BinTree CreatBinTree( ElementType X ){
	BinTree tree = (BinTree)malloc(sizeof(struct TNode));
	tree->Data = X;
	tree->Left = NULL;
	tree->Right = NULL;
	return tree;
}


//Tag == 0表示插入为左子树，Tag == 1表示插入为右子树
bool InsertItem( Position p, ElementType X, int Tag ){
	if (p == NULL)	{
		return false;
	}

	BinTree item = (BinTree)malloc(sizeof(struct TNode));
	item->Data = X;
	item->Left = NULL;
	item->Right = NULL;
	if (Tag == 0){
		p->Left = item;
	}else{
		p->Right = item;
	}
	return true;
}


//求二叉树高度
int GetHeight( BinTree BT ){
	if (BT == NULL){
		return 0;
	}
	int a = GetHeight(BT->Left);
	int b = GetHeight(BT->Right);
	if (a > b){ 
		return a + 1;
	}
	return b + 1;
}

int main(int argc, char const *argv[]){
	BinTree BT = CreatBinTree(0);
	InsertItem(BT,1,0);
	InsertItem(BT,2,1);
	InsertItem(BT->Left,3,0);
	InsertItem(BT->Right,5,0);
	InsertItem(BT->Left,4,1);
	InsertItem(BT->Right,6,1);
	InsertItem(BT->Left->Left,7,0);
	printf("\n%d\n",GetHeight(BT));
	return 0;
}