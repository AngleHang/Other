#include "seqlist.h"
#include <stdlib.h> 

Status InitList(SeqList *list) {
	if (list == NULL)return ERROR;
	list->length = 0;
	return OK;
}

Status DestroyList(SeqList *list) {
	return InitList(list);
}

int ListLength(SeqList list) {
	return list.length;
}

Status ListEmpty(SeqList list) {
	return list.length == 0 ? true : false;
}

Status ListInsert(SeqList *list, int position, Competitor e) {
	int i;
	if (list == NULL)return ERROR;
	if (position<0 || position>list->length)return ERROR;	//判断position是否合法,可以插入到[0,length]之间的位置
	if (list->length == MAX)return ERROR;					//判断顺序表是否已满
	for (i = list->length - 1; i >= position; i--) {					//将position及其以后的元素向后移动一位
		list->s[i + 1] = list->s[i];
	}
	list->s[position] = e;								//插入新的元素，长度增加
	++list->length;
	return OK;
}

Status ListPushBack(SeqList *list, Competitor e) {
	return ListInsert(list, list->length, e);//在末尾添加
}

Status ListDelete(SeqList *list, int position, Competitor *e) {
	int i;
	if (list == NULL)return ERROR;
	if (position < 0 || position >= list->length)return ERROR;	//判断position是否合法
	*e = list->s[position];							//取出待删除元素
	for (i = position + 1; i < list->length; i++) {					//将position以后的元素(不包括position)向前移动一位
		list->s[i - 1] = list->s[i];
	}
	--list->length;
	return OK;
}

Status ListReplace(SeqList *list, int position, Competitor *old, Competitor new) {
	if (list == NULL)return ERROR;
	if (position < 0 || position >= list->length)return ERROR;	//判断position是否合法
	*old = list->s[position];							//取出待替换元素
	list->s[position] = new;							//用新元素替换之
	return OK;
}

Status GetElem(SeqList list, int position, Competitor *e) {
	if (position < 0 || position >= list.length)return ERROR;
	*e = list.s[position];
	return OK;
}

Status ListTraverse(SeqList *list, Status(*visit)(Competitor*)) {
	int i;
	for (i = 0; i < list->length; i++)
		if (visit(&list->s[i]) == ERROR)
			return ERROR;
	return OK;
}

Status ListSort(SeqList *list,int (*comparator)(Competitor,Competitor)){
	int len = list->length;
	int i,j;
	int index;
	Competitor a,b;
	for(i=0;i<len;++i){
		index = i;
		for(j=i+1;j<len;++j){
			GetElem(*list,index,&a);
			GetElem(*list,j,&b);
			if(!comparator(a,b)){
				index = j;
			}
		}
		if(index != i){
			GetElem(*list,index,&a);
			GetElem(*list,i,&b);
			ListReplace(list,index,&b,b);
			ListReplace(list,i,&a,a);
		}
	}
}
