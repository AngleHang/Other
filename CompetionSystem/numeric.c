#include "numeric.h"

int random(int num){
	int offset = 0;	//偏移量
	int length = 10; //长度
	int tmp;
	int i;
	
	if(num != 1){
		offset = 1;
		tmp = num;
		while(--tmp>0)offset *= 10;
		length = offset * 9;
	}

	return rand() % length + offset;
}

int randomExpression2(int a,int b,char sign){
	int ret;
	printf("\t%4d %c %4d = ", a,sign,b);
	switch(sign){
		case '+':ret = a + b;break;
		case '-':ret = a - b;break;
		case '*':ret = a * b;break;
		case '/':ret = a / b;break;
	}
	return ret;
}

int randomExpression(int n,char sign){
	int a = random(n);
	int b = random(n);
	return randomExpression2(a,b,sign);
}

int multExpressionGeneral(int t,int n,char s){
	char sign[] = {'+','-','*','/'};
	int point = 0;
	int answer;
	int choice;
	while(t-->0){
		if(s)
			answer = randomExpression(n,s);
		else
			answer = randomExpression(n,sign[rand()%4]);

		scanf("%d",&choice);
		if(choice == answer)
			point += 5;
	}
	return point;
}

int multExpressionGeneral2(int t,char s){
	char sign[] = {'+','-','*','/'};
	int point = 0;
	int answer;
	int choice;
	int a,b;
	while(t-->0){
		a = random(rand()%3+2);
		b = random(rand()%3+2);
		if(s)
			answer = randomExpression2(a,b,s);
		else
			answer = randomExpression2(a,b,sign[rand()%4]);
		scanf("%d",&choice);
		if(choice == answer)
			point += 5;
	}
	return point;
}

int simplePracticeGeneral(char sign){
	int point = 0;
	// 随机生成2题2位整数的表达式
	point += multExpressionGeneral(2,2,sign);

	// 随机生成4题3位整数的表达式
	point += multExpressionGeneral(4,3,sign);

	// 随机生成6题4位整数的表达式
	point += multExpressionGeneral(6,4,sign);

	// 随机生成8题2-4位整数的表达式
	point += multExpressionGeneral2(8,sign);
	
	return point;
}

int mixedPracticeGeneral(){
	int point = 0;
	// 随机生成2题2位整数的表达式，符号随机
	point += multExpressionGeneral(2,2,'\0');

	// 随机生成4题3位整数的表达式，符号随机
	point += multExpressionGeneral(4,3,'\0');

	// 随机生成6题4位整数的表达式，符号随机
	point += multExpressionGeneral(6,4,'\0');

	// 随机生成8题2-4位整数的表达式，符号随机
	point += multExpressionGeneral2(8,'\0');
	
	return point;
}
