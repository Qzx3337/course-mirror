/********************
题目：
二、建立一个非递减的顺序表L，已知顺序表L中的元素为int，请编写一个算法，删除所有元素中的数值相等的多余元素。
时间复杂度：O(n)，空间复杂度：O(1)

思路：
根据空间限制，我们无法开新数组只能在原数组上相互赋值，用有用值覆盖无用值。
根据时间限制，我们只能采用双指针法单向遍历数组，不能循环。
我们使用指针p,q，使用q遍历数组，此过程中添加并维护[0,p]为严格上升序列（不重复）即可。

接口：
去重函数名为 PickAscendList()，封装在SeqList模板类中，作为可写访问接口，原型为
template <typename T> void SeqList<T>::PickAscendList();

language: C++;

********************/

#include "P2.h"
using namespace std;

int main() {
	
	// freopen("p2.in", "r", stdin);

	SeqList<int> la;
	// creat_not_decrease(la, 100, 12); // 随机生成有序列表
	readMyList(la);
	// la.show();

	la.PickAscendList(); // 去重
	// la.show();
	la.showElem();

	return 0;
}








