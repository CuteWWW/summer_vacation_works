#include "sm3.h"
#include <iostream>
#include <string>
#include <cmath>
#include<time.h>
using namespace std;
string iv = "7380166F4914B2B9172442D7DA8A0600A96F30BC163138AAE38DEE4DB0FB0E4E";
string pad(string s) {//对数据进行填充 
	string res = "";
	for (int i = 0; i < s.size(); i++) {//首先将输入值转换为16进制字符串
		res += DTH((int)s[i]);
	}
	int res_length = res.size() * 4;//记录的长度为2进制下的长度
	res += "8";//在获得的数据后面添1，在16进制下相当于是添加8
	while (res.size() % 128 != 112) {
		res += "0";//“0”数据填充
	}
	string res_len = DTH(res_length);//用于记录数据长度的字符串
	while (res_len.size() != 16) {
		res_len = "0" + res_len;
	}
	res += res_len;
	return res;
}
string ModAdd(string str1, string str2) {//mod 2^32运算的函数实现
	string res1 = HTB(str1);
	string res2 = HTB(str2);
	char temp = '0';
	string res = "";
	for (int i = res1.size() - 1; i >= 0; i--) {
		res = binXor(binXor(res1[i], res2[i]), temp) + res;
		if (binAnd(res1[i], res2[i]) == '1') {
			temp = '1';
		}
		else {
			if (binXor(res1[i], res2[i]) == '1') {
				temp = binAnd('1', temp);
			}
			else {
				temp = '0';
			}
		}
	}
	return BTH(res);
}

string P1(string str) {//实现置换功能P1（X）
	return XOR(XOR(str, LeftShift(str, 15)), LeftShift(str, 23));
}

string P0(string str) {//实现置换功能P0（X）
	return XOR(XOR(str, LeftShift(str, 9)), LeftShift(str, 17));
}

string T(int j) {//返回Tj常量值的函数实现
	if (0 <= j && j <= 15) {
		return "79CC4519";
	}
	else {
		return "7A879D8A";
	}
}

string FF(string X, string Y, string Z, int j) {//实现布尔函数FF功能
	if (0 <= j && j <= 15) {
		return XOR(XOR(X, Y), Z);
	}
	else {
		return OR(OR(AND(X, Y), AND(X, Z)), AND(Y, Z));
	}
}

string GG(string X, string Y, string Z, int j) {//实现布尔函数GG功能
	if (0 <= j && j <= 15) {
		return XOR(XOR(X, Y), Z);
	}
	else {
		return OR(AND(X, Y), AND(NOT(X), Z));
	}
}
string extension(string str) {//消息扩展函数
	string res = str;//字符串类型存储前68位存储扩展字W值
	for (int i = 16; i < 68; i++) {//根据公式生成第17位到第68位的W值
		res += XOR(XOR(P1(XOR(XOR(res.substr((i - 16) * 8, 8), res.substr((i - 9) * 8, 8)), LeftShift(res.substr((i - 3) * 8, 8), 15))), LeftShift(res.substr((i - 13) * 8, 8), 7)), res.substr((i - 6) * 8, 8));
	}
	for (int i = 0; i < 64; i++) {//根据公式生成64位W'值
		res += XOR(res.substr(i * 8, 8), res.substr((i + 4) * 8, 8));
	}
	return res;
}

string compress(string str1, string str2) {//消息压缩函数
	string IV = str2;
	string A = IV.substr(0, 8), B = IV.substr(8, 8), C = IV.substr(16, 8), D = IV.substr(24, 8), E = IV.substr(32, 8), F = IV.substr(40, 8), G = IV.substr(48, 8), H = IV.substr(56, 8);
	string SS1 = "", SS2 = "", TT1 = "", TT2 = "";
	for (int j = 0; j < 64; j++) {
		SS1 = LeftShift(ModAdd(ModAdd(LeftShift(A, 12), E), LeftShift(T(j), (j % 32))), 7);
		SS2 = XOR(SS1, LeftShift(A, 12));
		TT1 = ModAdd(ModAdd(ModAdd(FF(A, B, C, j), D), SS2), str1.substr((j + 68) * 8, 8));
		TT2 = ModAdd(ModAdd(ModAdd(GG(E, F, G, j), H), SS1), str1.substr(j * 8, 8));
		D = C;
		C = LeftShift(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = LeftShift(F, 19);
		F = E;
		E = P0(TT2);
	}
	string res = (A + B + C + D + E + F + G + H);
	cout << endl;
	return res;
}

string SM3(string str, string b) {//迭代压缩函数实现
	int num = str.size() / 128;
	//string V = "7380166F4914B2B9172442D7DA8A0600A96F30BC163138AAE38DEE4DB0FB0E4E";
	string V = b;
	string B = "", extensionB = "", compressB = "";
	for (int i = 0; i < num; i++) {
		B = str.substr(i * 128, 128);
		extensionB = extension(B);
		compressB = compress(extensionB, V);
		V = XOR(V, compressB);
	}
	return V;
}
int main() {
	//首先定义初始明文与扩展明文
	string plaintext = "helloworld";
	string ext = "ext";
	cout << "初始明文" << plaintext << endl;
	cout << "扩展明文" << ext << endl;
	//函数初始明文的填充值
	string pa = pad(plaintext);
	//开始计算sm3杂凑值
	time_t start, end;
	start = clock();
	string hash1 = SM3(pa, iv);
	string hash2 = SM3(ext, hash1);
	string hash3 = SM3(pa + ext, iv);
	end = clock();
	cout << "hash2:" << endl;
	for (int i = 0; i < 8; i++)
		cout << hash2.substr(i * 8, 8);
	cout << endl;
	cout << "hash3:" << endl;
	for (int i = 0; i < 8; i++)
		cout << hash3.substr(i * 8, 8);
	cout << endl;
	hash2 == hash3 ? cout << "攻击成功" : cout << "攻击失败";
	cout << endl;
	cout << "攻击时间" << end - start << "ms" << endl;
	return 0;
}
