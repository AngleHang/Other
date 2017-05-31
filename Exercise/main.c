#include <stdio.h>
#include <stdlib.h>
#include <time.h>		// time()
#include <conio.h>	// getch()
#include <ctype.h>	// tolower()
#include "exercise.h"

#define FILENAME "stk.txt"	//题库文件

//三种状态，无操作，已抽取题目，已答题完毕
//处于无操作状态只能抽取题目，不能答题和判题
//处于已抽取题目状态只能答题，不能再抽取和判题
//处于已答题完毕状态只能判题，不能再抽取和答题
//添加新题目与状态无关
#define NULLOP 0
#define LOAD 1
#define ANSWER 2

Status status;		//状态变量保存当前答题状态
SeqList exer;			//保存抽取到的题目
char answer[MAX];	//保存用户填写的答案

void menu();
//打印功能菜单
SeqList loadDataFromFile(const char *filename);
//从名为filename的文件中读取题库数据，返回装载数据的顺序表
Status saveDataToFile(const SeqList *list, const char *filename);
//将顺序表list的数据保存到名为filename的文件中，成功返回OK，否则返回ERROR
Status Print(QUE e);
//打印题目题干和选项
void readDataFromUser(QUE *stmp);
//从控制台读取用户输入，构建一道新试题
void insert();
//读取一道题目插入到试题库中。步骤：打开文件读取所有试题
//构建一道新题目，保存到顺序表中，将顺序表保存到文件
void find();
//提示用户输入要读取的条数
void modify();
void showAll();

void menu() {
	printf("\n\t*******单项选择题标准化考试系统*******\n");
	printf("\t*             1 试题录入             *\n");
	printf("\t*             2 试题抽取             *\n");
	printf("\t*             3 答题                 *\n");
	printf("\t*             4 自动判卷             *\n");
	printf("\t**************************************\n");
}

Status Print(QUE e) {
	printf("题干：%s\n", e.stem);
	printf("A：%s\n", e.A);
	printf("B：%s\n", e.B);
	printf("C：%s\n", e.C);
	printf("D：%s\n", e.D);
	printf("\n");
	return OK;
}

void insert() {
	SeqList list = loadDataFromFile(FILENAME);//读取试题库到顺序表
	QUE stmp;

	readDataFromUser(&stmp);//从控制台读取数据构建一道题目
	ListPushBack(&list, stmp);//将新试题保存在顺序表末尾
	saveDataToFile(&list, FILENAME);//将顺序表保存到文件

	printf("插入成功，请按任意键返回菜单！\n");
	getch();
}

void readDataFromUser(QUE *stmp) {
	printf("请输入要插入的试题:\n");

	printf("输入一个题目：");
	scanf("%s", stmp->stem);

	printf("输入备选选项A：");
	scanf("%s", stmp->A);

	printf("输入备选选项B：");
	scanf("%s", stmp->B);

	printf("输入备选选项C：");
	scanf("%s", stmp->C);

	printf("输入备选选项D：");
	scanf("%s", stmp->D);

	printf("输入正确答案：");
	scanf("%c", &stmp->standard);//消耗上一次输入时留下的'\n'
	scanf("%c", &stmp->standard);
}

/*随机平均抽取n道题的算法：
	1、首先将样本的前n个元素[0,n-1]添加到抽样集合中
	2、当接收到第i个元素时[n,list.length-1]，生成一个[0,i]之间的随机数random
		 若random<n，则用新元素替换list[j]
*/
void find()
{
	SeqList list, exercise;
	QUE e;
	int i, n, random;
	if (status != NULLOP) {	//判断状态能否抽取题目
		if(status == LOAD)
			printf("已经抽取过题目，请进行答题或判卷！\n");
		else if(status == ANSWER)
			printf("已经抽取过题目，请进行判卷！\n");
		getch();
		return;
	}

	list = loadDataFromFile(FILENAME);
	if (list.length == 0) {	// 判断题库中有无题目
		printf("题库数量为 0 ，请先添加题目！\n");
		getch();
		return;
	}

	do {	//提示用户输入一个[1,list.length]之间的数，抽取题目
		printf("请输入抽取的题目数量：");
		scanf("%d", &n);
		if (n > list.length || n < 1) {
			printf("题库现存题目数量为 %d 道，请输入正确的数字！\n", list.length);
		}
	} while (n > list.length || n < 1);

	InitList(&exercise);
	srand(time(NULL));//随机抽取算法，从所有题库中随机均匀抽取n到题目
	for (i = 0; i < list.length; ++i) {
		if (i < n) {//前n个元素直接加入
			GetElem(list, i, &e);
			ListPushBack(&exercise, e);
		}
		else {//此后的元素生成一个[0,i]之间的随机数random，若random<n，则用新元素替换之
			random = rand() % (i + 1);
			if (random < n) {
				QUE tmp;
				GetElem(list, i, &e);
				ListReplace(&exercise, random, &tmp, e);
			}
		}
	}
	ListTraverse(exercise,Print);//打印选取的题目
	printf("已随机抽取 %d 道题目，请返回菜单进行答题！\n", n);
	getch();
	status = LOAD;//修改状态为已抽取
	exer = exercise;//将抽取到的题目赋值给全局变量留待答题和判题使用
}

void modify() {
	int i;
	QUE e;
	if (status != LOAD) {//判断状态能否答题
		if(status == ANSWER)
			printf("已经答题完毕，请进行判卷！\n");
		else if(status == NULLOP)
			printf("请先抽取题目！\n");
		getch();
		return;
	}

	for (i = 0; i < exer.length; ++i) {//打印每道试题并读取用户答案储存在全局变量answer中
		GetElem(exer, i, &e);	//从顺序表取出
		Print(e);							//打印
		printf("请输入您的选项：");
		scanf("%c", &answer[i]);//消耗掉上一次输入留下的'\n'
		scanf("%c", &answer[i]);//回答
	}
	
	status = ANSWER;//修改状态

	do{
		i = -1;
		printf("答题完毕，请选择操作：\n");
		printf("1.进行判卷\n");
		printf("2.返回菜单\n");
		scanf("%d",&i);
		if(i!=1 && i!=2){
			printf("\t您输入的菜单项不存在，请重新选择!\n");
		}
	}while(i!=1 && i!=2);
	if(i==1)
		showAll();
}

void showAll() {
	int point = 0;
	int i;
	QUE e;
	if (status != ANSWER) {//判断状态能否判题
		if(status == NULLOP)
			printf("已经判卷完毕，请重新抽取题目并答题！\n");
		else if(status == LOAD)
			printf("请先作答所有题目！\n");
		getch();
		return;
	}

	for (i = 0; i < exer.length; ++i) {//比较每道试题与用户答案，相同则计分
		GetElem(exer, i, &e);	//取出
		if (tolower(e.standard) == tolower(answer[i]))//比较答案，忽略大小写
			++point;
	}

	printf("此次答题分数为 %d 分，按任意键返回菜单！\n", point);
	getch();
	status = NULLOP;//修改状态
}

SeqList loadDataFromFile(const char *filename) {
	SeqList list;
	QUE e;
	FILE *fp = fopen(filename, "r");	//以文本只读的形式打开文件
	InitList(&list);
	//若文件不存在，则创建一个新的空顺序表
	//否则读取题库信息，保存到顺序表中并返回
	if (fp != NULL){
		while(fscanf(fp,"%s%s%s%s%s %c",e.stem,e.A,e.B,e.C,e.D,&e.standard) != -1)
			ListPushBack(&list,e);
		fclose(fp);
	}
	return list;
}

Status saveDataToFile(const SeqList *list, const char *filename) {
	FILE *fp = fopen(filename, "w");	//以文本只写的形式打开文件
	int i;
	QUE e;
	if (fp == NULL)
		return ERROR;

	for(i=0;i<ListLength(*list);++i){ //将顺序表数据保存到题库中
		GetElem(*list,i,&e);
		fprintf(fp,"%s %s %s %s %s %c\n",e.stem,e.A,e.B,e.C,e.D,e.standard);
	}

	fclose(fp);
	return OK;
}

int main() {
	int choice = -1;
	status = NULLOP;	//初始化答题状态为无操作
	while (1)
	{
		menu();	// 打印菜案
		fflush(stdin); // 刷新缓冲区
		printf("\t请选择一个菜单项：");
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
			printf("\t您输入的菜单项不存在，请重新选择!\n");
		}

		choice = -1;			// 表示未选择菜单项 或者 菜单项选择错误
		//system("cls");		// 清屏，重新选择
	}
	return 0;
}
