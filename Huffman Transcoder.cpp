#include <iostream>
#include <windows.h>
#include "clgener.h"
#include "filetrans.h"

int main()
{
	HLinkedLists HLS = {};
	HCodeList HCL;
	string codefile, wlsource;
	int source;
	int c = 0;
	cout << "*************************" << endl;
	cout << "*��ӭʹ�ù�������/������*" << endl;
	cout << "*   �ݲ�֧�������ļ�    *" << endl;
	cout << "*                       *" << endl;
	cout << "* 1.��Ȩֵ�����ɱ����  *" << endl;
	cout << "*  2.���ļ����ɱ����   *" << endl;
	cout << "*     0.�˳�����        *" << endl;
	cout << "*                       *" << endl;
	cout << "* �Ƿ���������˳�����  *" << endl;
	cout << "*ע:��ѡ������ɵı����*" << endl;
	cout << "*��������Ӧ���ļ���/����*" << endl;
	cout << "*�������ʹ�ļ����ݶ�ʧ *" << endl;
	cout << "*************************" << endl;
	cout << "��ѡ��";
	cin >> c;
	source = c;
	int p = getchar();
	system("cls");
	if (c == 1)
	{
		HLS = InitHLS_std(wlsource);
		ToTreeHLS(HLS);
		HCL = InitHCL(HLS);
		PrintHT(HCL);
		cout << "����������������ɣ�" << endl;
		system("pause");
	}
	else if (c == 2)
	{
		HLS = InitHLS_file(wlsource);
		ToTreeHLS(HLS);
		HCL = InitHCL(HLS);
		PrintHT(HCL);
		cout << "����������������ɣ�" << endl;
		system("pause");
	}
	if (c == 1 || c == 2) //��������ɳɹ������빦�ܽ���
	{
		while (c)
		{
			system("cls");
			cout << "*************************" << endl;
			cout << "*��ӭʹ�ù�������/������*" << endl;
			cout << "*   �ݲ�֧�������ļ�    *" << endl;
			cout << "*                       *" << endl;
			cout << "*     1.�ļ�ת����      *" << endl;
			cout << "*     2.����ת�ļ�      *" << endl;
			cout << "*     3.��ӡ���봮      *" << endl;
			cout << "*     4.��ӡ�����      *" << endl;
			cout << "*     0.�˳��ó���      *" << endl;
			cout << "*                       *" << endl;
			cout << "* �Ƿ���������˳�����  *" << endl;
			cout << "*ѡ��3����ѡ��1֮��ִ�� *" << endl;
			cout << "*************************" << endl;
			cout << "��ǰ�������Դ:��" << wlsource << "��" ;
			if (source == 1) cout << "(��Ȩֵ������)" << endl;
			else if (source == 2) cout << "(���ļ�����)" << endl;
			cout << "��ѡ��";
			cin >> c;
			p = getchar();
			system("cls");
			switch (c)
			{
				case 1:
					cout << "��ǰ�������Դ:��" << wlsource << "��";
					if (source == 1) cout << "(��Ȩֵ������)" << endl;
					else if (source == 2) cout << "(���ļ�����)" << endl;
					codefile = TransCode(HCL);
					cout << "��ת��ɹ���" << endl;
					system("pause");
					break;
				case 2:
					cout << "��ǰ�������Դ:��" << wlsource << "��";
					if (source == 1) cout << "(��Ȩֵ������)" << endl;
					else if (source == 2) cout << "(���ļ�����)" << endl;
					TransText(HCL);
					cout << "��ת�ĳɹ���" << endl;
					system("pause");
					break;
				case 3:
					cout << "���봮����(50������/��):" << endl;
					PrintCode(codefile);
					system("pause");
					break;
				case 4:
					Print2H(HLS, HCL);
					Print2H_F(HLS, HCL);
					system("pause");
					break;
				default:
					break;
			}
		}
	}
	delete HLS;
	system("cls");
	cout << "��л����ʹ�ã��ټ���" << endl;
	return 0;
}