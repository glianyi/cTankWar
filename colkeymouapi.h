#pragma once

// 判断指定按键是否按下
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
// 判断指定案件是否弹起
#define KEYUP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

// 控制台API接收键盘鼠标输入

// 输出调试坐标信息
void outPutPos(int nX , int nY);

// 键盘事件处理函数 1
void keyEventProc(KEY_EVENT_RECORD ker);

// 键盘事件处理函数 2
void keyEventSec();

// 键盘事件处理函数 3
void keyEvent();

// 鼠标事件处理函数
void mouseEventProc(MOUSE_EVENT_RECORD mer);

// 消息处理函数
void messageLoop();