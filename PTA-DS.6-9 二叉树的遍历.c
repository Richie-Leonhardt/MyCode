//PTA数据结构与算法题目集:6-9 二叉树的遍历
//按层遍历需要用队列来实现，其他三个用递归或者循环就能搞定
//队列的先进先出恰好能够存每层的左右子树，取出来的时候再把它的左右子树再存进去

//中序遍历
void InorderTraversal( BinTree BT ){
	if (BT == NULL){
		return;
	}
	InorderTraversal(BT->Left);
	printf(" %c",BT->Data);
	InorderTraversal(BT->Right);
}

//前序遍历
void PreorderTraversal( BinTree BT ){
	if (BT == NULL){
		return;
	}
	printf(" %c",BT->Data );
	PreorderTraversal(BT->Left);
	PreorderTraversal(BT->Right);
}

//后序遍历
void PostorderTraversal( BinTree BT ){
	if ( BT == NULL ){
		return;
	}
	PostorderTraversal(BT->Left);
	PostorderTraversal(BT->Right);
	printf(" %c",BT->Data);
}

//按层遍历
void LevelorderTraversal( BinTree BT ){
	if (BT == NULL){
		return;
	}
	typedef struct LNode *List;
	struct LNode {
    	BinTree B;
    	List Next;
	};
	List front = (List)malloc(sizeof(struct LNode));//front 设置成head节点，用来与rear配合判空
	List rear = (List)malloc(sizeof(struct LNode));//rear直接把树根拿来插入
	rear->B = BT;
	front->Next = rear;
	while (front != rear){	//停止条件就是队列中没有元素的时候
		front = front->Next;	//取出队头元素并输出出来，然后如果有左右孩子就存到队列中队尾
		printf(" %c", front->B->Data);
		if (front->B->Left != NULL){
			rear->Next = (List)malloc(sizeof(struct LNode));
			rear->Next->B = front->B->Left;
			rear = rear->Next;
		}
		if (front->B->Right != NULL){
			rear->Next = (List)malloc(sizeof(struct LNode));
			rear->Next->B = front->B->Right;
			rear = rear->Next;
		}	
	}
}