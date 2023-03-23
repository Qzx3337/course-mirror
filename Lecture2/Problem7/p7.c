/****************

P7  停车场管理问题描述
介绍请阅读 README.MD

语言：C.

****************/

#define _CRT_SECURE_NO_WARNINGS 1

#include "p7.h"

//const int PARKING_CAPACITY = 9999;
#define MAX_LICENSE_LEN 9		// 最大车牌号长度
const char LEAVE_FALG = 'L';
const char PARK_FALG = 'P';


int main() {

	// freopen("p7.in", "r", stdin);

	int n, price;					// 停车场容纳量
	scanf("%d%d", &n, &price);

	ParkingLot lot;					// lot 是一个停车场
	InitParkingLot(&lot, n, price);		// 初始化 lot 最多放下 n辆车

	int m;							// 共有 m辆车会来
	scanf("%d", &m);
	int i;							// 迭代用
	char act_flag;					// 判别动作 来车 还是 出车
	char license[MAX_LICENSE_LEN];	// 车牌号
	int timeAct;					// 发生时间
	Car car;						// car 是一辆车，给停车场用
	for (i = 0; i < m; ++i) {		// 遍历这 m辆车的信息

		scanf("\n%c %s %d", &act_flag, license, &timeAct);
		//printf("----- =%c; =%s; =%d;-----\n", act_flag, license, timeAct);
		if (act_flag == PARK_FALG) {						// 要停泊
			car = ParkCar(lot, license, timeAct);			// car 存刚刚停的车的信息
			printf("%d %d\n", car.state, car.spaceNum);		// 打印 状态、车位号
		}
		else if(act_flag == LEAVE_FALG){					// 要离开
			car = LeaveCar(lot, license, timeAct);			// car 存停车场出来的车
			printf("%d %d\n", car.tLeave - car.tArrive, car.fee);	// 打印 停车时长、费用
		}
	}

	return 0;
}
