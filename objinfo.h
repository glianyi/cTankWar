#pragma once

/******************************************
����ṹ�嶨�壺
Type: �������� 0.���� 1.̹�� 2.�о�̹�� 4.�ӵ�
		 8.��ǽ16.שǽ 32.��ǽ 12.���� 7.�ݵ�
color:   ������ɫ
Bullft:  ����ֵ 0 - 255
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
	unshort Bullft;
	unshort Action;
	unshort ltposX;
	unshort ltposY;
	unshort size;
	unshort ID;
} objInfo;

// ����������
objInfo *creatObj(unshort Type , unshort size , unshort Action ,
				  unshort ltpostX , unshort ltpostY , unshort ID);

// ��ӡ̹��
void echoTanke(objInfo *tanke);

// ��ӡ�ӵ�
void echoBullft(objInfo *bullft);

// ��ӡ����
void echoHome(objInfo *myHome);

// ��ӡ������
void echoBuid(objInfo *buid);

/*********************************************
��ӡ��ʼ״̬
*********************************************/
void initDefObj();