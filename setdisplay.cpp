#include "tanke.h"

/*******************************
�������ܣ���ӡ�ַ�������̨�ƶ�λ��
Wide: ���X��
High: �߶�Y��
pszChar: ��ӡ���ַ�
wArr: ��ӡ�ַ�������
*******************************/
void WriteChar(int Wide ,int High ,  char* pszChar , WORD wArr){
	CONSOLE_CURSOR_INFO cii;
	cii.dwSize = 1;
	cii.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE) , &cii);
	COORD loc;
	loc.X = Wide * 2;
	loc.Y = High;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , wArr);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , loc);
	printf(pszChar);
}

/*********************************
��������: ���ô�����Ϣ
*pszWindewTitle: ��������
nX: ���ڿ��
nY: ���ڸ߶�
�ɹ�����ֵ: true
*********************************/
bool SetWindowSize(char *pszWindowTitle , int nX , int nY){
	// Title
	SetConsoleTitleA(pszWindowTitle);
	HANDLE hStdin , hStdOut;
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// get max console window size
	COORD pos = GetLargestConsoleWindowSize(hStdOut);
	COORD BufferSize = { pos.X + 1 , pos.Y + 1 };
	// set console buffer size
	if(!SetConsoleScreenBufferSize(hStdOut , BufferSize)){
		// set console buffer size false
		printf("buffer err(%d,%d)%d\n" , BufferSize.X , BufferSize.Y , GetLastError());
		return false;
	}
	SMALL_RECT srctWindow = { 0 , 0 , nX , nY };
	if(!SetConsoleWindowInfo(hStdOut , true , &srctWindow)){
		// set console window size false
		printf("size err %d\n" , GetLastError());
		return false;
	}
	COORD Buffer = { nX + 1 , nY + 1 };
	// set console buffer size
	if(!SetConsoleScreenBufferSize(hStdOut , Buffer)){
		// set console buffer size false
		printf("buffer err(%d, %d)%d\n" , BufferSize.X , BufferSize.Y , GetLastError());
		return false;
	}
	return true;
}
