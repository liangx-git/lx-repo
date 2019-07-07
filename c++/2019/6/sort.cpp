#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<functional>
#include<utility>


/**
 * 描述：冒泡排序
 * 输入：待排序数据拷贝
 * 输出：排序后数组拷贝
 */
template<typename T>
std::vector<T> bubbleSort(std::vector<T> nums){
	std::size_t len = nums.size();
	for (std::size_t i = 0; i < len; ++i){
		for (std::size_t j = 0; j < len - i - 1; ++j){
			if (nums[j] > nums[j + 1]){
				using std::swap;
				swap<T>(nums[j], nums[j + 1]);
			}
		}
	}
	return nums;
}


/**
 * 描述：插入排序
 * 输入：待排序数据拷贝
 * 输出：排序后数组拷贝
 */
template<typename T>
std::vector<T> insertSort(std::vector<T> nums){

	std::size_t len = nums.size();
	for (std::size_t i = 1; i < len; ++i){	//从下标为1元素开始逐个插入到左侧
		for (std::size_t j = i ; j > 0; --j){
			if (nums[j] < nums[j - 1]){
				using std::swap;
				swap(nums[j], nums[j - 1]);
			}
		}
	}
	return nums;
}


/**
 * 描述：选择排序
 * 输入：待排序数据拷贝
 * 输出：排序后数组拷贝
 */
template<typename T>
std::vector<T> selectSort(std::vector<T> nums){
	std::size_t len = nums.size();
	for (std::size_t i = 0; i < len - 1; ++i){
		for (std::size_t j = i + 1; j < len; ++j){
			if (nums[i] > nums[j]){
				using std::swap;
				swap(nums[i], nums[j]);
			}
		}
	}
	return nums;
}


/**
 * 描述：希尔排序
 * 输入：待排序数据拷贝
 * 输出：排序后数组拷贝
 T*/
template<typename T> 
std::vector<T> shellSort(std::vector<T> nums){
	std::size_t len = nums.size();	
	std::size_t inc = 0;	//排序中的递减增量
	while(inc < len){	//计算增量的初始值
		inc = inc * 3 + 1;
	}

	while (inc > 0){	//增量inc递减为0时排序完成
		for (int i = inc; i < len; ++i){	//对inc至后面元素插入排序
			for (int j = i - inc; j >= 0; j = j - inc){
				if (nums[j] > nums[j + inc]){
					using std::swap;
					swap(nums[j], nums[j + inc]);
				}
			}
		}
		
		inc = (inc - 1) / 3;
	}

	return nums;
}


/**
 * 描述：快速排序
 * 输入：待排序数据拷贝
 * 输出：排序后数组拷贝
 */
template<typename T>
std::size_t partition(std::vector<T> &nums, std::size_t left, std::size_t right){
	int key = nums[left];
	while (left < right){
		while (left < right && nums[right] > key)
			--right;
		if (left < right)
			nums[left++] = nums[right];

		while (left < right && nums[left] < key)
			++left;
		if (left < right)
			nums[right--] = nums[left];
	}
	nums[left] = key;
	return left;
}

template<typename T>
void quickSort(std::vector<T> &nums, std::size_t l, std::size_t r){
	if (l < r){
		int mid = partition(nums, l, r);
		quickSort(nums, l, mid - 1);
		quickSort(nums, mid + 1, r);
	}
}

template<typename T> 
std::vector<T> quickSort(std::vector<T> nums){
	std::size_t len = nums.size();
	quickSort(nums, 0, len - 1);	
	return nums;
}


/**
 * 描述：堆排序
 * 输入：待排序数据拷贝
 * 输出：排序后数组拷贝
 */
template<typename T>
void downAdjust(std::vector<T> &nums, std::size_t len, std::size_t index){

	std::size_t child_index = index * 2 + 1;
	std::size_t parent_index = index; 
	int temp = nums[index];
	while (child_index < len){
		if (child_index + 1 < len && nums[child_index + 1] > nums[child_index]){
			++child_index;
		}

		if (nums[child_index] > temp){
			nums[parent_index] = nums[child_index];
		}else{
			break;
		}

		parent_index = child_index;
		child_index = 2 * child_index + 1;
	}		
	nums[parent_index] = temp;
}


template<typename T>
std::vector<T> heapSort(std::vector<T> nums){
	
	std::size_t len = nums.size();

	//堆序化
	for (int i = (len - 1) / 2; i >= 0; --i){
		downAdjust(nums, len, i);			
	}	
	
	//利用堆序性为数组排序
	for (std::size_t i = 0; i < len; ++i){
		using std::swap;
		swap(nums[0], nums[len - 1 - i]);
		downAdjust(nums, len - 1 - i, 0);
	}
	return nums;
}



template<typename T>
void merge(std::vector<T> &nums, std::size_t left, std::size_t mid, std::size_t right){
	std::vector<T> temp(right - left + 1);
	std::size_t i = left;
	std::size_t j = mid + 1;
	std::size_t k = 0;
	while (i <= mid && j <= right){
		temp[k++] = nums[i] < nums[j] ? nums[i++] : nums[j++];
	}

	while (i <=  mid){
		temp[k++] = nums[i++];
	}

	while (j <= right){
		temp[k++] = nums[j++];
	}
	
	for (int i = 0; i + left <= right; ++i){
		nums[i + left] = temp[i]; 
	}
}


template<typename T>
void mergeSort(std::vector<T> &nums, std::size_t left, std::size_t right){
	if (left < right){
		std::size_t mid = (right + left) / 2;
		mergeSort(nums, left, mid);
		mergeSort(nums, mid + 1, right);
		merge(nums, left, mid, right);
	}	
}


template<typename T>
std::vector<T> mergeSort(std::vector<T> nums){
	std::size_t len = nums.size();	
	mergeSort(nums, 0, len - 1);
	return nums;
}




/**
 * 描述：格式化输出数组元素
 * 输入：
 * 		nums:数组引用
 * 		msg :提示字符串
 */
template<typename T>
void printVector(const std::vector<T> &nums, const std::string &msg){
	std::cout << msg << std::endl; 
	for (auto var : nums){
		std::cout << var << " ";
	}
	std::cout << std::endl << std::endl;
}


int main(){

	std::vector<int> nums = {3, 2, 8, 5, 0, 9, 7, 1, 4, 6};
	printVector(nums, "未排序前:");	
	printVector(bubbleSort(nums), "冒泡排序后：");
	printVector(insertSort(nums), "插入排序后：");
	printVector(selectSort(nums), "选择排序后：");
	printVector(shellSort(nums), "希尔排序后：");
	printVector(quickSort(nums), "快速排序后：");
	printVector(mergeSort(nums), "归并排序后：");
	printVector(heapSort(nums), "堆排序后：");
	return 0;
}
