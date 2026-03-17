/*
	許育菖 B113040045
	Octo. 14, 2023
	以linked list處理兩個多項式間的加法和除法
*/

#include <iostream>
#include <iomanip>
using namespace std;

class Node{
	public:
		Node() = default;
		Node(int coef, int exp);
		~Node() = default;
		/*
		coefficient: 係數
		exponent: 指數
		next: 指向 real 方向的下一個 node
		pre: 指向 first 方向的下一個 node
		*/
		int coefficient;
		int exponent;
		Node* next;
		Node* pre;
};

Node::Node(int coef, int exp)
{
	this->coefficient = coef;
	this->exponent = exp;
}

/*-----------------------------------------------------------*/

class List{
	public:
		List(void);
		~List() = default;
		
		//	operator overloading
		List operator + (const List& another);
		List operator * (const List& another);
		void operator = (List& another);
		
		//	將一個 node 加入 list 中，並依指數 exponent 由小(first)到大(real)進行排列
		void insert(int coef, int exp);
		
		//	清空 list 中的所有 node
		void clear(void);
		
		//	依指數 exponent 由大到小印出 list 中的所有 node
		void output(void);
	
	private:		
		//	指向 exponent 最小的 node
		Node* first = nullptr;
		//	指向 exponent 最大的 node
		Node* real = nullptr;
};

List::List(void)
{
	first = nullptr;
	real = nullptr;
}

//	建立一個新的 list ，將兩個 list 的所有 node 輪流 insert 進新的 list 中，最後回傳新的 list
List List::operator + (const List& another)
{
	//	create a new list
	List newList;
	
	//	從real開始，也就是從方程式的最大項將所有node insert進newList
	Node* temp = this->real;
	while(temp != nullptr)
	{
		newList.insert(temp->coefficient, temp->exponent);
		temp = temp->pre;
	}
	
	temp = another.real;
	while(temp != nullptr)
	{
		newList.insert(temp->coefficient, temp->exponent);
		temp = temp->pre;
	}
	
	return newList;
}

//	建立一個新的 list ，將兩個 list 的所有 node 進行乘法：係數coefficient相乘、指數exponent相加
//	並將相乘後的結果 insert 進新的 list 中，最後回傳該 list
List List::operator * (const List& another)
{	
	//	create a new list
	List newList;
	
	//	若其中一個方程式為0，則相乘後結果亦為0，不做任何計算直接回傳
	if(this->first == nullptr || another.first == nullptr)
		return newList;
	
	//	用於遍歷當前 list 的指標
	Node* temp_this = this->real;
	
	//	用於遍歷 another list 的指標
	Node* temp_another;
	
	//	分別將兩個 list 的所有 node 進行乘法運算
	while(temp_this != nullptr)
	{
		temp_another = another.real;
		while(temp_another != nullptr)
		{
			newList.insert( (temp_this->coefficient) * (temp_another->coefficient), (temp_this->exponent) + (temp_another->exponent) );
			temp_another = temp_another->pre;
		}
		temp_this = temp_this->pre;
	}
	
	return newList;
}

//	將 another 中的 first、real儲存的位置存入當前 list中
//	（	因本題無須進行 List A = List B 的運算，只需運算 List C = A + B 和 list D = A * B
//		所以可以直接儲存指標就好，否則要跟operator overloading的寫法一樣，將another list的所有node insert進當前list	）
void List::operator = (List& another)
{
	this->first = another.first;
	this->real = another.real;
}

//	coef: coefficient
//	exp: exponent
//	以傳入的兩參數建立一個新的 node，並將其依指數 exp 由小(first)到大(real)進行排列進 list中
void List::insert(int coef, int exp)
{
	//	係數為0時，直接回傳
	if(coef == 0)
	{
		return;
	}
	//	list為 empty 的情況
	else if(this->first == nullptr)
	{
		Node* temp = new Node(coef, exp);
		temp->next = nullptr;
		temp->pre = nullptr;
		
		this->real = temp;
		this->first = temp;
	}
	else
	{
		/*
		從exponent最小的開始，如果 new Node 的 exponent 比 run_through 指向的 Node的 exponent 還大，則繼續往後尋找
		跳脫迴圈有以下幾種幾況：
			run_through = 空指標nullptr：表示此時以遍歷完整個list，new node的exponent為list中最大的
			
			the exponent of new Node <= run_through->exponent：表示已找到new Node在list中該插入的位置，但還須討論以下情況：
				1、該位置為第一個Node時
				2、new Node與run_through->Node的指數相同時
				3、new Node處於list中間
		*/
		
		//	用於遍歷所有node的指標
		Node* run_through = this->first;
		
		while( run_through != nullptr && exp > (run_through->exponent) )
			run_through = run_through->next;
		
		//	new Node指數為當前方程式中最大時（new Node 在list末端）
		if(run_through == nullptr)
		{
			//	the new Node
			Node* temp = new Node(coef, exp);
			
			temp->pre = this->real; 
			temp->next = this->real->next;	// = nullptr
			
			this->real = temp;
		}
		//	指數相同時，係數相加
		else if(exp == run_through->exponent)
		{
			//	若係數相加 = 0，則進行 desert
			if(run_through->coefficient + coef == 0)
			{
				//	當前list只有一個Node
				if(run_through->next == nullptr && run_through->pre == nullptr)
				{
					this->real = this->first = nullptr;
					delete run_through;
				}
				//	待刪除的Node位於list末端(real)
				else if(run_through->next == nullptr)
				{
					run_through->pre->next = nullptr;
					this->real = run_through->pre;
					delete run_through;
				}
				//	待刪除的Node位於list前端(first)
				else if(run_through->pre == nullptr)
				{
					run_through->next->pre = nullptr;
					this->first = run_through->next;
					delete run_through;
				}
				else
				{
					run_through->next->pre = run_through->next;
					run_through->pre->next = run_through->pre;
					delete run_through;
				}
			}
			else
				run_through->coefficient += coef;
		}
		//	此時 run_through->pre = new Node，new Node->next = run_through
		else
		{
			//	the new Node
			Node* temp = new Node(coef, exp);
			
			//	new Node 的exponent為list中最小時（new Node 在list前端）
			if(run_through == this->first)
			{
				temp->pre = nullptr;
				temp->next = run_through;
				run_through->pre = temp;
				
				this->first = temp;
			}
			//	new Node在list中間
			else
			{
				(run_through->pre) ->next = temp;
				temp->pre = run_through->pre;
				
				temp->next = run_through;
				run_through->pre = temp;
			}
		}
	}
}

//	清空 list 中的所有 node
void List::clear(void)
{
	Node* temp;
	while(this->real != nullptr)
	{
		temp = this->real;
		this->real = this->real->pre;
		delete temp;
	}
	
	this->first = this->real = nullptr;
}

//	依指數 exponent 由大到小印出 list 中的所有 node
void List::output(void)
{
	if(this->first == nullptr)
		cout << setw(2) << 0 << setw(2) << 0 << '\n';
	
	Node* run_through = this->real;
	while(run_through != nullptr)
	{
		cout << setw(2) << run_through->coefficient << setw(2) << run_through->exponent << '\n';
		run_through = run_through->pre;
	}
}

/*-----------------------------------------------------------*/

int main()
{
	List A, B;
	
	//	List A 的輸入Node數
	int input_times_P;
	
	//	List B 的輸入Node數
	int input_times_Q;
	
	//	the index of Case
	int CaseIndex = 1;
	
	
	while(true)
	{
		int coefficient, exponent;
		
		cout << "The terms of function A: ";
		cin >> input_times_P;
		for(int i = 0; i < input_times_P; i++)
		{
			cin >> coefficient >> exponent;
			A.insert(coefficient, exponent);
		}
		
		cout << "The terms of function B: "  ;
		cin >> input_times_Q;
		for(int i = 0; i < input_times_Q; i++)
		{
			cin >> coefficient >> exponent;
			B.insert(coefficient, exponent);
		}
		
		//	end program
		if(input_times_P == 0 && input_times_Q == 0)
		{
			cout << "Program End\n";
			break;
		}
		
		//	List加法運算
		List C = (A + B);
		
		//	List乘法運算
		List D = (A * B);
		
		cout << "\n【Case " << CaseIndex << "】\n";
		cout << "ADD\n";
		C.output();
		
		cout << "MULTIPLY\n";
		D.output();
		
		//	return the memory of lists
		A.clear();	B.clear();
		C.clear();	D.clear();
		
		CaseIndex++;
		
		cout << endl;
	}
	return 0;
}