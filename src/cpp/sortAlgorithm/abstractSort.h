#pragma once

#include <vector>
using namespace std;

class abstractSort
{
public:
	virtual void sort(vector<int> &nums) = 0;

	void disPlay(const vector<int> &nums) {
		for (auto iter = nums.begin(); iter != nums.end(); ++iter) cout << *iter << " ";
		//for (auto num : nums) cout << num << " ";
		cout << endl;
	}
protected:
	void sw(int &a, int &b) {
		int tmp = a;
		a = b;
		b = tmp;
	}
};

