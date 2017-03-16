#pragma once

/******************************************
����ṹ�嶨�壺
Type: ��������: ��ϸ�μ�tanke.hͷ�ļ�����
color:   ������ɫ
Bullft:  ����ֵ(ǽ�屻����Ĳ���) 0 - 255
Action:  ������ 0.�� 1.�� 2.�� 3.�� 
ltpostX: ���Ͻ�Ԫ�غ����� 0 - 39
ltpostY: ���Ͻ�Ԫ�������� 0 - 39
size:    ������� 1 - 40
ID:      ����ID 0 - 255
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

// ����������
objInfo *creatObj(unshort Type , unshort size , unshort Action ,
				  unshort ltpostX , unshort ltpostY , unshort ID);

// ����µ�ͼ
void echoMap(objInfo *theObj = NULL);

// �����ƶ����޸�����
void objMove(objInfo *theObj , unshort act = 16);

// ��ӡ̹��
void echoTanke(objInfo *tanke);

// ��ӡ�ӵ�
void echoBullet(objInfo *bullet);

// ��ӡ����
void echoHome(objInfo *myHome);

// ��ӡ������
void echoBuid(objInfo *buid);

/*********************************************
��ӡ��ʼ״̬
*********************************************/
void initDefObj();