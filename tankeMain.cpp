#include "tanke.h"

int main(void)
{
	WORD wordColor = 10;
	SetWindowSize("̹�˴�ս" , 100 , 39);

	WriteChar(45 , 4 , "��" , 0x0A);
	WriteChar(45 , 3 , "��" , 0x0A);
	WriteChar(45 , 5 , "��" , 0x0A);
	WriteChar(44 , 4 , "��" , 0x0A);
	WriteChar(46 , 4 , "��" , 0x0A);
	
	// initDefObj();
	testLink();// �������
	echoMap();

	messageLoop();

	return 0;
}