#include<iostream>
#include<vector>


using namespace std;



void Swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

void Print(const vector<int> &arr)
{
	int len = arr.size();
	for (int i = 0; i < len; ++i)
	{
		cout << arr[i];
		if (i < len - 1)
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
		for (int j = 0; j < len - i - 1; ++j)
		{
			if (arr[j] > arr[j + 1])
				Swap(arr[j], arr[j + 1]);
		}
	}
	Print(arr);
}

//选择排序
void SelectSort(vector<int> arr)
{
	int len = arr.size();
	for (int i = 0; i < len - 1; ++i)
	{
		int min = i;
		for (int j = i + 1; j < len; ++j)
		{
			if (arr[j] < arr[min])
				min = j;
		}
		if (min != i)
			Swap(arr[i], arr[min]);
	}
	Print(arr);
}

//插入排序
void InsertSort(vector<int> arr)
{
	int len = arr.size();
	for (int i = 1; i < len; ++i)
	{
		for (int j = i - 1; j >= 0; --j)
		{
			if (arr[j] > arr[j + 1])
				Swap(arr[j], arr[j + 1]);
		}
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
	int key = arr[left];
	while (left < right)
	{
		while (left < right && arr[right] > key)
			--right;
		if (left < right)
			arr[left++] = arr[right];

		while (left < right && arr[left] < key)
			++left;
		if (left < right)
			arr[right--] = arr[left];
	}
	arr[left] = key;
	return left;
}

void _QuickSort(vector<int> &arr, int left, int right)
{
	if (left < right)
	{
		int mid = Partion(arr, left, right);
		_QuickSort(arr, left, mid - 1);
		_QuickSort(arr, mid + 1, right);
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
	int i = left;
	int j = mid + 1;
	int k = 0;
	int len = right - left + 1;
	vector<int> temp(len);
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
	_MergeSort(arr, mid + 1, right);
	Merge(arr, left, mid, right);
}

void MergeSort(vector<int> arr)
{
	int len = arr.size();
	_MergeSort(arr, 0, len - 1);
	Print(arr);
}

#define HEAP_END -1 

//堆排序
bool HasChild(int parent, int len)
{
	return (parent * 2 + 1) < len;
}
int GetLeftChild(int parent, int len)
{
	int leftChild = parent * 2 + 1;
	return 	leftChild < len ? leftChild : -1;
}

int GetRightChild(int parent, int len)
{
	int rightChild = parent * 2 + 2;
	return rightChild < len ? rightChild : -1;
}

void AdjustHeap(vector<int> &arr, int len, int parent)
{
	while (HasChild(parent, len))
	{
		int leftChild = GetLeftChild(parent, len);
		int rightChild = GetRightChild(parent, len);
		int maxChild;
		if (rightChild != HEAP_END)
			maxChild = arr[leftChild] > arr[rightChild] ? leftChild : rightChild;
		else
			maxChild = leftChild;
		
		if (arr[parent] < arr[maxChild])
		{
			Swap(arr[parent], arr[maxChild]);
			parent = maxChild;
		}
		else
		{
			break;
		}
	}
}

void HeapSort(vector<int> arr)
{
	int len = arr.size();

	//创建堆
	for(int i = len / 2 - 1; i >= 0; --i)
	{
		AdjustHeap(arr, len, i);
	}

	//利用堆序性开始排序
	for(int i = 0; i < len - 1; ++i)
	{
		Swap(arr[0], arr[len - 1 - i]);
		AdjustHeap(arr, len - 1 - i, 0);
	}
	Print(arr);
}


int main()
{
	vector<int> arr{7, 3, 9, 4, 0, 18, 3, 2};

	cout << "未排序前：" << endl;
	Print(arr);

	cout << "冒泡排序后：" << endl;
	BubbleSort(arr);

	cout << "选择排序后：" << endl;
	SelectSort(arr);

	cout << "插入排序后：" << endl;
	InsertSort(arr);

	cout << "希尔排序后：" << endl;
	ShellSort(arr);

	cout << "快速排序后：" << endl;
	QuickSort(arr);

	cout << "归并排序后：" << endl;
	MergeSort(arr);

	cout << "堆排序后：" << endl;
	HeapSort(arr);
	return 0;
}
