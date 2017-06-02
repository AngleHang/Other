#include <stdio.h>
#include <stdlib.h>
#include <time.h>	//time()
#include <conio.h>	//getch()
#include "seqlist.h"
#include "file.h"
#include "numeric.h"

void printMainMenu();
//��ӡ���˵�
void practice();
//��ϰģʽ
void compete();
//����ģʽ
void printPracticeMenu();
//��ӡ��ϰģʽ�˵�
void printCompetitionMenu();
//��ӡ����ģʽ�˵�
void printSignMenu();
//��ӡ����ѡ��˵�
void simpleArithmetic();
//������������ϰ
void mixedArithmetic();
//�������������ϰ
void teamCompetetion();
//����ģʽ�Ŷ���
void individualCompetetion();
//����ģʽ������

void printIndividualResult(SeqList list);
//��ӡ���˱������
void printTeamResult(SeqList list);
//��ӡС�������


int comparator(Competitor a,Competitor b);
//������
Status individualCompete(Competitor *e);
//���˾�����������
Status teamCompete(Competitor *e);
//С�龺����������
Status printCompetorResult(Competitor *e);
//��ӡ���˽������
Status printCompetorResult2(Competitor *e);
//��ӡС��������

int comparator(Competitor a,Competitor b){
	return a.point >= b.point;
}

Status individualCompete(Competitor *e){
	printf("\n\t***********�� %s ͬѧ����**********\n",e->name);
	// �������20��2-4λ�����ı��ʽ���������
	e->point = multExpressionGeneral2(20,'\0');
}

Status printCompetorResult(Competitor *e){
	printf("\t%s\t%3d��\t%s\n",e->name,e->point,e->point>60?"��Χ":"��̭");
}

Status teamCompete(Competitor *e){
	printf("\n\t***********�� %s С�鿪ʼ����***********\n",e->name);

	printf("\n\t***********��� 1 λͬѧ��ʼ����***********\n",e->name);
	// �������10��2-4λ�����ı��ʽ���������
	e->point = multExpressionGeneral2(10,'\0');

	printf("\n\t***********��� 2 λͬѧ��ʼ����***********\n",e->name);
	// �������10��2-4λ�����ı��ʽ���������
	e->point += multExpressionGeneral2(10,'\0');

	printf("\n\t***********��� 3 λͬѧ��ʼ����**********\n",e->name);
	// �������10��2-4λ�����ı��ʽ���������
	e->point += multExpressionGeneral2(10,'\0');

	e->point *= 2;
}

Status printCompetorResult2(Competitor *e){
	printf("\t%s\t%3d��\n",e->name,e->point);
}

void simpleArithmetic(){
	char sign[5]={'\0','+','-','*','/'};
	int choice;
	int point;
	do{
		printSignMenu();
		printf("\t��ѡ��������ţ�");
		scanf("%d", &choice);
		if(choice > 4 || choice < 1)
			printf("\t������Ĳ˵�����ڣ�������ѡ��!\n");
	}while(choice > 4 || choice < 1);
	do{
		point = simplePracticeGeneral(sign[choice]);
		if(point < 60){
			printf("���ĳɼ�С��60�֣������²��ԣ�\n");
			getch();
		}else{
			printf("��ϲ�������ı��γɼ�Ϊ %d �֣�\n",point);
		}
	}while(point < 60);
}

void mixedArithmetic(){
	int point; 
	do{
		point = mixedPracticeGeneral();
		if(point < 60){
			printf("���ĳɼ�С��60�֣������²��ԣ�\n");
			getch();
		}else{
			printf("��ϲ�������ı��γɼ�Ϊ %d �֣�\n",point);
		}
	}while(point < 60);
} 

void printMainMenu(){
	printf("\n\t***********������ϰ/����ϵͳ**********\n");
	printf("\t*             1 ƽ̨��ϰ             *\n");
	printf("\t*             2  ��  ��              *\n");
	printf("\t*             3 �˳�����             *\n");
	printf("\t**************************************\n");
}

void printPracticeMenu(){
	printf("\n\t************��ѡ����ϰģʽ************\n");
	printf("\t*           1 ����������           *\n");
	printf("\t*           2 �����������           *\n");
	printf("\t**************************************\n");
}

void printSignMenu(){
	printf("\n\t**************��ѡ�����**************\n");
	printf("\t*               1 + ��               *\n");
	printf("\t*               2 - ��               *\n");
	printf("\t*               3 * ��               *\n");
	printf("\t*               4 / ��               *\n");
	printf("\t**************************************\n");
}

void printCompetitionMenu(){
	printf("\n\t************��ѡ����ģʽ************\n");
	printf("\t*             1 С�龺��             *\n");
	printf("\t*             2 ���˾���             *\n");
	printf("\t**************************************\n");
}

void practice(){
	int choice;
	do{
		printPracticeMenu();
		printf("\t��ѡ��һ����ϰģʽ��");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			simpleArithmetic();
			break;
		case 2:
			mixedArithmetic();
			break;
		default:
			printf("\t������Ĳ˵�����ڣ�������ѡ��!\n");
		}
	}while(choice != 1 && choice!= 2);
}

void compete(){
	int choice;
	do{
		printCompetitionMenu();
		printf("\t��ѡ��һ������ģʽ��");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			teamCompetetion();
			break;
		case 2:
			individualCompetetion();
			break;
		default:
			printf("\t������Ĳ˵�����ڣ�������ѡ��!\n");
		}
	}while(choice != 1 && choice!= 2);
}

void printTeamResult(SeqList list){
	printf("\n\t***********С���������������**********\n");
	ListTraverse(&list,printCompetorResult2);
	printf("\n");
}

void teamCompetetion(){
	SeqList list;
	InitList(&list);
	if(loadCompetitorFromFile(&list,TEAM_DATA_FILE) == ERROR){
		printf("�޷��ҵ�С���������ļ���\n");
	}else if(ListLength(list) == 0){
		printf("С���������ļ�Ϊ�գ�û�в����ߣ�\n");
	}else{
		ListTraverse(&list,teamCompete);
		ListSort(&list,comparator);
		printTeamResult(list);
		if(saveTeamResult(list) == ERROR)
			printf("С���������������ʧ�ܣ�\n");
		else
			printf("С���������������ɹ���\n");;
	}
	getch();
}

void individualCompetetion(){
	SeqList list;
	InitList(&list);
	if(loadCompetitorFromFile(&list,INDIVIDUAL_DATA_FILE) == ERROR){
		printf("�޷��ҵ������������ļ���\n");
	}else if(ListLength(list) == 0){
		printf("�����������ļ�Ϊ�գ�û�в����ߣ�\n");
	}else{
		ListTraverse(&list,individualCompete);
		printIndividualResult(list);
		if(saveIndividualResult(list) == ERROR)
			printf("�����������������ʧ�ܣ�\n");
		else
			printf("�����������������ɹ���\n");;
	}
	getch();
}

void printIndividualResult(SeqList list){
	printf("\n\t***********�����������������**********\n");
	ListTraverse(&list,printCompetorResult);
	printf("\n");
}

int main(){
	int choice;
	srand(time(NULL));	//��ʼ�����������
	while (1)
	{
		choice = -1;
		printMainMenu();
		fflush(stdin); // ˢ�»�����
		printf("\t��ѡ��һ��ģʽ��");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			practice();
			break;
		case 2:
			compete();
			break;
		case 3:
			return 0;
		default:
			printf("\t������Ĳ˵�����ڣ�������ѡ��!\n");
		}
	}
	return 0;
}
