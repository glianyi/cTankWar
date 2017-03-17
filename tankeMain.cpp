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
	

	initDefObj();
	// testLink();// 链表测试
	echoMap();

	WriteChar(41 , 38 , "(Q) 退出" , 0x0A);

	//fflush(stdin); // 清理输入缓冲区
	messageLoop();

	clrLink(&nLink , NULLARR);
	clrLink(&dTankLink , LINKOBJ);
	clrLink(&bulletLink , LINKOBJ);

	return 0;
}