#pragma once

#include "abstractSort.h"

/*
归并排序
平均情况 最好情况 最坏情况 辅助空间 稳定性
O(nlogn) O(nlogn) O(nlogn)   O(1)   稳定
*/
class mergeSort1 :public abstractSort
{
public:
	//递归实现
	void sort(std::vector<int> &nums) {
		//先拆分，再合并
		int len = nums.size();
		vector<int> res(len);
		merge_sort(nums, res, 0, len - 1);
		nums = res;
		//disPlay(res);
	}
	void merge_sort(vector<int> &nums, vector<int> &res, int s, int e) {
		vector<int> tmp(nums.size());
		if (s == e) {
			res[s] = nums[s];
		} else {
			int m = (s + e) / 2;
			merge_sort(nums, tmp, s, m);
			merge_sort(nums, tmp, m + 1, e);
			merge(tmp, res, s, m, e);
		}
	}

	void merge(vector<int> &nums, vector<int> &res, int s, int m, int e) {
		//-s m e为数组下标
		//两有序数组合并为一个
		int i = s;
		int j = m + 1;
		while (i <= m&&j <= e) {
			res[s++] = nums[i] < nums[j] ? nums[i++] : nums[j++];
		}
		while (i <= m) {
			res[s++] = nums[i++];
		}
		while (j <= e) {
			res[s++] = nums[j++];
		}
	}

};


class mergeSort2 :public abstractSort
{
public:
	//循环实现
	void sort(std::vector<int> &nums) {
		int len = nums.size();
		vector<int> res(len);
		int gap = 1;
		while (gap < len) {
			merge_pass(nums, res, gap, len - 1);
			gap *= 2;    //按1 - 2 - 4 - 8 - 16 - ...
			merge_pass(res, nums, gap, len - 1);
			gap *= 2;
		}
	}
	void merge_pass(vector<int> &nums, vector<int> &res, int gap, int end) {
		//将拆分的子序例依次合并 
		//-gap 间隔
		//-ene 数组末下标
		int i = 0;
		while (i + 2 * gap - 1 <= end) {   //条件：s<=end
			merge(nums, res, i, i + gap - 1, i + 2 * gap - 1);    //s=i m=i+gap-1 e=i+2*gap-1
			i += 2 * gap;    //调试完成后更改
		}
		
		if (i + gap - 1 < end) {   //归并最后两个序列  m<end  
			merge(nums, res, i, i + gap - 1, end);
		} else {		//只剩下一个序列    
			while (i <= end) {
				res[i] = nums[i];
				i++;
			}
		}
		
	}

	void merge(vector<int> &nums, vector<int> &res, int s, int m, int e) {
		//-s m e为数组下标
		//两有序数组合并为一个
		int i = s;
		int j = m + 1;
		while (i <= m&&j <= e) {
			res[s++] = nums[i] < nums[j] ? nums[i++] : nums[j++];
		}
		while (i <= m) {
			res[s++] = nums[i++];
		}
		while (j <= e) {
			res[s++] = nums[j++];
		}
	}
};