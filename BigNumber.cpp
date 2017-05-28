#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

#define ER -1

using namespace std;

class BigNumber {
	friend BigNumber operator+(const BigNumber&, const BigNumber&);
	friend BigNumber operator-(const BigNumber&, const BigNumber&);
	friend BigNumber operator*(const BigNumber&, const BigNumber&);
	friend bool operator==(const BigNumber&, const BigNumber&);
	friend bool operator<(const BigNumber&, const BigNumber&);
	friend bool operator>(const BigNumber&, const BigNumber&);
	friend bool operator<=(const BigNumber&, const BigNumber&);
	friend bool operator>=(const BigNumber&, const BigNumber&);
	friend ostream& operator<<(ostream&, const BigNumber&);
	friend istream& operator>>(istream&, BigNumber&);
public:
	BigNumber(int n = 0);
	BigNumber(const vector<char> &v) { vec = v; }
	BigNumber(const BigNumber &b) { vec = b.vec; }


	BigNumber operator++();
	BigNumber operator++(int);
	BigNumber operator--();
	BigNumber operator--(int);
	BigNumber operator=(const BigNumber& b) { vec = b.vec; }

	BigNumber factor();
private:
	vector<char> vec;
	int char2int(char ch) {
		if (ch < '0' || ch > '9')return ER;
		return ch - 48;
	}
	char int2char(int n) {
		if (n > 9 || n < 0)return ER;
		return n + 45;
	}

	char add(char, char, int&);
	char add(char, char, char&);
	vector<char> add(char, vector<char>::size_type index = 0);
	vector<char> add(const vector<char>&);

	char sub(char, char, int&);
	char sub(char, char, char&);
	vector<char> sub(char, vector<char>::size_type index = 0);
	vector<char> sub(const vector<char>&);

	char mult(char, char, int&);
	vector<char> mult(char);
	vector<char> mult(const vector<char>&);

	void print_vec() {
		for (vector<char>::size_type i = 0; i < vec.size(); ++i)
			cout << vec[i];
		cout << endl;
	}
	void print_vec_reverse() {
		for (int i = vec.size() - 1; i >= 0; --i)
			cout << vec[i];
		cout << endl;
	}
	vector<char> reverse_vec() {
		vector<char> ret;
		for (int i = vec.size() - 1; i >= 0; --i)
			ret.push_back(vec[i]);
		return ret;
	}
};
BigNumber::BigNumber(int n) {
	if (n == 0)vec.push_back('0');
	else {
		while (n > 0) {
			vec.push_back(n % 10 + 48);
			n /= 10;
		}
	}
}
char BigNumber::add(char ch1, char ch2, int &c) {
	int num = char2int(ch1) + char2int(ch2);
	c = num / 10;
	return (num % 10) + 48;
}
char BigNumber::add(char ch1, char ch2, char &c) {
	int num = char2int(ch1) + char2int(ch2);
	c = num / 10 + 48;
	return (num % 10) + 48;
}
vector<char> BigNumber::add(char ch, vector<char>::size_type index) {
	vector<char> ret;
	char res;
	for (vector<char>::size_type i = 0; i < index; ++i)
		ret.push_back(vec[i]);
	for (vector<char>::size_type i = index; i < vec.size(); ++i) {
		res = add(vec[i], ch, ch);
		ret.push_back(res);
	}
	if (ch != '0')
		ret.push_back(ch);
	return ret;
}
vector<char> BigNumber::add(const vector<char> &v) {
	const vector<char> *max;
	const vector<char> *min;
	if (vec.size() < v.size()) {
		max = &v;
		min = &vec;
	}
	else {
		max = &vec;
		min = &v;
	}
	BigNumber bignumber(*max);
	for (vector<char>::size_type i = 0; i < min->size(); ++i)
		bignumber.vec = bignumber.add((*min)[i], i);
	return bignumber.vec;
}
char BigNumber::mult(char ch1, char ch2, int &c) {
	int num = char2int(ch1) * char2int(ch2);
	c = num / 10;
	return (num % 10) + 48;
}
vector<char> BigNumber::mult(char ch) {
	vector<char> ret;
	int c, pre_c;
	char res;
	c = 0;
	for (vector<char>::size_type i = 0; i < vec.size(); ++i) {
		pre_c = c;
		res = mult(vec[i], ch, c);
		res += pre_c;
		if (res > '9') {
			res -= 10;
			++c;
		}
		ret.push_back(res);
	}
	if (c != 0)
		ret.push_back(c + 48);
	return ret;
}
vector<char> BigNumber::mult(const vector<char> &v) {
	BigNumber bignumber(vec);
	BigNumber ret(0);
	for (vector<char>::size_type i = 0; i < v.size(); ++i) {
		vector<char> temp = bignumber.mult(v[i]);
		temp.insert(temp.begin(), i, '0');
		ret.vec = ret.add(temp);
	}
	return ret.vec;
}
BigNumber operator+(const BigNumber &number1, const BigNumber &number2) {
	BigNumber newnum(number1.vec);
	newnum.vec = newnum.add(number2.vec);
	return newnum;
}
BigNumber operator-(const BigNumber &number1, const BigNumber &number2) {
	BigNumber newnum(number1.vec);
	newnum.vec = newnum.sub(number2.vec);
	return newnum;
}
BigNumber operator*(const BigNumber &number1, const BigNumber &number2) {
	BigNumber newnum(number1.vec);
	newnum.vec = newnum.mult(number2.vec);
	return newnum;
}
ostream& operator<<(ostream& out, const BigNumber& bignumber) {
	if (out)
		for (int i = bignumber.vec.size() - 1; i >= 0; --i)
			out << bignumber.vec[i];
	return out;
}
istream& operator>>(istream& in, BigNumber& bignumber) {
	if (in) {
		vector<char> vec;
		char c;
		while (1) {
			c = in.get();
			if (c == '\n' || c == '\t' || c == 'r' || c == ' ') {
				bignumber.vec = vec;
				break;
			}
			else if (c < '0' || c > '9')
				break;
			else {
				vec.insert(vec.begin(), c);
			}
		}
	}
	return in;
}
bool operator==(const BigNumber& num1, const BigNumber& num2) {
	if (num1.vec.size() != num2.vec.size()) return false;
	for (vector<char>::size_type i = 0; i < num1.vec.size(); ++i)
		if (num1.vec[i] != num2.vec[i])
			return false;
	return true;
}
BigNumber BigNumber::factor() {
	BigNumber ans(1);
	for (BigNumber b = 2; b <= *this; ++b)
		ans = ans * b;
	return ans;
}
char BigNumber::sub(char ch1, char ch2, int &c) {
	int num = ch1 - ch2;
	if (num < 0) {
		c = 1;
		num += 10;
	}
	else
		c = 0;
	return num + 48;
}
char BigNumber::sub(char ch1, char ch2, char &c) {
	int num = ch1 - ch2;
	if (num < 0) {
		c = '1';
		num += 10;
	}
	else
		c = '0';
	return num + 48;
}
vector<char> BigNumber::sub(char ch, vector<char>::size_type index) {
	vector<char> ret;
	char res;
	for (vector<char>::size_type i = 0; i < index; ++i)
		ret.push_back(vec[i]);
	for (vector<char>::size_type i = index; i < vec.size(); ++i) {
		res = sub(vec[i], ch, ch);
		ret.push_back(res);
	}
	if (ret.back() == '0' && ret.size() > 1)
		ret.pop_back();
	return ret;
}
vector<char> BigNumber::sub(const vector<char> &v) {
	BigNumber bignumber(vec);
	for (vector<char>::size_type i = 0; i < v.size(); ++i)
		bignumber.vec = bignumber.sub(v[i], i);
	return bignumber.vec;
}
BigNumber BigNumber::operator++() {
	*this = *this + 1;
	return *this;
}
BigNumber BigNumber::operator++(int) {
	BigNumber temp = *this;
	*this = *this + 1;
	return temp;
}
BigNumber BigNumber::operator--() {
	*this = *this - 1;
	return *this;
}
BigNumber BigNumber::operator--(int) {
	BigNumber temp = *this;
	*this = *this - 1;
	return temp;
}
bool operator<(const BigNumber& n1, const BigNumber& n2) {
	if (n1.vec.size() < n2.vec.size())
		return true;
	else if (n1.vec.size() > n2.vec.size())
		return false;
	else {
		for (int i = n1.vec.size() - 1; i >= 0; --i)
			if (n1.vec[i] < n2.vec[i])
				return true;
		return false;
	}
}
bool operator>(const BigNumber& n1, const BigNumber& n2) {
	return n2 < n1;
}
bool operator<=(const BigNumber& n1, const BigNumber& n2) {
	return n1 == n2 || n1 < n2;
}
bool operator>=(const BigNumber& n1, const BigNumber& n2) {
	return n1 == n2 || n1 > n2;
}
int main() {
	BigNumber bignumber(5);
	bignumber = 6;
	cout << bignumber.factor() << endl;
	return 0;
}
