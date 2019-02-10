#include<iostream>
#include<vector>


using std::cin;
using std::cout;
using std::endl;
using std::vector;


void printNums(const vector<int> &nums)
{
	for (auto num : nums)
	{
		cout << num;
	}
	cout << endl << endl;
}


vector<int> bubbleSort(vector<int> nums)
{
	for (int i = 0; i < nums.size() - 1; ++i)
	{
		for (int j = 0; j < nums.size() - i - 1; ++j)
		{
			if (nums[j] > nums[j + 1])
			{
				using std::swap;
				swap(nums[j], nums[j + 1]);
			}
		}
	}
	return nums;
}


vector<int> insertSort(vector<int> nums)
{
	for (int i = 1; i < nums.size(); ++i)
	{
		for (int j = i; j >= 0; --j)
		{
			if (nums[j] < nums[j - 1])
			{
				using std::swap;
				swap(nums[j], nums[j - 1]);
			}
		}
	}
	return nums;
}


vector<int> selectSort(vector<int> nums)
{
	for (int i = 0; i < nums.size() - 1; ++i)
	{
		int minIndex = i;
		for (int j = i + 1; j < nums.size(); ++j)
		{
			
			if (nums[j] < nums[minIndex])
				minIndex = j;
		}
		if (minIndex != i)
		{
			using std::swap;
			swap(nums[minIndex], nums[i]);
		}
	}
	return nums;
}


vector<int> shellSort(vector<int> nums)
{
	int h = 0;
	while (h < nums.size())
		h = h * 3 + 1;

	while (h > 0)
	{
		for (int i = h; i < nums.size(); ++i)
		{
			//插入排序
			for (int j = i - h; j >= 0; j -= h)
			{
				if (nums[j] > nums[j + h])
				{
					using std::swap;
					swap(nums[j], nums[j + h]);
				}
			}
		}

		h= (h - 1) / 3;
	}
	return nums;
}


void merge(vector<int> &nums, int left, int mid, int right)
{
	int i = left;
	int j = mid + 1;
	int k = 0;
	int len = right - left + 1;
	vector<int> temp(len);
	while (i <= mid && j <= right)
		temp[k++] = nums[i] < nums[j] ? nums[i++] : nums[j++];

	while (i <= mid)
		temp[k++] = nums[i++];

	while (j <= right)
		temp[k++] = nums[j++];

	for (int l = 0; l < len; ++l)
	{
		nums[left + l] = temp[l];
	}

}

void mergeSort(vector<int> &nums, int left, int right)
{
	if (left >= right)
		return;
	int mid = (left + right) / 2;
	mergeSort(nums, left, mid);
	mergeSort(nums, mid + 1, right);
	merge(nums, left, mid, right);
}

vector<int> mergeSort(vector<int> nums)
{
	int len = nums.size();
	mergeSort(nums, 0, len - 1);
	return nums;
}


int partion(vector<int> &nums, int left, int right)
{
	using std::swap;
	int key = nums[left];
	while (left < right)
	{
		
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

void quickSort(vector<int> &nums, int left, int right)
{
	if (left < right)
	{
		int mid = partion(nums, left, right);
		quickSort(nums, left, mid - 1);
		quickSort(nums, mid + 1, right);
	}
}

vector<int> quickSort(vector<int> nums)
{
	int len = nums.size();
	quickSort(nums, 0, len - 1);

	return nums;
}




int main()
{
	vector<int> nums{9, 2, 7, 0, 4, 6, 1};

	cout << "未排序前：";
	printNums(nums);

	cout << "冒泡排序：";
	printNums(bubbleSort(nums));

	cout << "插入排序：";
	printNums(insertSort(nums));	

	cout << "选择排序：";
	printNums(selectSort(nums));

	cout << "希尔排序：";
	printNums(shellSort(nums));

	cout << "归并排序：";
	printNums(mergeSort(nums));

	cout << "快速排序：";
	printNums(quickSort(nums));

	return 0;
}
