#include "tanke.h"

// 控制台API接收键盘鼠标输入

extern objInfo *allObj[ MAXOBJ ];
extern unshort dftMap[ MAXMAPWID ][ MAXMAPWID ];

// 输出调试坐标信息
void outPutPos(int nX , int nY){
	char szBuff[ 100 ] = { 0 };
	sprintf_s(szBuff , sizeof(szBuff) , "x=%2d, y=%2d " , nY , nX / 2);
	WriteChar(41 , 0 , szBuff , 0x0A);
}

// 键盘事件处理函数
void keyEventProc(KEY_EVENT_RECORD ker){
	if(ker.bKeyDown && (ker.uChar.AsciiChar == 'W' || ker.uChar.AsciiChar == 'w')){
		WriteChar(45 , 3 , "↑" , 0xFA);
		objMove(allObj[ 1 ], UP); 
		echoMap();
	}
	else if(ker.uChar.AsciiChar == 'W' || ker.uChar.AsciiChar == 'w'){
		WriteChar(45 , 3 , "↑" , 0x0A);
	}

	if(ker.bKeyDown && (ker.uChar.AsciiChar == 'A' || ker.uChar.AsciiChar == 'a')){
		WriteChar(44 , 4 , "←" , 0xFA);
		objMove(allObj[ 1 ] , LEFT);
		echoMap();

	}
	else if(ker.uChar.AsciiChar == 'A' || ker.uChar.AsciiChar == 'a'){
		WriteChar(44 , 4 , "←" , 0x0A);
	}

	if(ker.bKeyDown && (ker.uChar.AsciiChar == 'S' || ker.uChar.AsciiChar == 's')){
		WriteChar(45 , 5 , "↓" , 0xFA);
		objMove(allObj[ 1 ] , DOWN);
		echoMap();

	}
	else if(ker.uChar.AsciiChar == 'S' || ker.uChar.AsciiChar == 's'){
		WriteChar(45 , 5 , "↓" , 0x0A);
	}

	if(ker.bKeyDown && (ker.uChar.AsciiChar == 'D' || ker.uChar.AsciiChar == 'd')){
		WriteChar(46 , 4 , "→" , 0xFA);
		objMove(allObj[ 1 ] , RIGHT);
		echoMap();

	}
	else if(ker.uChar.AsciiChar == 'd' || ker.uChar.AsciiChar == 'd'){
		WriteChar(46 , 4 , "→" , 0x0A);
	}

	if(ker.bKeyDown && (ker.uChar.AsciiChar == ' '))
		WriteChar(45 , 4 , "●" , 0xFA);
	else if(ker.uChar.AsciiChar == ' '){
		WriteChar(45 , 4 , "○" , 0x0A);
	}

	if(ker.bKeyDown && (ker.uChar.AsciiChar == 'Q' || ker.uChar.AsciiChar == 'q'))
		exit(0);

}

// 鼠标事件处理函数
void mouseEventProc(MOUSE_EVENT_RECORD mer){
	switch(mer.dwEventFlags){
		case 0:
			if(mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
				WriteChar(41 , 1 , "左键单击" , 10);
			else if(mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
				WriteChar(41 , 1 , "右键单击" , 10);
			break;
		case DOUBLE_CLICK:
			WriteChar(41 , 1 , "双击    " , 10);
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