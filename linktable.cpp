#include "tanke.h"

// �����������½�㣬����(void *)0xF000��ʾ�ɹ�
void *creatLink(hdLink *head , int wtLink){
	if(wtLink == NULLARR){ // ���������Ԫ������
		nullObj *newObj = (nullObj *)malloc(sizeof(nullObj));
		if(newObj == NULL)
			return NULL;
		nullObj *temp = head->wtObj.nullNext;
		head->wtObj.nullNext = newObj;
		newObj->next = temp;
	}
	else{ // ������������
		objLink *newObj = (objLink *)malloc(sizeof(objLink));
		if(newObj == NULL)
			return NULL;
		objLink *temp = head->wtObj.objNext;
		head->wtObj.objNext = newObj;
		newObj->next = temp;
	}
	return (void *)0XF000;
}

// ɾ����㣬����(void *)0xF000��ʾ�ɹ�
void *delLink(hdLink *head , int wtLink , unshort id){
	// ���������Ԫ������
	if(wtLink == NULLARR){
		nullObj *temp = head->wtObj.nullNext;
		id = temp->id;
		head->wtObj.nullNext = temp->next;
		free(temp);

		// �����ɾ�����λ�������������зǿ�Ԫ��֮��
		// ����ͷ�����Ϣ������NULL
		if(id == head->num - 1){
			(head->num) -= 1;
			return NULL;
		}

		return (void *)0XF000;
	}

	// ������������
	if(head->wtObj.objNext == NULL)
		return NULL;

	objLink *temp = head->wtObj.objNext;
	objLink *tempA = NULL;
	for( ; temp != NULL; tempA = temp, temp = temp->next){
		if(id == 0 || temp->theObj->ID == id){
			break;
		}
	}
	
	if(tempA == NULL){
		head->wtObj.objNext = temp->next;
		free(temp);
	}
	else if(temp == NULL){
		return NULL;
	}
	else{
		tempA->next = temp->next;
		free(temp);
	}
	return (void *)0XF000;
}

// �������
void clrLink(hdLink *head , int wtLink){
	// ���������Ԫ������
	if(wtLink == NULLARR){
		nullObj *temp = head->wtObj.nullNext;
		nullObj *tempA = NULL;
		while(temp != NULL){
			tempA = temp->next;
			free(temp);
			temp = tempA;
		}
		head->wtObj.nullNext = NULL;
		head->num = 1;
		return;
	}

	// ������������
	objLink *temp = head->wtObj.objNext;
	objLink *tempA = NULL;
	unshort id;
	while(temp != NULL){
		id = temp->theObj->ID;
		allObj[id] = (objInfo *)0xF000;
		tempA = temp->next;
		free(temp);
		temp = tempA;
	}
	head->wtObj.objNext = NULL;
}

// ��ӡ����
void echoLink(hdLink head , int wtLink){
	char szBuff[ 10 ] = { 0 };

	// ���������Ԫ������
	if(wtLink == NULLARR){
		WriteChar(1 , 1 , "��Ԫ������" , 0x0A);
		sprintf_s(szBuff , sizeof(szBuff) , "%4d" , head.num);
		WriteChar(6 , 1 , szBuff, 0x0F);

		nullObj *temp = head.wtObj.nullNext;
		for(int i = 2; temp != NULL; ++i , temp = temp->next){
			sprintf_s(szBuff , sizeof(szBuff) , "%4d" , temp->id);
			WriteChar(i * 2 + 4, 1 , szBuff , 0x0A);
		}
		return;
	}

	// ������������
	WriteChar(1 , 2 , "��������" , 0x0A);
	objLink *temp = head.wtObj.objNext;
	for(int i = 1; temp != NULL; ++i , temp = temp->next){
		sprintf_s(szBuff , sizeof(szBuff) , "%4d" , temp->theObj->ID);
		WriteChar(i * 2 + 4, 2 , szBuff , 0x0A);
	}
}


// �����������
void testLink(){
	hdLink testObj , testNull;
	testObj.num = 0;
	testObj.wtObj.objNext = NULL;
	testNull.num = 0;
	testNull.wtObj.nullNext = NULL;

	// �ҵ�̹��
	allObj[ 1 ] = creatObj(TANK , 1 , UP , 37 , 25 , 1);
	// ���ض���
	allObj[ 2 ] = creatObj(JIDI , 1 , DOWN , 36 , 18 , 2);
	// ���Χǽ
	allObj[ 3 ] = creatObj(TWALL , 40 , RIGHT , 0 , 0 , 3);
	allObj[ 4 ] = creatObj(TWALL , 40 , RIGHT , 39 , 0 , 4);
	allObj[ 5 ] = creatObj(TWALL , 38 , DOWN , 1 , 0 , 5);
	allObj[ 6 ] = creatObj(TWALL , 38 , DOWN , 1 , 39 , 6);
	// �������Χǽ
	allObj[ 7 ] = creatObj(ZWALL , 6 , RIGHT , 35 , 17 , 7);
	allObj[ 8 ] = creatObj(ZWALL , 3 , DOWN , 36 , 17 , 8);
	allObj[ 9 ] = creatObj(ZWALL , 3 , DOWN , 36 , 22 , 9);
	// �о�̹��
	allObj[ 10 ] = creatObj(DTANK , 1 , DOWN , 15 , 15 , 10);
	// ����
	allObj[ 11 ] = creatObj(HELIU , 5 , LEFT , 13 , 12 , 11);
	// �ݵ�
	allObj[ 12 ] = creatObj(CAODI , 8 , UP , 11 , 8 , 12);
	// �ӵ�
	allObj[ 13 ] = creatObj(ZIDAN , 1 , UP , 33 , 25 , 13);
	// �о�2��̹��
	allObj[ 14 ] = creatObj(DDTANK , 1 , UP , 25 , 31 , 14);
	// �о��ӵ�
	allObj[ 15 ] = creatObj(DZIDAN , 1 , UP , 18 , 15 , 15);

	for(int i = 1; i <= 15; ++i){
		creatLink(&testObj , LINKOBJ);
		if(testObj.wtObj.objNext != NULL){
			testObj.wtObj.objNext->theObj = allObj[ i ];
			testNull.num = i + 1;
		}
		else
			exit(1);
	}

	// ɾ�����һ������
// 	delLink(&testObj , LINKOBJ);
// 	testNull.num = 15;
// 	allObj[ 15 ] = (objInfo *)0xF000;

	// ����һ�����ӵ�����
	unshort id;
	creatLink(&testObj , LINKOBJ);
	if(testNull.wtObj.nullNext != NULL){
		id = testNull.wtObj.nullNext->id;
		allObj[ id ] = creatObj(ZIDAN , 1 , UP , 31 , 25 , id);
		testObj.wtObj.objNext->theObj = allObj[ id ];
		delLink(&testNull , NULLARR);
	}
	else{
		id = testNull.num;
		allObj[ testNull.num ] = creatObj(ZIDAN , 1 , UP , 31 , 25 , id);
		testObj.wtObj.objNext->theObj = allObj[ id ];
		(testNull.num) += 1;
	}

	// ɾ�������еĵ�13 �� ��8 ����
	delLink(&testObj , LINKOBJ , 13);
	allObj[ 13 ] = (objInfo *)0xF000;
	creatLink(&testNull , NULLARR);
	testNull.wtObj.nullNext->id = 13;
	delLink(&testObj , LINKOBJ , 8);
	allObj[ 8 ] = (objInfo *)0xF000;
	creatLink(&testNull , NULLARR);
	testNull.wtObj.nullNext->id = 8;

	// ����һ���µ��ӵ�����
	creatLink(&testObj , LINKOBJ);
	if(testNull.wtObj.nullNext != NULL){
		id = testNull.wtObj.nullNext->id;
		allObj[ id ] = creatObj(ZIDAN , 1 , UP , 28 , 25 , id);
		testObj.wtObj.objNext->theObj = allObj[ id ];
		delLink(&testNull , NULLARR);
	}
	else{
		id = testNull.num;
		allObj[ testNull.num ] = creatObj(ZIDAN , 1 , UP , 28 , 25 , id);
		testObj.wtObj.objNext->theObj = allObj[ id ];
		(testNull.num) += 1;
	}

	// �������
	//clrLink(&testNull , NULLARR);
	//clrLink(&testObj , LINKOBJ);

	echoLink(testNull , NULLARR);
	echoLink(testObj , LINKOBJ);
}