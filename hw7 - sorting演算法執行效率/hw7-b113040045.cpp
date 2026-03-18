/*
	許育菖 B113040045
	Nove. 26, 2023
	輸入一串數字，計算各種排序方式所花費的時間
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>

int ARRAY_SIZE = 0;

using namespace std;

typedef int* INTPTR;

/*====================================================================*/

int Composition ( const void * a , const void * b )
{
   return ( * ( int * ) a - * ( int * ) b ) ;
}

/*====================================================================*/

//	insertion sort
void insertion_sort(int arr[], double time)
{
	for(int sort_element = 1; sort_element < ARRAY_SIZE; sort_element++)
	{
		for(int i = sort_element; i >= 1; i--)
		{
			if(arr[i] < arr[i-1])
				swap(arr[i], arr[i-1]);
			else
				break;
		}
		
		if( ((double)clock() - time) / CLOCKS_PER_SEC > 3000.0 )
		{
			cout << "TLE\n";
			exit(0);
		}
	}
}

//	merge the array in merge sort
void merge(int arr[], int head, int mid, int tail, double time)
{
	if( ((double)clock() - time) / CLOCKS_PER_SEC > 3000.0 )
	{
		cout << "TLE\n";
		exit(0);
	}
	
	int len_A = mid - head + 1;
	int len_B = tail - (mid + 1) + 1;
	int* A = new int [len_A];
	int* B = new int [len_B];
	
	//	split the original array
	for(int i = 0; i < len_A; i++)
		A[i] = arr[head + i];
	for(int i = 0; i < len_B; i++)
		B[i] = arr[mid + 1 + i];
	
	
	int i = 0, j = 0;
	int k = head;
	//	將array A和array B的存回原本array中
	//		因為此時A、B中的元素已經由小到大排序好
	//		因此只要比較A、B第一個元素，儲存比較小的元素即可
	//	直到A、B其中一個陣列全部儲存完畢
	while(i < len_A && j < len_B)
	{
		if(A[i] < B[j])
		{
			arr[k] = A[i];
			i++;
		}
		else
		{
			arr[k] = B[j];
			j++;
		}
		k++;
	}
	
	//	將A、B中剩餘的元素儲存回原本的array
	//	(A、B只會有一個陣列還有剩餘的元素)
	while(i < len_A)
	{
		arr[k] = A[i];
		i++;
		k++;
	}
	while(j < len_B)
	{
		arr[k] = B[j];
		j++;
		k++;
	}
	
	delete [] A;
	delete [] B;
}

//	merge sort
void merge_sort(int arr[], int head, int tail, double time)
{
	if( ((double)clock() - time) / CLOCKS_PER_SEC > 3000.0 )
	{
		cout << "TLE\n";
		exit(0);
	}
	
	if(head < tail)
	{
		int mid = (head + tail) / 2;
		merge_sort(arr, head, mid, time);
		merge_sort(arr, mid + 1, tail, time);
		merge(arr, head, mid, tail, time);
	}
}

//	quick sort
void quick_sort(int arr[], const int left, const int right, double time)
{
	if(left < right)
	{
		int i = left, j = right + 1, pivot = arr[left];
		do{
			do{
				i++;
			}
			while(arr[i] < pivot);
			
			do{
				j--;
			}	
			while(arr[j] > pivot);
			
			if(i < j)
				swap(arr[i], arr[j]);
		}while(i < j);
		swap(arr[left], arr[j]);
		
		quick_sort(arr, left, j-1, time);
		quick_sort(arr, j+1, right, time);
	}
}

int main()
{
	//	input array size
	ifstream fin;
	fin.open("input.txt");
	fin >> ARRAY_SIZE;
	
	//	create the 2D array
	INTPTR* arr;
	arr = new INTPTR[10];
	for(int i = 0; i < 10; i++)
		arr[i] = new int[ARRAY_SIZE];
	
	//	input data	
	for(int i = 0; i < 10; i++)
		for(int j = 0; j < ARRAY_SIZE; j++)
			fin >> arr[i][j];
	
	//	choose sorting case
	int sort_case;
	cout << "How do you want to sort the array?\n";
	cout << "\t1 insertion sort\n";
	cout << "\t2 merge sort\n";
	cout << "\t3 quick sort\n";
	cout << "\t4 c++ sort\n";
	cout << "\t5 c qsort\n";
	
	cin >> sort_case;
	
	//	end_time - start_time = the time take on sorting
	double start_time, end_time;
	ofstream fout;
	
	//	一次進行10組
	switch(sort_case)
	{
		//	insertion sort
		case 1:{
			fout.open("outputA.txt");
			fout << "Insertion sort\n\n";
			
			start_time = clock();
			for(int i = 0; i < 10; i++)
			{
				insertion_sort(arr[i], start_time);
			}
			end_time = clock();
			cout << "The execution time of insertion sort is: " << (end_time - start_time) / CLOCKS_PER_SEC << '\n';
			cout << "Avarage time: " << (end_time - start_time) / CLOCKS_PER_SEC / 10 << '\n';
			break;
		}
		//	merge sort
		case 2:{
			fout.open("outputB.txt");
			fout << "Merge sort\n\n";
			
			start_time = clock();
			for(int i = 0; i < 10; i++)
			{
				merge_sort(arr[i], 0, ARRAY_SIZE - 1, start_time);
			}
			end_time = clock();
			cout << "The execution time of insertion sort is: " << (end_time - start_time) / CLOCKS_PER_SEC << '\n';
			cout << "Avarage time: " << (end_time - start_time) / CLOCKS_PER_SEC / 10 << '\n';
			break;
		}
		//	quick sort
		case 3:{
			fout.open("outputC.txt");
			fout << "Quick sort\n\n";
			
			start_time = clock();
			for(int i = 0; i < 10; i++)
			{
				quick_sort(arr[i], 0, ARRAY_SIZE - 1, start_time);
			}
			end_time = clock();
			cout << "The execution time of insertion sort is: " << (end_time - start_time) / CLOCKS_PER_SEC << '\n';
			cout << "Avarage time: " << (end_time - start_time) / CLOCKS_PER_SEC / 10 << '\n';
			break;
		}
		//	c++ sort
		case 4:{
			fout.open("outputD.txt");
			fout << "C++ sort\n\n";
			
			start_time = clock();
			for(int i = 0; i < 10; i++)
			{
				sort(arr[i], arr[i] + ARRAY_SIZE);
			}
			end_time = clock();
			cout << "The execution time of insertion sort is: " << (end_time - start_time) / CLOCKS_PER_SEC << '\n';
			cout << "Avarage time: " << (end_time - start_time) / CLOCKS_PER_SEC / 10 << '\n';
			break;
		}
		//	c qsort
		case 5:{
			fout.open("outputE.txt");
			fout << "C qsort\n\n";
			
			start_time = clock();
			for(int i = 0; i < 10; i++)
			{
				qsort(arr[i], ARRAY_SIZE, sizeof(int), Composition);
			}
			end_time = clock();
			cout << "The execution time of insertion sort is: " << (end_time - start_time) / CLOCKS_PER_SEC << '\n';
			cout << "Avarage time: " << (end_time - start_time) / CLOCKS_PER_SEC / 10 << '\n';

			break;
		}
		default:
			cout << "Wrong sorting_case!\n";
			exit(EXIT_FAILURE);
	}
	
	
	for(int j = 0; j < ARRAY_SIZE; j++)
		fout << arr[0][j] << " ";
	fout << '\n';

	
	fin.close();
	fout.close();
	
	// return memory
	for(int i = 0; i < 10; i++)
		delete [] arr[i];
	delete [] arr;
	
	return 0;
}
