#include "tanke.h"

/******************************************
����ṹ�崴��������
Type: �������� 0.���� 1.̹�� 2.�о�̹�� 4.�ӵ�
8.��ǽ16.שǽ 32.��ǽ 12.���� 7.�ݵ�
color:   ������ɫ
Bullft:  ����ֵ 0 - 255
Action:  ������ 0.�� 1.�� 2.�� 3.��
ltpostX: ���Ͻ�Ԫ�غ����� 0 - 39
ltpostY: ���Ͻ�Ԫ�������� 0 - 39
size:    ������� 1 - 40
ID:      ����ID 0 - 255
******************************************/
objInfo *creatObj(unshort Type , unshort size , unshort Action ,
				  unshort ltpostX , unshort ltpostY , unshort ID){
	objInfo *newObj = (objInfo*)malloc(sizeof(objInfo));
	if(newObj == NULL)
		exit(1);

	memset(newObj , 0 , sizeof(objInfo));
	newObj->Type = Type;
	newObj->size = size;
	newObj->Action = Action;
	newObj->ltposX = ltpostX;
	newObj->ltposY = ltpostY;
	newObj->ID = ID;

	switch(Type)
	{
		case 0:
			newObj->color = 0x04;
			newObj->Bullft = 1;
			break;
		case 1:
			newObj->color = 0x02;
			newObj->Bullft = 1;
			break;
		case 2:
			newObj->color = 0x04;
			newObj->Bullft = 1;
			break;
		case 4:
			newObj->color = 0x04;
			newObj->Bullft = 1;
			break;
		case 7:
			newObj->color = 0xAF;
			newObj->Bullft = 255;
			break;
		case 8:
			newObj->color = 0x0E;
			newObj->Bullft = 1;
			break;
		case 12:
			newObj->color = 0x9F;
			newObj->Bullft = 255;
			break;
		case 16:
			newObj->color = 0x06;
			newObj->Bullft = 2;
			break;
		case 32:
			newObj->color = 0x08;
			newObj->Bullft = 255;
			break;
		default:
			break;
	}
	return newObj;
}

// ϵͳ��ʼ��ͼ
unshort dftMap[ 40 ][ 40 ] = { 0 };
objInfo *allObj[ MAXOBJ ] = { NULL };
unshort objId = 5;
/*********************************************
��ӡ��ʼ״̬
*********************************************/
void initDefObj(){
	// ���Χǽ
	objInfo *mapWallTop = creatObj(32 , 40 , 3 , 0 , 0 , 1);
	allObj[ 1 ] = mapWallTop;
	objInfo *mapWallDown = creatObj(32 , 40 , 3 , 39 , 0 , 2);
	allObj[ 2 ] = mapWallDown;
	objInfo *mapWallLeft = creatObj(32 , 38 , 1 , 1 , 0 , 3);
	allObj[ 3 ] = mapWallLeft;
	objInfo *mapWallRight = creatObj(32 , 38 , 1 , 1 , 39 , 4);
	allObj[ 4 ] = mapWallRight;
	// ���ض���
	objInfo *myHome = creatObj(0 , 1 , 1 , 36 , 18 , 5);
	allObj[ 5 ] = myHome;
	// �������Χǽ
	objInfo *homeTopWall = creatObj( 8 , 6 , 3 , 35 , 17 , 6 );
	allObj[ 6 ] = homeTopWall;
	objInfo *homeLeftWall = creatObj( 8 , 3 , 1 , 36 , 17 , 7 );
	allObj[ 7 ] = homeLeftWall;
	objInfo *homeRightWall = creatObj( 8 , 3 , 1 , 36 , 22 , 8 );
	allObj[ 8 ] = homeRightWall;
	

	objInfo *objTemp;
	for(int i = 1; i < MAXOBJ; i++){
		if(allObj[ i ] == NULL)
			continue;
		objTemp = allObj[ i ];
		switch(objTemp->Type){
			case 0:
				echoHome(objTemp); break;
			case 7: case 8: case 12: case 16: case 32:
				echoBuid(objTemp); break;
			default:
				break;
		}
		// dftMap[ objTemp->ltposY ][ objTemp->ltposX ] = objTemp->ID;
	}
}

// ��ӡ̹��
void echoTanke(objInfo *tanke){
	if(tanke->Type != 1 || tanke->Type != 2 ||
	   tanke->ltposX > 36 || tanke->ltposY > 36)
		return;
}

// ��ӡ�ӵ�
void echoBullft(objInfo *bullft){
	if(bullft->Type != 4)
		return;
}

// ��ӡ����
void echoHome(objInfo *myHome){
	if(myHome->Type != 0)
		return;
	unshort x = myHome->ltposX;
	unshort y = myHome->ltposY;

	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 4; j++)
			dftMap[ x + i ][ y + j ] = myHome->ID;
}


// �жϽ�������������
int buidIsAct(short side,int xy, int ij){
	if(side == 0)
		return 0;
	if(side < 0){
		if(side + xy <= ij)
			return 1;
	}else
		if(side + xy >= ij)
			return 1;
	return 0;
}
void buidArtNum(short side , int *a){
	if(side == 0)
		return;
	if(side < 0){
		--(*a);
	}else
		++(*a);
}
// ��ӡ������
void echoBuid(objInfo *buid){
	unshort x = buid->ltposX;
	unshort y = buid->ltposY;
	short xSide = 0;
	short ySide = 0;
	if(buid->Action == 0)
		xSide -= buid->size + 1;
	else if(buid->Action == 1)
		xSide += buid->size - 1;
	else if(buid->Action == 2)
		ySide -= buid->size + 1;
	else
		ySide += buid->size - 1;
	
	for(int i = x, flagI = 1; (xSide == 0 && flagI-- == 1 ) ||
		buidIsAct(xSide, x , i); buidArtNum(xSide , &i))
		for(int j = y, flagJ = 1; (ySide == 0 && flagJ-- == 1) ||
			buidIsAct(ySide, y , j); buidArtNum(ySide , &j))
			dftMap[ i ][ j ] = buid->ID;
}