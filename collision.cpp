#include "tanke.h"

int tankLife = 6;
int gameOver = 0;
int dTankNum = 20;

// ��ײ���
bool collision(objInfo *ob , coor crBuff[]){
	unshort tp = ob->Type; // ��������
	unshort crTp; // ������������
	unshort crId = 0; // ��������ID
	int canMove = 1; // �ж��ܷ��ƶ�
	if(tp == TANK || tp == DTANK || tp == DDTANK){
		// �ж�̹��ÿһ����
		for(int i = 0; i < 6 ; i++){
			crTp = wtType(crBuff[ i ] , &crId);
			// Ŀ���������Ԫ��
			if(crTp == 128)
				continue;

			if((tp & crTp) == 0)
				canMove -= 1;

			// �ҷ�̹����ײ�з�̹�˻��ӵ�
			if((crTp == DTANK || crTp == DDTANK || crTp == DDTANK ||
				crTp == ZIDAN || crTp == DZIDAN) && tp == TANK){
				if(crTp == ZIDAN || crTp == DZIDAN){
					delT(&bulletLink , crId); //ɾ���ӵ�����
				}
				if(crTp == ZIDAN){
					canMove += 1;
				}
				else{
					//�޵�ʱ��
					if(tankLife > 0){
						if(tp == DDTANK){
							// ����̹������
							(allObj[ ob->ID ]->Type) = DTANK;
							(allObj[ ob->ID ]->Bullft) -= 1;
							(allObj[ ob->ID ]->color) = 0x03;
							// �޸�̹��ID ��ʵʱ���£�
							unshort tempid = getNullObj(&nLink);
							allObj[ ob->ID ] = (objInfo *)0xF000;
							// ��̹��ԭID�����Ԫ������
							creatLink(&testNull , NULLARR);
							testNull.wtObj.nullNext->id = ob->ID;
							ob->ID = tempid;
							allObj[ tempid ] = ob;
						}
						else{
							delT(&dTankLink , ob->ID);// ɾ���з�̹�˶���
						}
					}
					else{
						tankeOver();
						return false;
					}
				}
			}
			// �з�̹����ײ�ӵ����ҷ�̹��
			if((crTp == TANK || crTp == ZIDAN || crTp == DZIDAN) &&
			   (tp == DTANK || tp == DDTANK)){

				if(crTp == ZIDAN){
					if(tp == DDTANK){
						// ����̹������
						(allObj[ ob->ID ]->Type) = DTANK;
						(allObj[ ob->ID ]->Bullft) -= 1;
						(allObj[ ob->ID ]->color) = 0x03;
						// �޸�̹��ID ��ʵʱ���£�
						unshort tempid = getNullObj(&nLink);
						allObj[ ob->ID ] = (objInfo *)0xF000;
						// ��̹��ԭID�����Ԫ������
						creatLink(&testNull , NULLARR);
						testNull.wtObj.nullNext->id = ob->ID;
						ob->ID = tempid;
						allObj[ tempid ] = ob;
					}
					else{
						delT(&dTankLink , ob->ID);// ɾ���з�̹�˶���
					}
					delT(&bulletLink , crId);// ɾ���ӵ�����
					return false;
				}
				else if(crTp == DZIDAN){
					delT(&bulletLink , crId);// ɾ���ӵ�����
					canMove += 1;
				}
				else{
					//�޵�ʱ��
					if(tankLife > 0){
						if(tp == DDTANK){
							// ����̹������
							(allObj[ ob->ID ]->Type) = DTANK;
							(allObj[ ob->ID ]->Bullft) -= 1;
							(allObj[ ob->ID ]->color) = 0x03;
							// �޸�̹��ID ��ʵʱ���£�
							unshort tempid = getNullObj(&nLink);
							allObj[ ob->ID ] = (objInfo *)0xF000;
							// ��̹��ԭID�����Ԫ������
							creatLink(&testNull , NULLARR);
							testNull.wtObj.nullNext->id = ob->ID;
							ob->ID = tempid;
							allObj[ tempid ] = ob;
						}
						else{
							delT(&dTankLink , ob->ID);// ɾ���з�̹�˶���
						}
					}
					else{
						tankeOver();
						return false;
					}
				}
			}

			// �з�̹����ײ����
			if((tp == DTANK || tp == DDTANK || tp == TANK) &&
			   crTp == JIDI){
				if(tp != TANK){
					gameOver += 1;
					allObj[ 2 ]->color = 0x00; //�޸Ļ��ض�����ɫ
					return false;
				}
			}

			// ̹��ײǽ���������ֱ�Ӳ����ƶ�
// 			if(crTp == ZWALL || crTp == TWALL || crTp == HELIU){
// 				// canMove -= 1;
// 			}
		}
	}
	else{
		crTp = wtType(crBuff[ 0 ], &crId);
		// Ŀ���������Ԫ��
		if(crTp == 128)
			return true;
		else if(crTp == 127)
			return false;

		// �ӵ�������ײ���򷵻���
		if((tp & crTp) != 0)
			return true;
		canMove -= 1;
		delT(&bulletLink , ob->ID);// ɾ���ӵ�����

		// �ҷ��ӵ���ײ�з�̹��
		if(tp == ZIDAN && (crTp == DTANK || crTp == DDTANK)){
			if(crTp == DDTANK){
				(allObj[ crId ]->Type) = DTANK;
				(allObj[ crId ]->Bullft) -= 1;
				(allObj[ crId ]->color) = 0x03;
				unshort tempid = getNullObj(&nLink);
				objInfo *tempobj = allObj[ crId ];
				allObj[ tempobj->ID ] = (objInfo *)0xF000;
				creatLink(&testNull , NULLARR);
				testNull.wtObj.nullNext->id = tempobj->ID;
				tempobj->ID = tempid;
				allObj[ tempid ] = tempobj;
			}
			else{
				delT(&dTankLink , crId);// ɾ���з�̹�˶���
			}
		}

		// �з��ӵ���ײ�ҷ�̹��
		if(tp == DZIDAN && crTp == TANK){
			// �޵�ʱ��
			if(tankLife <= 0)
				tankeOver();
		}

		// �ӵ���ײ
		if(crTp == ZIDAN || crTp == DZIDAN){
			delT(&bulletLink , crId);// ɾ��crTp�ӵ�����
		}

		// �ӵ�ײǽ
		if(crTp == ZWALL){
			// �޸�ǽ������
			unshort crX , crY;
			long long len;
			crX = allObj[ crId ]->ltposX;
			crY = allObj[ crId ]->ltposY;

			if(crX == crBuff[ 0 ].x)
				len = abs((long long)crY - (long long)(crBuff[ 0 ].y));
			else
				len = abs((long long)crX - (long long)(crBuff[ 0 ].x));
			
			(allObj[ crId ]->Bullft) |= ((long long)1 << len);
		}

		if(crTp == JIDI){
			gameOver += 1;
			allObj[ 2 ]->color = 0x00; //�޸Ļ��ض�����ɫ
		}
	}

	if(canMove < 1)
		return false;

	return true;
}

// �ҷ�̹���е�
void tankeOver(){
	if(tankLife > 0)
		return;

	if((allObj[ 1 ]->Bullft) >= 0){
		(allObj[ 1 ]->Bullft) -= 1;
	}

	if(allObj[ 1 ]->Bullft <= 0)
		gameOver += 1;

	char szBuff[ 10 ];
	sprintf_s(szBuff , 10 , "%2d" , allObj[ 1 ]->Bullft);
	WriteChar(45 , 8 , szBuff , 0x0A);

	allObj[ 1 ]->Action = UP;
	allObj[ 1 ]->ltposX = 37;
	allObj[ 1 ]->ltposY = 25;
	tankLife = 6;
	echoTanke(allObj[ 1 ]);
}

// ͨ�������ж϶�������
unshort wtType(coor wObj, unshort *crId){
	if(wObj.x >= MAXMAPWID || wObj.y >= MAXMAPWID)
		return 127;

	unshort x = wObj.x;
	unshort y = wObj.y;
	if(allObj[ dftMap[ x ][ y ] ] != NULL &&
	   allObj[ dftMap[ x ][ y ] ] != (objInfo *)0xF000){
		*crId = dftMap[ x ][ y ];
		return allObj[ dftMap[ x ][ y ] ]->Type;
	}
	else if(allObj[ beforMap[ x ][ y ] ] != NULL &&
			allObj[beforMap[x][y]] != (objInfo *)0xF000){

		unshort tp = allObj[ beforMap[ x ][ y ] ]->Type;
		// �ھɵ�ͼ�е�̹�˺��ӵ���������
		if(tp != TANK && tp != DTANK && tp != DDTANK &&
		   tp != ZIDAN && tp != DZIDAN){
			*crId = beforMap[ x ][ y ];
			return tp;
		}
	}
	return 128;
}

// ɾ��̹�ˡ��ӵ�����Ԫ��
void delT(hdLink *theObj , unshort id){
	if(theObj->wtObj.objNext == NULL)
		return;
	unshort tp = theObj->wtObj.objNext->theObj->Type;
	unshort x = theObj->wtObj.objNext->theObj->ltposX;
	unshort y = theObj->wtObj.objNext->theObj->ltposY;
	unshort act = theObj->wtObj.objNext->theObj->Action;

	clrCanliu(theObj->wtObj.objNext->theObj);
	delLink(theObj , LINKOBJ , id);

	if(id == (nLink.num - 1)){
		nLink.num = id;
	}
	else{
		creatLink(&nLink , NULLARR);
		nLink.wtObj.nullNext->id = id;
	}

	allObj[ id ] = (objInfo *)0xF000;

	if(tp == DTANK){
		if(dTankNum > 0){
			// ������Ϊ���򴴽���̹��
			int flag = 1;
			for(int i = 1; i <= 3; i++){
				for(int j = 14; j <= 16; j++)
					if(dftMap[ i ][ j ] != 0)
						--flag;
			}
			if(flag == 1){
				seconds = clock();
				echoDtank(2 << (seconds % 2));
			}
		}
		--dTankNum;
		char szBuff[ 10 ];
		sprintf_s(szBuff , 10 , "%2d" , dTankNum);
		WriteChar(45 , 10 , szBuff , 0x0A);
	}

}


// �������
void clrCanliu(objInfo *theObj){
	unshort x = theObj->ltposX;
	unshort y = theObj->ltposY;
	unshort act = theObj->Action;
	dftMap[ x ][ y ] = 0;
	if(theObj->Type == ZIDAN || theObj->Type == DZIDAN)
		return;
	switch(act)
	{
		case UP:
			dftMap[ x - 1 ][ y ] = 0;
			dftMap[ x ][ y - 1 ] = 0;
			dftMap[ x ][ y + 1 ] = 0;
			dftMap[ x + 1 ][ y - 1 ] = 0;
			dftMap[ x + 1 ][ y + 1 ] = 0;
			break;
		case DOWN:
			dftMap[ x + 1 ][ y ] = 0;
			dftMap[ x ][ y + 1 ] = 0;
			dftMap[ x ][ y - 1 ] = 0;
			dftMap[ x - 1 ][ y + 1 ] = 0;
			dftMap[ x - 1 ][ y - 1 ] = 0;
			break;
		case LEFT:
			dftMap[ x ][ y - 1 ] = 0;
			dftMap[ x + 1 ][ y ] = 0;
			dftMap[ x - 1 ][ y ] = 0;
			dftMap[ x + 1 ][ y + 1 ] = 0;
			dftMap[ x - 1 ][ y + 1 ] = 0;
			break;
		case RIGHT:
			dftMap[ x ][ y + 1 ] = 0;
			dftMap[ x - 1 ][ y ] = 0;
			dftMap[ x + 1 ][ y ] = 0;
			dftMap[ x - 1 ][ y - 1 ] = 0;
			dftMap[ x + 1 ][ y - 1 ] = 0;

		default:
			break;
	}
}