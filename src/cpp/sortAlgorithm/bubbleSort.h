#pragma once
#include "abstractSort.h"

/*
冒泡排序
平均情况 最好情况 最坏情况 辅助空间 稳定性
 O(n^2)    O(n)    O(n^2)    O(1)    稳定
*/
class bubbleSort1:public abstractSort
{
public:
	//冒泡排序最简单版本
	//存在问题是交换过多
	void sort(std::vector<int> &nums) {
		int len = nums.size();
		for (int i = 0; i < len; ++i) {
			for (int j = i ; j < len; ++j) {
				if (nums[i] > nums[j]) {
					sw(nums[i], nums[j]);
				}				
			}
		}
	}
};

class bubbleSort2 :public abstractSort
{
public:
	//冒泡排序正宗版本
	//使每次最小的数字往上浮
	void sort(std::vector<int> &nums) {
		int len = nums.size();
		for (int i = 0; i < len; ++i) {
			for (int j = len - 1; j > i; --j) {     //最后一个元素为nums[len-1]   
				if (nums[j-1] > nums[j]) {
					sw(nums[j-1], nums[j]);
				}
			}
		}
	}
};

class bubbleSort3 :public abstractSort
{
public:
	//冒泡排序正宗版本 改进
	//若序列已经有序
	//则只需比较n-1次即可返回
	void sort(std::vector<int> &nums) {
		int len = nums.size();
		bool flag = true;
		for (int i = 0; i < len && flag; ++i) {
			for (int j = len - 1; j > i; --j) {     //最后一个元素为nums[len-1]   
				flag = false;
				if (nums[j - 1] > nums[j]) {
					sw(nums[j - 1], nums[j]);
					flag = true;  //=true 表示有数据交换
				}
			}
		}
	}
};