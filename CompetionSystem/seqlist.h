#ifndef SEQLIST_H
#define SEQLIST_H

#define STRLEN 21

typedef struct _{
	char name[STRLEN];
	int point;
}Competitor;

#define MAX 100	//线性表最大长度
#define OK 0
#define ERROR -1
#define Status int
#define true 1
#define false 0

// 静态顺序表结构体
typedef struct
{
	Competitor s[MAX];
	int length;
} SeqList;

Status InitList(SeqList *list);
//初始化顺序表list
Status DestroyList(SeqList *list);
//销毁顺序表list
Status ListLength(SeqList list);
//返回顺序表list的长度
Status ListEmpty(SeqList list);
//若顺序表为空表，则返回true，否则返回false
Status ListInsert(SeqList *list, int position, Competitor e);
//在顺序表list的position位置[0,length-1]插入数据元素e。若position位置非法或list已满，返回ERROR
Status ListPushBack(SeqList *list, Competitor e);
//在顺序表list的末尾添加数据元素e。若list为空，返回ERROR
Status ListDelete(SeqList *list, int position, Competitor *e);
//删除顺序表list的position位置上的数据元素，储存在e中，若position位置非法返回ERROR
Status ListReplace(SeqList *list, int position, Competitor *old, Competitor new);
//将顺序表list的position位置[0,length-1]插入数据元素new，旧元素存储在old中国，若position位置非法返回ERROR
Status GetElem(SeqList list, int position, Competitor *e);
//返回顺序表list的position位置上的数据元素，储存在e中，若position位置非法返回ERROR
Status ListTraverse(SeqList *list, Status(*visit)(Competitor*));
//依次对顺序表list的每个元素调用visit()，一旦调用失败，则操作失败
Status ListSort(SeqList *list,int (*comparator)(Competitor,Competitor));
//对顺序表list进行排序，排序规则由comparator指定

#endif
