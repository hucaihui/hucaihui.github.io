#pragma once

#include "abstractSort.h"

/*
堆排序
平均情况 最好情况 最坏情况 辅助空间 稳定性
O(nlogn) O(nlogn) O(nlogn)   O(1)   不稳定

附：
数组以0开头：父结点：i，左孩子：2*i+1，右孩子：2*i+2
数组以1开头：父结点：i，左孩子：2*i，  右孩子：2*i+1
*/
class heapSort :public abstractSort
{
public:
	//1、建堆
	//2、将最大值与末位交换
	//3、对剩下的元素调整成为最大堆
	void sort(std::vector<int> &nums) {
		int len = nums.size();
		for (int i = (len - 1) / 2; i >= 0; i--) {
			builtMaxHeap(nums, i, len - 1);   //对有孩子的结点进行构造
		}
		disPlay(nums);
		for (int i = len - 1; i > 0; i--) {
			sw(nums[0], nums[i]);
			builtMaxHeap(nums, 0, i-1);       //将剩下的元素保持为大顶堆
		}
	}

	void builtMaxHeap(vector<int> &nums,int p,int end) {
		int tmp = nums[p];
		int i = 2 * p + 1;    //数组以0开头，父结点i,左孩子是2i+1,右孩子是2i+2
		while (i < end) {     //此部分交换类似于插入排序
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
		//builtMaxHeap()简写版本
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