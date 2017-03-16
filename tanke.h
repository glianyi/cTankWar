#pragma once
// 头文件包含及数据定义
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdarg.h>
#include <math.h>

#define MAXMAPWID 40  // 地图宽度
#define MAXOBJ    255 // 对象数组大小

// 宏定义对象类型
#define JIDI    0
#define TANK    1
#define DTANK   2
#define DDTANK  4
#define ZIDAN   8
#define DZIDAN  16
#define HELIU   24
#define CAODI   31
#define ZWALL   32
#define TWALL   64

// 定义移动方向
#define UP    1
#define DOWN  2
#define LEFT  4
#define RIGHT 8


// 链表结点类型 0.对象数组空元素结点 1.对象链表结点
#define NULLARR   0
#define LINKOBJ   1

typedef unsigned short unshort;
typedef unsigned int   unint;

typedef struct coor
{
	unshort x , y;
} coor;

#include "objinfo.h"      // 对象处理
#include "setdisplay.h"   // 输出设置
#include "readmap.h"      // 打印地图
#include "colkeymouapi.h" // 鼠标事件
#include "linktable.h"    // 链表
#include "collision.h"    // 碰撞检测
#include "automove.h"     // 子弹和地方坦克们的自动移动

extern objInfo *allObj[ MAXOBJ ];  // 对象数组

extern unshort mapA[ MAXMAPWID ][ MAXMAPWID ];
extern unshort mapB[ MAXMAPWID ][ MAXMAPWID ];

extern unshort (*beforMap)[40]; // 前一个状态地图
extern unshort (*dftMap)[40];   // 当前地图
extern int tanekLife; // 坦克新生无敌时间
extern int gameOver;  // 定义游戏是否结束

extern hdLink testNull; // 链表测试用例中的空元素链表
extern hdLink testObj;  // 链表测试用例中的对象链表

extern hdLink nLink; // 全局对象数组空元素链表
extern hdLink dTankLink; // 敌方坦克链表
extern hdLink bulletLink; // 子弹链表