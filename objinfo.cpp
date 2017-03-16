#include "tanke.h"

/******************************************
对象结构体创建函数：
Type: 对象类型: 详细参见tanke.h头文件定义
color:   对象颜色
Bullft:  生命值(墙体被打掉的部分) 0 - 255
Action:  对象方向 0.上 1.下 2.左 3.右
ltpostX: 左上角元素横坐标 0 - 39
ltpostY: 左上角元素纵坐标 0 - 39
size:    对象体积 1 - 40
ID:      对象ID 0 - 255
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
			newObj->Bullft = 3;
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
			newObj->Bullft = 1;
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

// 声明创建链表元素
hdLink nLink; // 全局对象数组空元素链表
hdLink dTankLink; // 敌方坦克链表
hdLink bulletLink; // 子弹链表

// 系统初始地图
unshort mapA[ MAXMAPWID ][ MAXMAPWID ] = { 0 };
unshort mapB[ MAXMAPWID ][ MAXMAPWID ] = { 0 };
unshort (*dftMap)[40] = mapA;
unshort (*beforMap)[40] = mapB;
objInfo *allObj[ MAXOBJ ] = { NULL };
unshort objId = 0;
/*********************************************
打印初始状态
*********************************************/
void initDefObj(){

	// 初始化链表元素
	dTankLink.num = MAXOBJ; // 将此值置为对象数组最大值，防止误用
	dTankLink.wtObj.objNext = NULL;
	bulletLink.num = MAXOBJ; // 将此值置为对象数组最大值，防止误用
	bulletLink.wtObj.objNext = NULL;


	// 我的坦克
	objInfo *myTanke = creatObj(TANK , 1 , UP , 37 , 25 , 1);
	allObj[ 1 ] = myTanke;
	// 基地对象
	objInfo *myHome = creatObj(JIDI , 1 , DOWN , 36 , 18 , 2);
	allObj[ 2 ] = myHome;
	// 外层围墙
	objInfo *mapWallTop = creatObj(TWALL , 40 , RIGHT , 0 , 0 , 3);
	allObj[ 3 ] = mapWallTop;
	objInfo *mapWallDown = creatObj(TWALL , 40 , RIGHT , 39 , 0 , 4);
	allObj[ 4 ] = mapWallDown;
	objInfo *mapWallLeft = creatObj(TWALL , 38 , DOWN , 1 , 0 , 5);
	allObj[ 5 ] = mapWallLeft;
	objInfo *mapWallRight = creatObj(TWALL , 38 , DOWN , 1 , 39 , 6);
	allObj[ 6 ] = mapWallRight;
	// 基地外层围墙
	objInfo *homeTopWall = creatObj(ZWALL , 6 , RIGHT , 35 , 17 , 7);
	allObj[ 7 ] = homeTopWall;
	objInfo *homeLeftWall = creatObj(ZWALL , 3 , DOWN , 36 , 17 , 8);
	allObj[ 8 ] = homeLeftWall;
	objInfo *homeRightWall = creatObj(ZWALL , 3 , DOWN , 36 , 22 , 9);
	allObj[ 9 ] = homeRightWall;

	/* 测试 数据开始 */
	// 敌军坦克
	allObj[ 10 ] = creatObj(DTANK , 1 , DOWN , 15 , 15 , 10);
	// 河流
	allObj[ 11 ] = creatObj(HELIU , 5 , LEFT , 13 , 12 , 11);
	// 草地
	allObj[ 12 ] = creatObj(CAODI , 8 , UP , 11 , 8 , 12);
	// 子弹
	allObj[ 13 ] = creatObj(ZIDAN , 1 , UP , 33 , 25 , 13);
	// 敌军2级坦克
	allObj[ 14 ] = creatObj(DDTANK , 1 , UP , 25 , 31 , 14);
	// 敌军子弹
	allObj[ 15 ] = creatObj(DZIDAN , 1 , DOWN , 18 , 15 , 15);
	// 碰撞墙体子弹
	allObj[ 16 ] = creatObj(ZIDAN , 1 , UP , 37 , 17 , 16);
	// 碰撞墙体敌军子弹
	allObj[ 17 ] = creatObj(DZIDAN , 1 , UP , 35 , 19 , 17);
	// 敌军子弹碰撞基地
	//allObj[ 18 ] = creatObj(DZIDAN , 1 , UP , 36 , 18 , 18);
	

	nLink.num = 16;
	nLink.wtObj.nullNext = NULL;

	creatLink(&dTankLink , LINKOBJ);
	dTankLink.wtObj.objNext->theObj = allObj[ 10 ];
	creatLink(&dTankLink , LINKOBJ);
	dTankLink.wtObj.objNext->theObj = allObj[ 14 ];

	creatLink(&bulletLink , LINKOBJ);
	bulletLink.wtObj.objNext->theObj = allObj[ 13 ];
	creatLink(&bulletLink , LINKOBJ);
	bulletLink.wtObj.objNext->theObj = allObj[ 15 ];
	creatLink(&bulletLink , LINKOBJ);
	bulletLink.wtObj.objNext->theObj = allObj[ 16 ];
	creatLink(&bulletLink , LINKOBJ);
	bulletLink.wtObj.objNext->theObj = allObj[ 17 ];
// 	creatLink(&bulletLink , LINKOBJ);
// 	bulletLink.wtObj.objNext->theObj = allObj[ 18 ];
	/* 测试 数据结束 */
}

// 输出新地图
void echoMap(objInfo *theObj){
	// 更新单个对象
	if(theObj != NULL){
		switch(theObj->Type){
			case TANK: case DTANK: case DDTANK:
				echoTanke(theObj); break;
			case ZIDAN: case DZIDAN:
				echoBullet(theObj); break;
			case ZWALL:
				echoBuid(theObj); break;
			default:
				break;
		}
		return;
	}

	// 更新所有对象
	memset(dftMap , 0 , sizeof(mapA));
	objInfo *objTemp;
	for(int i = 1; i < MAXOBJ && allObj[ i ] != NULL; i++){
		if(allObj[ i ] == (objInfo *)0xF000) // 被删除的结点
			continue;
		objTemp = allObj[ i ];
		switch(objTemp->Type){
			case JIDI:
				echoHome(objTemp);
			case TANK: case DTANK: case DDTANK:
				echoTanke(objTemp); break;
			case ZIDAN: case DZIDAN:
				echoBullet(objTemp); break;
			case HELIU: case CAODI: case ZWALL: case TWALL:
				echoBuid(objTemp); break;
			default:
				break;
		}
	}
	readMap();
}

// 对象移动，修改坐标
void objMove(objInfo *theObj , unshort act){
	if(act == 16)
		act = theObj->Action;

	unshort tp = theObj->Type;
	unshort x = theObj->ltposX;
	unshort y = theObj->ltposY;
	coor crBuff[ 6 ] = { { 0 , 0 } };
	bool canMove = false;

	if(tp == TANK || tp == DTANK || tp == DDTANK){
		switch(act)
		{
			case UP:
				x -= 1;
				crBuff[ 0 ] = { x , y };
				crBuff[ 1 ] = { x - 1 , y };
				crBuff[ 2 ] = { x , y - 1 };
				crBuff[ 3 ] = { x , y + 1 };
				crBuff[ 4 ] = { x + 1 , y - 1 };
				crBuff[ 5 ] = { x + 1 , y + 1 };
				if(collision(theObj , crBuff)){
					(theObj->ltposX) -= 1;
					canMove = true;
				}
				break;
			case DOWN:
				x += 1;
				crBuff[ 0 ] = { x , y };
				crBuff[ 1 ] = { x + 1 , y };
				crBuff[ 2 ] = { x , y + 1 };
				crBuff[ 3 ] = { x , y - 1 };
				crBuff[ 4 ] = { x - 1 , y + 1 };
				crBuff[ 5 ] = { x - 1 , y - 1 };
				if(collision(theObj , crBuff)){
					(theObj->ltposX) += 1;
					canMove = true;
				}break;
			case LEFT:
				y -= 1;
				crBuff[ 0 ] = { x , y };
				crBuff[ 1 ] = { x , y - 1 };
				crBuff[ 2 ] = { x + 1 , y };
				crBuff[ 3 ] = { x - 1 , y };
				crBuff[ 4 ] = { x + 1 , y + 1 };
				crBuff[ 5 ] = { x - 1 , y + 1 };
				if(collision(theObj , crBuff)){
					(theObj->ltposY) -= 1;
					canMove = true;
				}
				break;
			case RIGHT:
				y += 1;
				crBuff[ 0 ] = { x , y };
				crBuff[ 1 ] = { x , y + 1 };
				crBuff[ 2 ] = { x - 1 , y };
				crBuff[ 3 ] = { x + 1 , y };
				crBuff[ 4 ] = { x - 1 , y - 1 };
				crBuff[ 5 ] = { x + 1 , y - 1 };
				if(collision(theObj , crBuff)){
					(theObj->ltposY) += 1;
					canMove = true;
				}
				break;
			default:
				break;
		}
	}
	else if(tp == ZIDAN || tp == DZIDAN){
		switch(act)
		{
			case UP:
				x -= 1;
				crBuff[ 0 ] = { x , y };
				if(collision(theObj , crBuff)){
					(theObj->ltposX) -= 1;
					canMove = true;
				}
				break;
			case DOWN:
				x += 1;
				crBuff[ 0 ] = { x , y };
				if(collision(theObj , crBuff)){
					(theObj->ltposX) += 1;
					canMove = true;
				}break;
			case LEFT:
				y -= 1;
				crBuff[ 0 ] = { x , y };
				if(collision(theObj , crBuff)){
					(theObj->ltposY) -= 1;
					canMove = true;
				}
				break;
			case RIGHT:
				y += 1;
				crBuff[ 0 ] = { x , y };
				if(collision(theObj , crBuff)){
					(theObj->ltposY) += 1;
					canMove = true;
				}
				break;
			default:
				break;
		}
	}

	if(canMove){
		if(act != theObj->Action)
			theObj->Action = act;
		switch(tp){
			case TANK: case DTANK: case DDTANK:
				echoTanke(theObj); break;
			case ZIDAN: case DZIDAN:
				echoBullet(theObj); break;
			default:
				break;
		}
	}
}

// 打印坦克
void echoTanke(objInfo *tanke){
	if(tanke->Type != TANK && tanke->Type != DTANK && tanke->Type != DDTANK)
		return;
	unshort x = tanke->ltposX;
	unshort y = tanke->ltposY;
	unshort id = tanke->ID;
	coor crBuff[ 6 ] = { { 0 , 0 } };
	crBuff[ 0 ] = { x , y };

	dftMap[ x ][ y ] = tanke->ID;
	switch(tanke->Action)
	{
		case UP:
			crBuff[ 1 ] = { x - 1 , y };
			crBuff[ 2 ] = { x , y - 1 };
			crBuff[ 3 ] = { x , y + 1 };
			crBuff[ 4 ] = { x + 1 , y - 1 };
			crBuff[ 5 ] = { x + 1 , y + 1 };
			if(collision(tanke , crBuff)){
				dftMap[ x - 1 ][ y ] = id;
				dftMap[ x ][ y - 1 ] = id;
				dftMap[ x ][ y + 1 ] = id;
				dftMap[ x + 1 ][ y - 1 ] = id;
				dftMap[ x + 1 ][ y + 1 ] = id;
			}
			break;
		case DOWN:
			crBuff[ 1 ] = { x + 1 , y };
			crBuff[ 2 ] = { x , y + 1 };
			crBuff[ 3 ] = { x , y - 1 };
			crBuff[ 4 ] = { x - 1 , y + 1 };
			crBuff[ 5 ] = { x - 1 , y - 1 };
			if(collision(tanke , crBuff)){
				dftMap[ x + 1 ][ y ] = id;
				dftMap[ x ][ y + 1 ] = id;
				dftMap[ x ][ y - 1 ] = id;
				dftMap[ x - 1 ][ y + 1 ] = id;
				dftMap[ x - 1 ][ y - 1 ] = id;
			}
			break;
		case LEFT:
			crBuff[ 1 ] = { x , y - 1 };
			crBuff[ 2 ] = { x + 1 , y };
			crBuff[ 3 ] = { x - 1 , y };
			crBuff[ 4 ] = { x + 1 , y + 1 };
			crBuff[ 5 ] = { x - 1 , y + 1 };
			if(collision(tanke , crBuff)){
				dftMap[ x ][ y - 1 ] = id;
				dftMap[ x + 1 ][ y ] = id;
				dftMap[ x - 1 ][ y ] = id;
				dftMap[ x + 1 ][ y + 1 ] = id;
				dftMap[ x - 1 ][ y + 1 ] = id;
			}
			break;
		case RIGHT:
			crBuff[ 1 ] = { x , y + 1 };
			crBuff[ 2 ] = { x - 1 , y };
			crBuff[ 3 ] = { x + 1 , y };
			crBuff[ 4 ] = { x - 1 , y - 1 };
			crBuff[ 5 ] = { x + 1 , y - 1 };
			if(collision(tanke , crBuff)){
				dftMap[ x ][ y + 1 ] = id;
				dftMap[ x - 1 ][ y ] = id;
				dftMap[ x + 1 ][ y ] = id;
				dftMap[ x - 1 ][ y - 1 ] = id;
				dftMap[ x + 1 ][ y - 1 ] = id;
			}
			break;

		default:
			break;
	}
}

// 打印子弹
void echoBullet(objInfo *bullet){
	if(bullet->Type != ZIDAN && bullet->Type != DZIDAN)
		return;
	coor szBuff[ 6 ] = { { bullet->ltposX , bullet->ltposY } };

	if(collision(bullet , szBuff))
	   dftMap[ bullet->ltposX ][ bullet->ltposY ] = bullet->ID;
}

// 打印基地
void echoHome(objInfo *myHome){
	if(myHome->Type != JIDI)
		return;
	unshort x = myHome->ltposX;
	unshort y = myHome->ltposY;

	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 4; j++)
			dftMap[ x + i ][ y + j ] = myHome->ID;
}


// 判断建筑物生长方向
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

// 判断某一块儿墙是否被打掉
bool wallIsEmpty(long long wall, long long a){
	wall >>= a;
	return wall & 1;
}

// 打印建筑物
void echoBuid(objInfo *buid){
	// 如果墙已全部被打掉
	long long allWallEmp = 0x3FFFFFFFFF >> (38 - buid->size);
	if(buid->Type == ZWALL && ((buid->Bullft) ^ allWallEmp) == 0){
		unshort id = buid->ID;
		free(buid);
		if(id == (nLink.num) - 1){
			(nLink.num) -= 1;
		}
		else{
			creatLink(&nLink , NULLARR);
			nLink.wtObj.nullNext->id = id;
		}		
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