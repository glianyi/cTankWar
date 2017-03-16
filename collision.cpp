#include "tanke.h"

int tankeLife = 4;
int gameOver = 0;

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
					tankeOver();
					return false;
				}
			}
			// �з�̹����ײ�ҷ�̹�˻��ӵ�
			if((crTp == TANK || crTp == ZIDAN || crTp == DZIDAN) &&
			   (tp == DTANK || tp == DDTANK)){

				if(crTp == ZIDAN){
					if(tp == DDTANK){
						(allObj[ ob->ID ]->Type) = DTANK;
						(allObj[ ob->ID ]->Bullft) -= 1;
						(allObj[ ob->ID ]->color) = 0x04;
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
					tankeOver();
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
			if(crTp == ZWALL || crTp == TWALL || crTp == HELIU){
				// canMove -= 1;
			}
		}
	}
	else{
		crTp = wtType(crBuff[ 0 ], &crId);
		// Ŀ���������Ԫ��
		if(crTp == 128)
			return true;

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
				(allObj[ crId ]->color) = 0x04;
			}
			else{
				delT(&dTankLink , crId);// ɾ���з�̹�˶���
			}
		}

		// �з��ӵ���ײ�ҷ�̹��
		if(tp == DZIDAN && crTp == TANK){
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
	if((allObj[1]->Bullft) >= 0)
		(allObj[ 1 ]->Bullft) -= 1;
// 	if(allObj[ 1 ]->Bullft <= 0)
// 		gameOver += 1;

	char szBuff[ 10 ];
	sprintf_s(szBuff , 10 , "%2d" , allObj[ 1 ]->Bullft);
	WriteChar(45 , 7 , szBuff , 0x0A);

	allObj[ 1 ]->Action = UP;
	allObj[ 1 ]->ltposX = 37;
	allObj[ 1 ]->ltposY = 25;
}

// ͨ�������ж϶�������
unshort wtType(coor wObj, unshort *crId){
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
void delT(hdLink *theObj, unshort id){
	delLink(theObj , LINKOBJ , id);
	
	if(id == (nLink.num - 1)){
		nLink.num = id;
	}
	else{
		creatLink(&nLink , NULLARR);
		nLink.wtObj.nullNext->id = id;
	}

	allObj[ id ] = (objInfo *)0xF000;
}