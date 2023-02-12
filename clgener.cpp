#include <iostream>
#include <fstream>
#include <windows.h>
#include "clgener.h"

ifstream ifs;
ofstream ofs;

void ClearHLS(HLinkedLists& HLS) //��չ�������ʽ�����
{
    for (HLinkedLists temp = HLS->next; temp;)
    {
        HLinkedLists p = temp;
        temp = temp->next;
        HLS->next = temp;
        delete p;
    }
}

HLinkedLists InitHLS_std(string& wlsource) //������������ʽ�����(ֱ�Ӷ���)
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
            cout << "Ȩֵ���谴���ַ� Ȩֵ����ʽ��д��Ȩֵ����Ϊ0\n�ַ�Ȩֵ��֮�����ÿո���и���" << endl;
            cout << "�����뼴�������Ȩֵ���ļ�·��(������׺)��" << endl;
            getline(cin, wlsource);
            ifs.open(wlsource, ios::in);
            if (!ifs.is_open())
            { //�ж��ļ��Ƿ�򿪳ɹ�
                cout << "�ļ���" << wlsource << "����ʧ�ܣ����������룡" << endl;
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
                cout << "Error input!����Ȩֵ��" << c_buf << " " << d_buf << endl;
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
            cout << "��Ȩֵ��δ��Ҫ���д��" << endl;
            system("pause");
            system("cls");
        }
    } while (error);
    return HLS;
}

HLinkedLists InitHLS_file(string& wlsource) //������������ʽ�����(���ļ�����ͳ��)
{
    HLinkedLists HLS = new HLinkedListsNode;
    HLS->next = NULL;
    HLinkedLists r = HLS;
    do
    {
        cout << "���򽫸���ĳ���ļ����������ɸ��ļ���ר��Ȩֵ��\n�����ݸ�Ȩֵ�����ɹ����������" << endl;
        cout << "�����뼴��������ļ�·��(������׺)��" << endl;
        getline(cin, wlsource);
        ifs.open(wlsource, ios::in);
        if (!ifs.is_open())
        { //�ж��ļ��Ƿ�򿪳ɹ�
            cout << "�ļ���" << wlsource << "����ʧ�ܣ����������룡" << endl;
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
    cout << "Ȩֵ�������ɣ��Ƿ���Ҫ����д���ļ���" << endl;
    cout << "1.��  0.�� (�Ƿ�������Ϊ��)" << endl;
    cout << "��ѡ��";
    cin >> c;
    int p = getchar();
    if (c==1)
    {
        string filename;
        cout << "������Ŀ���ļ�·��(������׺)��" << endl;
        getline(cin, filename);
        ofs.open(filename, ios::out);
        for (HLinkedLists temp = HLS->next; temp; temp = temp->next)
        {
            ofs << temp->data << " " << temp->weight;
            if (temp->next) ofs << endl;
        }
        cout << "�ѽ�Ȩֵ��д�롰" << filename << "����" << endl;
        ofs.close();
    }
    ifs.close();
    return HLS;
}

void ToTreeHLS(HLinkedLists& HLS) //������������
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

HCodeList InitHCL(HLinkedLists& HLS) //���������������
{
    HCodeList HCL;
    InitHCL_sub(HLS->next, HCL);
    return HCL;
}

void InitHCL_sub(HLinkedLists& HLS, HCodeList& HCL) //�����������������Ӻ���
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

void PrintHT(HCodeList& HCL) //����"hfmTree"�����
{
    ofs.open("hfmTree.txt", ios::out);
    for (int i = 1; i <= HCL.length; i++)
    {
        ofs << HCL.ce[i].name << HCL.ce[i].code;
        if (i < HCL.length) ofs << endl;
    }
    ofs.close();
}

void Print2H_F(HLinkedLists& HLS, HCodeList& HCL) //��������������������������(�ļ�)
{
    ofs.open("TreePrint.txt", ios::out);
    ofs << "������������������£�" << endl;
    Print2H_F_sub(HLS->next);
    ofs << endl;
    ofs << "��������������£�" << endl;
    for (int i = 1; i <= HCL.length; i++)
    {
        ofs << HCL.ce[i].name << "��";
        ofs << HCL.ce[i].code << endl;
    }
    ofs.close();
}

void Print2H_F_sub(HLinkedLists& HLS) //���������������(�ļ�)���Ӻ���
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

void Print2H(HLinkedLists& HLS, HCodeList& HCL) //��������������������������
{
    cout << "������������������£�" << endl;
    Print2H_sub(HLS->next);
    cout << endl;
    cout << "��������������£�" << endl;
    for (int i = 1; i <= HCL.length; i++)
    {
        cout << HCL.ce[i].name << "��";
        cout << HCL.ce[i].code << endl;
    }
}

void Print2H_sub(HLinkedLists& HLS) //������������������Ӻ���
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

int ToCodeHCL(HCodeList& HCL, char ch) //�����ַ���Ӧ�ı��봮
{
    HCL.ce[0].name = ch;
    int i;
    for (i = HCL.length; ch != HCL.ce[i].name; i--);
    return i;
}

int ToCharHCL(HCodeList& HCL, string st) //���ұ��봮��Ӧ���ַ�
{
    HCL.ce[0].code = st;
    int i;
    for (i = HCL.length; st != HCL.ce[i].code; i--);
    return i;
}