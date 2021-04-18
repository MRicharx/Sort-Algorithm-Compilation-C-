#include<iostream>
#include<fstream>
#include<chrono>
#include<math.h>
#include<list>

using namespace std;

void bubbleSort(int length, int arr[])
{
	int temp;
	for (int j = 0; j < length; j++)
	{
		for (int k = 0; k < length; k++)
		{
			if (arr[j] < arr[k])
			{
				temp = arr[j];
				arr[j] = arr[k];
				arr[k] = temp;
			}
		}
	}
}

void swap(int &a, int& b)
{
	int t = a;
	a = b;
	b = t;
}

int partition(int arr[], int low, int high)
{
	int pivot = arr[high]; // pivot
	int i = (low - 1); // Index of smaller element

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than the pivot
		if (arr[j] < pivot)
		{
			i++; // increment index of smaller element
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return (i + 1);
}

void quickSort(int high,int low,int arr[])
{
	if (low < high)
	{
		/* pi is partitioning index, arr[pi] is now
		   at right place */
		int pi = partition(arr, low, high);

		quickSort(pi-1, low, arr);  // Before pi
		quickSort(high, pi + 1, arr); // After pi
	}
}

//bool radixSort(int length, int arr[], int d = 0)
//{
//	bool cou = 0;
//	int k = 0;
//	int temp; int T;
//	int div = pow(10, d);
//	for (int i = 0; i <= 9; i++)
//	{
//		for (int j = 0; j < length; j++)
//		{
//			T = (arr[j] / div) % 10;
//			if (T==i&&arr[j]/div>=1)
//			{
//				temp = arr[k];
//				arr[k] = arr[j];
//				arr[j] = temp;
//				k++;
//			}
//		}
//		if (k != 0 && cou==0)
//			cou = true;
//	}
//
//	if(cou==0)
//		return 0;
//	radixSort(length, arr, d + 1);
//}

int getMax(int arr[], int n)
{
	int mx = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > mx)
			mx = arr[i];
	return mx;
}

void countSort(int arr[], int n, int exp)
{
	int *output;
	output = new int(n);// output array 
	int i, count[10] = { 0 };

	// Store count of occurrences in count[] 
	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;

	// Change count[i] so that count[i] now contains actual 
	//  position of this digit in output[] 
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	// Build the output array 
	for (i = n - 1; i >= 0; i--)
	{
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	// Copy the output array to arr[], so that arr[] now 
	// contains sorted numbers according to current digit 
	for (i = 0; i < n; i++)
		arr[i] = output[i];
}

// Radix Sort 
void radixSort(int n, int arr[])
{
	// Find the maximum number to know number of digits 
	int m = getMax(arr, n);

	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(arr, n, exp);
}

void main()
{
	int length;
	int* arr;
	char temp;
	string address;

	//LOOP PENGULANGAN SORT
	//SET i TO 5 TO CHECK ALL ARRAY
	for (int i = 0; i < 1; i++)
	{
		//USE 48 TO TEST FROM ARRAY 0
		temp = i + 49;
		string address = "Array";
		address += temp;
		address += ".txt";

		//READ FILE
		fstream read(address, ios::in);
		if (read.is_open())
		{
			cout << "Percobaan Sorting Dari Array ke-" << i + 1 << endl;
			read >> length;
			arr = new int[length];
			for (int j = 0; j < length; j++)
			{
				read >> arr[j];
			}
		}
		else
		{
			cout << "File Gagal Dibuka" << endl;
			break;
		}


		auto start = chrono::high_resolution_clock::now();

		//BUBBLE SORT
		//bubbleSort(length, arr);

		//QUICK SORT
		int left = 0;
		//quickSort(length,left, arr);

		//RADIX SORT
		radixSort(length, arr);

		chrono::duration<double> elapsed = chrono::high_resolution_clock::now() - start;
		cout << "Duration Taken: " << elapsed.count()<<" s" << endl;
		read.close();


		//OUTPUT CHECK
		for (int j = 0; j < length; j++)
		{
			cout << arr[j] << endl;
		}
	}
}