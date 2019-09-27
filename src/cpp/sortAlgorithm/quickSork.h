#pragma once

#include "abstractSort.h"

/*
快速排序  --冒泡排序的升级
平均情况 最好情况 最坏情况 辅助空间 稳定性
O(nlogn) O(nlogn) O(nlogn)   O(1)   不稳定
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
		//尾递归，减少递归深度
		if (low < high) {
			int pivot = partition(nums, low, high);
			quick_sork(nums, low, pivot - 1);
			low = pivot + 1;   
		}
	}
	int partition(vector<int> &nums, int low, int high) {
		if (high - low >= 2) {   //三个数以上
			getMidThreeNum(nums, low, high);
		}
		int pivot = nums[low];   //low  high  low
		while (low < high) { 
			while (low < high&&pivot <= nums[high]) {   //先高后低
				high--;
			}
			nums[low] = nums[high];   //省略不必要的交换
			//sw(nums[low], nums[high]);
			while (low < high&&nums[low] <= pivot) {
				low++;
			}
			nums[high] = nums[low];   
			//sw(nums[low], nums[high]);
		}
		nums[low] = pivot;
		return low;   //while结束时low=high
	}

	void getMidThreeNum(vector<int> &nums, int low, int high) {
		//三数取中
		int mid = low + (high - low) / 2;   //结果与(low+high)/2一样，但可以防溢出
		if (nums[low] > nums[mid]) 
			sw(nums[low], nums[mid]);
		if (nums[low] > nums[high])
			sw(nums[low], nums[high]);
	}

};