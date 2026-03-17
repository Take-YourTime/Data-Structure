/*
	許育菖 B113040045
	Sept. 12, 2023
	印出 N 階的魔方陣
*/
#include <iostream>
#include <iomanip>
using namespace std;

typedef int* INTptr;

void print_magic_square(int N)
{
	// 設置動態二維陣列
	INTptr* arr = new INTptr[N];
	for(int i = 0; i < N; i++)
	{
		arr[i] = new int[N];
		for(int j = 0; j < N; j++)
			arr[i][j] = 0;
	}
	
	int row = 0;
	int col = N/2;
	
	// 計算
	for(int k = 1; k <= N*N; k++)
	{
		arr[row][col] = k;
		
		if(arr[ (row-1+N)%N ][ (col-1+N)%N ]) // +N後才能取正的餘數
			row = (row + 1)%N;
		else
		{
			row = (row-1+N)%N;
			col = (col-1+N)%N;	
		}
	}
	
	// 印出魔方陣
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			cout << setw(3) << arr[i][j];
		}
		cout << '\n';
	}
	
	// 刪除陣列
	for(int i = 0; i < N; i++)
		delete [] arr[i];
	delete [] arr;
}

int main()
{
	cout << "一階魔方陣\n\n";
	print_magic_square(1);
	
	cout << "\n三階魔方陣\n\n";
	print_magic_square(3);
	
	cout << "\n五階魔方陣\n\n";
	print_magic_square(5);
	
	cout << "\n七階魔方陣\n\n";
	print_magic_square(7);
	
	cout << "\n九階魔方陣\n\n";
	print_magic_square(9);
	return 0;
}