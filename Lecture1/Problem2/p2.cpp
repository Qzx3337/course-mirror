/********************
��Ŀ��
��������һ���ǵݼ���˳���L����֪˳���L�е�Ԫ��Ϊint�����дһ���㷨��ɾ������Ԫ���е���ֵ��ȵĶ���Ԫ�ء�
ʱ�临�Ӷȣ�O(n)���ռ临�Ӷȣ�O(1)

˼·��
���ݿռ����ƣ������޷���������ֻ����ԭ�������໥��ֵ��������ֵ��������ֵ��
����ʱ�����ƣ�����ֻ�ܲ���˫ָ�뷨����������飬����ѭ����
����ʹ��ָ��p,q��ʹ��q�������飬�˹�������Ӳ�ά��[0,p]Ϊ�ϸ��������У����ظ������ɡ�

�ӿڣ�
ȥ�غ�����Ϊ PickAscendList()����װ��SeqListģ�����У���Ϊ��д���ʽӿڣ�ԭ��Ϊ
template <typename T> void SeqList<T>::PickAscendList();

language: C++;

********************/

#include "P2.h"
using namespace std;

int main() {
	
	// freopen("p2.in", "r", stdin);

	SeqList<int> la;
	// creat_not_decrease(la, 100, 12); // ������������б�
	readMyList(la);
	// la.show();

	la.PickAscendList(); // ȥ��
	// la.show();
	la.showElem();

	return 0;
}








