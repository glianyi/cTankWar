#pragma once

// 碰撞检测
bool collision(objInfo *ob , coor crBuff[]);

// 通过坐标判断对象类型
unshort wtType(coor wObj , unshort *crId);

// 我方坦克中弹
void tankeOver();

// 删除坦克、子弹链表元素
void delT(hdLink *theObj , unshort id);