#include <iostream>
#include <vector>
#include "bubbleSort.h"
#include "simpleSelectionSort.h"
#include "insertSort.h"
#include "shellSort.h"
#include "heapSort.h"
#include "mergeSort.h"
#include "quickSork.h"

using namespace std;


int main() {
	
	vector<int> nums = { 5,4,3,2,1,9,8,7,6,0,10,14,13,12,11};
	
	abstractSort *abs_sort = nullptr;

	//-Ã°ÅÝ bubbleSort1(¼òµ¥)  bubbleSort2(Õý×Ú)  bubbleSort2(Õý×ÚÉý¼¶°æ)
	//abs_sort = new bubbleSort3();

	//-¼òµ¥Ñ¡ÔñÅÅÐò
	//abs_sort = new simpleSelectionSort();

	//-²åÈëÅÅÐò insertSort()
	//abs_sort = new insertSort();

	//-Ï£¶ûÅÅÐò
	//abs_sort = new shellSort();

	//-¶ÑÅÅÐò
	//abs_sort = new heapSort();

	//-¹é²¢ÅÅÐò mergeSort1(µÝ¹é)   mergeSort2(Ñ­»·)
	//abs_sort = new mergeSort2();

	//¿ìËÙÅÅÐò
	abs_sort = new quickSort();


	abs_sort->sort(nums);
	abs_sort->disPlay(nums);

	delete abs_sort;
	system("pause");
	return 0;
}