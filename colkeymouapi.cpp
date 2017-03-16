#include "tanke.h"

// 控制台API接收键盘鼠标输入

// 输出调试坐标信息
void outPutPos(int nX , int nY){
	char szBuff[ 100 ] = { 0 };
	sprintf_s(szBuff , sizeof(szBuff) , "x=%2d, y=%2d " , nY , nX / 2);
	WriteChar(41 , 0 , szBuff , 0x0A);
}

// 键盘事件处理函数
void keyEventProc(){
	if(KEYDOWN('w') || KEYDOWN('W')){
		WriteChar(45 , 3 , "↑" , 0xFA);
		objMove(allObj[ 1 ] , UP);
		echoMap(allObj[1]);
	}
	else if(KEYDOWN('s') || KEYDOWN('S')){
		WriteChar(45 , 5 , "↓" , 0xFA);
		objMove(allObj[ 1 ] , DOWN);
		echoMap(allObj[ 1 ]);
	}
	else if(KEYDOWN('a') || KEYDOWN('A')){
		WriteChar(44 , 4 , "←" , 0xFA);
		objMove(allObj[ 1 ] , LEFT);
		echoMap(allObj[ 1 ]);
	}
	else if(KEYDOWN('d') || KEYDOWN('D')){
		WriteChar(46 , 4 , "→" , 0xFA);
		objMove(allObj[ 1 ] , RIGHT);
		echoMap(allObj[ 1 ]);
	}
	else if(KEYDOWN('h') || KEYDOWN('H')){
		WriteChar(45 , 4 , "●" , 0xFA);
		fire(allObj[ 1 ]);
	}
	else if(KEYDOWN('m') || KEYDOWN('M')){
		clrLink(&nLink , NULLARR);
		clrLink(&dTankLink , LINKOBJ);
		clrLink(&bulletLink , LINKOBJ);
		//fflush(stdin); // 清理输入缓冲区
		exit(0);
	}

	WriteChar(45 , 3 , "↑" , 0x0A);
	WriteChar(45 , 5 , "↓" , 0x0A);
	WriteChar(44 , 4 , "←" , 0x0A);
	WriteChar(46 , 4 , "→" , 0x0A);
	WriteChar(45 , 4 , "○" , 0x0A);
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
	//DWORD dwRead;
	SetConsoleMode(hStdin , ENABLE_MOUSE_INPUT);

	WriteChar(41 , 7 , "剩余生命" , 0x0A);
	char szBuff[ 10 ];
	sprintf_s(szBuff , 10 , "%2d" , allObj[ 1 ]->Bullft);
	WriteChar(45 , 7 , szBuff , 0x0A);

	int i = 0;
	while(1){
		echoMap();

 		moveBul();
		if(i > 5){
			i = 0;
			// 自动移动坦克
			moveDtk();
		}
		++i;

		// 等待事件
		//ReadConsoleInput(hStdin , &stcRecord , 1 , &dwRead);
		// 处理事件
		// 键盘事件
		keyEventProc();
		if(stcRecord.EventType == MOUSE_EVENT){
			mouseEventProc(stcRecord.Event.MouseEvent);
		}
		if(gameOver > 0){
			//fflush(stdin); // 清理输入缓冲区
			return;
		}
		//Sleep(100);
	}
}