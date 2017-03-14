#pragma once

// 控制台API接收键盘鼠标输入

// 输出调试坐标信息
void outPutPos(int nX , int nY);

// 键盘事件处理函数
void keyEventProc(KEY_EVENT_RECORD ker);

// 鼠标事件处理函数
void mouseEventProc(MOUSE_EVENT_RECORD mer);

// 消息处理函数
void messageLoop();