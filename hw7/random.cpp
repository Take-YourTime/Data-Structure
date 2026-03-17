#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream> 

using namespace std;

int main()
{
	//	資料量
	int test_case = 10;
	int data;
	srand(time(nullptr));
	
	//	建立文字檔
	ofstream fout;
	fout.open("input.txt");
	fout << test_case << '\n';
	
	test_case = test_case * 10;
	
	while(test_case)
	{
		//	範圍：0 ~ RAND_MAX - 1
		data = rand() % RAND_MAX;
		fout << data << '\n';
		test_case--;
	}
	
	fout.close();
	return 0;
}
