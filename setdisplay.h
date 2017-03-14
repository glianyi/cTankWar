#pragma once

/*******************************
函数功能：打印字符到控制台制定位置
High: 高度X行
Wide: 宽度Y列
pszChar: 打印的字符
wArr: 打印字符的属性
*******************************/
void WriteChar(int High , int Wide , char* pszChar , WORD wArr);

/*********************************
函数功能: 设置窗口信息
*pszWindewTitle: 窗口名称
nX: 窗口宽度
nY: 窗口高度
成功返回值: true
*********************************/
bool SetWindowSize(char *pszWindowTitle , int nX , int nY);