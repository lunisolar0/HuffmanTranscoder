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
	cout << "*欢迎使用哈夫曼编/译码器*" << endl;
	cout << "*   暂不支持中文文件    *" << endl;
	cout << "*                       *" << endl;
	cout << "* 1.按权值表生成编码表  *" << endl;
	cout << "*  2.按文件生成编码表   *" << endl;
	cout << "*     0.退出程序        *" << endl;
	cout << "*                       *" << endl;
	cout << "* 非法输入亦会退出程序  *" << endl;
	cout << "*注:以选项二生成的编码表*" << endl;
	cout << "*尽量对相应的文件编/译码*" << endl;
	cout << "*否则可能使文件内容丢失 *" << endl;
	cout << "*************************" << endl;
	cout << "请选择：";
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
		cout << "哈夫曼编码表已生成！" << endl;
		system("pause");
	}
	else if (c == 2)
	{
		HLS = InitHLS_file(wlsource);
		ToTreeHLS(HLS);
		HCL = InitHCL(HLS);
		PrintHT(HCL);
		cout << "哈夫曼编码表已生成！" << endl;
		system("pause");
	}
	if (c == 1 || c == 2) //编码表生成成功，进入功能界面
	{
		while (c)
		{
			system("cls");
			cout << "*************************" << endl;
			cout << "*欢迎使用哈夫曼编/译码器*" << endl;
			cout << "*   暂不支持中文文件    *" << endl;
			cout << "*                       *" << endl;
			cout << "*     1.文件转编码      *" << endl;
			cout << "*     2.编码转文件      *" << endl;
			cout << "*     3.打印代码串      *" << endl;
			cout << "*     4.打印编码表      *" << endl;
			cout << "*     0.退出该程序      *" << endl;
			cout << "*                       *" << endl;
			cout << "* 非法输入亦会退出程序  *" << endl;
			cout << "*选项3须在选项1之后执行 *" << endl;
			cout << "*************************" << endl;
			cout << "当前编码表来源:“" << wlsource << "”" ;
			if (source == 1) cout << "(按权值表生成)" << endl;
			else if (source == 2) cout << "(按文件生成)" << endl;
			cout << "请选择：";
			cin >> c;
			p = getchar();
			system("cls");
			switch (c)
			{
				case 1:
					cout << "当前编码表来源:“" << wlsource << "”";
					if (source == 1) cout << "(按权值表生成)" << endl;
					else if (source == 2) cout << "(按文件生成)" << endl;
					codefile = TransCode(HCL);
					cout << "文转码成功！" << endl;
					system("pause");
					break;
				case 2:
					cout << "当前编码表来源:“" << wlsource << "”";
					if (source == 1) cout << "(按权值表生成)" << endl;
					else if (source == 2) cout << "(按文件生成)" << endl;
					TransText(HCL);
					cout << "码转文成功！" << endl;
					system("pause");
					break;
				case 3:
					cout << "代码串如下(50个代码/行):" << endl;
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
	cout << "感谢您的使用，再见！" << endl;
	return 0;
}