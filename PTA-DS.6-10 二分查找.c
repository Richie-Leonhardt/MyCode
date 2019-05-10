//PTA-DS.6-10 二分查找
//数组的线性表的二分查找，以下标1开始存储元素
Position BinarySearch( List L, ElementType X ){
	if (X > L->Data[L->Last] || X < L->Data[1])return NotFound;
	//最后一个单独拎出来，通过循环不能够使mid最后与Last相同
	if (X == L->Data[L->Last])return L->Last;
	Position mid;
	Position left = 1;
	Position right = L->Last;
	
	while(mid != (left + right)/2){//一旦mid开始重复就说明已经找不到了，或是在最后一个，最后一个的情况前面已经搞定
		mid = (left + right)/2;
		if (L->Data[mid] == X){
			return mid;
		}else if(L->Data[mid] > X){
			right = mid;
		}else{
			left = mid;
		}
	}
	return NotFound;
}

//二分查找：通过每次移动下标加一位的方式来实现，这样不用末尾单独拎出来了
Position BinarySearch( List L, ElementType X ){
	if (X > L->Data[L->Last] || X < L->Data[1])return NotFound;
	Position mid, left = 1, right = L->Last;
	while(left <= right){			//left > right的时候就说明已经找不到了
		mid = (left + right)/2;
		if (L->Data[mid] < X){
			left = mid + 1;
		} else if(L->Data[mid] > X){
			right = mid - 1;
		} else {
			return mid;
		}
	}
	return NotFound;
}