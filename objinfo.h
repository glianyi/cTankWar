#pragma once

/******************************************
对象结构体定义：
Type: 对象类型 0.基地 1.坦克 2.敌军坦克 4.子弹
		 8.土墙16.砖墙 32.铁墙 12.河流 7.草地
color:   对象颜色
Bullft:  生命值 0 - 255
Action:  对象方向 0.上 1.下 2.左 3.右 
ltpostX: 左上角元素横坐标 0 - 39
ltpostY: 左上角元素纵坐标 0 - 39
size:    对象体积 1 - 40
ID:      对象ID 0 - 255
******************************************/
typedef struct objInfo
{
	unshort Type;
	unshort color;
	unshort Bullft;
	unshort Action;
	unshort ltposX;
	unshort ltposY;
	unshort size;
	unshort ID;
} objInfo;

// 创建对象函数
objInfo *creatObj(unshort Type , unshort size , unshort Action ,
				  unshort ltpostX , unshort ltpostY , unshort ID);

// 打印坦克
void echoTanke(objInfo *tanke);

// 打印子弹
void echoBullft(objInfo *bullft);

// 打印基地
void echoHome(objInfo *myHome);

// 打印建筑物
void echoBuid(objInfo *buid);

/*********************************************
打印初始状态
*********************************************/
void initDefObj();