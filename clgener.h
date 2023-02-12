#pragma once
#include <string>

using namespace std;

typedef struct HLinkedListsNode //链式哈夫曼树节点
{
    HLinkedListsNode* left, * right, * next;
    char data;
    int weight;
} *HLinkedLists;

/*定义编码表*/
typedef struct HCodeElem //编码单元
{
    char name = {};
    string code = {};
}HCodeElem;

typedef struct HCodeList //编码表
{
    HCodeElem ce[100];
    int length = 0;
}HCodeList;

void ClearHLS(HLinkedLists& HLS); //清空哈夫曼链式广义表
HLinkedLists InitHLS_std(string& wlsource); //创建哈夫曼链式广义表(直接读入)
HLinkedLists InitHLS_file(string& wlsource); //创建哈夫曼链式广义表(按文件内容统计)
void ToTreeHLS(HLinkedLists& HLS); //哈夫曼树生成
void PrintHT(HCodeList& HCL); //生成"hfmTree"编码表
void Print2H(HLinkedLists& HLS, HCodeList& HCL); //中序输出哈夫曼树及附带编码表
void Print2H_sub(HLinkedLists& HLS); //中序输出哈夫曼树的子函数
void Print2H_F(HLinkedLists& HLS, HCodeList& HCL); //中序输出哈夫曼树及附带编码表(文件)
void Print2H_F_sub(HLinkedLists& HLS); //中序输出哈夫曼树(文件)的子函数

HCodeList InitHCL(HLinkedLists& HLS); //创建哈夫曼编码表
void InitHCL_sub(HLinkedLists& HLS, HCodeList& HCL); //创建哈夫曼编码表的子函数
int ToCodeHCL(HCodeList& HCL, char ch); //查找字符对应的编码串
int ToCharHCL(HCodeList& HCL, string st); //查找编码串对应的字符
