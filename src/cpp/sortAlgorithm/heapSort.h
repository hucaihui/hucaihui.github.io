#pragma once

#include "abstractSort.h"

/*
������
ƽ����� ������ ���� �����ռ� �ȶ���
O(nlogn) O(nlogn) O(nlogn)   O(1)   ���ȶ�

����
������0��ͷ������㣺i�����ӣ�2*i+1���Һ��ӣ�2*i+2
������1��ͷ������㣺i�����ӣ�2*i��  �Һ��ӣ�2*i+1
*/
class heapSort :public abstractSort
{
public:
	//1������
	//2�������ֵ��ĩλ����
	//3����ʣ�µ�Ԫ�ص�����Ϊ����
	void sort(std::vector<int> &nums) {
		int len = nums.size();
		for (int i = (len - 1) / 2; i >= 0; i--) {
			builtMaxHeap(nums, i, len - 1);   //���к��ӵĽ����й���
		}
		disPlay(nums);
		for (int i = len - 1; i > 0; i--) {
			sw(nums[0], nums[i]);
			builtMaxHeap(nums, 0, i-1);       //��ʣ�µ�Ԫ�ر���Ϊ�󶥶�
		}
	}

	void builtMaxHeap(vector<int> &nums,int p,int end) {
		int tmp = nums[p];
		int i = 2 * p + 1;    //������0��ͷ�������i,������2i+1,�Һ�����2i+2
		while (i < end) {     //�˲��ֽ��������ڲ�������
			if (nums[i + 1] >= nums[i])
				i++;
			if (tmp > nums[i])
				break;
			nums[p] = nums[i];
			p = i;
			i = 2 * i + 1;
		}
		nums[p] = tmp;
	}

	void builtMaxHeap_v2(vector<int> &nums, int p, int end) {
		//builtMaxHeap()��д�汾
		int i = 2 * p + 1;   
		while (i < end) {
			if (nums[i + 1] >= nums[i])
				i++;
			if (nums[p] > nums[i])
				break;
			sw(nums[p], nums[i]);     //*
			i = 2 * i + 1;
		}
	}

};