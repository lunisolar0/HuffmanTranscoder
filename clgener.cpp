#include <iostream>
#include <fstream>
#include <windows.h>
#include "clgener.h"

ifstream ifs;
ofstream ofs;

void ClearHLS(HLinkedLists& HLS) //清空哈夫曼链式广义表
{
    for (HLinkedLists temp = HLS->next; temp;)
    {
        HLinkedLists p = temp;
        temp = temp->next;
        HLS->next = temp;
        delete p;
    }
}

HLinkedLists InitHLS_std(string& wlsource) //创建哈夫曼链式广义表(直接读入)
{
    HLinkedLists HLS= new HLinkedListsNode;
    HLS->next = NULL;
    HLinkedLists r = HLS;
    int error;
    do
    {
        error = 0;
        do
        {
            cout << "权值表需按“字符 权值”形式编写且权值不可为0\n字符权值组之间需用空格或换行隔开" << endl;
            cout << "请输入即将读入的权值表文件路径(包括后缀)：" << endl;
            getline(cin, wlsource);
            ifs.open(wlsource, ios::in);
            if (!ifs.is_open())
            { //判断文件是否打开成功
                cout << "文件“" << wlsource << "”打开失败，请重新输入！" << endl;
            }
        } while (!ifs.is_open());
        while(1)
        {
            char c_buf;
            int d_buf;
            if ((c_buf = ifs.get()) == EOF) break;
            ifs >> d_buf;
            if (!d_buf)
            {
                ClearHLS(HLS);
                error = 1;
                cout << "Error input!错误权值：" << c_buf << " " << d_buf << endl;
                break;
            }
            HLinkedLists temp = new HLinkedListsNode;
            temp->left = NULL;
            temp->right = NULL;
            temp->data = c_buf;
            temp->weight = d_buf;
            temp->next = NULL;
            r->next = temp;
            r = r->next;
            ifs.get();
        }
        ifs.close();
        if (error)
        {
            cout << "该权值表未按要求编写！" << endl;
            system("pause");
            system("cls");
        }
    } while (error);
    return HLS;
}

HLinkedLists InitHLS_file(string& wlsource) //创建哈夫曼链式广义表(按文件内容统计)
{
    HLinkedLists HLS = new HLinkedListsNode;
    HLS->next = NULL;
    HLinkedLists r = HLS;
    do
    {
        cout << "程序将根据某个文件的内容生成该文件的专属权值表\n并根据该权值表生成哈夫曼编码表" << endl;
        cout << "请输入即将读入的文件路径(包括后缀)：" << endl;
        getline(cin, wlsource);
        ifs.open(wlsource, ios::in);
        if (!ifs.is_open())
        { //判断文件是否打开成功
            cout << "文件“" << wlsource << "”打开失败，请重新输入！" << endl;
        }
    } while (!ifs.is_open());
    char ch;
    while ((ch = ifs.get()) != EOF)
    {
        int flag = 0;
        for (HLinkedLists temp = HLS->next; !flag; temp = temp->next)
        {
            if (temp && temp->data == ch)
            {
                temp->weight++;
                flag = 1;
            }
            else if (!temp)
            {
                temp = new HLinkedListsNode;
                temp->left = NULL;
                temp->right = NULL;
                temp->data = ch;
                temp->weight = 1;
                temp->next = NULL;
                r->next = temp;
                r = r->next;
                flag = 1;
            }
        }
    }
    int c;
    cout << "权值表已生成！是否需要将其写入文件？" << endl;
    cout << "1.是  0.否 (非法输入视为否)" << endl;
    cout << "请选择：";
    cin >> c;
    int p = getchar();
    if (c==1)
    {
        string filename;
        cout << "请输入目标文件路径(包括后缀)：" << endl;
        getline(cin, filename);
        ofs.open(filename, ios::out);
        for (HLinkedLists temp = HLS->next; temp; temp = temp->next)
        {
            ofs << temp->data << " " << temp->weight;
            if (temp->next) ofs << endl;
        }
        cout << "已将权值表写入“" << filename << "”！" << endl;
        ofs.close();
    }
    ifs.close();
    return HLS;
}

void ToTreeHLS(HLinkedLists& HLS) //哈夫曼树生成
{
    HLinkedLists p1 = HLS, p2 = HLS, p1f = HLS, p2f = HLS, temp = HLS;
    int min = 0;
    while (temp->next)
    {
        if (min == 0 || temp->next->weight < min)
        {
            min = temp->next->weight;
            p1f = temp;
            p1 = temp->next;
        }
        temp = temp->next;
    }
    temp = HLS;
    min = 0;
    while (temp->next)
    {
        if (min == 0 || temp->next->weight < min)
        {
            if (temp != p1f)
            {
                min = temp->next->weight;
                p2f = temp;
                p2 = temp->next;
            }
        }
        temp = temp->next;
    }
    p1f->next = p1->next;
    p1->next = NULL;
    if (p2f == p1)
        p2f = p1f;
    p2f->next = p2->next;
    p2->next = NULL;
    temp = new HLinkedListsNode;
    temp->data = {};
    temp->weight = p1->weight + p2->weight;
    temp->left = p1;
    temp->right = p2;
    temp->next = HLS->next;
    HLS->next = temp;
    if (HLS->next->next)
    {
        ToTreeHLS(HLS);
    }
}

HCodeList InitHCL(HLinkedLists& HLS) //创建哈夫曼编码表
{
    HCodeList HCL;
    InitHCL_sub(HLS->next, HCL);
    return HCL;
}

void InitHCL_sub(HLinkedLists& HLS, HCodeList& HCL) //创建哈夫曼编码表的子函数
{
    if (HLS->data)
    {
        HCL.ce[++HCL.length].name = HLS->data;
        HCL.ce[HCL.length].code = HCL.ce[0].code;
        while (1)
        {
            char temp = HCL.ce[0].code.back();
            HCL.ce[0].code.pop_back();
            if (temp == '0' || HCL.ce[0].code.empty()) break;
        }
    }
    else
    {
        HCL.ce[0].code = HCL.ce[0].code + '0';
        InitHCL_sub(HLS->left, HCL);
        HCL.ce[0].code = HCL.ce[0].code + '1';
        InitHCL_sub(HLS->right, HCL);
    }
}

void PrintHT(HCodeList& HCL) //生成"hfmTree"编码表
{
    ofs.open("hfmTree.txt", ios::out);
    for (int i = 1; i <= HCL.length; i++)
    {
        ofs << HCL.ce[i].name << HCL.ce[i].code;
        if (i < HCL.length) ofs << endl;
    }
    ofs.close();
}

void Print2H_F(HLinkedLists& HLS, HCodeList& HCL) //中序输出哈夫曼树及附带编码表(文件)
{
    ofs.open("TreePrint.txt", ios::out);
    ofs << "哈夫曼树中序输出如下：" << endl;
    Print2H_F_sub(HLS->next);
    ofs << endl;
    ofs << "哈夫曼编码表如下：" << endl;
    for (int i = 1; i <= HCL.length; i++)
    {
        ofs << HCL.ce[i].name << "：";
        ofs << HCL.ce[i].code << endl;
    }
    ofs.close();
}

void Print2H_F_sub(HLinkedLists& HLS) //中序输出哈夫曼树(文件)的子函数
{
    if (!HLS)
        return;
    else
    {
        Print2H_F_sub(HLS->left);
        ofs << HLS->data << HLS->weight << " -> ";
        Print2H_F_sub(HLS->right);
    }
}

void Print2H(HLinkedLists& HLS, HCodeList& HCL) //中序输出哈夫曼树及附带编码表
{
    cout << "哈夫曼树中序输出如下：" << endl;
    Print2H_sub(HLS->next);
    cout << endl;
    cout << "哈夫曼编码表如下：" << endl;
    for (int i = 1; i <= HCL.length; i++)
    {
        cout << HCL.ce[i].name << "：";
        cout << HCL.ce[i].code << endl;
    }
}

void Print2H_sub(HLinkedLists& HLS) //中序输出哈夫曼树的子函数
{
    if (!HLS)
        return;
    else
    {
        Print2H_sub(HLS->left);
        cout << HLS->data << HLS->weight << " -> ";
        Print2H_sub(HLS->right);
    }
}

int ToCodeHCL(HCodeList& HCL, char ch) //查找字符对应的编码串
{
    HCL.ce[0].name = ch;
    int i;
    for (i = HCL.length; ch != HCL.ce[i].name; i--);
    return i;
}

int ToCharHCL(HCodeList& HCL, string st) //查找编码串对应的字符
{
    HCL.ce[0].code = st;
    int i;
    for (i = HCL.length; st != HCL.ce[i].code; i--);
    return i;
}