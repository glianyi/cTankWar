#pragma once

/*******************************
�������ܣ���ӡ�ַ�������̨�ƶ�λ��
High: �߶�X��
Wide: ���Y��
pszChar: ��ӡ���ַ�
wArr: ��ӡ�ַ�������
*******************************/
void WriteChar(int High , int Wide , char* pszChar , WORD wArr);

/*********************************
��������: ���ô�����Ϣ
*pszWindewTitle: ��������
nX: ���ڿ��
nY: ���ڸ߶�
�ɹ�����ֵ: true
*********************************/
bool SetWindowSize(char *pszWindowTitle , int nX , int nY);