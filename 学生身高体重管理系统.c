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
/* �˵� */
Student *p;
void Menu()
{
    system("cls");
    fflush(stdin);
    printf("ͨ������Ϣ����ѧԺ     ��׿Ⱥ    ����     ����ʤ     \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("************ѧ��������ع���ϵͳ****************\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("  1-¼��ѧ����Ϣ\n");
    printf("  2-��ӡȫ��ѧ����Ϣ\n");
    printf("  3-����������ѧ����Ϣ\n");
    printf("  4-��ѧ�Ų���ѧ����Ϣ\n");
    printf("  5-���Ա�ͳ��ѧ����Ϣ\n");
	  printf("  6-������ͳ��ѧ����Ϣ\n");
    printf("  0-�˳�\n");
}
/*��ʼ��*/
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
/*������ҳ*/
void back()
{
	system("cls");
	Menu();
}
/* �˳� */
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
/*ѡ��*/
void select()
{	int n;
	printf("  1-������ҳ\n");
  printf("  2-����ϵͳ\n");
	printf("\n������������: ");
	scanf("%d",&n);
	while(n!=1 && n!=2)
	{
		fflush(stdin);
		printf("\n������ı�Ŵ������������룺");
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
/*���������Ϣ*/
void Output_message(Student *p)
{
	printf("%4s%4s%4s%4lf%4lf%4s",p->id,p->name,p->sex,p->height,p->weight,p->shape);
}
/*���ѧ��*/
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
/*�������*/
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
/*����������*/
void Searchname_Student()
{
    char name[10];
    int i=0;
    Student *head=p->next;
    printf("��������Ҫ���ҵ�ѧ������:");
    do{
       gets(name);
       if(!Check_Name(name))

         printf("������������ȷ!��������:");

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
        printf("�Ҳ���������!");
    }
	select();
}
/*��ѧ�Ų���*/
void SearchID_Student()
{
    int i=0;
	char id[20];
    Student *head=p->next;
    printf("��������Ҫ���ҵ�ѧ��ѧ��:");
    do{
       gets(id);
       if(Check_ID(id)==0)
         printf("����ѧ�Ų���ȷ!��������:");

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
        printf("�Ҳ�����ѧ��!");
    }
	select();
}
/*���ȫ��ѧ����Ϣ*/
void Output_List(Student *head)
{
	int i;
	printf("    ѧ��    ����    �Ա�         ��ߣ�cm��         ���أ�kg��    ����\n");
	head=head->next;
  for(;head;head=head->next){
		printf("%8s%8s%8s%19lf%18lf%8s\n",head->id,head->name,head->sex, head->height,head->weight,head->shape);
	}
	select();
}
/*���Ա�ͳ��ѧ����Ϣ*/
void count_sex()
{
	int c,n;
	char sex[10];
	printf("ѡ����Ҫͳ�Ƶ�ѧ���Ա�\n");
	printf("1.����\n");
	printf("2.Ů��\n");
	printf("3.������ҳ\n");
	printf("������������: \n");
	scanf("%d",&n);
	while(n<1 || n>3);
	{
		fflush(stdin);
		printf("������ı�Ŵ������������룺\n");
		scanf("%d",&n);
	}
	switch(n)
	{
		case 1:strcpy(sex,"��");break;
		case 2:strcpy(sex,"Ů");break;
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
	printf("\n\n����ͳ�Ƶ�%s����%d��",sex[10],c);
	select();	
}
/*������ͳ��ѧ����Ϣ*/
void count_shape()
{
	int c,i,n;
	Student *p;
	char shape[10];
	printf("ѡ����Ҫͳ�Ƶ�ѧ������:\n");
	printf("1.��������\n");
	printf("2.����\n");
	printf("3.����\n");
	printf("4.����\n");
	printf("5.����\n");
	printf("6.������ҳ\n");
	printf("\n������������: ");
	scanf("%d",&n);
	while(n<1 || n>6)
	{
		printf("\n������ı�Ŵ������������룺");
		scanf("%d",&n);
	}
	switch(n)
	{
		case 1:strcpy(shape,"��������");break;
		case 2:strcpy(shape,"����");break;
		case 3:strcpy(shape,"����");break;
		case 4:strcpy(shape,"����");break;
		case 5:strcpy(shape,"����");break;
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
	printf("\n\n����ͳ�Ƶ�%s�Ĺ���%d��",&shape[10],&c);
	select();
}
Student *Input(){
    Student *head;
    double biaozhun;
    double temp;
    printf("������ѧ��(����0����¼��)��");
    head=(Student *)malloc(sizeof(Student));
    scanf("%s",&head->id);
    if(!strcmp(head->id,"0")){
        free(head);
        head=NULL;
        return NULL;
    }
    printf("������������");
    scanf("%s",head->name);
    printf("�������Ա�");
    scanf("%s",head->sex);
    printf("��������ߣ�");
    scanf("%lf",&head->height);
    printf("���������أ�");
    scanf("%lf",&head->weight);
    if(!strcmp("��",head->sex))biaozhun=head->height*0.9-90;
    else biaozhun=(head->height-105)*0.92;
    temp=head->weight-biaozhun;
    if(temp>biaozhun*0.2)strcpy(head->shape,"����");
    else if(temp>biaozhun*0.1&&temp<=biaozhun*0.2)strcpy(head->shape,"����");
    else if(temp<0&&-temp>biaozhun*0.2)strcpy(head->shape,"��������");
    else if(temp<0&&-temp>biaozhun*0.1&&-temp<=biaozhun*0.2)strcpy(head->shape,"����");
    else strcpy(head->shape,"����");
    return head;
}
/*������*/
int main()
{
	int x;
    Student *p;
    Student *head;
	  p=Init();
    Menu();
    while(1)
    {
      printf("\n������������: ");
      scanf("%d", &x);
      switch(x)
      {
        case 1:  //¼��ѧ����Ϣ
                 for(head=p;head->next;head=head->next);
                 head->next=Input();
                 printf("¼��ɹ�!!!\n");
                 break;
        case 2:  //��ӡ��������Ϣ
                 Output_List(p);
                 break;
        case 3:  //����������ѧ����Ϣ
                 Searchname_Student();
                 break;
        case 4:  //��ѧ�Ų���ѧ����Ϣ
                 SearchID_Student();
                 break;
		    case 5:  //���Ա�ͳ��ѧ����Ϣ
				         count_sex();
				         break;
		    case 6:  //������ͳ��ѧ����Ϣ
				         count_shape();
				         break;
        case 0: /*����*/
                 Quit();
                 break;
        default:printf("�������\n\n");
      }
	}
  return 0;
}
