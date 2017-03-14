#include "tanke.h"

// 控制台API接收键盘鼠标输入

// 输出调试坐标信息
void outPutPos(int nX , int nY){
	char szBuff[ 100 ] = { 0 };
	sprintf_s(szBuff , sizeof(szBuff) , "x=%2d, y=%2d " , nX / 2 , nY);
	WriteChar(1 , 1 , szBuff , 10);
}

// 键盘事件处理函数
void keyEventProc(KEY_EVENT_RECORD ker){
	if(ker.bKeyDown && (ker.uChar.AsciiChar == 'W' || ker.uChar.AsciiChar == 'w'))
		WriteChar(1 , 2 , "W键盘按下" , 10);
	else if(ker.uChar.AsciiChar == 'W' || ker.uChar.AsciiChar == 'w'){
		WriteChar(1 , 2 , "        " , 10);
	}

	if(ker.bKeyDown && (ker.uChar.AsciiChar == 'A' || ker.uChar.AsciiChar == 'a'))
		WriteChar(1 , 3 , "A键盘按下" , 10);
	else if(ker.uChar.AsciiChar == 'A' || ker.uChar.AsciiChar == 'a'){
		WriteChar(1 , 3 , "        " , 10);
	}

	if(ker.bKeyDown && (ker.uChar.AsciiChar == 'S' || ker.uChar.AsciiChar == 's'))
		WriteChar(1 , 4 , "S键盘按下" , 10);
	else if(ker.uChar.AsciiChar == 'S' || ker.uChar.AsciiChar == 's'){
		WriteChar(1 , 4 , "        " , 10);
	}

	if(ker.bKeyDown && (ker.uChar.AsciiChar == 'D' || ker.uChar.AsciiChar == 'd'))
		WriteChar(1 , 5 , "D键盘按下" , 10);
	else if(ker.uChar.AsciiChar == 'd' || ker.uChar.AsciiChar == 'd'){
		WriteChar(1 , 5 , "        " , 10);
	}

	if(ker.bKeyDown && (ker.uChar.AsciiChar == ' '))
		WriteChar(1 , 6 , "空格键按下" , 10);
	else if(ker.uChar.AsciiChar == ' '){
		WriteChar(1 , 6 , "          " , 10);
	}

	if(ker.bKeyDown && (ker.uChar.AsciiChar == 'Q' || ker.uChar.AsciiChar == 'q'))
		exit(0);

}

// 鼠标事件处理函数
void mouseEventProc(MOUSE_EVENT_RECORD mer){
	switch(mer.dwEventFlags){
		case 0:
			if(mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
				WriteChar(1 , 2 , "左键单击" , 10);
			else if(mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
				WriteChar(1 , 2 , "右键单击" , 10);
			break;
		case DOUBLE_CLICK:
			WriteChar(1 , 2 , "双击" , 10);
			break;
		case MOUSE_MOVED:
			outPutPos(mer.dwMousePosition.X , mer.dwMousePosition.Y);
			break;
	}
}

// 消息处理函数
void messageLoop(){
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD stcRecord = { 0 };
	DWORD dwRead;
	SetConsoleMode(hStdin , ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

	while(1){
		// 等待事件
		ReadConsoleInput(hStdin , &stcRecord , 1 , &dwRead);
		// 处理事件
		if(stcRecord.EventType == KEY_EVENT){
			// 键盘事件
			keyEventProc(stcRecord.Event.KeyEvent);
		}
		else if(stcRecord.EventType == MOUSE_EVENT){
			mouseEventProc(stcRecord.Event.MouseEvent);
		}
	}
}