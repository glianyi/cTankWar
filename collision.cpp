#include "tanke.h"

int tankeLife = 4;
int gameOver = 0;

// 碰撞检测
bool collision(objInfo *ob , coor crBuff[]){
	unshort tp = ob->Type; // 对象类型
	unshort crTp; // 坐标点对象类型
	int canMove = 1; // 判断能否移动
	if(tp == 1 || tp == 2){
		// 判断坦克每一个点
		for(int i = 0; i < 6 ; i++){
			crTp = wtType(crBuff[ i ]);
			if((tp & crTp) == 0)
				canMove -= 1;

			// 我方坦克碰撞敌方坦克或子弹
			if((crTp == 2 || crTp == 64) && tp == 1){
				if(crTp == 64){
					//delLink();// 删除子弹对象
				}
				tankeOver();
				return false;
			}
			// 敌方坦克碰撞我方坦克或子弹
			if((crTp == 1 || crTp == 4) && tp == 2){
				if(crTp == 4){
					//delLink();// 删除子弹对象
					//delLink();// 删除地方坦克对象
				}
				else{
				tankeOver();
				}
				return false;
			}
		}
	}
	else{
		crTp = wtType(crBuff[ 0 ]);
		// 子弹若无碰撞，则返回真
		if((tp & crTp) != 0)
			return true;
		canMove -= 1;
		//delLink();// 删除子弹对象

		// 我方子弹碰撞敌方坦克
		if(tp == 4 && crTp == 2){
			//delLink();// 删除敌方坦克对象
		}

		// 敌方子弹碰撞我方坦克
		if(tp == 64 && crTp == 1){
			tankeOver();
		}

		// 子弹相撞
		if(crTp == 64 || crTp == 4){
			//delLink();// 删除crTp子弹对象
		}

		// 子弹撞墙
		if(crTp == 8){

		}
	}

	if(canMove < 1)
		return false;

	return true;
}

// 我方坦克中弹
void tankeOver(){
	if(tankeLife >= 0)
		tankeLife -= 1;
	if(tankeLife == -1)
		gameOver = 1;

	// creatObj(1 , 1 , UP , 37 , 25 , 1);
	allObj[ 1 ]->Action = UP;
	allObj[ 1 ]->ltposX = 37;
	allObj[ 1 ]->ltposY = 25;
}

// 通过坐标判断对象类型
unshort wtType(coor wObj){
	unshort x = wObj.x;
	unshort y = wObj.y;
	if(allObj[ dftMap[ x ][ y ] ] != NULL){
		return allObj[ dftMap[ x ][ y ] ]->Type;
	}
	else if(allObj[ beforMap[ x ][ y ] ] != NULL){
		unshort tp = allObj[ dftMap[ x ][ y ] ]->Type;
		// 在旧地图中的坦克和子弹不被考虑
		if(tp != 1 && tp != 2 && tp != 4 && tp != 6)
			return tp;
	}
	return 64;
}