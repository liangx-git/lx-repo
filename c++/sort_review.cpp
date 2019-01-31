#include<iostream>
#include<vector>


using namespace std;


void Swap(int &numa, int &numb)
{
	int temp = numa;
	numa = numb;
	numb = temp;
}

void Print(const vector<int> &arr)
{
	int len = arr.size();
	for (int i = 0; i < len; ++i)
	{
		cout << arr[i];
		if (i < len -1)
			cout << ", ";
	}
	cout << endl;
}

//冒泡排序
void BubbleSort(vector<int> arr)
{
	int len = arr.size();
	for (int i = 0; i < len - 1; ++i)
	{
		for (int j = 0; j < len - 1 - i; ++j)
		{
			if (arr[j] > arr[j + 1])
				Swap(arr[j], arr[j + 1]);
		}
	}
	Print(arr);
}

//插入排序
void InsertSort(vector<int> arr)
{
	int len = arr.size();
	for(int i = 1; i < len; ++i)
	{
		for(int j = i - 1; j >= 0; --j)
		{
			if (arr[j + 1] < arr[j])
				Swap(arr[j + 1], arr[j]);
		}
	}
	Print(arr);
}

//选择排序
void SelectSort(vector<int> arr)
{
	int len = arr.size();
	for (int i = 0; i < len; ++i)
	{
		int min = i;
		for (int j = i + 1; j < len; ++j)
		{
			if (arr[j] < arr[min])
				min = j;
		}
		if (min != i)
			Swap(arr[min], arr[i]);
	}
	Print(arr);
}

//希尔排序
void ShellSort(vector<int> arr)
{
	int len = arr.size();

	int h = 0;
	while (h < len)
		h = h * 3 + 1;

	while (h > 0)
	{
		for (int i = h; i < len; ++i)
		{
			//单次选择排序
			for (int j = i - h; j >= 0; j -= h)
			{
				if (arr[j] > arr[j + h])
					Swap(arr[j], arr[j + h]);
			}
		}	
		h = (h - 1) / 3;
	}
	Print(arr);
}

//快速排序
int Partion(vector<int> &arr, int left, int right)
{
	int base = arr[left];
	while (left < right)
	{
		while (left < right && arr[right] > base)
			--right;
		if (left < right)
			arr[left++] = arr[right];
		
		while (left < right && arr[left] < base)
			++left;
		if (left < right)
			arr[right--] = arr[left];
	}
	arr[left] = base;
	return left;
}

void _QuickSort(vector<int> &arr, int left, int right)
{
	if (left < right)
	{
		int base = Partion(arr, left, right);
		_QuickSort(arr, left, base - 1);
		_QuickSort(arr, base + 1, right);
	}
}

void QuickSort(vector<int> arr)
{
	int len = arr.size();
	_QuickSort(arr, 0, len - 1);
	Print(arr);
}

//归并排序
void Merge(vector<int> &arr, int left, int mid, int right)
{
	int len = right - left + 1;
	vector<int> temp(len);
	int i = left; 
	int j = mid + 1;
	int k = 0;
	while (i <= mid && j <= right)
		temp[k++] = arr[i] < arr[j] ? arr[i++] : arr[j++];
	while (i <= mid)
		temp[k++] = arr[i++];
	while (j <= right)
		temp[k++] = arr[j++];
	for (int i = 0; i < len; ++i)
		arr[left++] = temp[i];
}

void _MergeSort(vector<int> &arr, int left, int right)
{
	if (left >= right)
		return;
	int mid = (left + right) / 2;
	_MergeSort(arr, left, mid);
	_MergeSort(arr, mid + 1 , right);
	Merge(arr, left, mid, right);
}

void MergeSort(vector<int> arr)
{
	int len = arr.size();
	_MergeSort(arr, 0, len - 1);
	Print(arr);
}

//归并排序
int GetLeftChild(int parentIndex, int len)
{
	return (parentIndex * 2 + 1) < len ? (parentIndex * 2 + 1) : -1;
}

int GetRightChild(int parentIndex, int len)
{
	return (parentIndex * 2 + 2) < len ? (parentIndex * 2 + 2) : -1;
}

bool HasLeftChild(int parentIndex, int len)
{
	if (GetLeftChild(parentIndex, len) == -1)
		return false;
	return true;
}

bool HasRightChild(int parentIndex, int len)
{
	if (GetRightChild(parentIndex, len) == -1)
		return false;
	return true;
}

void AdjustHeap(vector<int> &arr, int len, int index)
{
	if (!HasLeftChild(index, len))
		return;
	int parentIndex = index;
	int maxIndex;
	while (HasLeftChild(parentIndex, len))
	{
		int leftChildIndex = GetLeftChild(index, len);
		if (HasRightChild(index, len))
		{
			int rightChildIndex = GetRightChild(index, len);
			maxIndex = arr[leftChildIndex] > arr[rightChildIndex] ? leftChildIndex : rightChildIndex;
		}
		else
			maxIndex = leftChildIndex;
		
		if (arr[maxIndex] > arr[index])
		{
			Swap(arr[maxIndex], arr[index]);
			parentIndex = maxIndex;
			continue;
		}
		break;
	}
}

void HeapSort(vector<int> arr)
{
	//创建大根堆
	int len = arr.size();
	for(int i = len / 2 - 1; i >= 0; --i)
	{
		AdjustHeap(arr, len, i);
	}

	for (int i = 0; i < len - 1; ++i)
	{
		Swap(arr[0], arr[len - 1 - i]);
		AdjustHeap(arr, len - 1 - i, 0);
	}
	Print(arr);
}

int main()
{
	vector<int> arr{6, 2, 0, 5, 10, 4, 7};
	cout << "未排序前：" << endl;
	Print(arr);
	
	//冒泡排序后
	cout << "冒泡排序后：" << endl;
	BubbleSort(arr);

	//选择排序后
	cout << "选择排序后：" << endl;
	SelectSort(arr);
	
	//插入排序
	cout << "插入排序后：" << endl;
	InsertSort(arr);

	//希尔排序
	cout << "希尔排序后：" << endl;
	ShellSort(arr);
	
	//快速排序后
	cout << "快速排序后:" << endl;
	QuickSort(arr);

	//归并排序
	cout << "归并排序后：" << endl;
	MergeSort(arr);
	
	//堆排序
	cout << "堆排序后：" << endl;
	HeapSort(arr);

	return 0;
}
