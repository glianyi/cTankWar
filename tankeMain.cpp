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
	
/*  BUG_01: ��������˳�ǰ����ĳ�������£�
			���´δ򿪳��򲻰��Ǹ���������
			��һֱ���ڱ�����״̬
			������볢�Ժ��޹�
*/
// 	BYTE a[ 256 ] = { 0 };
// 	LPBYTE b = a;
// 	if(SetKeyboardState(b))
// 		memset(a, 0, sizeof(a));
// 	if(a[ 'w' ] == 0 || a[ 'W' ] == 0)
// 		system("pause");

	initDefObj();
	// testLink();// �������
	echoMap();


	//fflush(stdin); // �������뻺����
	messageLoop();

	clrLink(&nLink , NULLARR);
	clrLink(&dTankLink , LINKOBJ);
	clrLink(&bulletLink , LINKOBJ);

	return 0;
}