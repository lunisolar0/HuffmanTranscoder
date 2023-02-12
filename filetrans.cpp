#include <iostream>
#include <fstream>
#include <bitset>
#include "clgener.h"
#include "filetrans.h"

using namespace std;

ifstream inFile;
ofstream outFile;

string TransCode(HCodeList& HCL) //文转码功能
{
	string filename;
	do
	{
		cout << "程序将根据当前哈夫曼编码表对一个文件进行编码" << endl;
		cout << "请输入即将读入的文件路径(包括后缀)：" << endl;
		getline(cin, filename);
		inFile.open(filename, ios::in);
		if (!inFile.is_open())
		{ //判断文件是否打开成功
			cout << "文件“" << filename << "”打开失败，请重新输入！" << endl;
		}
	} while (!inFile.is_open());
	char* text = new char[100000];
	for (int i = 0; (text[i] = inFile.get()) != EOF; i++); //从文件中读入字符
	inFile.close();
	size_t size0, size1;
	size0 = GetSize_File(filename);//计算原文本文件大小
	cout << "文件读入成功！" << endl;
	cout << "接下来，程序将进行编码并将之写入文件" << endl;
	cout << "请输入目标文件路径(包括后缀)：" << endl;
	getline(cin, filename);
	string st = {};
	for (int i = 0; text[i] != '\0'; i++)
	{ //逐字符转码
		int ret = ToCodeHCL(HCL, text[i]);
		st = st + HCL.ce[ret].code;
	}
	size_t codelen = st.length();
	bitset<32> cl(st.length());
	outFile.open(filename, ios::out | ios::binary);
	outFile.write((char*)&cl, sizeof(bitset<32>));
	for (int start = 0; start < codelen; start = start + 32)
	{
		bitset<32> tempcode(st.substr(start, 32));
		outFile.write((char*)&tempcode, sizeof(bitset<32>));
	}
	outFile.close();
	size1 = GetSize_File(filename);
	cout << "转码前文件大小：" << size0 << "byte" << endl;
	cout << "转码后文件大小：" << size1 << "byte" << endl;
	cout << "本次转码压缩率：" << ((float)size1 / (float)size0) * 100 << "%" << endl;
	return filename;
}

void TransText(HCodeList& HCL) //码转文功能
{
	string filename;
	do
	{
		cout << "程序将根据当前哈夫曼编码表对一个编码文件进行解码" << endl;
		cout << "请输入即将读入的编码文件路径(包括后缀)：" << endl;
		getline(cin, filename);
		inFile.open(filename, ios::in | ios::binary);
		if (!inFile.is_open())
		{ //判断文件是否打开成功
			cout << "文件“" << filename << "”打开失败，请重新输入！" << endl;
		}
	} while (!inFile.is_open());
	bitset<32> cl;
	inFile.read((char*)&cl, sizeof(bitset<32>));
	long codelen = cl.to_ulong();
	string st = {};
	for (long n = codelen; n > 0; n = n - 32)
	{
		bitset<32> tempcode;
		inFile.read((char*)&tempcode, sizeof(bitset<32>));
		if (n >= 32) st = st + tempcode.to_string();
		else st = st + tempcode.to_string().substr(32 - n, n);
	}
	char* code = new char[100000];
	strcpy_s(code, 100000, st.c_str());
	cout << "编码文件读入成功！" << endl;
	cout << "接下来，程序将进行编码并将之写入文件" << endl;
	cout << "请输入目标文件路径(包括后缀)：" << endl;
	getline(cin, filename);
	string buf = {};
	outFile.open(filename, ios::out);
	for (int i = 0; code[i] != '\0'; i++)
	{ //逐码转字符
		buf = buf + code[i];
		int ret = ToCharHCL(HCL, buf);
		if (ret)
		{ 
			outFile << HCL.ce[ret].name;
			buf.erase(0, buf.length());
		}
	}
	outFile.close();
	inFile.close();
}

void PrintCode(string codefile) //打印代码串
{
	inFile.open(codefile, ios::in | ios::binary);
	bitset<32> cl;
	inFile.read((char*)&cl, sizeof(bitset<32>));
	long codelen = cl.to_ulong();
	string st = {};
	for (long n = codelen; n > 0; n = n - 32)
	{
		bitset<32> tempcode;
		inFile.read((char*)&tempcode, sizeof(bitset<32>));
		if (n >= 32) st = st + tempcode.to_string();
		else st = st + tempcode.to_string().substr(32 - n, n);
	}
	char* code = new char[100000];
	strcpy_s(code, 100000, st.c_str()); //读取编码串
	for (int i = 0; code[i] != '\0'; i++)
	{
		cout << code[i];
		if ((i + 1) % 50 == 0) cout << endl;
	}
	cout << endl;
	inFile.close();
}

size_t GetSize_File(string filename) //计算文件大小
{
	inFile.open(filename, ios::ate | ios::binary);
	size_t size = inFile.tellg();
	inFile.close();
	return size;
}