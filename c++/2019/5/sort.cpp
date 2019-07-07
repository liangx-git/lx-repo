#include<iostream>
#include<vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

//冒泡排序
vector<int> BubbleSort(vector<int> nums){
	for (size_t i = 0; i < nums.size() - 1; ++i ){
		for(size_t j = 0; j < nums.size() - 1 - i; ++j){
			if (nums[j + 1] < nums[j]){
				std::swap(nums[j + 1], nums[j]);
			}	
		}
	}
	return nums;
}

//插入排序
vector<int> InsertSort(vector<int> nums){
	for (size_t i = 1; i < nums.size(); ++i){
		for (size_t j = i; j > 0; --j){
			if (nums[j] < nums[j - 1]){
				std::swap(nums[j], nums[j - 1]);
			}
		}	
	}
	return nums;
}

//选择排序
vector<int> SelectSort(vector<int> nums){
	for (size_t i = 0; i < nums.size() - 1; ++i){
		for (size_t j = i + 1; j < nums.size(); ++j){
			if (nums[j] < nums[i]){
				std::swap(nums[j], nums[i]);
			}
		}
	}	
	return nums;
}



void printNums(const vector<int> &nums){
	for (int num : nums){
		cout << num << " ";
	}
	cout << endl;
}




int main (){
	vector<int> nums{8, 3, 7, 9, 4, 2, 1, 5, 6};

	cout << "未排序前：" << endl;
	printNums(nums);

	cout << "冒泡排序：" << endl;
	printNums(BubbleSort(nums));

	cout << "插入排序：" << endl;
	printNums(InsertSort(nums));

	cout << "选择排序：" << endl;
	printNums(SelectSort(nums));

	return 0;
}
