#pragma once

/******************************************
对象结构体定义：
Type: 对象类型: 详细参见tanke.h头文件定义
color:   对象颜色
Bullft:  生命值(墙体被打掉的部分) 0 - 255
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
	long long Bullft;
	unshort Action;
	unshort ltposX;
	unshort ltposY;
	unshort size;
	unshort ID;
} objInfo;

// 创建对象函数
objInfo *creatObj(unshort Type , unshort size , unshort Action ,
				  unshort ltpostX , unshort ltpostY , unshort ID);

// 输出新地图
void echoMap(objInfo *theObj = NULL);

// 对象移动，修改坐标
void objMove(objInfo *theObj , unshort act = 16);

// 打印坦克
void echoTanke(objInfo *tanke);

// 打印子弹
void echoBullet(objInfo *bullet);

// 打印基地
void echoHome(objInfo *myHome);

// 打印建筑物
void echoBuid(objInfo *buid);

/*********************************************
打印初始状态
*********************************************/
void initDefObj();