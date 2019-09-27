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

	//-ð�� bubbleSort1(��)  bubbleSort2(����)  bubbleSort2(����������)
	//abs_sort = new bubbleSort3();

	//-��ѡ������
	//abs_sort = new simpleSelectionSort();

	//-�������� insertSort()
	//abs_sort = new insertSort();

	//-ϣ������
	//abs_sort = new shellSort();

	//-������
	//abs_sort = new heapSort();

	//-�鲢���� mergeSort1(�ݹ�)   mergeSort2(ѭ��)
	//abs_sort = new mergeSort2();

	//��������
	abs_sort = new quickSort();


	abs_sort->sort(nums);
	abs_sort->disPlay(nums);

	delete abs_sort;
	system("pause");
	return 0;
}