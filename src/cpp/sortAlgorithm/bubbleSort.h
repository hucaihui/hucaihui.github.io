#pragma once
#include "abstractSort.h"

/*
ð������
ƽ����� ������ ���� �����ռ� �ȶ���
 O(n^2)    O(n)    O(n^2)    O(1)    �ȶ�
*/
class bubbleSort1:public abstractSort
{
public:
	//ð��������򵥰汾
	//���������ǽ�������
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
	//ð���������ڰ汾
	//ʹÿ����С���������ϸ�
	void sort(std::vector<int> &nums) {
		int len = nums.size();
		for (int i = 0; i < len; ++i) {
			for (int j = len - 1; j > i; --j) {     //���һ��Ԫ��Ϊnums[len-1]   
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
	//ð���������ڰ汾 �Ľ�
	//�������Ѿ�����
	//��ֻ��Ƚ�n-1�μ��ɷ���
	void sort(std::vector<int> &nums) {
		int len = nums.size();
		bool flag = true;
		for (int i = 0; i < len && flag; ++i) {
			for (int j = len - 1; j > i; --j) {     //���һ��Ԫ��Ϊnums[len-1]   
				flag = false;
				if (nums[j - 1] > nums[j]) {
					sw(nums[j - 1], nums[j]);
					flag = true;  //=true ��ʾ�����ݽ���
				}
			}
		}
	}
};