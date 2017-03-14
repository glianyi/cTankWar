#include "tanke.h"

// ����̨API���ռ����������

// �������������Ϣ
void outPutPos(int nX , int nY){
	char szBuff[ 100 ] = { 0 };
	sprintf_s(szBuff , sizeof(szBuff) , "x=%2d, y=%2d " , nX / 2 , nY);
	WriteChar(1 , 1 , szBuff , 10);
}

// �����¼�������
void keyEventProc(KEY_EVENT_RECORD ker){
	if(ker.bKeyDown && (ker.uChar.AsciiChar == 'W' || ker.uChar.AsciiChar == 'w'))
		WriteChar(1 , 2 , "W���̰���" , 10);
	else if(ker.uChar.AsciiChar == 'W' || ker.uChar.AsciiChar == 'w'){
		WriteChar(1 , 2 , "        " , 10);
	}

	if(ker.bKeyDown && (ker.uChar.AsciiChar == 'A' || ker.uChar.AsciiChar == 'a'))
		WriteChar(1 , 3 , "A���̰���" , 10);
	else if(ker.uChar.AsciiChar == 'A' || ker.uChar.AsciiChar == 'a'){
		WriteChar(1 , 3 , "        " , 10);
	}

	if(ker.bKeyDown && (ker.uChar.AsciiChar == 'S' || ker.uChar.AsciiChar == 's'))
		WriteChar(1 , 4 , "S���̰���" , 10);
	else if(ker.uChar.AsciiChar == 'S' || ker.uChar.AsciiChar == 's'){
		WriteChar(1 , 4 , "        " , 10);
	}

	if(ker.bKeyDown && (ker.uChar.AsciiChar == 'D' || ker.uChar.AsciiChar == 'd'))
		WriteChar(1 , 5 , "D���̰���" , 10);
	else if(ker.uChar.AsciiChar == 'd' || ker.uChar.AsciiChar == 'd'){
		WriteChar(1 , 5 , "        " , 10);
	}

	if(ker.bKeyDown && (ker.uChar.AsciiChar == ' '))
		WriteChar(1 , 6 , "�ո������" , 10);
	else if(ker.uChar.AsciiChar == ' '){
		WriteChar(1 , 6 , "          " , 10);
	}

	if(ker.bKeyDown && (ker.uChar.AsciiChar == 'Q' || ker.uChar.AsciiChar == 'q'))
		exit(0);

}

// ����¼�������
void mouseEventProc(MOUSE_EVENT_RECORD mer){
	switch(mer.dwEventFlags){
		case 0:
			if(mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
				WriteChar(1 , 2 , "�������" , 10);
			else if(mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
				WriteChar(1 , 2 , "�Ҽ�����" , 10);
			break;
		case DOUBLE_CLICK:
			WriteChar(1 , 2 , "˫��" , 10);
			break;
		case MOUSE_MOVED:
			outPutPos(mer.dwMousePosition.X , mer.dwMousePosition.Y);
			break;
	}
}

// ��Ϣ������
void messageLoop(){
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD stcRecord = { 0 };
	DWORD dwRead;
	SetConsoleMode(hStdin , ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

	while(1){
		// �ȴ��¼�
		ReadConsoleInput(hStdin , &stcRecord , 1 , &dwRead);
		// �����¼�
		if(stcRecord.EventType == KEY_EVENT){
			// �����¼�
			keyEventProc(stcRecord.Event.KeyEvent);
		}
		else if(stcRecord.EventType == MOUSE_EVENT){
			mouseEventProc(stcRecord.Event.MouseEvent);
		}
	}
}