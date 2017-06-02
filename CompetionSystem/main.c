#include <stdio.h>
#include <stdlib.h>
#include <time.h>	//time()
#include <conio.h>	//getch()
#include "seqlist.h"
#include "file.h"
#include "numeric.h"

void printMainMenu();
//打印主菜单
void practice();
//练习模式
void compete();
//竞赛模式
void printPracticeMenu();
//打印练习模式菜单
void printCompetitionMenu();
//打印竞赛模式菜单
void printSignMenu();
//打印符号选择菜单
void simpleArithmetic();
//简单四则运算练习
void mixedArithmetic();
//混合四则运算练习
void teamCompetetion();
//竞赛模式团队赛
void individualCompetetion();
//竞赛模式个人赛

void printIndividualResult(SeqList list);
//打印个人比赛结果
void printTeamResult(SeqList list);
//打印小组赛结果


int comparator(Competitor a,Competitor b);
//排序函数
Status individualCompete(Competitor *e);
//个人竞赛比赛函数
Status teamCompete(Competitor *e);
//小组竞赛比赛函数
Status printCompetorResult(Competitor *e);
//打印个人结果函数
Status printCompetorResult2(Competitor *e);
//打印小组结果函数

int comparator(Competitor a,Competitor b){
	return a.point >= b.point;
}

Status individualCompete(Competitor *e){
	printf("\n\t***********请 %s 同学答题**********\n",e->name);
	// 随机生成20题2-4位整数的表达式，符号随机
	e->point = multExpressionGeneral2(20,'\0');
}

Status printCompetorResult(Competitor *e){
	printf("\t%s\t%3d分\t%s\n",e->name,e->point,e->point>60?"入围":"淘汰");
}

Status teamCompete(Competitor *e){
	printf("\n\t***********请 %s 小组开始答题***********\n",e->name);

	printf("\n\t***********请第 1 位同学开始答题***********\n",e->name);
	// 随机生成10题2-4位整数的表达式，符号随机
	e->point = multExpressionGeneral2(10,'\0');

	printf("\n\t***********请第 2 位同学开始答题***********\n",e->name);
	// 随机生成10题2-4位整数的表达式，符号随机
	e->point += multExpressionGeneral2(10,'\0');

	printf("\n\t***********请第 3 位同学开始答题**********\n",e->name);
	// 随机生成10题2-4位整数的表达式，符号随机
	e->point += multExpressionGeneral2(10,'\0');

	e->point *= 2;
}

Status printCompetorResult2(Competitor *e){
	printf("\t%s\t%3d分\n",e->name,e->point);
}

void simpleArithmetic(){
	char sign[5]={'\0','+','-','*','/'};
	int choice;
	int point;
	do{
		printSignMenu();
		printf("\t请选择运算符号：");
		scanf("%d", &choice);
		if(choice > 4 || choice < 1)
			printf("\t您输入的菜单项不存在，请重新选择!\n");
	}while(choice > 4 || choice < 1);
	do{
		point = simplePracticeGeneral(sign[choice]);
		if(point < 60){
			printf("您的成绩小于60分，请重新测试！\n");
			getch();
		}else{
			printf("恭喜您，您的本次成绩为 %d 分！\n",point);
		}
	}while(point < 60);
}

void mixedArithmetic(){
	int point; 
	do{
		point = mixedPracticeGeneral();
		if(point < 60){
			printf("您的成绩小于60分，请重新测试！\n");
			getch();
		}else{
			printf("恭喜您，您的本次成绩为 %d 分！\n",point);
		}
	}while(point < 60);
} 

void printMainMenu(){
	printf("\n\t***********心算练习/竞赛系统**********\n");
	printf("\t*             1 平台练习             *\n");
	printf("\t*             2  竞  赛              *\n");
	printf("\t*             3 退出程序             *\n");
	printf("\t**************************************\n");
}

void printPracticeMenu(){
	printf("\n\t************请选择练习模式************\n");
	printf("\t*           1 简单四则运算           *\n");
	printf("\t*           2 混合四则运算           *\n");
	printf("\t**************************************\n");
}

void printSignMenu(){
	printf("\n\t**************请选择符号**************\n");
	printf("\t*               1 + 加               *\n");
	printf("\t*               2 - 减               *\n");
	printf("\t*               3 * 乘               *\n");
	printf("\t*               4 / 除               *\n");
	printf("\t**************************************\n");
}

void printCompetitionMenu(){
	printf("\n\t************请选择竞赛模式************\n");
	printf("\t*             1 小组竞赛             *\n");
	printf("\t*             2 个人竞赛             *\n");
	printf("\t**************************************\n");
}

void practice(){
	int choice;
	do{
		printPracticeMenu();
		printf("\t请选择一个练习模式：");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			simpleArithmetic();
			break;
		case 2:
			mixedArithmetic();
			break;
		default:
			printf("\t您输入的菜单项不存在，请重新选择!\n");
		}
	}while(choice != 1 && choice!= 2);
}

void compete(){
	int choice;
	do{
		printCompetitionMenu();
		printf("\t请选择一个竞赛模式：");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			teamCompetetion();
			break;
		case 2:
			individualCompetetion();
			break;
		default:
			printf("\t您输入的菜单项不存在，请重新选择!\n");
		}
	}while(choice != 1 && choice!= 2);
}

void printTeamResult(SeqList list){
	printf("\n\t***********小组赛比赛结果如下**********\n");
	ListTraverse(&list,printCompetorResult2);
	printf("\n");
}

void teamCompetetion(){
	SeqList list;
	InitList(&list);
	if(loadCompetitorFromFile(&list,TEAM_DATA_FILE) == ERROR){
		printf("无法找到小组赛数据文件！\n");
	}else if(ListLength(list) == 0){
		printf("小组赛数据文件为空，没有参赛者！\n");
	}else{
		ListTraverse(&list,teamCompete);
		ListSort(&list,comparator);
		printTeamResult(list);
		if(saveTeamResult(list) == ERROR)
			printf("小组赛比赛结果保存失败！\n");
		else
			printf("小组赛比赛结果保存成功！\n");;
	}
	getch();
}

void individualCompetetion(){
	SeqList list;
	InitList(&list);
	if(loadCompetitorFromFile(&list,INDIVIDUAL_DATA_FILE) == ERROR){
		printf("无法找到个人赛数据文件！\n");
	}else if(ListLength(list) == 0){
		printf("个人赛数据文件为空，没有参赛者！\n");
	}else{
		ListTraverse(&list,individualCompete);
		printIndividualResult(list);
		if(saveIndividualResult(list) == ERROR)
			printf("个人赛比赛结果保存失败！\n");
		else
			printf("个人赛比赛结果保存成功！\n");;
	}
	getch();
}

void printIndividualResult(SeqList list){
	printf("\n\t***********个人赛比赛结果如下**********\n");
	ListTraverse(&list,printCompetorResult);
	printf("\n");
}

int main(){
	int choice;
	srand(time(NULL));	//初始化随机数种子
	while (1)
	{
		choice = -1;
		printMainMenu();
		fflush(stdin); // 刷新缓冲区
		printf("\t请选择一个模式：");
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
			printf("\t您输入的菜单项不存在，请重新选择!\n");
		}
	}
	return 0;
}
