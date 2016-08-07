#include<stdio.h>
#define ROW 5
#define COLUMN 11
int a[3][3];
void mapping(int maze[][COLUMN],const int row,const int column){  //ӳ�亯��
    int i,j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            a[i][j]=maze[row+i-1][column+j-1];
        }
    }
}
void judge(char m,int *row,int *column){                 //�жϺ���
    switch(m){
        case 'A':
        case 'a':if(a[1][0]==0 || a[1][0]==4)*column-=1;
                 else printf("��������ȷ���ƶ�ָ��\n");break;
        case 'S':
        case 's':if(a[2][1]==0 || a[2][1]==4)*row+=1;
                 else printf("��������ȷ���ƶ�ָ��\n");break;
        case 'D':
        case 'd':if(a[1][2]==0 || a[1][2]==4)*column+=1;
                 else printf("��������ȷ���ƶ�ָ��\n");break;
        case 'W':
        case 'w':if(a[0][1]==0 || a[0][1]==4)*row-=1;
                 else printf("��������ȷ���ƶ�ָ��\n");break;
        default:printf("��������ȷ���ƶ�ָ��\n");
    }
}
void display(){                                       //��ʾ����
    int i,j;
	a[1][1]=5;
    printf("\n");
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(a[i][j]==0)printf("  ");
            else if(a[i][j]==1)printf("��");
            else if(a[i][j]==4)printf("��");
            else if(a[i][j]==5)printf("��");
    	}
        printf("\n");
    }
    printf("\n");
}
void initialize(int maze[][11]){
    int i,j;
    for(i=0;i<5;i++)for(j=0;j<11;j++)maze[i][j]=1;   //ȫ���ʼ
    for(j=1;j<10;j++)if(j!=2 && j!=7)maze[1][j]=0;   //��һ��
    maze[2][1]=0,maze[2][6]=0,maze[2][9]=0;          //�ڶ���
    for(j=1;j<10;j++)maze[3][j]=0;                   //������
    maze[1][3]=4;                                    //�����յ�
}
int main(){
	int maze[ROW][COLUMN];
    int m,i,j;
    int row_cur=1,column_cur=1;
    initialize(maze);
	printf("������WSAD�����������ң����س���ȷ�ϡ�\n");  //���濪ʼ�Ǳ���
	while(1){
        mapping(maze,row_cur,column_cur);
		display();
		scanf(" %c",&m);
        judge(m,&row_cur,&column_cur);
		if(maze[row_cur][column_cur]==4)break;
	}
	printf("\n��ϲ�߳��Թ�~\n");
    return 0;
}