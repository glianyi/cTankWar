#include "tanke.h"

/******************************************
����ṹ�崴��������
Type: ��������: ��ϸ�μ�tanke.hͷ�ļ�����
color:   ������ɫ
Bullft:  ����ֵ(ǽ�屻����Ĳ���) 0 - 255
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
		case JIDI:
			newObj->color = 0x04;
			newObj->Bullft = 1;
			break;
		case TANK:
			newObj->color = 0x0A;
			newObj->Bullft = 1;
			break;
		case DTANK:
			newObj->color = 0x04;
			newObj->Bullft = 1;
			break;
		case DDTANK:
			newObj->color = 0x74;
			newObj->Bullft = 2;
			break;
		case ZIDAN:
			newObj->color = 0x0F;
			newObj->Bullft = 1;
			break;
		case DZIDAN:
			newObj->color = 0x04;
			newObj->Bullft = 2;
			break;
		case HELIU:
			newObj->color = 0x9F;
			newObj->Bullft = 255;
			break;
		case CAODI:
			newObj->color = 0x20;
			newObj->Bullft = 255;
			break;
		case ZWALL:
			newObj->color = 0x76;
			newObj->Bullft = 0;
			break;
		case TWALL:
			newObj->color = 0x78;
			newObj->Bullft = 255;
			break;
		default:
			break;
	}
	return newObj;
}

// ϵͳ��ʼ��ͼ
unshort dftMap[ MAXMAPWID ][ MAXMAPWID ] = { 0 };
unshort beforMap[ MAXMAPWID ][ MAXMAPWID ] = { 0 };
objInfo *allObj[ MAXOBJ ] = { NULL };
unshort objId = 0;
/*********************************************
��ӡ��ʼ״̬
*********************************************/
void initDefObj(){
	// �ҵ�̹��
	objInfo *myTanke = creatObj(TANK , 1 , UP , 37 , 25 , 1);
	allObj[ 1 ] = myTanke;
	// ���ض���
	objInfo *myHome = creatObj(JIDI , 1 , DOWN , 36 , 18 , 2);
	allObj[ 2 ] = myHome;
	// ���Χǽ
	objInfo *mapWallTop = creatObj(TWALL , 40 , RIGHT , 0 , 0 , 3);
	allObj[ 3 ] = mapWallTop;
	objInfo *mapWallDown = creatObj(TWALL , 40 , LEFT , 39 , 0 , 4);
	allObj[ 4 ] = mapWallDown;
	objInfo *mapWallLeft = creatObj(TWALL , 38 , DOWN , 1 , 0 , 5);
	allObj[ 5 ] = mapWallLeft;
	objInfo *mapWallRight = creatObj(TWALL , 38 , DOWN , 1 , 39 , 6);
	allObj[ 6 ] = mapWallRight;
	// �������Χǽ
	objInfo *homeTopWall = creatObj(ZWALL , 6 , RIGHT , 35 , 17 , 7);
	allObj[ 7 ] = homeTopWall;
	objInfo *homeLeftWall = creatObj(ZWALL , 3 , DOWN , 36 , 17 , 8);
	allObj[ 8 ] = homeLeftWall;
	objInfo *homeRightWall = creatObj(ZWALL , 3 , DOWN , 36 , 22 , 9);
	allObj[ 9 ] = homeRightWall;
}

// ����µ�ͼ
void echoMap(){
	/************************************
	��Ҫ�� д�ӳٺ�Ҫ�Ѵ˺���д���ӳٻ��Ѻ�
	************************************/
	memset(dftMap , 0 , sizeof(dftMap));

	objInfo *objTemp;
	for(int i = 1; i < MAXOBJ && allObj[ i ] != NULL; i++){
		if(allObj[ i ] == (objInfo *)0xF000) // ��ɾ���Ľ��
			continue;
		objTemp = allObj[ i ];
		switch(objTemp->Type){
			case JIDI:
				echoHome(objTemp); break;
			case TANK: case DTANK: case DDTANK:
				echoTanke(objTemp); break;
			case ZIDAN: case DZIDAN:
				echoBullft(objTemp); break;
			case HELIU: case CAODI: case ZWALL: case TWALL:
				echoBuid(objTemp); break;
			default:
				break;
		}
	}
	readMap();
}

// �����ƶ����޸�����
void objMove(objInfo *theObj , unshort act){
	if(act == 16)
		act = theObj->Action;
	if(act != theObj->Action)
		theObj->Action = act;

	switch(act)
	{
		case UP:
			(theObj->ltposX) -= 1; break;
		case DOWN:
			(theObj->ltposX) += 1; break;
		case LEFT:
			(theObj->ltposY) -= 1; break;
		case RIGHT:
			(theObj->ltposY) += 1; break;
		default:
			break;
	}

	switch(theObj->Type){
		case TANK: case DTANK: case DDTANK:
			echoTanke(theObj); break;
		case ZIDAN: case DZIDAN:
			echoBullft(theObj); break;
		default:
			break;
	}
}

// ��ӡ̹��
void echoTanke(objInfo *tanke){
	if(tanke->Type != TANK && tanke->Type != DTANK && tanke->Type != DDTANK)
		return;
	unshort x = tanke->ltposX;
	unshort y = tanke->ltposY;
	unshort id = tanke->ID;
	dftMap[ x ][ y ] = tanke->ID;
	switch(tanke->Action)
	{
		case UP:
			dftMap[ x - 1 ][ y ] = id;
			dftMap[ x ][ y - 1 ] = id;
			dftMap[ x ][ y + 1 ] = id;
			dftMap[ x + 1 ][ y - 1 ] = id;
			dftMap[ x + 1 ][ y + 1 ] = id;
			break;
		case DOWN:
			dftMap[ x + 1 ][ y ] = id;
			dftMap[ x ][ y + 1 ] = id;
			dftMap[ x ][ y - 1 ] = id;
			dftMap[ x - 1 ][ y + 1 ] = id;
			dftMap[ x - 1 ][ y - 1 ] = id;
			break;
		case LEFT:
			dftMap[ x ][ y - 1 ] = id;
			dftMap[ x + 1 ][ y ] = id;
			dftMap[ x - 1 ][ y ] = id;
			dftMap[ x + 1 ][ y + 1 ] = id;
			dftMap[ x - 1 ][ y + 1 ] = id;
			break;
		case RIGHT:
			dftMap[ x ][ y + 1 ] = id;
			dftMap[ x - 1 ][ y ] = id;
			dftMap[ x + 1 ][ y ] = id;
			dftMap[ x - 1 ][ y - 1 ] = id;
			dftMap[ x + 1 ][ y - 1 ] = id;
			break;

		default:
			break;
	}
}

// ��ӡ�ӵ�
void echoBullft(objInfo *bullft){
	if(bullft->Type != ZIDAN && bullft->Type != DZIDAN)
		return;
	dftMap[ bullft->ltposX ][ bullft->ltposY ] = bullft->ID;
}

// ��ӡ����
void echoHome(objInfo *myHome){
	if(myHome->Type != JIDI)
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

// �ж�ĳһ���ǽ�Ƿ񱻴��
bool wallIsEmpty(long long wall, long long a){
	wall >>= a;
	return wall & 1;
}

// ��ӡ������
void echoBuid(objInfo *buid){
	// ���ǽ��ȫ�������
	long long allWallEmp = 0x3FFFFFFFFF >> (38 - buid->size);
	if(buid->Type == ZWALL && ((buid->Bullft) ^ allWallEmp) == 0){
		// delLink();// ɾ��ǽ�����
		return;
	}
	unshort x = buid->ltposX;
	unshort y = buid->ltposY;
	short xSide = 0;
	short ySide = 0;
	if(buid->Action == UP)
		xSide -= buid->size + 1;
	else if(buid->Action == DOWN)
		xSide += buid->size - 1;
	else if(buid->Action == LEFT)
		ySide -= buid->size + 1;
	else
		ySide += buid->size - 1;
	
	long long a = 0;
	for(int i = x, flagI = 1; (xSide == 0 && flagI-- == 1 ) ||
		buidIsAct(xSide, x , i); buidArtNum(xSide , &i))
		for(int j = y , flagJ = 1; (ySide == 0 && flagJ-- == 1) ||
			buidIsAct(ySide , y , j); buidArtNum(ySide , &j), ++a){

			if((buid->Type) == ZWALL && wallIsEmpty(buid->Bullft , a))
				continue;
			
			dftMap[ i ][ j ] = buid->ID;
		}
}