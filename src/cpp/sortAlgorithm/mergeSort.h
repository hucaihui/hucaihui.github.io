#pragma once

#include "abstractSort.h"

/*
�鲢����
ƽ����� ������ ���� �����ռ� �ȶ���
O(nlogn) O(nlogn) O(nlogn)   O(1)   �ȶ�
*/
class mergeSort1 :public abstractSort
{
public:
	//�ݹ�ʵ��
	void sort(std::vector<int> &nums) {
		//�Ȳ�֣��ٺϲ�
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
		//-s m eΪ�����±�
		//����������ϲ�Ϊһ��
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
	//ѭ��ʵ��
	void sort(std::vector<int> &nums) {
		int len = nums.size();
		vector<int> res(len);
		int gap = 1;
		while (gap < len) {
			merge_pass(nums, res, gap, len - 1);
			gap *= 2;    //��1 - 2 - 4 - 8 - 16 - ...
			merge_pass(res, nums, gap, len - 1);
			gap *= 2;
		}
	}
	void merge_pass(vector<int> &nums, vector<int> &res, int gap, int end) {
		//����ֵ����������κϲ� 
		//-gap ���
		//-ene ����ĩ�±�
		int i = 0;
		while (i + 2 * gap - 1 <= end) {   //������s<=end
			merge(nums, res, i, i + gap - 1, i + 2 * gap - 1);    //s=i m=i+gap-1 e=i+2*gap-1
			i += 2 * gap;    //������ɺ����
		}
		
		if (i + gap - 1 < end) {   //�鲢�����������  m<end  
			merge(nums, res, i, i + gap - 1, end);
		} else {		//ֻʣ��һ������    
			while (i <= end) {
				res[i] = nums[i];
				i++;
			}
		}
		
	}

	void merge(vector<int> &nums, vector<int> &res, int s, int m, int e) {
		//-s m eΪ�����±�
		//����������ϲ�Ϊһ��
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