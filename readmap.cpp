#include "tanke.h"

/***********************
函数功能：读取地图并打印
************************/
void readMap(){
	WORD mapColor;
	for(int i = 0; i < MAXMAPWID; i++){
		for(int j = 0; j < MAXMAPWID; j++){
			if(dftMap[i][j] != 0 || beforMap[i][j] != 0){

				if(beforMap[ i ][ j ] == dftMap[ i ][ j ])
					continue;

				if(beforMap[ i ][ j ] != 0 && dftMap[ i ][ j ] == 0){
					WriteChar(j , i , "  " , 0);
					continue;
				}

				if(allObj[ dftMap[ i ][ j ] ] == (objInfo *)0xF000)
					continue;

				mapColor = allObj[ dftMap[ i ][ j ] ]->color;
				switch(allObj[dftMap[i][j]]->Type)
				{
					case JIDI: case TANK: case DTANK: case DDTANK: case ZWALL: case TWALL:
						WriteChar(j , i , "■" , mapColor); break;
					case ZIDAN: case DZIDAN:
						WriteChar(j , i , "●" , mapColor); break;
					case HELIU: case CAODI:
						WriteChar(j , i , "＾" , mapColor); break;
					default:
						break;
				}
			}
		}
	}
	unshort(*temp)[ 40 ] = dftMap;
	dftMap = beforMap;
	beforMap = temp;
	memset(dftMap , 0 , sizeof(mapA));
}