#pragma once

// ��ͼ����
typedef struct Point {
	int x, y;
}Point;

// ������ӣ�����λ��
Point addPnt(Point a, Point b) {
	Point c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return c;
}

// �������������λ��
Point subtractPnt(Point a, Point b) {
	Point c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return c;
}

// �ж�����������ȣ���ȷ��� 1
int cmpPnt(Point a, Point b) {
	if (a.x != b.x) return false;
	if (a.y != b.y) return false;
	return true;
}

