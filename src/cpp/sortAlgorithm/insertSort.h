#pragma once

#include "abstractSort.h"

/*
插入排序
平均情况 最好情况 最坏情况 辅助空间 稳定性
O(n^2)    O(n)    O(n^2)    O(1)    稳定
*/
class insertSort :public abstractSort
{
public:
	//从第二个元素开始
	//找出已排序序列好的位置
	//大于该元素的后移，该元素插入至该位置
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