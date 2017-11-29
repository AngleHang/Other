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
	char num[MAXLENGTH];	//ѧ��
	char name[MAXLENGTH];	//����
	char pwd[MAXLENGTH];	//����
	char _class[MAXLENGTH];	//�༶
	double money;			//���
	Flag flag;				//�Ƿ��ʧ�ı�־
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
	char num[MAXLENGTH];	//ѧ��
	Date date;				//�ϻ�����
	Time start_time;		//��ʼʱ��
	Time use_time;			//�ϻ�ʹ��ʱ��
	char place[MAXLENGTH];	//�ϻ��ص�
}Record;

Card cards[MAX_SIZE];
int cards_size;

Record records[MAX_SIZE];
int record_size;

void PrintMenuTea();							//��ӡ����Ա�˵�
void PrintMenuStu();							//��ӡѧ���˵�
void PrintLogin();								//��ӡ��¼�˵�
void PrintQueryMenu();							//��ӡ��ѯ�Ӳ˵�
int getChoice(int start, int end);
int searchCardByNum(char *num);					//����ѧ�ŷ��ػ������±�
void saveRecordToFile();
void readRecordFromFile();
void saveCardsToFile();
void readCardsFromFile();
void setDate(Date *date, int h, int m, int s);
void setTime(Time *t, int h, int m, int s);
Time getTime(int h, int m, int s);				//���������ظ�ʱ���Time
Date getDate(int h, int m, int s);				//���������ظ����ڵ�Date
int LoginTea();									//����Ա��¼
int LoginStu(char *num);						//ѧ����¼��������ѧ��
int RegisterStu();								//ѧ��ע��
int ChargeCard();								//��ֵ����
int ChangePassword(char *num);					//�޸�����
int LoseCard();									//������ʧ
int RelieveCard();								//���������ʧ
void QueryRecord();								//��ѯ��¼�ӹ���
void PrintRecord(Record record);				//��ӡһ���ϻ���¼
void PrintHead();
void DisplayAllRecord();
void QueryRecordByDate();
void QueryRecordByNum();
void mergeTime(int*, int*, int*);				//����ʱ����
void convertTime(int*, int*, int*, int);		//����ʱ��ʹ�����ƽ��ʱ��
int QueryMoney(char *num);						//��ѯ����ѧ�Ż��������
int QueryMyRecord(char *num);					//��ѯ����ѧ�Ż������ϻ���¼
int Login(char *num);							//�ϻ�
void getLoginDate(int*, int*, int*);
void getLoginTime(int*, int*, int*);
void getLoginPlace(char*);
void getLogoutTime(int*, int*, int*);
int getLegalInput(int start, int end, char *hint);
int legal_time(int h, int m, int s);

void PrintMenuTea() {                      		 //��ӡ��ʦ�˵�
	printf("\n");
	printf("         ��������������������������������������������������������������         \n");
	printf("         ��                                                          ��         \n");
	printf("         ��            ��ѡ�������Ŀ��                              ��         \n");
	printf("         ��               1.ע�����          2.��ֵ����             ��         \n");
	printf("         ��               3.��ʧ����          4.��ѯͳ��             ��         \n");
	printf("         ��               5.�����ʧ          0.�˳�ϵͳ             ��         \n");
	printf("         ��������������������������������������������������������������         \n");
}

void PrintMenuStu() {					         //��ӡѧ���˵�
	printf("\n");
	printf("         ��������������������������������������������������������������         \n");
	printf("         ��                                                          ��         \n");
	printf("         ��            ��ѡ�������Ŀ��                              ��         \n");
	printf("         ��               1.�޸�����          2.��ѯ���             ��         \n");
	printf("         ��               3.��ѯ��¼          4.��    ��             ��         \n");
	printf("         ��               0.�˳�ϵͳ                                 ��         \n");
	printf("         ��������������������������������������������������������������         \n");
}

void PrintLogin() {                               //��ӡ��¼����
	printf("\n");
	printf("         ��������������������������������������������������������������         \n");
	printf("         ��                                                          ��         \n");
	printf("         ��                  ��ѡ����ݵ�¼��                        ��         \n");
	printf("         ��                         1.����Ա��¼                     ��         \n");
	printf("         ��                         2.ѧ����¼                       ��         \n");
	printf("         ��                         0.�˳�ϵͳ                       ��         \n");
	printf("         ��������������������������������������������������������������         \n");
}

void PrintQueryMenu() {                      		 //��ӡ��ѯ�˵�
	printf("\n");
	printf("         ��������������������������������������������������������������         \n");
	printf("         ��                                                          ��         \n");
	printf("         ��            ��ѡ���ѯ��ʽ��                              ��         \n");
	printf("         ��             1.��ʾ���м�¼    2.��ѯĳ���¼             ��         \n");
	printf("         ��             3.��ѯѧ����¼    0.�����ϼ��˵�             ��         \n");
	printf("         ��������������������������������������������������������������         \n");
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

int RegisterStu() {								 //ѧ��ע��
	Card card;

	printf("������ѧ�ţ�");
	scanf("%s", card.num);

	if (searchCardByNum(card.num) != cards_size) {
		printf("ѧ��Ϊ %s �Ļ�����ע�ᣡ", card.num);
		return 0;
	}

	printf("������������");
	scanf("%s", card.name);
	printf("������༶��");
	scanf("%s", card._class);

	card.money = 0;
	card.flag = NORMAL;
	strcpy(card.pwd, INIT_PWD);

	cards[cards_size++] = card;
	saveCardsToFile();

	printf("ѧ��Ϊ %s �Ļ���ע��ɹ���", card.num);
	return 1;
}

int ChargeCard() {
	char num[MAXLENGTH];
	int i;
	double money;

	printf("������ѧ�ţ�");
	scanf("%s", num);

	if ((i = searchCardByNum(num)) == cards_size) {
		printf("ѧ��Ϊ %s �Ļ��������ڣ�", num);
		return 0;
	}
	else if (cards[i].flag == FROZEN) {
		printf("ѧ��Ϊ %s �Ļ���״̬�쳣�����Ƚⶳ���ٲ�����", num);
		return 0;
	}

	printf("�������ֵ��");
	scanf("%lf", &money);
	while (money <= 0) {
		printf("���������������0������");
		scanf("%lf", &money);
	}

	cards[i].money += money;
	saveCardsToFile();
	printf("ѧ��Ϊ %s �Ļ�����ֵ %.2f Ԫ����� %.2f Ԫ!\n", num, money, cards[i].money);
	return 1;
}

int ChangePassword(char *num) {
	int i;
	char pwd[MAXLENGTH];
	char pwd_check[MAXLENGTH];

	if ((i = searchCardByNum(num)) == cards_size) {
		printf("ѧ��Ϊ %s �Ļ��������ڣ�", num);
		return 0;
	}
	else if (cards[i].flag == FROZEN) {
		printf("ѧ��Ϊ %s �Ļ���״̬�쳣�����Ƚⶳ���ٲ�����", num);
		return 0;
	}

	do {
		printf("���������룺");
		scanf("%s", pwd);

		printf("���ٴ��������룺");
		scanf("%s", pwd_check);

		if (strcmp(pwd, pwd_check))
			printf("�������벻һ�£�����������!\n");
	} while (strcmp(pwd, pwd_check));

	strcpy(cards[i].pwd, pwd);
	printf("�����޸ĳɹ�!\n");
	saveCardsToFile();
	return 1;
}

int LoseCard() {
	char num[MAXLENGTH];
	int i;

	printf("������ѧ�ţ�");
	scanf("%s", num);

	if ((i = searchCardByNum(num)) == cards_size) {
		printf("ѧ��Ϊ %s �Ļ��������ڣ�", num);
		return 0;
	}
	else if (cards[i].flag == FROZEN) {
		printf("ѧ��Ϊ %s �Ļ����Ѿ����ڹ�ʧ״̬��", num);
		return 0;
	}

	cards[i].flag = FROZEN;
	printf("ѧ��Ϊ %s �Ļ�����ʧ�ɹ�!\n", num);
	saveCardsToFile();
	return 1;
}

int RelieveCard() {
	char num[MAXLENGTH];
	int i;

	printf("������ѧ�ţ�");
	scanf("%s", num);

	if ((i = searchCardByNum(num)) == cards_size) {
		printf("ѧ��Ϊ %s �Ļ��������ڣ�", num);
		return 0;
	}
	else if (cards[i].flag == NORMAL) {
		printf("ѧ��Ϊ %s �Ļ����Ѿ���������״̬��", num);
		return 0;
	}

	cards[i].flag = NORMAL;
	printf("ѧ��Ϊ %s �Ļ����ѻָ�����״̬!\n", num);
	saveCardsToFile();
	return 1;
}

int LoginTea() {									 //��ʦ��¼
	char account[MAXLENGTH], password[MAXLENGTH];       	    //�˺ţ�����
	char che_acc[MAXLENGTH] = { 0 }, che_pas[MAXLENGTH] = { 0 };       //�����˺ţ���������
	FILE *fp;
	int turn = 0;                                 //���ڼ����˺������Ƿ�ƥ��

	if ((fp = fopen(TEA_LOGIN_FILE, "r")) == NULL) {
		printf("ȱ�ٹ���Ա�˺��ļ������飡");
		return 0;
	}

	printf("���������Ա�˺ţ�");
	scanf("%s", account);
	printf("���������룺");
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
		printf("��¼�ɹ���");
	}
	else {
		printf("�˺Ż�������󣬵�¼ʧ��");
	}

	return turn;
}

void freezeCard(int i) {
	cards[i].flag = FROZEN;
	saveCardsToFile();
}

int LoginStu(char *num) {                                  //ѧ����¼
	char account[MAXLENGTH], password[MAXLENGTH];       	    //�˺ţ�����
	int turn = 0;                                 //���ڼ����˺������Ƿ�ƥ��
	int t = 3;
	int i;

	printf("����������ѧ�ţ�");
	scanf("%s", account);

	i = searchCardByNum(account);
	if (i == cards_size) {
		printf("ѧ�Ų����ڣ������ɹ���Աע�������");
		return 0;
	}
	else if (cards[i].money < 3) {
		printf("�û������С�� 3 Ԫ����֪ͨ����Ա��ֵ���¼��");
		return 0;
	}
	else if (cards[i].flag == FROZEN) {
		printf("�û����ѱ����ᣬ��֪ͨ����Ա������¼��");
		return 0;
	}

	do {
		if (t != 3)
			printf("��������㻹�� %d �γ��Ի��ᣬ�������������룺", t);
		--t;

		printf("���������룺");
		scanf("%s", password);

		if (!strcmp(cards[i].pwd, password))
			turn = 1;
	} while (!turn && t > 0);

	if (!turn) {
		freezeCard(i);
		printf("3�����������Ļ����ѱ����ᣬ��֪ͨ����Ա�Ӵ����ᣡ");
	}
	else {
		printf("��¼�ɹ�");
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
			printf("������������� %d~%d ֮���ѡ�\n", start, end);
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
	printf("%8s  %10s  %8s  %8s  %8s\n", "ѧ��ѧ��", "�ϻ�����", "��ʼʱ��", "�ϻ�ʱ��", "�ϻ��ص�");
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
		printf("���ϻ���¼��\n");
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

	printf("\n�ϻ���ʱ����  %2d:%2d:%2d  ���������룺%4.2f  �ϻ��ܴ�����%4d\n", h, m, s, cost, record_size);
	convertTime(&h, &m, &s, record_size);
	printf("ƽ��ÿ��ʱ����%2d:%2d:%2d  ����ƽ�����룺%4.2f\n", h, m, s, cost / record_size);
}

void QueryRecordByDate() {
	int y, m, d, i, c;
	int h, min, s;
	double cost;

	if (!record_size) {
		printf("���ϻ���¼��\n");
		return;
	}

	printf("��������ݣ�");
	scanf("%d", &y);
	printf("�������·ݣ�");
	scanf("%d", &m);
	printf("���������ڣ�");
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
		printf("�� %4d/%2d/%2d ���ϻ���¼��\n", y, m, d);
		return 0;
	}

	mergeTime(&h, &min, &s);

	printf("\n�ϻ���ʱ����  %2d:%2d:%2d  ���������룺%4.2f  �ϻ��ܴ�����%4d\n", h, min, s, cost, c);
	convertTime(&h, &min, &s, c);
	printf("ƽ��ÿ��ʱ����%2d:%2d:%2d  ����ƽ�����룺%4.2f\n", h, min, s, cost / c);
}

void QueryRecordByNum() {
	char num[MAXLENGTH];

	if (!record_size) {
		printf("���ϻ���¼��\n");
		return;
	}

	printf("������ѧ��ѧ�ţ�");
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
		printf("ѧ��Ϊ %s �Ļ��������ڣ�", num);
		return 0;
	}
	else if (cards[i].flag == FROZEN) {
		printf("ѧ��Ϊ %s �Ļ���״̬�쳣�����Ƚⶳ���ٲ�����", num);
		return 0;
	}

	printf("���Ļ������Ϊ��%4.2f\n", cards[i].money);
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
		printf("��ѧ��Ϊ %s ���ϻ���¼��\n", num);
		return;
	}

	mergeTime(&h, &m, &s);

	printf("\n�ϻ���ʱ����  %2d:%2d:%2d  ���������룺%4.2f  �ϻ��ܴ�����%4d\n", h, m, s, cost, c);
	convertTime(&h, &m, &s, c);
	printf("ƽ��ÿ��ʱ����%2d:%2d:%2d  ����ƽ�����룺%4.2f\n", h, m, s, cost / c);
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
	printf("���ֶ������ϻ���ݣ�");
	*year = getLegalInput(1970, 2500, "������ 1970��2500 ֮�����ݣ�\n");
	printf("���ֶ������ϻ��·ݣ�");
	*month = getLegalInput(1, 12, "��������ȷ����ݣ�\n");
	printf("���ֶ������ϻ����ڣ�");
	*day = getLegalInput(1, 31, "��������ȷ�����ڣ�\n");   // review
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
		printf("���ֶ������ϻ�ʱ�䣨��ʽ��\"ʱ:��:��\"����");
		scanf("%s", t);
		sscanf(t, "%d:%d:%d", &h, &m, &s);
		if (!legal_time(h, m, s))
			sscanf(t, "%d��%d��%d", &h, &m, &s);
		if (!legal_time(h, m, s))
			printf("ʱ���ʽ�������������룡\n");
	} while (!legal_time(h, m, s));

	*hour = h;
	*min = m;
	*sec = s;
}

void getLoginPlace(char* place) {
	printf("���ֶ������ϻ��ص㣺");
	scanf("%s", place);
}

void getLogoutTime(int* hour, int* min, int* sec) {
	char t[MAXLENGTH];
	int h, m, s;

	do {
		printf("���ֶ������»�ʱ�䣨��ʽ��\"ʱ:��:��\"����");
		scanf("%s", t);
		sscanf(t, "%d:%d:%d", &h, &m, &s);
		if (!legal_time(h, m, s))
			printf("ʱ���ʽ�������������룡\n");
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
		printf("ѧ��Ϊ %s �Ļ��������ڣ�", num);
		return 0;
	}
	else if (cards[i].flag == FROZEN) {
		printf("ѧ��Ϊ %s �Ļ���״̬�쳣�����Ƚⶳ���ٲ�����", num);
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
			printf("������֧�������»�ʱ�䣬���������룡\n");
		}
	} while (flag);

	records[record_size++] = record;
	cards[i].money -= cost;
	saveRecordToFile();
	return 1;
}

int main() {
	int turn = 0;			//�����Ƿ��¼��ע��ɹ��Ŀ���
	int choice;
	int admin = 0;		//�����û����Խ�ʦ��ѧ����ݵ�¼�Ŀ���
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
