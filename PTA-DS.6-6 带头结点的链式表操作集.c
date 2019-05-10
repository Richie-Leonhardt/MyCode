//数据结构与算法题目集:6-6 带头结点的链式表操作集
//网址https://pintia.cn/problem-sets/15/problems/729

List MakeEmpty(){
	List L = (List)malloc(sizeof(struct LNode));
	L->Next =NULL;
	return L;
}

//find先考虑L是null的情况，其次是找到首尾和一般情况，发现首尾和一般情况可以合起来
Position Find( List L, ElementType X ){
	if ( L == NULL ){
		return ERROR;
	}

	Position p = L->Next;
	while(p != NULL && p->Data != X ){
		p = p->Next;
	}

	if (p != NULL) return p;
	return ERROR;
}

/*
插入到头结点前面P == L，不行
传入的参数：L是NULL的情况：P只能是NULL，且要先初始化
P是NULL的情况：在最后一位插入
最前插入：由于有头结点可以跟头结点后面是NULL和头结点后面不是NULL的情况合起来考虑
中间插入：一般情况
可以再做优化，由于P是NULL的关系，插入到最后一个可以跟一般情况合起来
 */
bool Insert( List L, ElementType X, Position P ){
	List tmp;
	List ptrL = L;

	if ( ( L == NULL && P != NULL ) || P == L ){
		printf("Wrong Position for Insertion\n");
		return false;
	}

	tmp = (List)malloc(sizeof(struct LNode));
	tmp -> Data = X;

	if ( L == NULL ){
		L = MakeEmpty();
		tmp->Next = NULL;
		L->Next = tmp;
		return true;
	}

	//下面一块可以再作优化
	if (P == NULL){
		tmp->Next = NULL;
		if(L->Next != NULL){
			while(L->Next != NULL){
				L = L->Next;
			}
			L->Next = tmp;
			return true;
		}else{
			L->Next = tmp;
			return true;
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
		return true;
	}else{
		free(tmp);
		printf("Wrong Position for Insertion\n");
		return false;
	}
}

bool Delete( List L, Position P ){

	if ( L == NULL || P == NULL || L == P ){
		printf("Wrong Position for Deletion\n");
		return false;
	}

	while ( L->Next != NULL && L->Next != P ){
		L = L->Next;
	}
	
	if (L->Next == P){
		L->Next = P->Next;
		free(P);
		return true;
	}else{
		printf("Wrong Position for Deletion\n");
		return false;
	}

}