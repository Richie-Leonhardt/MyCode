//PTA数据结构与算法题目集：6-1翻转链表
//首先需要考虑特殊情况：翻转链表读入的是空，或是只有一个节点，那么直接返回即可
//其次，考虑到一般情况，让L指针先行，设置a,b来进行前面的工作，那么头尾分开，中间一个循环OK
//需要注意的是循环不执行的话头尾也要保证接上，即两个节点的情况
//https://pintia.cn/problem-sets/15/problems/724

List Reverse( List L ){

//	List a,b = L;		//定义赋值时必须分开赋值才行，这个bug找了好久

	List a = L,b = L;
	if (L == NULL || L->Next == NULL){
		return L;
	}

	L = L->Next;
	a->Next = NULL;

	while(L->Next != NULL){
		b = L;
		L = L->Next;
		b->Next = a;
		a = b;
	}

	L->Next = b;	//末尾分开来一定要注意，如果while直接不执行了就直接调到这，也要满足条件继续执行下去，这里碰巧狗屎了

	return L;
}