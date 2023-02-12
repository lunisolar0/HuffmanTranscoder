#pragma once
#include "clgener.h"

string TransCode(HCodeList& HCL); //文转码功能
void TransText(HCodeList& HCL); //码转文功能
void PrintCode(string codefile); //打印代码串
size_t GetSize_File(string filename); //计算文件大小