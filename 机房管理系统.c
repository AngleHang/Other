#include <stdio.h>
#include <string.h>

#define TEA_LOGIN_FILE "admintea.txt"
#define STUD_LOGIN_FILE "adminstu.txt"
#define RECORD_FILE "records.txt"

#define MAXLENGTH 21
#define MAX_SIZE 500
#define COST_PER_HOUR 1.0
#define INIT_PWD "12345678"

typedef enum _flag {
	NORMAL, FROZEN
}Flag;

typedef struct _card {
	char num[MAXLENGTH];	//学号
	char name[MAXLENGTH];	//姓名
	char pwd[MAXLENGTH];	//密码
	char _class[MAXLENGTH];	//班级
	double money;			//余额
	Flag flag;				//是否挂失的标志
}Card;

typedef struct _time {
	int hour;
	int min;
	int sec;
}Time;

typedef struct _date {
	int year;
	int month;
	int day;
}Date;

typedef struct _record {
	char num[MAXLENGTH];	//学号
	Date date;				//上机日期
	Time start_time;		//开始时间
	Time use_time;			//上机使用时间
	char place[MAXLENGTH];	//上机地点
}Record;

Card cards[MAX_SIZE];
int cards_size;

Record records[MAX_SIZE];
int record_size;

void PrintMenuTea();							//打印管理员菜单
void PrintMenuStu();							//打印学生菜单
void PrintLogin();								//打印登录菜单
void PrintQueryMenu();							//打印查询子菜单
int getChoice(int start, int end);
int searchCardByNum(char *num);					//根据学号返回机卡的下标
void saveRecordToFile();
void readRecordFromFile();
void saveCardsToFile();
void readCardsFromFile();
void setDate(Date *date, int h, int m, int s);
void setTime(Time *t, int h, int m, int s);
Time getTime(int h, int m, int s);				//创建并返回该时间的Time
Date getDate(int h, int m, int s);				//创建并返回该日期的Date
int LoginTea();									//管理员登录
int LoginStu(char *num);						//学生登录，并传回学号
int RegisterStu();								//学生注册
int ChargeCard();								//充值机卡
int ChangePassword(char *num);					//修改密码
int LoseCard();									//机卡挂失
int RelieveCard();								//机卡解除挂失
void QueryRecord();								//查询记录子功能
void PrintRecord(Record record);				//打印一条上机记录
void PrintHead();
void DisplayAllRecord();
void QueryRecordByDate();
void QueryRecordByNum();
void mergeTime(int*, int*, int*);				//调整时分秒
void convertTime(int*, int*, int*, int);		//给定时间和次数求平均时间
int QueryMoney(char *num);						//查询给定学号机卡的余额
int QueryMyRecord(char *num);					//查询给定学号机卡的上机记录
int Login(char *num);							//上机
void getLoginDate(int*, int*, int*);
void getLoginTime(int*, int*, int*);
void getLoginPlace(char*);
void getLogoutTime(int*, int*, int*);
int getLegalInput(int start, int end, char *hint);
int legal_time(int h, int m, int s);

void PrintMenuTea() {                      		 //打印老师菜单
	printf("\n");
	printf("         ┌─────────────────────────────┐         \n");
	printf("         │                                                          │         \n");
	printf("         │            请选择操作项目：                              │         \n");
	printf("         │               1.注册机卡          2.充值机卡             │         \n");
	printf("         │               3.挂失机卡          4.查询统计             │         \n");
	printf("         │               5.解除挂失          0.退出系统             │         \n");
	printf("         └─────────────────────────────┘         \n");
}

void PrintMenuStu() {					         //打印学生菜单
	printf("\n");
	printf("         ┌─────────────────────────────┐         \n");
	printf("         │                                                          │         \n");
	printf("         │            请选择操作项目：                              │         \n");
	printf("         │               1.修改密码          2.查询余额             │         \n");
	printf("         │               3.查询记录          4.上    机             │         \n");
	printf("         │               0.退出系统                                 │         \n");
	printf("         └─────────────────────────────┘         \n");
}

void PrintLogin() {                               //打印登录界面
	printf("\n");
	printf("         ┌─────────────────────────────┐         \n");
	printf("         │                                                          │         \n");
	printf("         │                  请选择身份登录：                        │         \n");
	printf("         │                         1.管理员登录                     │         \n");
	printf("         │                         2.学生登录                       │         \n");
	printf("         │                         0.退出系统                       │         \n");
	printf("         └─────────────────────────────┘         \n");
}

void PrintQueryMenu() {                      		 //打印查询菜单
	printf("\n");
	printf("         ┌─────────────────────────────┐         \n");
	printf("         │                                                          │         \n");
	printf("         │            请选择查询方式：                              │         \n");
	printf("         │             1.显示所有记录    2.查询某天记录             │         \n");
	printf("         │             3.查询学生记录    0.返回上级菜单             │         \n");
	printf("         └─────────────────────────────┘         \n");
}

void setDate(Date *date, int y, int m, int d) {
	date->day = d;
	date->year = y;
	date->month = m;
}

void setTime(Time *t, int h, int m, int s) {
	t->hour = h;
	t->min = m;
	t->sec = s;
}

Time getTime(int h, int m, int s) {
	Time t;
	setTime(&t, h, m, s);
	return t;
}

Date getDate(int h, int m, int s) {
	Date d;
	setDate(&d, h, m, s);
	return d;
}

int searchCardByNum(char *num) {
	int i;
	for (i = 0; i < cards_size; ++i)
		if (!strcmp(cards[i].num, num))
			break;
	return i;
}

void saveCardsToFile() {
	FILE *fp;
	if ((fp = fopen(STUD_LOGIN_FILE, "wb")) != NULL) {
		fwrite(&cards_size, sizeof(int), 1, fp);
		fwrite(cards, sizeof(Card), cards_size, fp);
		fclose(fp);
	}
}

void readCardsFromFile() {
	FILE *fp;
	if ((fp = fopen(STUD_LOGIN_FILE, "rb")) != NULL) {
		fread(&cards_size, sizeof(int), 1, fp);
		fread(cards, sizeof(Card), cards_size, fp);
		fclose(fp);
	}
}

void readRecordFromFile() {
	FILE *fp;
	if ((fp = fopen(RECORD_FILE, "rb")) != NULL) {
		fread(&record_size, sizeof(int), 1, fp);
		fread(records, sizeof(Record), record_size, fp);
		fclose(fp);
	}
}

void saveRecordToFile() {
	FILE *fp;
	if ((fp = fopen(RECORD_FILE, "wb")) != NULL) {
		fwrite(&record_size, sizeof(int), 1, fp);
		fwrite(records, sizeof(Record), record_size, fp);
		fclose(fp);
	}
}

int RegisterStu() {								 //学生注册
	Card card;

	printf("请输入学号：");
	scanf("%s", card.num);

	if (searchCardByNum(card.num) != cards_size) {
		printf("学号为 %s 的机卡已注册！", card.num);
		return 0;
	}

	printf("请输入姓名：");
	scanf("%s", card.name);
	printf("请输入班级：");
	scanf("%s", card._class);

	card.money = 0;
	card.flag = NORMAL;
	strcpy(card.pwd, INIT_PWD);

	cards[cards_size++] = card;
	saveCardsToFile();

	printf("学号为 %s 的机卡注册成功！", card.num);
	return 1;
}

int ChargeCard() {
	char num[MAXLENGTH];
	int i;
	double money;

	printf("请输入学号：");
	scanf("%s", num);

	if ((i = searchCardByNum(num)) == cards_size) {
		printf("学号为 %s 的机卡不存在！", num);
		return 0;
	}
	else if (cards[i].flag == FROZEN) {
		printf("学号为 %s 的机卡状态异常，请先解冻后再操作！", num);
		return 0;
	}

	printf("请输入充值金额：");
	scanf("%lf", &money);
	while (money <= 0) {
		printf("金额错误，请输入大于0的数：");
		scanf("%lf", &money);
	}

	cards[i].money += money;
	saveCardsToFile();
	printf("学号为 %s 的机卡充值 %.2f 元，余额 %.2f 元!\n", num, money, cards[i].money);
	return 1;
}

int ChangePassword(char *num) {
	int i;
	char pwd[MAXLENGTH];
	char pwd_check[MAXLENGTH];

	if ((i = searchCardByNum(num)) == cards_size) {
		printf("学号为 %s 的机卡不存在！", num);
		return 0;
	}
	else if (cards[i].flag == FROZEN) {
		printf("学号为 %s 的机卡状态异常，请先解冻后再操作！", num);
		return 0;
	}

	do {
		printf("请输入密码：");
		scanf("%s", pwd);

		printf("请再次输入密码：");
		scanf("%s", pwd_check);

		if (strcmp(pwd, pwd_check))
			printf("两次密码不一致，请重新输入!\n");
	} while (strcmp(pwd, pwd_check));

	strcpy(cards[i].pwd, pwd);
	printf("密码修改成功!\n");
	saveCardsToFile();
	return 1;
}

int LoseCard() {
	char num[MAXLENGTH];
	int i;

	printf("请输入学号：");
	scanf("%s", num);

	if ((i = searchCardByNum(num)) == cards_size) {
		printf("学号为 %s 的机卡不存在！", num);
		return 0;
	}
	else if (cards[i].flag == FROZEN) {
		printf("学号为 %s 的机卡已经处于挂失状态！", num);
		return 0;
	}

	cards[i].flag = FROZEN;
	printf("学号为 %s 的机卡挂失成功!\n", num);
	saveCardsToFile();
	return 1;
}

int RelieveCard() {
	char num[MAXLENGTH];
	int i;

	printf("请输入学号：");
	scanf("%s", num);

	if ((i = searchCardByNum(num)) == cards_size) {
		printf("学号为 %s 的机卡不存在！", num);
		return 0;
	}
	else if (cards[i].flag == NORMAL) {
		printf("学号为 %s 的机卡已经处于正常状态！", num);
		return 0;
	}

	cards[i].flag = NORMAL;
	printf("学号为 %s 的机卡已恢复正常状态!\n", num);
	saveCardsToFile();
	return 1;
}

int LoginTea() {									 //教师登录
	char account[MAXLENGTH], password[MAXLENGTH];       	    //账号，密码
	char che_acc[MAXLENGTH] = { 0 }, che_pas[MAXLENGTH] = { 0 };       //检验账号，检验密码
	FILE *fp;
	int turn = 0;                                 //用于检验账号密码是否匹配

	if ((fp = fopen(TEA_LOGIN_FILE, "r")) == NULL) {
		printf("缺少管理员账号文件，请检查！");
		return 0;
	}

	printf("请输入管理员账号：");
	scanf("%s", account);
	printf("请输入密码：");
	scanf("%s", password);

	while (!feof(fp)) {
		fscanf(fp, "%s%s", che_acc, che_pas);
		if (!strcmp(che_acc, account) && !strcmp(che_pas, password)) {
			turn = 1;
			break;
		}
	}
	fclose(fp);

	if (turn) {
		printf("登录成功！");
	}
	else {
		printf("账号或密码错误，登录失败");
	}

	return turn;
}

void freezeCard(int i) {
	cards[i].flag = FROZEN;
	saveCardsToFile();
}

int LoginStu(char *num) {                                  //学生登录
	char account[MAXLENGTH], password[MAXLENGTH];       	    //账号，密码
	int turn = 0;                                 //用于检验账号密码是否匹配
	int t = 3;
	int i;

	printf("请输入您的学号：");
	scanf("%s", account);

	i = searchCardByNum(account);
	if (i == cards_size) {
		printf("学号不存在，请先由管理员注册机卡！");
		return 0;
	}
	else if (cards[i].money < 3) {
		printf("该机卡余额小于 3 元，请通知管理员充值后登录！");
		return 0;
	}
	else if (cards[i].flag == FROZEN) {
		printf("该机卡已被冻结，请通知管理员解除后登录！");
		return 0;
	}

	do {
		if (t != 3)
			printf("密码错误，你还有 %d 次尝试机会，请重新输入密码：", t);
		--t;

		printf("请输入密码：");
		scanf("%s", password);

		if (!strcmp(cards[i].pwd, password))
			turn = 1;
	} while (!turn && t > 0);

	if (!turn) {
		freezeCard(i);
		printf("3次密码错误，你的机卡已被冻结，请通知管理员接触冻结！");
	}
	else {
		printf("登录成功");
		strcpy(num, account);
	}

	return turn;
}

int getChoice(int start, int end) {
	int choice;
	do {
		choice = start - 1;
		scanf("%d", &choice);
		if (choice < start || choice > end) {
			printf("输入错误，请输入 %d~%d 之间的选项！\n", start, end);
		}
	} while (choice < start || choice > end);
	return choice;
}

void PrintRecord(Record record) {
	printf("%8s  ", record.num);
	printf("%4d/%2d/%2d  ", record.date.year, record.date.month, record.date.day);
	printf("%2d:%2d:%2d  ", record.start_time.hour, record.start_time.min, record.start_time.sec);
	printf("%2d:%2d:%2d  ", record.use_time.hour, record.use_time.min, record.use_time.sec);
	printf("%8s\n", record.place);
}

void PrintHead() {
	printf("%8s  %10s  %8s  %8s  %8s\n", "学生学号", "上机日期", "开始时间", "上机时长", "上机地点");
}

void mergeTime(int* hour, int* min, int* sec) {
	if (*sec < 0) {
		--(*min);
		*sec += 60;
	}
	if (*min < 0) {
		--(*hour);
		*min += 60;
	}

	*min += *sec / 60;
	*sec %= 60;

	*hour += *min / 60;
	*min %= 60;
}

void convertTime(int* hour, int* min, int* sec, int count) {
	int sec_total = *sec;
	sec_total += *min * 60;
	sec_total += *hour * 3600;

	sec_total /= count;

	*hour = sec_total / 3600;
	sec_total %= 3600;

	*min = sec_total / 60;
	sec_total %= 60;

	*sec = sec_total;
}

void DisplayAllRecord() {
	int i;
	int h, m, s;
	double cost;

	if (!record_size) {
		printf("无上机记录！\n");
		return;
	}

	h = m = s = 0;
	cost = 0;
	PrintHead();
	for (i = 0; i < record_size; ++i) {
		h += records[i].use_time.hour;
		m += records[i].use_time.min;
		s += records[i].use_time.sec;

		if (records[i].use_time.min == 0 && records[i].use_time.sec == 0)
			cost += records[i].use_time.hour * COST_PER_HOUR;
		else
			cost += (records[i].use_time.hour + 1) * COST_PER_HOUR;

		PrintRecord(records[i]);
	}

	mergeTime(&h, &m, &s);

	printf("\n上机总时数：  %2d:%2d:%2d  机房总收入：%4.2f  上机总次数：%4d\n", h, m, s, cost, record_size);
	convertTime(&h, &m, &s, record_size);
	printf("平均每次时数：%2d:%2d:%2d  机房平均收入：%4.2f\n", h, m, s, cost / record_size);
}

void QueryRecordByDate() {
	int y, m, d, i, c;
	int h, min, s;
	double cost;

	if (!record_size) {
		printf("无上机记录！\n");
		return;
	}

	printf("请输入年份：");
	scanf("%d", &y);
	printf("请输入月份：");
	scanf("%d", &m);
	printf("请输入日期：");
	scanf("%d", &d);

	h = min = s = c = 0;
	cost = 0;
	PrintHead();
	for (i = 0; i < record_size; ++i) {
		if (records[i].date.day == d && records[i].date.year == y && records[i].date.month) {
			++c;
			PrintRecord(records[i]);

			h += records[i].use_time.hour;
			min += records[i].use_time.min;
			s += records[i].use_time.sec;

			if (records[i].use_time.min == 0 && records[i].use_time.sec == 0)
				cost += records[i].use_time.hour * COST_PER_HOUR;
			else
				cost += (records[i].use_time.hour + 1) * COST_PER_HOUR;
		}
	}

	if (!c) {
		printf("无 %4d/%2d/%2d 的上机记录！\n", y, m, d);
		return 0;
	}

	mergeTime(&h, &min, &s);

	printf("\n上机总时数：  %2d:%2d:%2d  机房总收入：%4.2f  上机总次数：%4d\n", h, min, s, cost, c);
	convertTime(&h, &min, &s, c);
	printf("平均每次时数：%2d:%2d:%2d  机房平均收入：%4.2f\n", h, min, s, cost / c);
}

void QueryRecordByNum() {
	char num[MAXLENGTH];

	if (!record_size) {
		printf("无上机记录！\n");
		return;
	}

	printf("请输入学生学号：");
	scanf("%s", num);

	QueryMyRecord(num);
}

void QueryRecord() {
	int choice;
	while (1) {
		PrintQueryMenu();
		choice = getChoice(0, 3);

		switch (choice) {
		case 0:
			return;
		case 1:
			DisplayAllRecord();
			break;
		case 2:
			QueryRecordByDate();
			break;
		case 3:
			QueryRecordByNum();
			break;
		}
	}
}

int QueryMoney(char *num) {
	int i;

	if ((i = searchCardByNum(num)) == cards_size) {
		printf("学号为 %s 的机卡不存在！", num);
		return 0;
	}
	else if (cards[i].flag == FROZEN) {
		printf("学号为 %s 的机卡状态异常，请先解冻后再操作！", num);
		return 0;
	}

	printf("您的机卡余额为：%4.2f\n", cards[i].money);
	return 1;
}

int QueryMyRecord(char *num) {
	int h, m, s, c, i;
	double cost;

	h = m = s = c = 0;
	cost = 0;
	PrintHead();
	for (i = 0; i < record_size; ++i) {
		if (!strcmp(records[i].num, num)) {
			++c;
			PrintRecord(records[i]);

			h += records[i].use_time.hour;
			m += records[i].use_time.min;
			s += records[i].use_time.sec;

			if (records[i].use_time.min == 0 && records[i].use_time.sec == 0)
				cost += records[i].use_time.hour * COST_PER_HOUR;
			else
				cost += (records[i].use_time.hour + 1) * COST_PER_HOUR;
		}
	}

	if (!c) {
		printf("无学号为 %s 的上机记录！\n", num);
		return;
	}

	mergeTime(&h, &m, &s);

	printf("\n上机总时数：  %2d:%2d:%2d  机房总收入：%4.2f  上机总次数：%4d\n", h, m, s, cost, c);
	convertTime(&h, &m, &s, c);
	printf("平均每次时数：%2d:%2d:%2d  机房平均收入：%4.2f\n", h, m, s, cost / c);
	return 1;
}

int getLegalInput(int start, int end, char *hint) {
	int ret;
	do {
		ret = start - 1;
		scanf("%d", &ret);
		if (ret < start || ret > end) {
			printf(hint);
		}
	} while (ret < start || ret > end);
	return ret;
}

void getLoginDate(int* year, int* month, int* day) {
	printf("请手动输入上机年份：");
	*year = getLegalInput(1970, 2500, "请输入 1970～2500 之间的年份！\n");
	printf("请手动输入上机月份：");
	*month = getLegalInput(1, 12, "请输入正确的年份！\n");
	printf("请手动输入上机日期：");
	*day = getLegalInput(1, 31, "请输入正确的日期！\n");   // review
}

int legal_time(int h, int m, int s) {
	if (h>23 || h<0)
		return 0;
	if (m>59 || m<0)
		return 0;
	if (s>59 || s<0)
		return 0;
	return 1;
}

void getLoginTime(int* hour, int* min, int* sec) {
	char t[MAXLENGTH];
	int h, m, s;

	do {
		printf("请手动输入上机时间（格式：\"时:分:秒\"）：");
		scanf("%s", t);
		sscanf(t, "%d:%d:%d", &h, &m, &s);
		if (!legal_time(h, m, s))
			sscanf(t, "%d：%d：%d", &h, &m, &s);
		if (!legal_time(h, m, s))
			printf("时间格式错误，请重新输入！\n");
	} while (!legal_time(h, m, s));

	*hour = h;
	*min = m;
	*sec = s;
}

void getLoginPlace(char* place) {
	printf("请手动输入上机地点：");
	scanf("%s", place);
}

void getLogoutTime(int* hour, int* min, int* sec) {
	char t[MAXLENGTH];
	int h, m, s;

	do {
		printf("请手动输入下机时间（格式：\"时:分:秒\"）：");
		scanf("%s", t);
		sscanf(t, "%d:%d:%d", &h, &m, &s);
		if (!legal_time(h, m, s))
			printf("时间格式错误，请重新输入！\n");
	} while (!legal_time(h, m, s));

	*hour = h;
	*min = m;
	*sec = s;
}

int Login(char *num) {
	Record record;
	double cost;
	int i;
	int h, m, s;
	int flag;

	if ((i = searchCardByNum(num)) == cards_size) {
		printf("学号为 %s 的机卡不存在！", num);
		return 0;
	}
	else if (cards[i].flag == FROZEN) {
		printf("学号为 %s 的机卡状态异常，请先解冻后再操作！", num);
		return 0;
	}

	getLoginDate(&record.date.year, &record.date.month, &record.date.day);
	getLoginTime(&record.start_time.hour, &record.start_time.min, &record.start_time.sec);
	getLoginPlace(record.place);

	strcpy(record.num, num);

	do {
		flag = 0;
		getLogoutTime(&h, &m, &s);

		record.use_time.hour = h - record.start_time.hour;
		if (record.use_time.hour < 0)
			record.use_time.hour += 24;
		record.use_time.min = m - record.start_time.min;
		record.use_time.sec = s - record.start_time.sec;

		mergeTime(&record.use_time.hour, &record.use_time.min, &record.use_time.sec);

		if (record.use_time.min == 0 && record.use_time.sec == 0)
			cost = record.use_time.hour * COST_PER_HOUR;
		else
			cost = (record.use_time.hour + 1) * COST_PER_HOUR;

		if (cost > cards[i].money) {
			flag = 1;
			printf("余额不足以支付到此下机时间，请重新输入！\n");
		}
	} while (flag);

	records[record_size++] = record;
	cards[i].money -= cost;
	saveRecordToFile();
	return 1;
}

int main() {
	int turn = 0;			//检验是否登录或注册成功的开关
	int choice;
	int admin = 0;		//检验用户是以教师或学生身份登录的开关
	char num[MAXLENGTH];
	readCardsFromFile();
	readRecordFromFile();
	while (1) {
		if (admin == 0) {
			turn = 0;
			PrintLogin();
			choice = getChoice(0, 2);

			switch (choice) {
			case 0:
				return 0;
			case 1:
				turn = LoginTea();
				break;
			case 2:
				turn = LoginStu(num);
				break;
			}

			if (turn == 1) {
				admin = choice;
			}
		}
		else if (admin == 1) {
			PrintMenuTea();
			choice = getChoice(0, 5);

			switch (choice) {
			case 0:
				return 0;
			case 1:
				RegisterStu();
				break;
			case 2:
				ChargeCard();
				break;
			case 3:
				LoseCard();
				break;
			case 4:
				QueryRecord();
				break;
			case 5:
				RelieveCard();
				break;
			}
		}
		else if (admin == 2) {
			PrintMenuStu();
			choice = getChoice(0, 4);

			switch (choice) {
			case 0:
				return 0;
			case 1:
				ChangePassword(num);
				break;
			case 2:
				QueryMoney(num);
				break;
			case 3:
				QueryMyRecord(num);
				break;
			case 4:
				Login(num);
				break;
			}
		}
	}
	return 0;
}
