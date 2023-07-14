#include <iostream>
#include <string>
#include <cmath>
using namespace std;
//将二进制长度补零为4的倍数
string BZ(string s)
{
	int l = s.size();
	while (l % 4 != 0) {//因为每四位二进制数就能够成为一个十六进制数，所以将二进制数长度转换为4的倍数
		s = "0" + s;//最高位添0直到长度为4的倍数即可
	}
	return s;
}
//二进制转换为十六进制函数实现
string BTH(string s) {
	s = BZ(s);//将二进制长度补零为4的倍数
	string h = "";//用来存储最后生成的十六进制数
	int D = 0;//用来存储每次四位二进制数的十进制值
	int l = s.size();
	for (int i = 0; i < l; i += 4) {
		D = (s[i] - '0') * 8 + (s[i + 1] - '0') * 4 + (s[i + 2] - '0') * 2 + (s[i + 3] - '0') * 1;//4位二进制数的十进制
		if (D < 10) {
			h += to_string(D);
		}
		else {
			h += 'A' + (D - 10);
		}
	}
	return h;
}

//十六进制转换为二进制函数实现
string HTB(string s) {
	int l = s.size();
	string b = "";
	string table[16] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	for (int i = 0; i < l; i++) {
		if (s[i] >= 'A' && s[i] <= 'F') {
			b += table[s[i] - 'A' + 10];
		}
		else {
			b += table[s[i] - '0'];
		}
	}
	return b;
}

//二进制转换为十进制的函数实现
int BTD(string s) {
	int d = 0;
	for (int i = 0; i < s.size(); i++) {
		d += (s[i] - '0') * pow(2, s.size() - i - 1);
	}
	return d;
}

//十进制转换为二进制的函数实现
string DTB(int s) {
	string b = "";
	while (s >= 1) {
		b = to_string(s % 2) + b;
		s = s / 2;
	}
	return b;
}

//十六进制转换为十进制的函数实现
int HTD(string s) {
	int d = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] >= 'A' && s[i] <= 'F') {
			d += (s[i] - 'A' + 10) * pow(16, s.size() - i - 1);
		}
		else {
			d += (s[i] - '0') * pow(16, s.size() - i - 1);
		}
	}
	return d;
}

//十进制转换为十六进制的函数实现
string DTH(int s) {
	string h = "";
	int t = 0;
	while (s >= 1) {
		t = s % 16;
		if (t < 10 && t >= 0) {
			h = to_string(t) + h;
		}
		else {
			h += ('A' + (t - 10));
		}
		s = s / 16;
	}
	return h;
}
string LeftShift(string str, int len) {//实现循环左移len位功能
	string res = HTB(str);
	res = res.substr(len) + res.substr(0, len);
	return BTH(res);
}

string XOR(string str1, string str2) {//实现异或操作
	string res1 = HTB(str1);
	string res2 = HTB(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == res2[i]) {
			res += "0";
		}
		else {
			res += "1";
		}
	}
	return BTH(res);
}

string AND(string str1, string str2) {//实现与操作
	string res1 = HTB(str1);
	string res2 = HTB(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == '1' && res2[i] == '1') {
			res += "1";
		}
		else {
			res += "0";
		}
	}
	return BTH(res);
}

string OR(string str1, string str2) {//实现或操作
	string res1 = HTB(str1);
	string res2 = HTB(str2);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == '0' && res2[i] == '0') {
			res += "0";
		}
		else {
			res += "1";
		}
	}
	return BTH(res);
}

string NOT(string str) {//实现非操作
	string res1 = HTB(str);
	string res = "";
	for (int i = 0; i < res1.size(); i++) {
		if (res1[i] == '0') {
			res += "1";
		}
		else {
			res += "0";
		}
	}
	return BTH(res);
}

char binXor(char str1, char str2) {//实现单比特的异或操作
	return str1 == str2 ? '0' : '1';
}

char binAnd(char str1, char str2) {//实现单比特的与操作
	return (str1 == '1' && str2 == '1') ? '1' : '0';
}
