#include "tanke.h"

// 创建默认地图中的建筑物对象
void echoDefaultObj(){
	allObj[ 10 ] = creatObj(HELIU , 3 , DOWN , 15 , 18 , 10);
	allObj[ 11 ] = creatObj(HELIU , 3 , DOWN , 15 , 19 , 11);
	allObj[ 12 ] = creatObj(HELIU , 3 , DOWN , 15 , 20 , 12);
	allObj[ 13 ] = creatObj(HELIU , 3 , DOWN , 15 , 21 , 13);
	allObj[ 14 ] = creatObj(HELIU , 3 , DOWN , 18 , 19 , 14);
	allObj[ 15 ] = creatObj(HELIU , 3 , DOWN , 18 , 20 , 15);
	allObj[ 16 ] = creatObj(ZWALL , 8 , DOWN , 13 , 16 , 16);
	allObj[ 17 ] = creatObj(ZWALL , 8 , DOWN , 13 , 17 , 17);
	allObj[ 18 ] = creatObj(ZWALL , 8 , DOWN , 13 , 22 , 18);
	allObj[ 19 ] = creatObj(ZWALL , 8 , DOWN , 13 , 23 , 19);
	allObj[ 20 ] = creatObj(ZWALL , 4 , RIGHT , 13 , 18 , 20);
	allObj[ 21 ] = creatObj(ZWALL , 4 , RIGHT , 14 , 18 , 21);
	allObj[ 22 ] = creatObj(ZWALL , 3 , DOWN , 18 , 18 , 22);
	allObj[ 23 ] = creatObj(ZWALL , 3 , DOWN , 18 , 21 , 23);
	allObj[ 24 ] = creatObj(TWALL , 3 , RIGHT , 29 , 18 , 24);
	allObj[ 25 ] = creatObj(TWALL , 3 , RIGHT , 30 , 18 , 25);
	allObj[ 26 ] = creatObj(SENLIN , 18 , RIGHT , 29 , 21 , 26);
	allObj[ 27 ] = creatObj(SENLIN , 18 , RIGHT , 30 , 21 , 27);


	nLink.num = 28;
}

// 创建第一批敌军
void echoStartDtank(){
	echoDtank(DTANK , 2 , 2);
	echoDtank(DDTANK , 2 , 6);
	echoDtank(DDTANK , 2 , 37);
	echoDtank(DTANK , 2 , 33);
	echoDtank(DTANK , 2 , 15);
	dTankNum -= 5;
}

// 创建敌军坦克
void echoDtank(unshort type ,unshort x, unshort y){
	if(dTankNum > 0){
		int id = getNullObj(&nLink);
		if(id == 0)
			return;

		allObj[ id ] = creatObj(type , 1 , DOWN , x , y , id);

		creatLink(&dTankLink , LINKOBJ);
		dTankLink.wtObj.objNext->theObj = allObj[ id ];
		echoTanke(allObj[ id ]);
	}
}