#ifndef SEQLIST_H
#define SEQLIST_H

#define MAXSIZE 501	//字符串最大长度

// 单项选择题结构体
typedef struct {
	char stem[MAXSIZE];//题干
	char A[MAXSIZE];//A选项
	char B[MAXSIZE];//B选项
	char C[MAXSIZE];//C选项
	char D[MAXSIZE];//D选项
	char standard;//正确答案
}QUE;

#define MAX 100	//线性表最大长度
#define OK 0
#define ERROR -1
#define Status int
#define true 1
#define false 0

// 静态顺序表结构体
typedef struct
{
	QUE s[MAX];		// 存放线性表中的题目，数组大小MAX不能扩充，因此称其为“静态”
	int length;		// 当前表中元素的个数
} SeqList;

Status InitList(SeqList *list);
//初始化顺序表list
Status DestroyList(SeqList *list);
//销毁顺序表list
Status ListLength(SeqList list);
//返回顺序表list的长度
Status ListEmpty(SeqList list);
//若顺序表为空表，则返回true，否则返回false
Status ListInsert(SeqList *list, int position, QUE e);
//在顺序表list的position位置[0,length-1]插入数据元素e。若position位置非法或list已满，返回ERROR
Status ListPushBack(SeqList *list, QUE e);
//在顺序表list的末尾添加数据元素e。若list为空，返回ERROR
Status ListDelete(SeqList *list, int position, QUE *e);
//删除顺序表list的position位置上的数据元素，储存在e中，若position位置非法返回ERROR
Status ListReplace(SeqList *list, int position, QUE *old, QUE new);
//将顺序表list的position位置[0,length-1]插入数据元素new，旧元素存储在old中国，若position位置非法返回ERROR
Status GetElem(SeqList list, int position, QUE *e);
//返回顺序表list的position位置上的数据元素，储存在e中，若position位置非法返回ERROR
Status ListTraverse(SeqList list, Status(*visit)(QUE));
//依次对顺序表list的每个元素调用visit()，一旦调用失败，则操作失败

#endif
