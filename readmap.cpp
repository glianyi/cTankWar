#include "tanke.h"

/***********************
�������ܣ���ȡ��ͼ����ӡ
*mapBuff: ��ͼ����ָ��
wid: ��ͼ���
high: ��ͼ�߶�
************************/
extern objInfo *allObj[ MAXOBJ ];
extern unshort dftMap[ 40 ][ 40 ];
void readMap(){
	WORD mapColor;
	for(int i = 0; i < MAXMAPWID; i++){
		for(int j = 0; j < MAXMAPWID; j++){
			if(dftMap[ i ][ j ] != 0){
				mapColor = allObj[ dftMap[ i ][ j ] ]->color;
				WriteChar(j , i , "��" , mapColor);
			}
		}
	}
}