#pragma once
// 头文件包含及数据定义
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdarg.h>

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

#include "objinfo.h"
#include "setdisplay.h"
#include "readmap.h"
#include "colkeymouapi.h"
#include "linktable.h"
#include "collision.h"

extern objInfo *allObj[ MAXOBJ ];
extern unshort beforMap[ MAXMAPWID ][ MAXMAPWID ];
extern unshort dftMap[ MAXMAPWID ][ MAXMAPWID ];
extern int tanekLife;
extern int gameOver;