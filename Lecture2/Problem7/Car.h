#pragma once

#ifndef MAX_LICENSE_LEN
#define MAX_LICENSE_LEN 9
#endif // !MAX_LICENSE_LEN

// ������
typedef struct Car {
	//int id;							// ͣ������ǳ���Ψһ�� id
	char license[MAX_LICENSE_LEN];	// ���ƺ�
	int tArrive;					// ����ʱ��
	int tLeave;						// �뿪ʱ��
	int fee;						// ͣ������
	int state;						// ״̬
	/// <summary>
	/// state = 0; ��ʾͣ�ڳ���ȴ�����ͣ����
	/// state = 1; ��ʾͣ��ͣ�����ڵĳ�λ��
	/// state = 2; ��ʾ�Ѿ��뿪ͣ����
	/// Ŀǰ��δά������ͣ������ĳ�̬
	/// </summary>
	int spaceNum;					// ���ڳ�λ�ı��
}Car;
