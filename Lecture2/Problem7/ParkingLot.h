#pragma once

#include "Car.h"
#define ElemType Car
#include "SeqStack.h"
#include "LinkQueue.h"

#define PARK_IN_LOT 0		// ������ͣ����
#define WAIT_OUTSIDE 1		// �����ڵȴ�������

// ͣ������
typedef struct ParkingLotBody {
// ��̬��
	int capacity;		// ͣ������������
	int price;			// �շѼ۸�
// ��̬ά��
	int number;			// ��ǰͣ�������������������ȴ��еĳ�
	Queue waiters;		// �ȴ��еĳ�
	Stack parkers;		// �Ѿ�ͣ���ĳ�
} ParkingLotBody, *ParkingLot;


// �ڲ�����

int CheckLicense(Car const car, char* const lice);

// ��д�ӿ�

void InitParkingLot(ParkingLot* lot, int n, int price);
Car ParkCar(ParkingLot lot, char* lice, int tArr);
Car LeaveCar(ParkingLot lot, char* lice, int tLev);

// ֻ���ӿ�


/****** ʵ�� *******/

// ��鳵���ƺ�������ƺ��Ƿ����
inline int CheckLicense(Car const car, char const *lice) {
	return strcmp(lice, car.license) == 0;
}

// ��ʼ��ͣ��������Ϊ n
inline void InitParkingLot(ParkingLot* lot, int n, int price) {
	(*lot) = (ParkingLot)malloc(sizeof(ParkingLotBody));
	(*lot)->capacity = n;
	(*lot)->price = price;
	(*lot)->number = 0;
	InitStack(&(*lot)->parkers);
	InitQue(&(*lot)->waiters);
}

// ͣ��һ���³�
Car ParkCar(ParkingLot lot, char* lice, int tArr) {
	Car newCar;						// ����һ����
	newCar.tArrive = tArr;
	strcpy(newCar.license, lice);
	
	lot->number++;					// ������ ++
	if (lot->number <= lot->capacity) {		// ͣ�������г�λ
		newCar.state = 1;
		newCar.spaceNum = GetSizeSta(lot->parkers);
		PushStack(lot->parkers, newCar);	// ���복λ
	}
	else {									// û��λ�ˣ���
		newCar.state = 0;
		newCar.spaceNum = GetSizeQue(lot->waiters);
		PushQue(lot->waiters, newCar);		// �ŵȴ�������
	}
	return newCar;
}

// �г��뿪
Car LeaveCar(ParkingLot lot, char* lice, int tLev) {
	Car leavingCar;							// �뿪��������
	strcpy(leavingCar.license, "");			// �ҵ������֮ǰ������û����
	Stack parkers = lot->parkers;			// ͣ�����ڵĳ�
	Stack tmp;  InitStack(&tmp);			// Ų��ʱ ��·ר�ó���
	for (; !IsEmptySta(parkers);) {			// ͣ�����ǿգ�����Ų��
		if (CheckLicense(GetTop(parkers), lice)) { // Ŀ�공 ����
			leavingCar = GetTop(parkers);	// ���Ϊ �뿪����
			PopStack(parkers);				// ͣ���� -1
			break;
		}
		else {								// ����Ŀ�공����Ų��
			PushStack(tmp, GetTop(parkers));// ��·ר�õ� +1
			PopStack(parkers);				// ͣ���� -1
		}
	}
	for (; !IsEmptySta(tmp);) {				// ��·�����ǿվͲ��ϻص�ͣ����
		PushStack(parkers, GetTop(tmp));	// ͣ���� +1
		PopStack(tmp);						// ��·���� -1
	}

	if (CheckLicense(leavingCar, "")) {		// ͣ������û���������
		leavingCar.fee = -1;				// ���������ڷ���
		return leavingCar;
	}
	leavingCar.tLeave = tLev;				// ����뿪ʱ��
	leavingCar.fee = (tLev - leavingCar.tArrive) * lot->price;	// �������

	lot->number--;		// ͣ�������г�һλ���ȴ����еĳ����Խ�����
	if (!IsEmptyQue(lot->waiters)) {			// ����ȴ��������г�
		Car stepIn = GetFront(lot->waiters);	// ���
		PopQue(lot->waiters);					// ����
		stepIn.tArrive = tLev;					// ��¼ͣ��ʱ��
		PushStack(parkers, stepIn);				// ��ջ
	}

	return leavingCar;
}

