#pragma once

// �ж�ָ�������Ƿ���
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
// �ж�ָ�������Ƿ���
#define KEYUP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

// ����̨API���ռ����������

// �������������Ϣ
void outPutPos(int nX , int nY);

// �����¼������� 1
void keyEventProc(KEY_EVENT_RECORD ker);

// �����¼������� 2
void keyEventSec();

// �����¼������� 3
void keyEvent();

// ����¼�������
void mouseEventProc(MOUSE_EVENT_RECORD mer);

// ��Ϣ������
void messageLoop();