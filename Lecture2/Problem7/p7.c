/****************
* 
【问题描述】

停车场管理问题描述：设停车场是一个可停放n辆车的狭长通道，且只有一个大门可供汽车进出。在停车场内，汽车按到达的先后次序，由北向南依次排列（假设大门在最南端）。若车场内已停满n辆车，则后来的汽车需在门外的便道上等候，当有车开走时，便道上的第一辆车即可开入。当停车场内某辆车要离开时，在它之后进入的车辆必须先退出车场为它让路，待该辆车开出大门后，其它车辆再按原次序返回车场。每辆车离开停车场时，应按其停留时间的长短交费（在便道上停留的时间不收费）。

试编写程序，模拟上述管理过程。要求以顺序栈模拟停车场，以链队列模拟便道。

从终端读入汽车到达或离去的数据，每组数据包括三项：

① 是“到达”还是“离去”；

② 汽车牌照号码；

③ “到达”或“离去”的时刻。

与每组输入信息相应的输出信息为：

如果是到达的车辆，则输出其在停车场中或便道上的位置；

如果是离去的车辆，则输出其在停车场中停留的时间和应交的费用。


【输入格式】

 第一行，两个整数 n, price, m 。
 表示停车场容纳量 n 、收费价格 m、共计 m 条请求信息。

 接下来 m 行，每行一条请求信息：
  请求类型 c，车牌号 lice，动作时间 t。

 c 为字符：'P'表示停泊请求，'L'表示离开请求。
 lice 为字符串，由大写字母和数字组成，表示车牌号。
 t 为整数，表示时间

 请求数据按照时间顺序输入，保证输入合法。


【样例输入】

2 2 6
P A1001 1
P A1002 3
P A1003 5
L A1002 6
P A1004 7
L A1003 10


【样例输出】

1 0
1 1
0 0
3 6
0 0
4 8


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
