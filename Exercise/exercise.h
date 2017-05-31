#ifndef SEQLIST_H
#define SEQLIST_H

#define MAXSIZE 501	//�ַ�����󳤶�

// ����ѡ����ṹ��
typedef struct {
	char stem[MAXSIZE];//���
	char A[MAXSIZE];//Aѡ��
	char B[MAXSIZE];//Bѡ��
	char C[MAXSIZE];//Cѡ��
	char D[MAXSIZE];//Dѡ��
	char standard;//��ȷ��
}QUE;

#define MAX 100	//���Ա���󳤶�
#define OK 0
#define ERROR -1
#define Status int
#define true 1
#define false 0

// ��̬˳���ṹ��
typedef struct
{
	QUE s[MAX];		// ������Ա��е���Ŀ�������СMAX�������䣬��˳���Ϊ����̬��
	int length;		// ��ǰ����Ԫ�صĸ���
} SeqList;

Status InitList(SeqList *list);
//��ʼ��˳���list
Status DestroyList(SeqList *list);
//����˳���list
Status ListLength(SeqList list);
//����˳���list�ĳ���
Status ListEmpty(SeqList list);
//��˳���Ϊ�ձ��򷵻�true�����򷵻�false
Status ListInsert(SeqList *list, int position, QUE e);
//��˳���list��positionλ��[0,length-1]��������Ԫ��e����positionλ�÷Ƿ���list����������ERROR
Status ListPushBack(SeqList *list, QUE e);
//��˳���list��ĩβ�������Ԫ��e����listΪ�գ�����ERROR
Status ListDelete(SeqList *list, int position, QUE *e);
//ɾ��˳���list��positionλ���ϵ�����Ԫ�أ�������e�У���positionλ�÷Ƿ�����ERROR
Status ListReplace(SeqList *list, int position, QUE *old, QUE new);
//��˳���list��positionλ��[0,length-1]��������Ԫ��new����Ԫ�ش洢��old�й�����positionλ�÷Ƿ�����ERROR
Status GetElem(SeqList list, int position, QUE *e);
//����˳���list��positionλ���ϵ�����Ԫ�أ�������e�У���positionλ�÷Ƿ�����ERROR
Status ListTraverse(SeqList list, Status(*visit)(QUE));
//���ζ�˳���list��ÿ��Ԫ�ص���visit()��һ������ʧ�ܣ������ʧ��

#endif
