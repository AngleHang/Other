#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  MAXID 10
#define  MAXNAME 20
#define N 50
typedef struct node
{
    char id[20];
    char name[15];
    char sex[10];
    double height;
    double weight;
    char shape[10];
	struct node *next;
}Student;
/* 菜单 */
Student *p;
void Menu()
{
    system("cls");
    fflush(stdin);
    printf("通信与信息工程学院     刘卓群    汤恒     孙善胜     \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("************学生身高体重管理系统****************\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("  1-录入学生信息\n");
    printf("  2-打印全部学生信息\n");
    printf("  3-按姓名查找学生信息\n");
    printf("  4-按学号查找学生信息\n");
    printf("  5-按性别统计学生信息\n");
	  printf("  6-按体型统计学生信息\n");
    printf("  0-退出\n");
}
/*初始化*/
Student *Init()
{
    Student *head;
    Student *pf,*pb;
    FILE *fp;
    head=(Student *)malloc(sizeof(Student));
    pb=head->next=NULL;
    pf=head;
    fp=fopen("studata.dat","r");
    if(!fp)return head;
    else{
        while(!feof(fp))
        {
            pb=(Student *)malloc(sizeof(Student));
            pf->next=pb;
            pf=pb;
            fscanf(fp, "%s%s%s%lf%lf%s", pb->id, pb->name, pb->sex, &pb->height,&pb->weight,pb->shape);  
        }
        pf->next=NULL;
        fclose(fp);
    }
    return head;
}
/*返回首页*/
void back()
{
	system("cls");
	Menu();
}
/* 退出 */
void Quit()
{
    FILE *fp;
    Student *head;
    fp=fopen("studata.dat","a");
    head=p->next;
    for(;head;head=head->next)
    {
        fprintf(fp, "%s %s %s %lf %lf %s\n", head->id, head->name, head->sex, &head->height,&head->weight,head->shape);
    }
    exit(0);
}
/*选择*/
void select()
{	int n;
	printf("  1-返回首页\n");
  printf("  2-结束系统\n");
	printf("\n请输入命令编号: ");
	scanf("%d",&n);
	while(n!=1 && n!=2)
	{
		fflush(stdin);
		printf("\n你输入的编号错误，请重新输入：");
		scanf("%d",&n);
	}
	switch(n)
	{
		case 1:back();
			   break;
		case 2:Quit();
			   break;
	}
}
/*输出个人信息*/
void Output_message(Student *p)
{
	printf("%4s%4s%4s%4lf%4lf%4s",p->id,p->name,p->sex,p->height,p->weight,p->shape);
}
/*检查学号*/
char Check_ID(char *s)
{
    int i;
    int turn=1;
    if(strlen(s)==0||strlen(s)>MAXID)return 0;
    for(i=0;i<strlen(s);i++)
    {
     if (s[i] > '9' || s[i] < '0')turn=0;
    }
    if(turn)return 1;
    else return 0;
}
/*检查姓名*/
char Check_Name(char *s)
{
    int i;
    int turn=1;
    if(strlen(s)==0||strlen(s)>MAXNAME) return 0;

    for(i=0; i<strlen(s); i++)
    {
        if(!(s[i] <='z' && s[i] >='a') || !(s[i] >= 'A' &&  s[i] <= 'Z'))
        turn=0;;
    }
    if(turn)return 1;
    else return 0;
}
/*按姓名查找*/
void Searchname_Student()
{
    char name[10];
    int i=0;
    Student *head=p->next;
    printf("请输入你要查找的学生姓名:");
    do{
       gets(name);
       if(!Check_Name(name))

         printf("输入姓名不正确!重新输入:");

    }while(!Check_Name(name));

    while(head!=NULL)
    {
        if(strcmp(head->name,name)==0)
         {
             Output_message(head);
             i=1;
         }
        head=head->next;
    }
    if(i==0)
    {
        printf("找不到此姓名!");
    }
	select();
}
/*按学号查找*/
void SearchID_Student()
{
    int i=0;
	char id[20];
    Student *head=p->next;
    printf("请输入你要查找的学生学号:");
    do{
       gets(id);
       if(Check_ID(id)==0)
         printf("输入学号不正确!重新输入:");

    }while(!Check_ID(id));
    
	while(head!=NULL)
    {
        if(strcmp(head->id,id)==0)
         {
             Output_message(head);
			 i=1;
         }
        head=head->next;
    }
    if(i==0)
    {
        printf("找不到此学号!");
    }
	select();
}
/*输出全体学生信息*/
void Output_List(Student *head)
{
	int i;
	printf("    学号    姓名    性别         身高（cm）         体重（kg）    体型\n");
	head=head->next;
  for(;head;head=head->next){
		printf("%8s%8s%8s%19lf%18lf%8s\n",head->id,head->name,head->sex, head->height,head->weight,head->shape);
	}
	select();
}
/*按性别统计学生信息*/
void count_sex()
{
	int c,n;
	char sex[10];
	printf("选择你要统计的学生性别\n");
	printf("1.男生\n");
	printf("2.女生\n");
	printf("3.返回首页\n");
	printf("请输入命令编号: \n");
	scanf("%d",&n);
	while(n<1 || n>3);
	{
		fflush(stdin);
		printf("你输入的编号错误，请重新输入：\n");
		scanf("%d",&n);
	}
	switch(n)
	{
		case 1:strcpy(sex,"男");break;
		case 2:strcpy(sex,"女");break;
		case 3:back();return;
	}
	while(p!=NULL)
    {
        if(!strcmp(p->sex,sex))
         {
             Output_message(p);
			 c++;
         }
        p=p->next;
    }
	printf("\n\n你所统计的%s共有%d人",sex[10],c);
	select();	
}
/*按体型统计学生信息*/
void count_shape()
{
	int c,i,n;
	Student *p;
	char shape[10];
	printf("选择你要统计的学生体型:\n");
	printf("1.严重消瘦\n");
	printf("2.消瘦\n");
	printf("3.正常\n");
	printf("4.过重\n");
	printf("5.肥胖\n");
	printf("6.返回首页\n");
	printf("\n请输入命令编号: ");
	scanf("%d",&n);
	while(n<1 || n>6)
	{
		printf("\n你输入的编号错误，请重新输入：");
		scanf("%d",&n);
	}
	switch(n)
	{
		case 1:strcpy(shape,"严重消瘦");break;
		case 2:strcpy(shape,"消瘦");break;
		case 3:strcpy(shape,"正常");break;
		case 4:strcpy(shape,"过重");break;
		case 5:strcpy(shape,"肥胖");break;
		case 6:back();return;
	}
	while(p!=NULL)
    {
        if(strcmp(p->shape,shape)==0)
         {
             Output_message(p);
			 c++;
         }
        p=p->next;
    }
	printf("\n\n你所统计的%s的共有%d人",&shape[10],&c);
	select();
}
Student *Input(){
    Student *head;
    double biaozhun;
    double temp;
    printf("请输入学号(输入0结束录入)：");
    head=(Student *)malloc(sizeof(Student));
    scanf("%s",&head->id);
    if(!strcmp(head->id,"0")){
        free(head);
        head=NULL;
        return NULL;
    }
    printf("请输入姓名：");
    scanf("%s",head->name);
    printf("请输入性别：");
    scanf("%s",head->sex);
    printf("请输入身高：");
    scanf("%lf",&head->height);
    printf("请输入体重：");
    scanf("%lf",&head->weight);
    if(!strcmp("男",head->sex))biaozhun=head->height*0.9-90;
    else biaozhun=(head->height-105)*0.92;
    temp=head->weight-biaozhun;
    if(temp>biaozhun*0.2)strcpy(head->shape,"肥胖");
    else if(temp>biaozhun*0.1&&temp<=biaozhun*0.2)strcpy(head->shape,"过重");
    else if(temp<0&&-temp>biaozhun*0.2)strcpy(head->shape,"严重消瘦");
    else if(temp<0&&-temp>biaozhun*0.1&&-temp<=biaozhun*0.2)strcpy(head->shape,"消瘦");
    else strcpy(head->shape,"正常");
    return head;
}
/*主函数*/
int main()
{
	int x;
    Student *p;
    Student *head;
	  p=Init();
    Menu();
    while(1)
    {
      printf("\n请输入命令编号: ");
      scanf("%d", &x);
      switch(x)
      {
        case 1:  //录入学生信息
                 for(head=p;head->next;head=head->next);
                 head->next=Input();
                 printf("录入成功!!!\n");
                 break;
        case 2:  //打印出所有信息
                 Output_List(p);
                 break;
        case 3:  //按姓名查找学生信息
                 Searchname_Student();
                 break;
        case 4:  //按学号查找学生信息
                 SearchID_Student();
                 break;
		    case 5:  //按性别统计学生信息
				         count_sex();
				         break;
		    case 6:  //按体型统计学生信息
				         count_shape();
				         break;
        case 0: /*结束*/
                 Quit();
                 break;
        default:printf("输入错误！\n\n");
      }
	}
  return 0;
}
