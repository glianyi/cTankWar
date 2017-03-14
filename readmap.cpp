#include "tanke.h"

/***********************
函数功能：读取地图并打印
*mapBuff: 地图数组指针
wid: 地图宽度
high: 地图高度
************************/
extern objInfo *allObj[ MAXOBJ ];
extern unshort dftMap[ 40 ][ 40 ];
void readMap(){
	WORD mapColor;
	for(int i = 0; i < MAXMAPWID; i++){
		for(int j = 0; j < MAXMAPWID; j++){
			if(dftMap[ i ][ j ] != 0){
				mapColor = allObj[ dftMap[ i ][ j ] ]->color;
				WriteChar(j , i , "■" , mapColor);
			}
		}
	}
}