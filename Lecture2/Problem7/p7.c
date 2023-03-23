/****************

P7  ͣ����������������
�������Ķ� README.MD

���ԣ�C.

****************/

#define _CRT_SECURE_NO_WARNINGS 1

#include "p7.h"

//const int PARKING_CAPACITY = 9999;
#define MAX_LICENSE_LEN 9		// ����ƺų���
const char LEAVE_FALG = 'L';
const char PARK_FALG = 'P';


int main() {

	// freopen("p7.in", "r", stdin);

	int n, price;					// ͣ����������
	scanf("%d%d", &n, &price);

	ParkingLot lot;					// lot ��һ��ͣ����
	InitParkingLot(&lot, n, price);		// ��ʼ�� lot ������ n����

	int m;							// ���� m��������
	scanf("%d", &m);
	int i;							// ������
	char act_flag;					// �б��� ���� ���� ����
	char license[MAX_LICENSE_LEN];	// ���ƺ�
	int timeAct;					// ����ʱ��
	Car car;						// car ��һ��������ͣ������
	for (i = 0; i < m; ++i) {		// ������ m��������Ϣ

		scanf("\n%c %s %d", &act_flag, license, &timeAct);
		//printf("----- =%c; =%s; =%d;-----\n", act_flag, license, timeAct);
		if (act_flag == PARK_FALG) {						// Ҫͣ��
			car = ParkCar(lot, license, timeAct);			// car ��ո�ͣ�ĳ�����Ϣ
			printf("%d %d\n", car.state, car.spaceNum);		// ��ӡ ״̬����λ��
		}
		else if(act_flag == LEAVE_FALG){					// Ҫ�뿪
			car = LeaveCar(lot, license, timeAct);			// car ��ͣ���������ĳ�
			printf("%d %d\n", car.tLeave - car.tArrive, car.fee);	// ��ӡ ͣ��ʱ��������
		}
	}

	return 0;
}
