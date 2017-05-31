#include "exercise.h"
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

Status ListInsert(SeqList *list, int position, QUE e) {
	int i;
	if (list == NULL)return ERROR;
	if (position<0 || position>list->length)return ERROR;	//�ж�position�Ƿ�Ϸ�,���Բ��뵽[0,length]֮���λ��
	if (list->length == MAX)return ERROR;					//�ж�˳����Ƿ�����
	for (i = list->length - 1; i >= position; i--) {					//��position�����Ժ��Ԫ������ƶ�һλ
		list->s[i + 1] = list->s[i];
	}
	list->s[position] = e;								//�����µ�Ԫ�أ���������
	++list->length;
	return OK;
}

Status ListPushBack(SeqList *list, QUE e) {
	return ListInsert(list, list->length, e);//��ĩβ���
}

Status ListDelete(SeqList *list, int position, QUE *e) {
	int i;
	if (list == NULL)return ERROR;
	if (position < 0 || position >= list->length)return ERROR;	//�ж�position�Ƿ�Ϸ�
	*e = list->s[position];							//ȡ����ɾ��Ԫ��
	for (i = position + 1; i < list->length; i++) {					//��position�Ժ��Ԫ��(������position)��ǰ�ƶ�һλ
		list->s[i - 1] = list->s[i];
	}
	--list->length;
	return OK;
}

Status ListReplace(SeqList *list, int position, QUE *old, QUE new) {
	if (list == NULL)return ERROR;
	if (position < 0 || position >= list->length)return ERROR;	//�ж�position�Ƿ�Ϸ�
	*old = list->s[position];							//ȡ�����滻Ԫ��
	list->s[position] = new;							//����Ԫ���滻֮
	return OK;
}

Status GetElem(SeqList list, int position, QUE *e) {
	if (position < 0 || position >= list.length)return ERROR;
	*e = list.s[position];
	return OK;
}

Status ListTraverse(SeqList list, Status(*visit)(QUE)) {
	int i;
	for (i = 0; i < list.length; i++)
		if (visit(list.s[i]) == ERROR)
			return ERROR;
	return OK;
}
