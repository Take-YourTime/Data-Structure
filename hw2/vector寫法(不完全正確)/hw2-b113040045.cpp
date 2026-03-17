/*
	許育菖 B113040045
	Sept. 19, 2023
	使兩個集合能進行「聯集」、「交集」、「差集」、「包含」、「屬於」等五種運算
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Set{
	public:
		// constructor
		Set() = default;
		Set(string str);
		Set(vector<char> arr);
		
		void printSet(void);
		
		void set_list(char, int);
		
		bool find_key(char);
		
		// operator overloading
		Set operator +(Set another);
		Set operator *(Set another);
		Set operator -(Set another);
		
		bool operator >=(const Set& another);
		void operator =(const Set& another);
		
 
	private:
		vector<char> list;
};


Set::Set(string str)
{
	for(int i = 0; i < str.size(); i++)
		this->list.push_back(str[i]);
}
Set::Set(vector<char> arr)
{
	this->list = arr;
}

void Set::printSet(void)
{
	for(int i = 0; i < this->list.size(); i++)
		cout << list[i];
}

void Set::set_list(char ch, int index)
{
	this->list[index] = ch;
}

bool Set::find_key(char ch)
{
	for(int i = 0; i < this->list.size(); i++)
	{
		if(ch == this->list[i])
			return true;
	}
	
	return false;
}

Set Set::operator +(Set another)
{
	vector<char> newlist;
	newlist = this->list;
	
	for(int i = 0; i < another.list.size(); i++)
	{
		// 字元是空字元NUL時，不進行運算
		if(another.list[i] == '\0')
			continue;
		// 將another字串後相同的字元設為空字元NUL，避免重複運算
		for(int j = i+1; j < another.list.size(); j++)
		{
			if(another.list[i] == another.list[j])
				another.set_list('\0', j);
		}
		
		bool not_include = true;
		
		for(int j = 0; j < this->list.size(); j++)
		{
			if(another.list[i] == this->list[j])
			{
				not_include = false;
				break;
			}	
		}
		
		if(not_include)
			newlist.push_back(another.list[i]);
	}
	
	return Set(newlist);
}

Set Set::operator *(Set another)
{
	vector<char> newlist;
	
	for(int i = 0; i < another.list.size(); i++)
	{
		// 字元是空字元NUL時，不進行運算
		if(another.list[i] == '\0')
			continue;
		// 將another字串後相同的字元設為空字元NUL，避免重複運算
		for(int j = i+1; j < another.list.size(); j++)
		{
			if(another.list[i] == another.list[j])
				another.set_list('\0', j);
		}
		
		bool include = false;
		
		for(int j = 0; j < this->list.size(); j++)
		{
			if(another.list[i] == this->list[j])
			{
				include = true;
				break;
			}	
		}
		
		if(include)
			newlist.push_back(another.list[i]);
	}
	
	return Set(newlist);
}

Set Set::operator -(Set another)
{
	vector<char> newlist;
	
	for(int i = 0; i < this->list.size(); i++)
	{
		bool not_include = true;
		
		for(int j = 0; j < another.list.size(); j++)
		{
			if(this->list[i] == another.list[j])
			{
				not_include = false;
				break;
			}	
		}
		
		if(not_include)
			newlist.push_back(this->list[i]);
	}
	
	return Set(newlist);
}

bool Set::operator >=(const Set& another)
{
	for(int i = 0; i < another.list.size(); i++)
	{	
		bool include = false;
		
		for(int j = 0; j < this->list.size(); j++)
		{
			if(another.list[i] == this->list[j])
			{
				include = true;
				break;
			}	
		}
		
		if(!include)
			return false;
	}
	
	return true;
}

void Set::operator =(const Set& another)
{
	this->list = another.list;
}

/*----------------------------------------------------------------------------------------------------*/

void string_sorting(string& str)
{
	int length = str.size();
	
	// bubble sort
	for(int i = 0; i < length; i++)
	{
		for(int j = 0; j < length-i-1; j++)
		{
			if(str[j] > str[j+1])
				swap(str[j], str[j+1]);
			else
			{
				// 刪除字串中的相同元素
				while(length > 1 && str[j] == str[j+1])
				{
					str.erase(j+1, 1);
					length--;
				}
			}
			
		}
	}
}

int main()
{
	int n;
	cin >> n;
	
	for(int i = 0; i < n; i++)
	{
		string str;
		char key;
		
		cin >> str;
		string_sorting(str);
		Set A(str);
		
		cin >> str;
		string_sorting(str);
		Set B(str);
		
		cin >> key;
		
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