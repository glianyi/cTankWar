#include "tanke.h"

extern unshort dftMap[40][40];
int main(void)
{
	WORD wordColor = 10;
	SetWindowSize("̹�˴�ս" , 80 , 39);
	
	initDefObj();

	readMap();

	messageLoop();

	return 0;
}