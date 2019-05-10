//PTA-DS.6-11 先序输出叶结点
void PreorderPrintLeaves( BinTree BT ){
    if (BT == NULL){
        return;
    }
    if (BT->Left == NULL && BT->Right == NULL){
        printf(" %c",BT->Data );
    }
    PreorderPrintLeaves(BT->Left);
    PreorderPrintLeaves(BT->Right);
}