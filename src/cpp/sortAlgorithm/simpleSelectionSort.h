#pragma once
#include "abstractSort.h"


/*
��ѡ������
ƽ����� ������ ���� �����ռ� �ȶ���
O(n^2)    O(n^2)   O(n^2)    O(1)    �ȶ�
*/
class simpleSelectionSort :public abstractSort
{
public:
	//�ҵ�ʣ��Ԫ�ص���СԪ��
	//����Ԫ�ؽ�����ָ��λ��
	void sort(vector<int> &nums) {
		int len = nums.size();
		for (int i = 0; i < len; ++i) {
			int index = i;  //��СԪ���±�
			for (int j = i + 1; j < len; ++j) {
				if (nums[j] < nums[index]) {   //�ҳ���СԪ�ص��±�
					index = j;
				}
			}
			if (index != i) 
				sw(nums[i], nums[index]);
		}
	}
};