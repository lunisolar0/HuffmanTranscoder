#include <iostream>
#include <fstream>
#include <bitset>
#include "clgener.h"
#include "filetrans.h"

using namespace std;

ifstream inFile;
ofstream outFile;

string TransCode(HCodeList& HCL) //��ת�빦��
{
	string filename;
	do
	{
		cout << "���򽫸��ݵ�ǰ������������һ���ļ����б���" << endl;
		cout << "�����뼴��������ļ�·��(������׺)��" << endl;
		getline(cin, filename);
		inFile.open(filename, ios::in);
		if (!inFile.is_open())
		{ //�ж��ļ��Ƿ�򿪳ɹ�
			cout << "�ļ���" << filename << "����ʧ�ܣ����������룡" << endl;
		}
	} while (!inFile.is_open());
	char* text = new char[100000];
	for (int i = 0; (text[i] = inFile.get()) != EOF; i++); //���ļ��ж����ַ�
	inFile.close();
	size_t size0, size1;
	size0 = GetSize_File(filename);//����ԭ�ı��ļ���С
	cout << "�ļ�����ɹ���" << endl;
	cout << "�����������򽫽��б��벢��֮д���ļ�" << endl;
	cout << "������Ŀ���ļ�·��(������׺)��" << endl;
	getline(cin, filename);
	string st = {};
	for (int i = 0; text[i] != '\0'; i++)
	{ //���ַ�ת��
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
	cout << "ת��ǰ�ļ���С��" << size0 << "byte" << endl;
	cout << "ת����ļ���С��" << size1 << "byte" << endl;
	cout << "����ת��ѹ���ʣ�" << ((float)size1 / (float)size0) * 100 << "%" << endl;
	return filename;
}

void TransText(HCodeList& HCL) //��ת�Ĺ���
{
	string filename;
	do
	{
		cout << "���򽫸��ݵ�ǰ������������һ�������ļ����н���" << endl;
		cout << "�����뼴������ı����ļ�·��(������׺)��" << endl;
		getline(cin, filename);
		inFile.open(filename, ios::in | ios::binary);
		if (!inFile.is_open())
		{ //�ж��ļ��Ƿ�򿪳ɹ�
			cout << "�ļ���" << filename << "����ʧ�ܣ����������룡" << endl;
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
	cout << "�����ļ�����ɹ���" << endl;
	cout << "�����������򽫽��б��벢��֮д���ļ�" << endl;
	cout << "������Ŀ���ļ�·��(������׺)��" << endl;
	getline(cin, filename);
	string buf = {};
	outFile.open(filename, ios::out);
	for (int i = 0; code[i] != '\0'; i++)
	{ //����ת�ַ�
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

void PrintCode(string codefile) //��ӡ���봮
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
	strcpy_s(code, 100000, st.c_str()); //��ȡ���봮
	for (int i = 0; code[i] != '\0'; i++)
	{
		cout << code[i];
		if ((i + 1) % 50 == 0) cout << endl;
	}
	cout << endl;
	inFile.close();
}

size_t GetSize_File(string filename) //�����ļ���С
{
	inFile.open(filename, ios::ate | ios::binary);
	size_t size = inFile.tellg();
	inFile.close();
	return size;
}