//PTA:6-12 二叉搜索树的操作集

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void InorderTraversal( BinTree BT ){
    if (BT == NULL){
        return;
    }
    InorderTraversal(BT->Left);
    printf(" %d",BT->Data);
    InorderTraversal(BT->Right);
}

void PreorderTraversal( BinTree BT ){
    if (BT == NULL){
        return;
    }
    printf(" %d",BT->Data );
    PreorderTraversal(BT->Left);
    PreorderTraversal(BT->Right);
}

void PostorderTraversal( BinTree BT ){
    if ( BT == NULL ){
        return;
    }
    PostorderTraversal(BT->Left);
    PostorderTraversal(BT->Right);
    printf(" %d",BT->Data);
}

BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;
    BST = NULL;
    scanf("%d", &N);
    for ( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:"); PreorderTraversal(BST); printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp==MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp==MaxP) printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:"); InorderTraversal(BST); printf("\n");

    return 0;
}

/*插入实际上插入的都是叶子节点，像find那样找近似的最大最小值就行*/
BinTree Insert( BinTree BST, ElementType X ){
    BinTree tmp = (BinTree)malloc(sizeof(struct TNode));
    BinTree head = BST,pre;     //pre记录前一个节点
    tmp->Data = X;
    // tmp->Left = NULL;
    // tmp->Right = NULL;
    tmp->Left = tmp->Right = NULL;
    if (BST) {
        while (BST != NULL){
            if (X > BST->Data){
                pre = BST;
                BST = BST->Right;
            }else if (X < BST->Data){
                pre = BST;
                BST = BST->Left;
            }else{
                free(tmp);
                return head;
            }
        }
        if (X < pre->Data)pre->Left = tmp;
        else pre->Right = tmp;
        return head;
    }else{
        return tmp;
    }
}

//老师的方法，通过递归简化了代码
BinTree Insert2( ElementType X, BinTree BST ) 
{ 
    if( !BST ){  
            /*若原树为空，生成并返回一个结点的二叉搜索树*/ 
        BST = malloc(sizeof(struct TreeNode)); 
        BST->Data = X; 
        BST->Left = BST->Right = NULL; 
    }else  /*开始找要插入元素的位置*/ 
        if( X < BST->Data ) 
            BST->Left = Insert2( X, BST->Left);  
                        /*递归插入左子树*/ 
        else  if( X > BST->Data ) 
            BST->Right = Insert2( X, BST->Right); 
                         /*递归插入右子树*/ 
        /* else X已经存在，什么都不做 */ 
    return BST; 
} 

/*
因为返回的是根节点，所以首先要考虑根节点变化的情况，再看删除位置分情况讨论
1.删除的是叶子节点，直接删除即可，注意叶子可能就是树根，那么先要把删除树根的情况单独拿出来
2.删除的节点有一个子树，那么子树的位置代替这个删除的位置就行，如果这个是树根，那么返回的值要改变成指向其子树才行
3.删除的节点有两个子树，那么左子树的最大值或者右子树的最小值（用已有的FindMax直接得出）代替原来的位置就行，注意根节点情况
 */

//我自己写的全部用迭代的方法来删除，几种情况并不能整合起来，代码冗余比较大
BinTree Delete( BinTree BST, ElementType X ){
    BinTree tmp,p = Find(BST,X);
    tmp = p;
    if (p){
        if (p->Left == NULL && p->Right == NULL){   //很重要的一点是，不能直接将p赋值成NULL就好了，p是一个指针，p的改变并没有影响到它上一个节点的struct中的left和right指针，因为改变的只是p的引用
            if (p->Data == BST->Data){
                free(p);
                return NULL;
            }
            tmp = BST;
            while (tmp->Left != p && tmp->Right != p){      //这边如果是直接将p指向的节点free了也是有错的，free之后原来的父节点的指针指向的位置可能并不是NULL了，没法将free掉的那块内存再赋值为NULL
                if (tmp->Data > p->Data) tmp = tmp->Left;
                else tmp = tmp->Right;
            }
            if (tmp->Left == p)tmp->Left = NULL;
            else tmp->Right = NULL;
            free(p);
        }
        else if (p->Left == NULL && p->Right != NULL ){
            if (p->Data == BST->Data){
                p = BST->Right;
                free(BST);
                return p;
            }
            tmp = BST;
            while (tmp->Left != p && tmp->Right != p){
                if (tmp->Data > p->Data)tmp = tmp->Left;
                else tmp = tmp->Right;
            }
            if (tmp->Left == p)tmp->Left = p->Right;
            else tmp->Right = p->Right;
            free(p);
        }
        else if (p->Left != NULL && p->Right == NULL){
            if (p->Data == BST->Data){
                p = BST->Left;
                free(BST);
                return p;
            }
            tmp = BST;
            while (tmp->Left != p && tmp->Right != p){
                if (tmp->Data > p->Data)tmp = tmp->Left;
                else tmp = tmp->Right;
            }
            if (tmp->Left == p)tmp->Left = p->Left;
            else tmp->Right = p->Left;
            free(p);
        }
        else /* if (p->Left != NULL && p->Right != NULL) */{
            tmp = FindMax(p->Left);
            BST->Data = tmp->Data;  
            BST->Left = Delete(BST->Left,BST->Data);   //先赋值，再将左子树的多余的那个删去，省的建一个临时变量了
        }

    }else{
        printf("Not Found\n");
    }
    return BST;
}

//老师的方法，通过递归简化了代码，并且将几个情况整合起来了
BinTree Delete2( ElementType X, BinTree BST ){
    Position Tmp;  
    if( !BST ) printf("Not Found\n");  
    else if( X < BST->Data )  
            BST->Left = Delete2( X, BST->Left); /* 左子树递归删除 */ 
    else if( X > BST->Data )  
            BST->Right = Delete2( X, BST->Right); /* 右子树递归删除 */ 
    else /*找到要删除的结点 */  
         if( BST->Left && BST->Right ) { /*被删除结点有左右两个子结点 */  
             Tmp = FindMin( BST->Right );  
                           /*在右子树中找最小的元素填充删除结点*/ 
             BST->Data = Tmp->Data;  
             BST->Right = Delete2( BST->Data, BST->Right); 
                                    /*在删除结点的右子树中删除最小元素*/ 
         } else { /*被删除结点有一个或无子结点*/ 
             Tmp = BST;  
             if( !BST->Left ) /* 有右孩子或无子结点*/ 
                  BST = BST->Right;  
             else if( !BST->Right ) /*有左孩子或无子结点*/ 
                  BST = BST->Left; 
             free( Tmp ); 
         } 
    return BST; 
}





/*find函数的尾递归实现*/
// Position Find( BinTree BST, ElementType X )
// {
//     if (BST) {
//         if (X > BST->Data) {
//             BST = BST->Right;
//             return (Find(BST,X));
//         }else if (X < BST->Data){
//             BST = BST->Left;
//             return (Find(BST,X));
//         }else{
//             return BST;
//         }
//     }
//     return NULL;
// }

/*尾递归的执行效率往往没有while迭代的效率高，所以这里用迭代函数替代尾递归提高执行效率*/
Position Find( BinTree BST, ElementType X ){
    while (BST) {
        if (X > BST->Data) BST = BST->Right;
        else if (X < BST->Data) BST = BST->Left;
        else return BST;
    }
    return NULL;
}

/*最小的数字一定在树的最左边的节点上，所以一直往左搜索就行*/
Position FindMin( BinTree BST ){
    if(BST)
        while(BST->Left != NULL)BST = BST->Left;
    return BST;
}
/*同样，最大的肯定在树的最右边，一直往右搜索就是*/
Position FindMax( BinTree BST ){   
    if(BST)
        while(BST->Right != NULL)BST = BST->Right;
    return BST;
}