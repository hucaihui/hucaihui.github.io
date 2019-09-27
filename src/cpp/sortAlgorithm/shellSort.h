#pragma once
#include "abstractSort.h"

/*
ϣ������  -- �������������
   ƽ�����        ������  ���� �����ռ�  �ȶ���
O(nlogn)~O(n^2)    O(n^1.3)  O(n^2)     O(1)    ���ȶ�

�ο���
[ͼ���㷨---ϣ������](https://blog.csdn.net/qq_39207948/article/details/80006224)
[�����ѧ��һ�����Ѷ��㷨��ϣ������](https://www.jianshu.com/p/40dcc3b83ddc)
*/
class shellSort :public abstractSort
{
public:
	//�������ųɻ�������
	//��Ծ�������   --9 9/2=4 4/2=2 2/1=1
	//��ʱ�临�Ӷ�ȡ����gap(�����ѡ��
	void sort(vector<int> &nums) {
		int len = nums.size();
		for (int gap = len / 2; gap >= 1; gap /= 2) {    //�˼���ɱ� �ɳ���gap = gap/3+1 
			for (int i = gap; i < len; i++) {
				int tmp = nums[i];
				int j = i;
				while (j > (gap-1) && tmp < nums[j - gap]) {
					nums[j] = nums[j - gap];
					j -= gap;
				}
				nums[j] = tmp;

				//_insert(nums,gap,i);
			}
		}
	}

private:
	void _insert(vector<int> nums, const int gap, const int pos) {
		//����������Ĵ���
		// -gap ���  gap=1ʱ��Ϊֱ�Ӳ�������
		// -pos �������Ԫ��
		int tmp = nums[pos];
		int j = pos;
		while (j >=gap && tmp < nums[j - gap]) {
			nums[j] = nums[j - gap];
			j -= gap;
		}
		nums[j] = tmp;	
	}

};