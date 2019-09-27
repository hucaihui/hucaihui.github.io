#pragma once
#include "abstractSort.h"

/*
希尔排序  -- 插入排序的升级
   平均情况        最好情况  最坏情况 辅助空间  稳定性
O(nlogn)~O(n^2)    O(n^1.3)  O(n^2)     O(1)    不稳定

参考：
[图解算法---希尔排序](https://blog.csdn.net/qq_39207948/article/details/80006224)
[五分钟学会一个高难度算法：希尔排序](https://www.jianshu.com/p/40dcc3b83ddc)
*/
class shellSort :public abstractSort
{
public:
	//将序列排成基本有序
	//跳跃间隔插入   --9 9/2=4 4/2=2 2/1=1
	//其时间复杂度取决于gap(间隔的选择）
	void sort(vector<int> &nums) {
		int len = nums.size();
		for (int gap = len / 2; gap >= 1; gap /= 2) {    //此间隔可变 可尝试gap = gap/3+1 
			for (int i = gap; i < len; i++) {
				int tmp = nums[i];
				int j = i;
				while (j > (gap-1) && tmp < nums[j - gap]) {
					nums[j] = nums[j - gap];
					j -= gap;
				}
				nums[j] = tmp;

				//_insert(nums,gap,i);
			}
		}
	}

private:
	void _insert(vector<int> nums, const int gap, const int pos) {
		//插入排序核心代码
		// -gap 间隔  gap=1时即为直接插入排序
		// -pos 待插入的元素
		int tmp = nums[pos];
		int j = pos;
		while (j >=gap && tmp < nums[j - gap]) {
			nums[j] = nums[j - gap];
			j -= gap;
		}
		nums[j] = tmp;	
	}

};