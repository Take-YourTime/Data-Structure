/*
	許育菖 B113040045
	Octo. 11, 2023
	給定一個 n×n 的棋盤，找到「騎士」走完棋盤的解（以recursion的方式）
*/
#include <iostream>
#include <iomanip>
using namespace std;

typedef int* INTptr;

//	宣告一個全域雙重指標以設置動態二維陣列
INTptr* map;

//	the quantity of non-zero element in the 2D array
int map_went_through;

//	傳入矩陣邊長、當前位置
//	先判斷該走法下一個位置是否會超出地圖邊界，再判斷該位置是否已經走過
//		如果該走法可行，以下一個位置的座標重新呼叫knight()函式
//		如果該走法行不通，繼續判斷下一個走法，直到當前位置的所有走法都判斷行不通後，回傳 false

//	當找到騎士走完整個地圖的解，回傳 true
//		n: the side of the map
//		row, col: location
bool knight(int n, int row, int col)
{
	//	detect finding a answer or not
	if(map_went_through >= n*n)
		return true;
	
	
	// -2, 1
	if( (row-2) >= 0 && (row-2) < n && (col+1) >= 0 && (col+1) < n && map[row-2][col+1] == 0)
	{
		map_went_through++;
		map[row-2][col+1] = map_went_through;
		
		if( knight(n, row-2, col+1) )
			return true;
	}
	// -1, 2
	if( (row-1) >= 0 && (row-1) < n && (col+2) >= 0 && (col+2) < n && map[row-1][col+2] == 0)
	{
		map_went_through++;
		map[row-1][col+2] = map_went_through;
		
		if( knight(n, row-1, col+2) )
			return true;
	}
	// 1, 2
	if( (row+1) >= 0 && (row+1) < n && (col+2) >= 0 && (col+2) < n && map[row+1][col+2] == 0)
	{
		map_went_through++;
		map[row+1][col+2] = map_went_through;
		
		if( knight(n, row+1, col+2) )
			return true;
	}
	// 2, 1
	if( (row+2) >= 0 && (row+2) < n && (col+1) >= 0 && (col+1) < n && map[row+2][col+1] == 0)
	{
		map_went_through++;
		map[row+2][col+1] = map_went_through;
		
		if( knight(n, row+2, col+1) )
			return true;
	}
	// 2, -1
	if( (row+2) >= 0 && (row+2) < n && (col-1) >= 0 && (col-1) < n && map[row+2][col-1] == 0)
	{
		map_went_through++;
		map[row+2][col-1] = map_went_through;
		
		if( knight(n, row+2, col-1) )
			return true;
	}
	// 1, -2
	if( (row+1) >= 0 && (row+1) < n && (col-2) >= 0 && (col-2) < n && map[row+1][col-2] == 0)
	{
		map_went_through++;
		map[row+1][col-2] = map_went_through;
		
		if( knight(n, row+1, col-2) )
			return true;
	}
	// -1, -2
	if( (row-1) >= 0 && (row-1) < n && (col-2) >= 0 && (col-2) < n && map[row-1][col-2] == 0)
	{
		map_went_through++;
		map[row-1][col-2] = map_went_through;
		
		if( knight(n, row-1, col-2) )
			return true;
	}
	// -2, -1
	if( (row-2) >= 0 && (row-2) < n && (col-1) >= 0 && (col-1) < n && map[row-2][col-1] == 0)
	{
		map_went_through++;
		map[row-2][col-1] = map_went_through;
		
		if( knight(n, row-2, col-1) )
			return true;
	}
	
	//	當前位置的所有移動方式都行不通
	map_went_through--;
	map[row][col] = 0;
	return false;
}

int main()
{
	//	n: the side of the 2D array
	for(int n = 1; n <= 6; n++)
	{
		//	create a 2D array
		map = new INTptr[n];
		for(int i = 0; i < n; i++)
		{
			map[i] = new int[n];
			for(int j = 0; j < n; j++)
				map[i][j] = 0;
		}
		
		//	reset variable value
		map_went_through = 1;
		
		//	knight starts from (0, 0)
		map[0][0] = map_went_through;
		
		//	calculate
		bool find_solution = knight(n, 0, 0);
		
		//	output answer
		cout << "[ n = " << n << " ]\n";
		if(find_solution)
		{
			for(int i = 0; i < n; i++)
			{
				for(int j = 0; j < n; j++)
					cout << setw(3) << map[i][j];
				cout << '\n';
			}
			cout << endl;
		}
		else
			cout << "No solution!\n" << endl;
		
		// release the space of the 2D array, and delete it
		for(int i = 0; i < n; i++)
			delete [] map[i];
		delete [] map;
	}
	
	return 0;
}