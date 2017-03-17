#include "tanke.h"

// ����̨API���ռ����������

// �������������Ϣ
void outPutPos(int nX , int nY){
	char szBuff[ 100 ] = { 0 };
	sprintf_s(szBuff , sizeof(szBuff) , "x=%2d, y=%2d " , nY , nX / 2);
	WriteChar(41 , 0 , szBuff , 0x0A);
}

// �����¼������� 3
void keyEvent(){
	if(KEYDOWN('w') || KEYDOWN('W')){
		WriteChar(45 , 3 , "��" , 0xFA);
		objMove(allObj[ 1 ] , UP);
		echoMap(allObj[1]);
	}
	else if(KEYDOWN('s') || KEYDOWN('S')){
		WriteChar(45 , 5 , "��" , 0xFA);
		objMove(allObj[ 1 ] , DOWN);
		echoMap(allObj[ 1 ]);
	}
	else if(KEYDOWN('a') || KEYDOWN('A')){
		WriteChar(44 , 4 , "��" , 0xFA);
		objMove(allObj[ 1 ] , LEFT);
		echoMap(allObj[ 1 ]);
	}
	else if(KEYDOWN('d') || KEYDOWN('D')){
		WriteChar(46 , 4 , "��" , 0xFA);
		objMove(allObj[ 1 ] , RIGHT);
		echoMap(allObj[ 1 ]);
	}
	else if(KEYDOWN('h') || KEYDOWN('H')){
		WriteChar(45 , 4 , "��" , 0xFA);
		fire(allObj[ 1 ]);
	}
	else if(KEYDOWN('m') || KEYDOWN('M')){
		clrLink(&nLink , NULLARR);
		clrLink(&dTankLink , LINKOBJ);
		clrLink(&bulletLink , LINKOBJ);
		//fflush(stdin); // �������뻺����
		exit(0);
	}

	if(KEYUP('w') || KEYUP('W')){
		WriteChar(45 , 3 , "��" , 0x0A);
	}
	if(KEYUP('s') || KEYUP('S')){
		WriteChar(45 , 5 , "��" , 0x0A);
	}
	if(KEYUP('a') || KEYUP('A')){
		WriteChar(44 , 4 , "��" , 0x0A);
	}
	if(KEYUP('d') || KEYUP('D')){
		WriteChar(46 , 4 , "��" , 0x0A);
	}
	if(KEYUP('h') || KEYUP('H')){
		WriteChar(45 , 4 , "��" , 0x0A);
	}
}

// �����¼������� 2
void keyEventSec(){
	if(_kbhit()){
		char ch = _getch();
		switch(ch)
		{
			case 'w': case 'W':
				WriteChar(45 , 3 , "��" , 0xFA);
				objMove(allObj[ 1 ] , UP);
				echoMap(allObj[ 1 ]);
				break;
			case 's': case 'S':
				WriteChar(45 , 5 , "��" , 0xFA);
				objMove(allObj[ 1 ] , DOWN);
				echoMap(allObj[ 1 ]);
				break;
			case 'a': case 'A':
				WriteChar(44 , 4 , "��" , 0xFA);
				objMove(allObj[ 1 ] , LEFT);
				echoMap(allObj[ 1 ]);
				break;
			case 'd': case 'D':
				WriteChar(46 , 4 , "��" , 0xFA);
				objMove(allObj[ 1 ] , RIGHT);
				echoMap(allObj[ 1 ]);
				break;
			case 'h': case 'H':
				WriteChar(45 , 4 , "��" , 0xFA);
				fire(allObj[ 1 ]);
				break;
			case 'q': case 'Q':
				clrLink(&nLink , NULLARR);
				clrLink(&dTankLink , LINKOBJ);
				clrLink(&bulletLink , LINKOBJ);
				//fflush(stdin); // �������뻺����
				exit(0);
				break;
			default:
				break;
		}
	}
}
// �����¼������� 1
void keyEventProc(KEY_EVENT_RECORD ker){
	char ch = ker.uChar.AsciiChar;
	switch(ch)
	{
		case 'w': case 'W':
			WriteChar(45 , 3 , "��" , 0xFA);
			objMove(allObj[ 1 ] , UP);
			echoMap(allObj[1]);
			break;
		case 's': case 'S':
			WriteChar(45 , 5 , "��" , 0xFA);
			objMove(allObj[ 1 ] , DOWN);
			echoMap(allObj[ 1 ]);
			break;
		case 'a': case 'A':
			WriteChar(44 , 4 , "��" , 0xFA);
			objMove(allObj[ 1 ] , LEFT);
			echoMap(allObj[ 1 ]);
			break;
		case 'd': case 'D':
			WriteChar(46 , 4 , "��" , 0xFA);
			objMove(allObj[ 1 ] , RIGHT);
			echoMap(allObj[ 1 ]);
			break;
		case 'h': case 'H':
			WriteChar(45 , 4 , "��" , 0xFA);
			fire(allObj[ 1 ]);
			break;
		case 'q': case 'Q':
			clrLink(&nLink , NULLARR);
			clrLink(&dTankLink , LINKOBJ);
			clrLink(&bulletLink , LINKOBJ);
			//fflush(stdin); // �������뻺����
			exit(0);
			break;
		default:
			break;
	}
}

// ����¼�������
void mouseEventProc(MOUSE_EVENT_RECORD mer){
	switch(mer.dwEventFlags){
		case 0:
			if(mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
				WriteChar(41 , 1 , "�������" , 10);
			else if(mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
				WriteChar(41 , 1 , "�Ҽ�����" , 10);
			break;
		case DOUBLE_CLICK:
			WriteChar(41 , 1 , "˫��    " , 10);
			break;
		case MOUSE_MOVED:
			outPutPos(mer.dwMousePosition.X , mer.dwMousePosition.Y);
			break;
	}
}

// CPUʱ�ӵδ��� - ���ڿ��Ƶз�̹�˺��ӵ����ٶ�
long long seconds = 0; // ʵʱ����
long long bullseconds = 0;// �ӵ��ƶ��ж�����
long long tankseconds = 0;// ̹���ƶ��ж�����
long long keyseconds = 0;// �����ƶ��ж�����

// ��Ϣ������
void messageLoop(){
	/*
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD stcRecord = { 0 };
	DWORD dwRead;
	SetConsoleMode(hStdin , ENABLE_MOUSE_INPUT);
	*/

	WriteChar(41 , 8 , "ʣ������" , 0x0A);
	char szBuff[ 10 ];
	sprintf_s(szBuff , 10 , "%2d" , allObj[ 1 ]->Bullft);
	WriteChar(45 , 8 , szBuff , 0x0A);

	WriteChar(41 , 10 , "�о�����" , 0x0A);
	sprintf_s(szBuff , 10 , "%2d" , dTankNum);
	WriteChar(45 , 10 , szBuff , 0x0A);

	while(1){
		seconds = clock();
		if(seconds - bullseconds > 100){
			bullseconds = seconds;

			// �Զ��ƶ��ӵ�
 			moveBul();

			// ���ð����������
			WriteChar(45 , 3 , "��" , 0x0A);
			WriteChar(45 , 5 , "��" , 0x0A);
			WriteChar(44 , 4 , "��" , 0x0A);
			WriteChar(46 , 4 , "��" , 0x0A);
			WriteChar(45 , 4 , "��" , 0x0A);
		}
		if(seconds - tankseconds > 300){
			tankseconds = seconds;
			// ̹���޵�ʱ��
			if(tankLife > 0){
				allObj[ 1 ]->color = ((allObj[ 1 ]->color) == 0x0A) ? 0x0D : 0x0A;
				--tankLife;
			}
			// �Զ��ƶ�̹��
			moveDtk();
		}

		WriteChar(41 , 12 , "�޵�ʱ��" , 0x0A);
		sprintf_s(szBuff , 10 , "%2d" , tankLife);
		WriteChar(45 , 12 , szBuff , 0x0A);
		keyEventSec();
		echoMap();

		if(gameOver > 0){
			//return;
		}
		//Sleep(100);
	}
/*	while(0){
		// �ȴ��¼�
		ReadConsoleInput(hStdin , &stcRecord , 1 , &dwRead);
		// ��������¼�
		// if(stcRecord.EventType == MOUSE_EVENT){
			mouseEventProc(stcRecord.Event.MouseEvent);
		}
	}*/
}