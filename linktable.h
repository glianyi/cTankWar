#pragma once

// ������������Ԫ������
typedef struct nullObj
{
	unint id;
	nullObj *next;
} nullObj;

// ��������������ڴ���ӵ��͵з�̹��
typedef struct objLink
{
	objInfo *theObj;
	objLink *next;
} objLink;

// ��������ͬ������ͷ�ṹ��
typedef struct hdLink
{
	unint num;
	union
	{
		objLink *objNext;
		nullObj *nullNext;
	} wtObj;
} hdLink;

// �����������½��
void *creatLink(hdLink *head , int wtLink);

// ɾ�����
void *delLink(hdLink *head , int wtLink , unshort id = 0);

// �������
void clrLink(hdLink *head , int wtLink);

// ��ӡ����
void echoLink(hdLink head , int wtLink);

// ��ȡ���������Ԫ���±�
unint getNullObj(hdLink *head);

// �����������
void testLink();