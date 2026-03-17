/*
	許育菖 B113040045
	Sept. 19, 2023
	使兩個集合能進行「聯集」、「交集」、「差集」、「包含」、「屬於」等五種運算
*/
#include <iostream>

#define ASCII_LENGTH 127
#define INPUT_ARRAY_LENGTH 200

using namespace std;

class Set{
	public:
		// constructor
		Set();
		Set(char arr[]);
		
		void printSet(void);
		
		bool find_key(char);
		
		// operator overloading
		Set operator +(Set another);
		Set operator *(Set another);
		Set operator -(Set another);
		
		bool operator >=(const Set& another);
		void operator =(const Set& another);
		
 
	private:
		// 以bool陣列表示該字原有沒有在字串中出現
		// bool陣列大小為ASCII code長度
		bool ascii_list[ASCII_LENGTH];
};

// 預設constructor
Set::Set()
{
	for(int i = 0; i < ASCII_LENGTH; i++)
		this->ascii_list[i] = false;
}

// 判斷字串中所出現的字元編號
// 並將對應該編號的布林陣列元素設為true
Set::Set(char arr[])
{
	for(int i = 0; i < ASCII_LENGTH; i++)
		this->ascii_list[i] = false;
	
	for(int i = 0; i < INPUT_ARRAY_LENGTH; i++)
	{
		if(arr[i])
			this->ascii_list[ int(arr[i]) ] = true;
		else
			break;
	}
}

// 將集合Set中擁有的字元按ASCII code順序印出
void Set::printSet(void)
{
	for(int i = 0; i < ASCII_LENGTH; i++)
		if(this->ascii_list[i])
			cout << char(i);
}
// 回傳集合Set中有無特定字元
bool Set::find_key(char ch)
{
	return ( (this->ascii_list[ int(ch) ]) ? true : false );
}

/*-----------------------------------------operator overloading-----------------------------------------------------*/

// 聯集
Set Set::operator +(Set another)
{
	/* 	遍歷 ascii_list 陣列
		將兩個Set含有的字元傳入新的Set並回傳 */
	Set newSet;
	for(int i = 0; i < ASCII_LENGTH; i++)
		if(this->ascii_list[i] || another.ascii_list[i])
			newSet.ascii_list[i] = true;
			
	return newSet;
}

// 交集
Set Set::operator *(Set another)
{
	/* 	遍歷 ascii_list 陣列
		將兩個Set皆含有的字元傳入新的Set並回傳 */
	Set newSet;
	for(int i = 0; i < ASCII_LENGTH; i++)
		if(this->ascii_list[i] && another.ascii_list[i])
			newSet.ascii_list[i] = true;
			
	return newSet;
}

// 差集
Set Set::operator -(Set another)
{
	/* 	遍歷本集合的 ascii_list 陣列
		將 本集合含有 且 another集合未含有 的字元傳入新的Set並回傳 */
	Set newSet;
	for(int i = 0; i < ASCII_LENGTH; i++)
		if(this->ascii_list[i] && another.ascii_list[i] == false)
			newSet.ascii_list[i] = true;
			
	return newSet;
}

// 判斷another集合是否包含在原集合內
bool Set::operator >=(const Set& another)
{
	/* 	遍歷another集合的 ascii_list 陣列
		如果發現 another集合含有 但 本集合沒有 的字元，回傳false
		否則回傳true */
	Set newSet;
	for(int i = 0; i < ASCII_LENGTH; i++)
		if(another.ascii_list[i] == true && this->ascii_list[i] == false)
			return false;
	
	return true;
}

// 清空本集合，並將another集合的值傳入本集合中
void Set::operator =(const Set& another)
{
	for(int i = 0; i < ASCII_LENGTH; i++)
		this->ascii_list[i] = another.ascii_list[i];
}

/*----------------------------------------------------------------------------------------------*/

int main()
{
	// 測試資料組數
	int n;
	cin >> n;
	cin.ignore(); // 清除cin>>的迴車值
	
	for(int i = 0; i < n; i++)
	{
		// 被測試的字串
		char str[INPUT_ARRAY_LENGTH];
		// 被偵測的特定字元
		char key;
		
		cin.getline(str, INPUT_ARRAY_LENGTH); 
		Set A(str);
		
		cin.getline(str, INPUT_ARRAY_LENGTH);
		Set B(str);
		
		cin >> key;
		cin.ignore(); // 清除cin>>的迴車值
		
		Set C = A + B;
		Set D = A * B;
		
		cout << "\nTest Case "<< i+1 << ":\n";
		cout << "A: {";		A.printSet();		cout << "}\n";
		cout << "B: {";		B.printSet();		cout << "}\n";
		cout << "A+B: {";	C.printSet();		cout << "}\n";
		cout << "A*B: {";	D.printSet();		cout << "}\n";
		cout << "A-B: {";	(A-B).printSet();	cout << "}\n";
		cout << "B-A: {";	(B-A).printSet();	cout << "}\n";
		cout << ((A >= B) ? "A contains B\n" : "A does not contain B\n");
		cout << ((B >= A) ? "B contains A\n" : "B does not contain A\n");
		cout << "\'" << key << "\'" << ((A.find_key(key)) ? "is in A\n" : "is not in A\n");
		cout << "\'" << key << "\'" << ((B.find_key(key)) ? "is in B\n\n" : "is not in B\n\n");
	}
	return 0;
}