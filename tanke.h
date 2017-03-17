#pragma once
// 头文件包含及数据定义
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>

#define MAXMAPWID 40  // 地图宽度
#define MAXOBJ    255 // 对象数组大小

// 宏定义对象类型
#define JIDI    0  // 基地
#define TANK    1  // 坦克
#define DTANK   2  // 敌方坦克
#define DDTANK  4  // 敌方2级坦克
#define ZIDAN   8  // 子弹
#define DZIDAN  16 // 敌方子弹
#define HELIU   24 // 河流
#define SENLIN   31 // 森林
#define ZWALL   32 // 砖墙
#define TWALL   64 // 铁墙

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
#include "gamestart.h"    // 提供开始游戏所需对象

extern objInfo *allObj[ MAXOBJ ];  // 对象数组

extern unshort mapA[ MAXMAPWID ][ MAXMAPWID ];
extern unshort mapB[ MAXMAPWID ][ MAXMAPWID ];

extern unshort (*beforMap)[40]; // 前一个状态地图
extern unshort (*dftMap)[40];   // 当前地图
extern int tankLife; // 坦克新生无敌时间
extern int gameOver;  // 定义游戏是否结束
extern int dTankNum; //敌军坦克数量

extern hdLink testNull; // 链表测试用例中的空元素链表
extern hdLink testObj;  // 链表测试用例中的对象链表

extern hdLink nLink; // 全局对象数组空元素链表
extern hdLink dTankLink; // 敌方坦克链表
extern hdLink bulletLink; // 子弹链表

// CPU时钟滴答数 - 用于控制敌方坦克和子弹的速度
extern long long seconds; // 实时更新
extern long long bullseconds;// 子弹移动判断条件
extern long long tankseconds;// 坦克移动判断条件
extern long long fireseconds;// 开火判断条件
extern long long keyseconds;// 键盘移动判断条件