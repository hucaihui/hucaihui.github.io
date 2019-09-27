#pragma once
#include "abstractSort.h"


/*
简单选择排序
平均情况 最好情况 最坏情况 辅助空间 稳定性
O(n^2)    O(n^2)   O(n^2)    O(1)    稳定
*/
class simpleSelectionSort :public abstractSort
{
public:
	//找到剩下元素的最小元素
	//将该元素交换入指定位置
	void sort(vector<int> &nums) {
		int len = nums.size();
		for (int i = 0; i < len; ++i) {
			int index = i;  //最小元素下标
			for (int j = i + 1; j < len; ++j) {
				if (nums[j] < nums[index]) {   //找出最小元素的下标
					index = j;
				}
			}
			if (index != i) 
				sw(nums[i], nums[index]);
		}
	}
};