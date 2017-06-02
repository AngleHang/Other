#ifndef NUMERIC_H
#define NUMERIC_H

int random(int n);
//产生一个n位数的随机数
int randomExpression(int n,char sign);
//根据位数和符号产生一条表达式打印到屏幕，并返回结果
int randomExpression2(int a,int b,char sign);
//根据两个数和符号产生一条表达式打印到屏幕，并返回结果
int simplePracticeGeneral(char sign);
//根据符号产生简单四则运算的套题，计算分数并返回
int mixedPracticeGeneral();
//根据随机符号和数字产生混合四则运算套题，计算分数并返回
int multExpressionGeneral(int t,int n,char sign);
//随机生成t道位数为n，符号为sign的表达式，计算分数并返回
int multExpressionGeneral2(int t,char sign);
//随机生成t道2-4位数，符号为sign的表达式，计算分数并返回

#endif
