#include <stdio.h>
#include <stdlib.h>
#include <time.h>		// time()
#include <conio.h>	// getch()
#include <ctype.h>	// tolower()
#include "exercise.h"

#define FILENAME "stk.txt"	//����ļ�

//����״̬���޲������ѳ�ȡ��Ŀ���Ѵ������
//�����޲���״ֻ̬�ܳ�ȡ��Ŀ�����ܴ��������
//�����ѳ�ȡ��Ŀ״ֻ̬�ܴ��⣬�����ٳ�ȡ������
//�����Ѵ������״ֻ̬�����⣬�����ٳ�ȡ�ʹ���
//�������Ŀ��״̬�޹�
#define NULLOP 0
#define LOAD 1
#define ANSWER 2

Status status;		//״̬�������浱ǰ����״̬
SeqList exer;			//�����ȡ������Ŀ
char answer[MAX];	//�����û���д�Ĵ�

void menu();
//��ӡ���ܲ˵�
SeqList loadDataFromFile(const char *filename);
//����Ϊfilename���ļ��ж�ȡ������ݣ�����װ�����ݵ�˳���
Status saveDataToFile(const SeqList *list, const char *filename);
//��˳���list�����ݱ��浽��Ϊfilename���ļ��У��ɹ�����OK�����򷵻�ERROR
Status Print(QUE e);
//��ӡ��Ŀ��ɺ�ѡ��
void readDataFromUser(QUE *stmp);
//�ӿ���̨��ȡ�û����룬����һ��������
void insert();
//��ȡһ����Ŀ���뵽������С����裺���ļ���ȡ��������
//����һ������Ŀ�����浽˳����У���˳����浽�ļ�
void find();
//��ʾ�û�����Ҫ��ȡ������
void modify();
void showAll();

void menu() {
	printf("\n\t*******����ѡ�����׼������ϵͳ*******\n");
	printf("\t*             1 ����¼��             *\n");
	printf("\t*             2 �����ȡ             *\n");
	printf("\t*             3 ����                 *\n");
	printf("\t*             4 �Զ��о�             *\n");
	printf("\t**************************************\n");
}

Status Print(QUE e) {
	printf("��ɣ�%s\n", e.stem);
	printf("A��%s\n", e.A);
	printf("B��%s\n", e.B);
	printf("C��%s\n", e.C);
	printf("D��%s\n", e.D);
	printf("\n");
	return OK;
}

void insert() {
	SeqList list = loadDataFromFile(FILENAME);//��ȡ����⵽˳���
	QUE stmp;

	readDataFromUser(&stmp);//�ӿ���̨��ȡ���ݹ���һ����Ŀ
	ListPushBack(&list, stmp);//�������Ᵽ����˳���ĩβ
	saveDataToFile(&list, FILENAME);//��˳����浽�ļ�

	printf("����ɹ����밴��������ز˵���\n");
	getch();
}

void readDataFromUser(QUE *stmp) {
	printf("������Ҫ���������:\n");

	printf("����һ����Ŀ��");
	scanf("%s", stmp->stem);

	printf("���뱸ѡѡ��A��");
	scanf("%s", stmp->A);

	printf("���뱸ѡѡ��B��");
	scanf("%s", stmp->B);

	printf("���뱸ѡѡ��C��");
	scanf("%s", stmp->C);

	printf("���뱸ѡѡ��D��");
	scanf("%s", stmp->D);

	printf("������ȷ�𰸣�");
	scanf("%c", &stmp->standard);//������һ������ʱ���µ�'\n'
	scanf("%c", &stmp->standard);
}

/*���ƽ����ȡn������㷨��
	1�����Ƚ�������ǰn��Ԫ��[0,n-1]��ӵ�����������
	2�������յ���i��Ԫ��ʱ[n,list.length-1]������һ��[0,i]֮��������random
		 ��random<n��������Ԫ���滻list[j]
*/
void find()
{
	SeqList list, exercise;
	QUE e;
	int i, n, random;
	if (status != NULLOP) {	//�ж�״̬�ܷ��ȡ��Ŀ
		if(status == LOAD)
			printf("�Ѿ���ȡ����Ŀ������д�����о�\n");
		else if(status == ANSWER)
			printf("�Ѿ���ȡ����Ŀ��������о�\n");
		getch();
		return;
	}

	list = loadDataFromFile(FILENAME);
	if (list.length == 0) {	// �ж������������Ŀ
		printf("�������Ϊ 0 �����������Ŀ��\n");
		getch();
		return;
	}

	do {	//��ʾ�û�����һ��[1,list.length]֮���������ȡ��Ŀ
		printf("�������ȡ����Ŀ������");
		scanf("%d", &n);
		if (n > list.length || n < 1) {
			printf("����ִ���Ŀ����Ϊ %d ������������ȷ�����֣�\n", list.length);
		}
	} while (n > list.length || n < 1);

	InitList(&exercise);
	srand(time(NULL));//�����ȡ�㷨�������������������ȳ�ȡn����Ŀ
	for (i = 0; i < list.length; ++i) {
		if (i < n) {//ǰn��Ԫ��ֱ�Ӽ���
			GetElem(list, i, &e);
			ListPushBack(&exercise, e);
		}
		else {//�˺��Ԫ������һ��[0,i]֮��������random����random<n��������Ԫ���滻֮
			random = rand() % (i + 1);
			if (random < n) {
				QUE tmp;
				GetElem(list, i, &e);
				ListReplace(&exercise, random, &tmp, e);
			}
		}
	}
	ListTraverse(exercise,Print);//��ӡѡȡ����Ŀ
	printf("�������ȡ %d ����Ŀ���뷵�ز˵����д��⣡\n", n);
	getch();
	status = LOAD;//�޸�״̬Ϊ�ѳ�ȡ
	exer = exercise;//����ȡ������Ŀ��ֵ��ȫ�ֱ����������������ʹ��
}

void modify() {
	int i;
	QUE e;
	if (status != LOAD) {//�ж�״̬�ܷ����
		if(status == ANSWER)
			printf("�Ѿ�������ϣ�������о�\n");
		else if(status == NULLOP)
			printf("���ȳ�ȡ��Ŀ��\n");
		getch();
		return;
	}

	for (i = 0; i < exer.length; ++i) {//��ӡÿ�����Ⲣ��ȡ�û��𰸴�����ȫ�ֱ���answer��
		GetElem(exer, i, &e);	//��˳���ȡ��
		Print(e);							//��ӡ
		printf("����������ѡ�");
		scanf("%c", &answer[i]);//���ĵ���һ���������µ�'\n'
		scanf("%c", &answer[i]);//�ش�
	}
	
	status = ANSWER;//�޸�״̬

	do{
		i = -1;
		printf("������ϣ���ѡ�������\n");
		printf("1.�����о�\n");
		printf("2.���ز˵�\n");
		scanf("%d",&i);
		if(i!=1 && i!=2){
			printf("\t������Ĳ˵�����ڣ�������ѡ��!\n");
		}
	}while(i!=1 && i!=2);
	if(i==1)
		showAll();
}

void showAll() {
	int point = 0;
	int i;
	QUE e;
	if (status != ANSWER) {//�ж�״̬�ܷ�����
		if(status == NULLOP)
			printf("�Ѿ��о���ϣ������³�ȡ��Ŀ�����⣡\n");
		else if(status == LOAD)
			printf("��������������Ŀ��\n");
		getch();
		return;
	}

	for (i = 0; i < exer.length; ++i) {//�Ƚ�ÿ���������û��𰸣���ͬ��Ʒ�
		GetElem(exer, i, &e);	//ȡ��
		if (tolower(e.standard) == tolower(answer[i]))//�Ƚϴ𰸣����Դ�Сд
			++point;
	}

	printf("�˴δ������Ϊ %d �֣�����������ز˵���\n", point);
	getch();
	status = NULLOP;//�޸�״̬
}

SeqList loadDataFromFile(const char *filename) {
	SeqList list;
	QUE e;
	FILE *fp = fopen(filename, "r");	//���ı�ֻ������ʽ���ļ�
	InitList(&list);
	//���ļ������ڣ��򴴽�һ���µĿ�˳���
	//�����ȡ�����Ϣ�����浽˳����в�����
	if (fp != NULL){
		while(fscanf(fp,"%s%s%s%s%s %c",e.stem,e.A,e.B,e.C,e.D,&e.standard) != -1)
			ListPushBack(&list,e);
		fclose(fp);
	}
	return list;
}

Status saveDataToFile(const SeqList *list, const char *filename) {
	FILE *fp = fopen(filename, "w");	//���ı�ֻд����ʽ���ļ�
	int i;
	QUE e;
	if (fp == NULL)
		return ERROR;

	for(i=0;i<ListLength(*list);++i){ //��˳������ݱ��浽�����
		GetElem(*list,i,&e);
		fprintf(fp,"%s %s %s %s %s %c\n",e.stem,e.A,e.B,e.C,e.D,e.standard);
	}

	fclose(fp);
	return OK;
}

int main() {
	int choice = -1;
	status = NULLOP;	//��ʼ������״̬Ϊ�޲���
	while (1)
	{
		menu();	// ��ӡ�˰�
		fflush(stdin); // ˢ�»�����
		printf("\t��ѡ��һ���˵��");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			insert();
			break;
		case 2:
			find();
			break;
		case 3:
			modify();
			break;
		case 4:
			showAll();
			break;
		default:
			printf("\t������Ĳ˵�����ڣ�������ѡ��!\n");
		}

		choice = -1;			// ��ʾδѡ��˵��� ���� �˵���ѡ�����
		//system("cls");		// ����������ѡ��
	}
	return 0;
}
