#pragma once

// 定义对象数组空元素链表
typedef struct nullObj
{
	unint id;
	nullObj *next;
} nullObj;

// 定义对象链表，用于存放子弹和敌方坦克
typedef struct objLink
{
	objInfo *theObj;
	objLink *next;
} objLink;

// 两种链表共同的链表头结构体
typedef struct hdLink
{
	unint num;
	union
	{
		objLink *objNext;
		nullObj *nullNext;
	} wtObj;
} hdLink;

// 创建并插入新结点
void *creatLink(hdLink *head , int wtLink);

// 删除结点
void *delLink(hdLink *head , int wtLink , unshort id = 0);

// 清空链表
void clrLink(hdLink *head , int wtLink);

// 打印链表
void echoLink(hdLink head , int wtLink);

// 获取对象数组空元素下标
unint getNullObj(hdLink *head);

// 链表测试用例
void testLink();