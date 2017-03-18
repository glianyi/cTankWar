#include "tanke.h"

int tankLife = 6;
int gameOver = 0;
int dTankNum = 20;

// 碰撞检测
bool collision(objInfo *ob , coor crBuff[]){
	unshort tp = ob->Type; // 对象类型
	unshort crTp; // 坐标点对象类型
	unshort crId = 0; // 坐标点对象ID
	int canMove = 1; // 判断能否移动
	if(tp == TANK || tp == DTANK || tp == DDTANK){
		// 判断坦克每一个点
		for(int i = 0; i < 6 ; i++){
			crTp = wtType(crBuff[ i ] , &crId);
			// 目标坐标点无元素
			if(crTp == 128)
				continue;

			if((tp & crTp) == 0)
				canMove -= 1;

			// 我方坦克碰撞敌方坦克或子弹
			if((crTp == DTANK || crTp == DDTANK || crTp == DDTANK ||
				crTp == ZIDAN || crTp == DZIDAN) && tp == TANK){
				if(crTp == ZIDAN || crTp == DZIDAN){
					delT(&bulletLink , crId); //删除子弹对象
				}
				if(crTp == ZIDAN){
					canMove += 1;
				}
				else{
					//无敌时间
					if(tankLife > 0){
						if(tp == DDTANK){
							// 更改坦克属性
							(allObj[ ob->ID ]->Type) = DTANK;
							(allObj[ ob->ID ]->Bullft) -= 1;
							(allObj[ ob->ID ]->color) = 0x03;
							// 修改坦克ID （实时更新）
							unshort tempid = getNullObj(&nLink);
							allObj[ ob->ID ] = (objInfo *)0xF000;
							// 将坦克原ID放入空元素链表
							creatLink(&testNull , NULLARR);
							testNull.wtObj.nullNext->id = ob->ID;
							ob->ID = tempid;
							allObj[ tempid ] = ob;
						}
						else{
							delT(&dTankLink , ob->ID);// 删除敌方坦克对象
						}
					}
					else{
						tankeOver();
						return false;
					}
				}
			}
			// 敌方坦克碰撞子弹或我方坦克
			if((crTp == TANK || crTp == ZIDAN || crTp == DZIDAN) &&
			   (tp == DTANK || tp == DDTANK)){

				if(crTp == ZIDAN){
					if(tp == DDTANK){
						// 更改坦克属性
						(allObj[ ob->ID ]->Type) = DTANK;
						(allObj[ ob->ID ]->Bullft) -= 1;
						(allObj[ ob->ID ]->color) = 0x03;
						// 修改坦克ID （实时更新）
						unshort tempid = getNullObj(&nLink);
						allObj[ ob->ID ] = (objInfo *)0xF000;
						// 将坦克原ID放入空元素链表
						creatLink(&testNull , NULLARR);
						testNull.wtObj.nullNext->id = ob->ID;
						ob->ID = tempid;
						allObj[ tempid ] = ob;
					}
					else{
						delT(&dTankLink , ob->ID);// 删除敌方坦克对象
					}
					delT(&bulletLink , crId);// 删除子弹对象
					return false;
				}
				else if(crTp == DZIDAN){
					delT(&bulletLink , crId);// 删除子弹对象
					canMove += 1;
				}
				else{
					//无敌时间
					if(tankLife > 0){
						if(tp == DDTANK){
							// 更改坦克属性
							(allObj[ ob->ID ]->Type) = DTANK;
							(allObj[ ob->ID ]->Bullft) -= 1;
							(allObj[ ob->ID ]->color) = 0x03;
							// 修改坦克ID （实时更新）
							unshort tempid = getNullObj(&nLink);
							allObj[ ob->ID ] = (objInfo *)0xF000;
							// 将坦克原ID放入空元素链表
							creatLink(&testNull , NULLARR);
							testNull.wtObj.nullNext->id = ob->ID;
							ob->ID = tempid;
							allObj[ tempid ] = ob;
						}
						else{
							delT(&dTankLink , ob->ID);// 删除敌方坦克对象
						}
					}
					else{
						tankeOver();
						return false;
					}
				}
			}

			// 敌方坦克碰撞基地
			if((tp == DTANK || tp == DDTANK || tp == TANK) &&
			   crTp == JIDI){
				if(tp != TANK){
					gameOver += 1;
					allObj[ 2 ]->color = 0x00; //修改基地对象颜色
					return false;
				}
			}

			// 坦克撞墙无需操作，直接不能移动
// 			if(crTp == ZWALL || crTp == TWALL || crTp == HELIU){
// 				// canMove -= 1;
// 			}
		}
	}
	else{
		crTp = wtType(crBuff[ 0 ], &crId);
		// 目标坐标点无元素
		if(crTp == 128)
			return true;
		else if(crTp == 127)
			return false;

		// 子弹若无碰撞，则返回真
		if((tp & crTp) != 0)
			return true;
		canMove -= 1;
		delT(&bulletLink , ob->ID);// 删除子弹对象

		// 我方子弹碰撞敌方坦克
		if(tp == ZIDAN && (crTp == DTANK || crTp == DDTANK)){
			if(crTp == DDTANK){
				(allObj[ crId ]->Type) = DTANK;
				(allObj[ crId ]->Bullft) -= 1;
				(allObj[ crId ]->color) = 0x03;
				unshort tempid = getNullObj(&nLink);
				objInfo *tempobj = allObj[ crId ];
				allObj[ tempobj->ID ] = (objInfo *)0xF000;
				creatLink(&testNull , NULLARR);
				testNull.wtObj.nullNext->id = tempobj->ID;
				tempobj->ID = tempid;
				allObj[ tempid ] = tempobj;
			}
			else{
				delT(&dTankLink , crId);// 删除敌方坦克对象
			}
		}

		// 敌方子弹碰撞我方坦克
		if(tp == DZIDAN && crTp == TANK){
			// 无敌时间
			if(tankLife <= 0)
				tankeOver();
		}

		// 子弹相撞
		if(crTp == ZIDAN || crTp == DZIDAN){
			delT(&bulletLink , crId);// 删除crTp子弹对象
		}

		// 子弹撞墙
		if(crTp == ZWALL){
			// 修改墙体属性
			unshort crX , crY;
			long long len;
			crX = allObj[ crId ]->ltposX;
			crY = allObj[ crId ]->ltposY;

			if(crX == crBuff[ 0 ].x)
				len = abs((long long)crY - (long long)(crBuff[ 0 ].y));
			else
				len = abs((long long)crX - (long long)(crBuff[ 0 ].x));
			
			(allObj[ crId ]->Bullft) |= ((long long)1 << len);
		}

		if(crTp == JIDI){
			gameOver += 1;
			allObj[ 2 ]->color = 0x00; //修改基地对象颜色
		}
	}

	if(canMove < 1)
		return false;

	return true;
}

// 我方坦克中弹
void tankeOver(){
	if(tankLife > 0)
		return;

	if((allObj[ 1 ]->Bullft) >= 0){
		(allObj[ 1 ]->Bullft) -= 1;
	}

	if(allObj[ 1 ]->Bullft <= 0)
		gameOver += 1;

	char szBuff[ 10 ];
	sprintf_s(szBuff , 10 , "%2d" , allObj[ 1 ]->Bullft);
	WriteChar(45 , 8 , szBuff , 0x0A);

	allObj[ 1 ]->Action = UP;
	allObj[ 1 ]->ltposX = 37;
	allObj[ 1 ]->ltposY = 25;
	tankLife = 6;
	echoTanke(allObj[ 1 ]);
}

// 通过坐标判断对象类型
unshort wtType(coor wObj, unshort *crId){
	if(wObj.x >= MAXMAPWID || wObj.y >= MAXMAPWID)
		return 127;

	unshort x = wObj.x;
	unshort y = wObj.y;
	if(allObj[ dftMap[ x ][ y ] ] != NULL &&
	   allObj[ dftMap[ x ][ y ] ] != (objInfo *)0xF000){
		*crId = dftMap[ x ][ y ];
		return allObj[ dftMap[ x ][ y ] ]->Type;
	}
	else if(allObj[ beforMap[ x ][ y ] ] != NULL &&
			allObj[beforMap[x][y]] != (objInfo *)0xF000){

		unshort tp = allObj[ beforMap[ x ][ y ] ]->Type;
		// 在旧地图中的坦克和子弹不被考虑
		if(tp != TANK && tp != DTANK && tp != DDTANK &&
		   tp != ZIDAN && tp != DZIDAN){
			*crId = beforMap[ x ][ y ];
			return tp;
		}
	}
	return 128;
}

// 删除坦克、子弹链表元素
void delT(hdLink *theObj , unshort id){
	if(theObj->wtObj.objNext == NULL)
		return;
	unshort tp = theObj->wtObj.objNext->theObj->Type;
	unshort x = theObj->wtObj.objNext->theObj->ltposX;
	unshort y = theObj->wtObj.objNext->theObj->ltposY;
	unshort act = theObj->wtObj.objNext->theObj->Action;

	clrCanliu(theObj->wtObj.objNext->theObj);
	delLink(theObj , LINKOBJ , id);

	if(id == (nLink.num - 1)){
		nLink.num = id;
	}
	else{
		creatLink(&nLink , NULLARR);
		nLink.wtObj.nullNext->id = id;
	}

	allObj[ id ] = (objInfo *)0xF000;

	if(tp == DTANK){
		if(dTankNum > 0){
			// 出生地为空则创建新坦克
			int flag = 1;
			for(int i = 1; i <= 3; i++){
				for(int j = 14; j <= 16; j++)
					if(dftMap[ i ][ j ] != 0)
						--flag;
			}
			if(flag == 1){
				seconds = clock();
				echoDtank(2 << (seconds % 2));
			}
		}
		--dTankNum;
		char szBuff[ 10 ];
		sprintf_s(szBuff , 10 , "%2d" , dTankNum);
		WriteChar(45 , 10 , szBuff , 0x0A);
	}

}


// 清除残留
void clrCanliu(objInfo *theObj){
	unshort x = theObj->ltposX;
	unshort y = theObj->ltposY;
	unshort act = theObj->Action;
	dftMap[ x ][ y ] = 0;
	if(theObj->Type == ZIDAN || theObj->Type == DZIDAN)
		return;
	switch(act)
	{
		case UP:
			dftMap[ x - 1 ][ y ] = 0;
			dftMap[ x ][ y - 1 ] = 0;
			dftMap[ x ][ y + 1 ] = 0;
			dftMap[ x + 1 ][ y - 1 ] = 0;
			dftMap[ x + 1 ][ y + 1 ] = 0;
			break;
		case DOWN:
			dftMap[ x + 1 ][ y ] = 0;
			dftMap[ x ][ y + 1 ] = 0;
			dftMap[ x ][ y - 1 ] = 0;
			dftMap[ x - 1 ][ y + 1 ] = 0;
			dftMap[ x - 1 ][ y - 1 ] = 0;
			break;
		case LEFT:
			dftMap[ x ][ y - 1 ] = 0;
			dftMap[ x + 1 ][ y ] = 0;
			dftMap[ x - 1 ][ y ] = 0;
			dftMap[ x + 1 ][ y + 1 ] = 0;
			dftMap[ x - 1 ][ y + 1 ] = 0;
			break;
		case RIGHT:
			dftMap[ x ][ y + 1 ] = 0;
			dftMap[ x - 1 ][ y ] = 0;
			dftMap[ x + 1 ][ y ] = 0;
			dftMap[ x - 1 ][ y - 1 ] = 0;
			dftMap[ x + 1 ][ y - 1 ] = 0;

		default:
			break;
	}
}