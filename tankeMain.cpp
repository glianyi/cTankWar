#include "tanke.h"

int main(void)
{
	WORD wordColor = 10;
	SetWindowSize("坦克大战" , 100 , 39);

	WriteChar(45 , 4 , "○" , 0x0A);
	WriteChar(45 , 3 , "↑" , 0x0A);
	WriteChar(45 , 5 , "↓" , 0x0A);
	WriteChar(44 , 4 , "←" , 0x0A);
	WriteChar(46 , 4 , "→" , 0x0A);
	
/*  BUG_01: 如果程序退出前键盘某按键按下，
			则下次打开程序不按那个按键，它
			会一直处于被按下状态
			下面代码尝试后无果
*/
// 	BYTE a[ 256 ] = { 0 };
// 	LPBYTE b = a;
// 	if(SetKeyboardState(b))
// 		memset(a, 0, sizeof(a));
// 	if(a[ 'w' ] == 0 || a[ 'W' ] == 0)
// 		system("pause");

	initDefObj();
	// testLink();// 链表测试
	echoMap();


	//fflush(stdin); // 清理输入缓冲区
	messageLoop();

	clrLink(&nLink , NULLARR);
	clrLink(&dTankLink , LINKOBJ);
	clrLink(&bulletLink , LINKOBJ);

	return 0;
}