#pragma once

#include "abstractSort.h"

/*
��������  --ð�����������
ƽ����� ������ ���� �����ռ� �ȶ���
O(nlogn) O(nlogn) O(nlogn)   O(1)   ���ȶ�
*/
class quickSort :public abstractSort
{
public:
	//
	void sort(std::vector<int> &nums) {
		int len = nums.size();
		quick_sork(nums, 0, len - 1);
	}

	void quick_sork(vector<int> &nums, int low, int high) {
		if (low < high) {
			int pivot = partition(nums, low, high);
			quick_sork(nums, 0, pivot - 1);
			quick_sork(nums, pivot+1, high);
		}
	}
	void quick_sork_v2(vector<int> &nums, int low, int high) {
		//β�ݹ飬���ٵݹ����
		if (low < high) {
			int pivot = partition(nums, low, high);
			quick_sork(nums, low, pivot - 1);
			low = pivot + 1;   
		}
	}
	int partition(vector<int> &nums, int low, int high) {
		if (high - low >= 2) {   //����������
			getMidThreeNum(nums, low, high);
		}
		int pivot = nums[low];   //low  high  low
		while (low < high) { 
			while (low < high&&pivot <= nums[high]) {   //�ȸߺ��
				high--;
			}
			nums[low] = nums[high];   //ʡ�Բ���Ҫ�Ľ���
			//sw(nums[low], nums[high]);
			while (low < high&&nums[low] <= pivot) {
				low++;
			}
			nums[high] = nums[low];   
			//sw(nums[low], nums[high]);
		}
		nums[low] = pivot;
		return low;   //while����ʱlow=high
	}

	void getMidThreeNum(vector<int> &nums, int low, int high) {
		//����ȡ��
		int mid = low + (high - low) / 2;   //�����(low+high)/2һ���������Է����
		if (nums[low] > nums[mid]) 
			sw(nums[low], nums[mid]);
		if (nums[low] > nums[high])
			sw(nums[low], nums[high]);
	}

};