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
		objMove(temp->theObj);
		temp = tempA;
	}
}

// 开炮
void fire(objInfo *theObj){
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
}