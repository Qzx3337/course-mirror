#pragma once

#include "Car.h"
#define ElemType Car
#include "SeqStack.h"
#include "LinkQueue.h"

#define PARK_IN_LOT 0		// 车放在停车场
#define WAIT_OUTSIDE 1		// 车放在等待队列中

// 停车场类
typedef struct ParkingLotBody {
// 静态量
	int capacity;		// 停车场的容纳量
	int price;			// 收费价格
// 动态维护
	int number;			// 当前停车场车的数量，包括等待中的车
	Queue waiters;		// 等待中的车
	Stack parkers;		// 已经停泊的车
} ParkingLotBody, *ParkingLot;


// 内部函数

int CheckLicense(Car const car, char* const lice);

// 可写接口

void InitParkingLot(ParkingLot* lot, int n, int price);
Car ParkCar(ParkingLot lot, char* lice, int tArr);
Car LeaveCar(ParkingLot lot, char* lice, int tLev);

// 只读接口


/****** 实现 *******/

// 检查车的牌号与给定牌号是否相等
inline int CheckLicense(Car const car, char const *lice) {
	return strcmp(lice, car.license) == 0;
}

// 初始化停车场容量为 n
inline void InitParkingLot(ParkingLot* lot, int n, int price) {
	(*lot) = (ParkingLot)malloc(sizeof(ParkingLotBody));
	(*lot)->capacity = n;
	(*lot)->price = price;
	(*lot)->number = 0;
	InitStack(&(*lot)->parkers);
	InitQue(&(*lot)->waiters);
}

// 停泊一辆新车
Car ParkCar(ParkingLot lot, char* lice, int tArr) {
	Car newCar;						// 构造一辆车
	newCar.tArrive = tArr;
	strcpy(newCar.license, lice);
	
	lot->number++;					// 车辆数 ++
	if (lot->number <= lot->capacity) {		// 停车场还有车位
		newCar.state = 1;
		newCar.spaceNum = GetSizeSta(lot->parkers);
		PushStack(lot->parkers, newCar);	// 放入车位
	}
	else {									// 没车位了，寄
		newCar.state = 0;
		newCar.spaceNum = GetSizeQue(lot->waiters);
		PushQue(lot->waiters, newCar);		// 排等待队列里
	}
	return newCar;
}

// 有车离开
Car LeaveCar(ParkingLot lot, char* lice, int tLev) {
	Car leavingCar;							// 离开的那辆车
	strcpy(leavingCar.license, "");			// 找到这个车之前，假设没车牌
	Stack parkers = lot->parkers;			// 停车场内的车
	Stack tmp;  InitStack(&tmp);			// 挪车时 让路专用车道
	for (; !IsEmptySta(parkers);) {			// 停车场非空，不断挪车
		if (CheckLicense(GetTop(parkers), lice)) { // 目标车 到了
			leavingCar = GetTop(parkers);	// 标记为 离开车辆
			PopStack(parkers);				// 停车场 -1
			break;
		}
		else {								// 不是目标车辆，挪车
			PushStack(tmp, GetTop(parkers));// 让路专用道 +1
			PopStack(parkers);				// 停车场 -1
		}
	}
	for (; !IsEmptySta(tmp);) {				// 让路车道非空就不断回到停车场
		PushStack(parkers, GetTop(tmp));	// 停车场 +1
		PopStack(tmp);						// 让路车道 -1
	}

	if (CheckLicense(leavingCar, "")) {		// 停车场里没有这个车牌
		leavingCar.fee = -1;				// 根本不存在费用
		return leavingCar;
	}
	leavingCar.tLeave = tLev;				// 标记离开时间
	leavingCar.fee = (tLev - leavingCar.tArrive) * lot->price;	// 计算费用

	lot->number--;		// 停车场空闲出一位，等待队列的车可以进入了
	if (!IsEmptyQue(lot->waiters)) {			// 如果等待队列里有车
		Car stepIn = GetFront(lot->waiters);	// 标记
		PopQue(lot->waiters);					// 出队
		stepIn.tArrive = tLev;					// 记录停车时间
		PushStack(parkers, stepIn);				// 入栈
	}

	return leavingCar;
}

