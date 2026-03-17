/*
	許育菖 B113040045
	Sept. 12, 2023
	印出 1 到 N 之間所有整數之階乘 ，其中 N < 50
*/
#include <iostream>
using namespace std;

void print_level(int n)
{
	int arr[100] = {0};
	arr[0] = 1;
	
	cout << "1!=" << 1 << '\n';
	
	if(n > 1)
	{
		// 紀錄有幾位數 (第幾個格子後沒有數字)
		int Number_of_digits = 0;
		
		for(int times_number = 2; times_number <= n; times_number++)
		{
			// 乘法運算
			for(int i = 0; i < 100; i++)
			{
				if(i <= Number_of_digits)
					arr[i] *= times_number;
				else
				{
					Number_of_digits = i - 1;
					break;
				}
			}
			
			// 進位
			for(int i = 0; i < 100; i++)
			{
				if(arr[i])
				{
					if(arr[i] >= 10)
					{
						arr[i+1] += (arr[i] / 10);
						arr[i] = arr[i] % 10;
					}
				}
				else if(i <= Number_of_digits)
				{
					if(arr[i] >= 10)
					{
						arr[i+1] += (arr[i] / 10);
						arr[i] = arr[i] % 10;
					}
				}
				else
				{
					Number_of_digits = i - 1;
					break;
				}
			}
			
			// 印出數字
			cout << times_number << "!=";
			for(int i = Number_of_digits; i >= 0; i--)
				cout << arr[i];
			cout << '\n';
		}
	}
	cout << '\n';
}

int main()
{
	int n;
	cin >> n;
	// n = 0時，跳出迴圈
	while(n)
	{
		print_level(n);
		cin >> n;
	}

	return 0;
}
