#include "tanke.h"

// 移动子弹
void moveBul(){
	objLink *temp = bulletLink.wtObj.objNext;
	objLink *tempA = NULL;
	while(temp != NULL){
		tempA = temp->next;
		objMove(temp->theObj);
		temp = tempA;
	}
}

// 移动坦克
void moveDtk(){
	objLink *temp = dTankLink.wtObj.objNext;
	objLink *tempA = NULL;
	while(temp != NULL){
		tempA = temp->next;
		seconds = clock();
		if(seconds % 4 == 0)
			fire(temp->theObj, 1);
		objMove(temp->theObj, 1 << (seconds % 4));
		temp = tempA;
	}
}

// CPU时钟滴答数 - 用于控制敌方坦克和子弹的速度

long long fireseconds = 0;// 开火判断条件
// 开炮
void fire(objInfo *theObj , int flag){
	if(seconds - fireseconds < 500 && flag == 0){
		return;
	}
	else{
		fireseconds = seconds;
	}
	

	unshort tp = theObj->Type;
	unshort x = theObj->ltposX;
	unshort y = theObj->ltposY;
	unshort act = theObj->Action;

	switch(act)
	{
		case UP:
			x -= 2; break;
		case DOWN:
			x += 2; break;
		case LEFT:
			y -= 2; break;
		case RIGHT:
			y += 2; break;
		default:
			break;
	}

	int id = getNullObj(&nLink);
	if(id == 0)
		return;

	if(tp == TANK){
		allObj[ id ] = creatObj(ZIDAN , 1 , act , x , y , id);
	}
	else{
		allObj[ id ] = creatObj(DZIDAN , 1 , act , x , y , id);
	}

	creatLink(&bulletLink , LINKOBJ);
	bulletLink.wtObj.objNext->theObj = allObj[ id ];
	echoBullet(allObj[id]);
}