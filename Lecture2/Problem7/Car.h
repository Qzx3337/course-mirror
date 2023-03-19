#pragma once

#ifndef MAX_LICENSE_LEN
#define MAX_LICENSE_LEN 9
#endif // !MAX_LICENSE_LEN

// 汽车类
typedef struct Car {
	//int id;							// 停车场标记车的唯一的 id
	char license[MAX_LICENSE_LEN];	// 车牌号
	int tArrive;					// 到达时间
	int tLeave;						// 离开时间
	int fee;						// 停车费用
	int state;						// 状态
	/// <summary>
	/// state = 0; 表示停在场外等待进入停车场
	/// state = 1; 表示停在停车场内的车位中
	/// state = 2; 表示已经离开停车场
	/// 目前尚未维护进入停车场后的常态
	/// </summary>
	int spaceNum;					// 所在车位的编号
}Car;
