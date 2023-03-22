#pragma once

// 地图点类
typedef struct Point {
	int x, y;
}Point;

// 坐标相加，发生位移
Point addPnt(Point a, Point b) {
	Point c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return c;
}

// 坐标详见，发生位移
Point subtractPnt(Point a, Point b) {
	Point c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return c;
}

// 判断两个坐标相等，相等返回 1
int cmpPnt(Point a, Point b) {
	if (a.x != b.x) return false;
	if (a.y != b.y) return false;
	return true;
}

