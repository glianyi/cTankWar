#pragma once
// ͷ�ļ����������ݶ���
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdarg.h>
#include <math.h>

#define MAXMAPWID 40  // ��ͼ���
#define MAXOBJ    255 // ���������С

// �궨���������
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

// �����ƶ�����
#define UP    1
#define DOWN  2
#define LEFT  4
#define RIGHT 8


// ���������� 0.���������Ԫ�ؽ�� 1.����������
#define NULLARR   0
#define LINKOBJ   1

typedef unsigned short unshort;
typedef unsigned int   unint;

typedef struct coor
{
	unshort x , y;
} coor;

#include "objinfo.h"      // ������
#include "setdisplay.h"   // �������
#include "readmap.h"      // ��ӡ��ͼ
#include "colkeymouapi.h" // ����¼�
#include "linktable.h"    // ����
#include "collision.h"    // ��ײ���
#include "automove.h"     // �ӵ��͵ط�̹���ǵ��Զ��ƶ�

extern objInfo *allObj[ MAXOBJ ];  // ��������

extern unshort mapA[ MAXMAPWID ][ MAXMAPWID ];
extern unshort mapB[ MAXMAPWID ][ MAXMAPWID ];

extern unshort (*beforMap)[40]; // ǰһ��״̬��ͼ
extern unshort (*dftMap)[40];   // ��ǰ��ͼ
extern int tanekLife; // ̹�������޵�ʱ��
extern int gameOver;  // ������Ϸ�Ƿ����

extern hdLink testNull; // ������������еĿ�Ԫ������
extern hdLink testObj;  // ������������еĶ�������

extern hdLink nLink; // ȫ�ֶ��������Ԫ������
extern hdLink dTankLink; // �з�̹������
extern hdLink bulletLink; // �ӵ�����