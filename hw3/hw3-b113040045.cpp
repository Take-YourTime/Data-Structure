/*
	許育菖 B113040045
	Octo. 06, 2023
	給定一個 n×n 的棋盤，找到「騎士」走完棋盤的解
*/

#include <iostream>
#include <iomanip>
using namespace std;

class Stack{
	public:
		Stack() = default;
		
		//	i: row of knight's location
		//	j: col of knight's location
		//	position: the way how knight moved to the new location
		int i;
		int j;
		char position;
		
		//	next data
		Stack* next;
};

Stack* top = nullptr;

//	刪除 stack 最頂端的data
void pop(void)
{
	if(top == nullptr)
	{
		cout << "The stack is empty!\n";
		return;
	}
	
	Stack* delete_node = top;
	top = top->next;
	
	delete [] delete_node;
}

// 	將資料放入stack
//		newnode_i: row of knight's location
//		newnode_j: col of knight's location
//		newnode_position : the way how knight moved to the new location
void push(int newnode_i, int newnode_j, char newnode_position)
{
	Stack* temp = new Stack;
	temp->i = newnode_i;
	temp->j = newnode_j;
	temp->position = newnode_position;
	
	temp->next = top;
	top = temp; 
}


int main()
{
	/*
		n = 1 和 n = 2 是特別情況
		可以明顯看出 n = 1 有唯一解
		而 n = 2 因為邊長小於騎士移動的最長軸，因而無解
	*/
	
	// n: the side of map
	for(int n = 1; n <= 6; n++)
	{
		// clear the stack
		while(top != nullptr)
			pop();
		
		cout << "【n = " << n << "】\n";
		
		int map[n][n];
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				map[i][j] = 0;
		
		//	the quantity of non-zero map-element
		int map_went_through = 1;
		map[0][0] = map_went_through;
		
		//	knight's location
		int row = 0, col = 0;
		
		//	knight's moving method
		char mode = 'a';
		
		//	false → there is a solution		true: no solution
		bool noAnswer = false;
		
		/*
			騎士的移動方式共有八種，以 a~h 作為代號
			騎士每到一個新的位置時，都先從移動方式 a 開始作判斷：
				如果此移動方式可行， push當前位置和移動方式，並移動騎士到下一個新位置 
				如果不行則繼續判斷下一種移動方式的可行性，直到移動方式 h
			
			當移動方式 h 也行不通時，代表當前的位置不能繼續移動了，退回到移動方式還沒全部確認的位置
				如果所有位置的移動方式都確認行不通時，此棋盤無解
				如果 map_went_throw = n * n 時，表示騎士已走遍整個棋盤，找到此棋盤的解
		*/
		while(map_went_through < n*n)
		{
			//	先判斷移動終點是否超出地圖邊界，再判斷該位置是否已經走過
			switch(mode)
			{
			case 'a':	// -2, 1
				if( (row-2) >= 0 && (row-2) < n && (col+1) >= 0 && (col+1) < n && map[row-2][col+1] == 0)
				{
					push(row, col, 'a');
					
					row -= 2;
					col += 1;
					mode = 'a';
					map_went_through++;
					map[row][col] = map_went_through;
					
					continue;
				}
			case 'b':	// -1, 2
				if( (row-1) >= 0 && (row-1) < n && (col+2) >= 0 && (col+2) < n && map[row-1][col+2] == 0)
				{
					push(row, col, 'b');
					
					row -= 1;
					col += 2;
					mode = 'a';
					map_went_through++;
					map[row][col] = map_went_through;
					
					continue;
				}
			case 'c':	// 1, 2
				if( (row+1) >= 0 && (row+1) < n && (col+2) >= 0 && (col+2) < n && map[row+1][col+2] == 0)
				{
					push(row, col, 'c');
					
					row += 1;
					col += 2;
					mode = 'a';
					map_went_through++;
					map[row][col] = map_went_through;
					
					continue;
				}
			case 'd':	// 2, 1
				if( (row+2) >= 0 && (row+2) < n && (col+1) >= 0 && (col+1) < n && map[row+2][col+1] == 0)
				{
					push(row, col, 'd');
					
					row += 2;
					col += 1;
					mode = 'a';
					map_went_through++;
					map[row][col] = map_went_through;
					
					continue;
				}
			case 'e':	// 2, -1
				if( (row+2) >= 0 && (row+2) < n && (col-1) >= 0 && (col-1) < n && map[row+2][col-1] == 0)
				{
					push(row, col, 'e');
					
					row += 2;
					col -= 1;
					mode = 'a';
					map_went_through++;
					map[row][col] = map_went_through;
					
					continue;
				}
			case 'f':	// 1, -2
				if( (row+1) >= 0 && (row+1) < n && (col-2) >= 0 && (col-2) < n && map[row+1][col-2] == 0)
				{
					push(row, col, 'f');
					
					row += 1;
					col -= 2;
					mode = 'a';
					map_went_through++;
					map[row][col] = map_went_through;
					
					continue;
				}
			case 'g':	// -1, -2
				if( (row-1) >= 0 && (row-1) < n && (col-2) >= 0 && (col-2) < n && map[row-1][col-2] == 0)
				{
					push(row, col, 'g');
				
					row -= 1;
					col -= 2;
					mode = 'a';
					map_went_through++;
					map[row][col] = map_went_through;
					
					continue;
				}
			case 'h':	// -2, -1
				if( (row-2) >= 0 && (row-2) < n && (col-1) >= 0 && (col-1) < n && map[row-2][col-1] == 0)
				{
					push(row, col, 'h');
					
					row -= 2;
					col -= 1;
					mode = 'a';
					map_went_through++;
					map[row][col] = map_went_through;
					
					continue;
				}
				//	當前位置的所有移動方式都行不通
				else
				{
					//	如果此時 stack 是空的，表示已經試過所有走法，但沒有找到答案
					if(top == nullptr)
					{
						cout << "No solution!\n";
						break;
					}
					
					//	如果上一步的所有移動方式也都確認行不通
					//	繼續退回上一步，直到退回還沒全部確認完的位置
					//	如果所有位置的移動方式都確認行不通，此棋盤無解
					while(top->position == 'h')
					{
						map[row][col] = 0;
						row = top->i;
						col = top->j;
						
						map_went_through--;
						pop();
						
						//	此處 pop 後不需要判斷 stack 是否為空的
						//	因為起始點必定不能以移動方式 h 走到下一步
					}
					
					map[row][col] = 0;
					row = top->i;
					col = top->j;
					
					mode = char( (top->position) + 1 );
					map_went_through--;
					pop();
					continue;
				}
			default:
				cout << "wrong mode!\n";
				break;
			}
			
			noAnswer = true;
			break;
		}
		
		//	There is a answer
		if(!noAnswer)
		{
			//	output the map
			for(int i = 0; i < n; i++)
			{
				for(int j = 0; j < n; j++)
					cout << setw(3) << map[i][j];
				cout << '\n';
			}	
		}
		cout << '\n';
	}
	
	return 0;
}