#include "tanke.h"

int tankeLife = 4;
int gameOver = 0;

// ��ײ���
bool collision(objInfo *ob , coor crBuff[]){
	unshort tp = ob->Type; // ��������
	unshort crTp; // ������������
	int canMove = 1; // �ж��ܷ��ƶ�
	if(tp == 1 || tp == 2){
		// �ж�̹��ÿһ����
		for(int i = 0; i < 6 ; i++){
			crTp = wtType(crBuff[ i ]);
			if((tp & crTp) == 0)
				canMove -= 1;

			// �ҷ�̹����ײ�з�̹�˻��ӵ�
			if((crTp == 2 || crTp == 64) && tp == 1){
				if(crTp == 64){
					//delLink();// ɾ���ӵ�����
				}
				tankeOver();
				return false;
			}
			// �з�̹����ײ�ҷ�̹�˻��ӵ�
			if((crTp == 1 || crTp == 4) && tp == 2){
				if(crTp == 4){
					//delLink();// ɾ���ӵ�����
					//delLink();// ɾ���ط�̹�˶���
				}
				else{
				tankeOver();
				}
				return false;
			}
		}
	}
	else{
		crTp = wtType(crBuff[ 0 ]);
		// �ӵ�������ײ���򷵻���
		if((tp & crTp) != 0)
			return true;
		canMove -= 1;
		//delLink();// ɾ���ӵ�����

		// �ҷ��ӵ���ײ�з�̹��
		if(tp == 4 && crTp == 2){
			//delLink();// ɾ���з�̹�˶���
		}

		// �з��ӵ���ײ�ҷ�̹��
		if(tp == 64 && crTp == 1){
			tankeOver();
		}

		// �ӵ���ײ
		if(crTp == 64 || crTp == 4){
			//delLink();// ɾ��crTp�ӵ�����
		}

		// �ӵ�ײǽ
		if(crTp == 8){

		}
	}

	if(canMove < 1)
		return false;

	return true;
}

// �ҷ�̹���е�
void tankeOver(){
	if(tankeLife >= 0)
		tankeLife -= 1;
	if(tankeLife == -1)
		gameOver = 1;

	// creatObj(1 , 1 , UP , 37 , 25 , 1);
	allObj[ 1 ]->Action = UP;
	allObj[ 1 ]->ltposX = 37;
	allObj[ 1 ]->ltposY = 25;
}

// ͨ�������ж϶�������
unshort wtType(coor wObj){
	unshort x = wObj.x;
	unshort y = wObj.y;
	if(allObj[ dftMap[ x ][ y ] ] != NULL){
		return allObj[ dftMap[ x ][ y ] ]->Type;
	}
	else if(allObj[ beforMap[ x ][ y ] ] != NULL){
		unshort tp = allObj[ dftMap[ x ][ y ] ]->Type;
		// �ھɵ�ͼ�е�̹�˺��ӵ���������
		if(tp != 1 && tp != 2 && tp != 4 && tp != 6)
			return tp;
	}
	return 64;
}