#pragma once

// 碰撞检测
bool collision(objInfo *ob , coor crBuff[]);

// 通过坐标判断对象类型
unshort wtType(coor wObj);

// 我方坦克中弹
void tankeOver();