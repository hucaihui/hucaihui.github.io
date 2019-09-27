#pragma once

#include "abstractSort.h"

/*
��������
ƽ����� ������ ���� �����ռ� �ȶ���
O(n^2)    O(n)    O(n^2)    O(1)    �ȶ�
*/
class insertSort :public abstractSort
{
public:
	//�ӵڶ���Ԫ�ؿ�ʼ
	//�ҳ����������кõ�λ��
	//���ڸ�Ԫ�صĺ��ƣ���Ԫ�ز�������λ��
	void sort(std::vector<int> &nums) {
		int len = nums.size();
		for (int i = 1; i < len; ++i) {
			int tmp = nums[i];
			int j = i;
			while (j>0 && tmp < nums[j-1]) {
				nums[j] = nums[j-1];
				j--;
			}
			nums[j] = tmp;

			//_insert(nums,1,i);    //shellSort.h
		}
	}

};