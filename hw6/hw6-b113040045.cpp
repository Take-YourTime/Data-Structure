/*
	許育菖 B113040045
	Nove. 10, 2023
	以輸入的資料建立一個Binary tree，最後以inorder的方式將每個節點的data印出
*/
#include <iostream>
#include <vector>
using namespace std;


//	tree node
class Node{
	public:
		Node() = default;
		Node(int n);
		~Node() = default;
		
		friend void insert(int n);
		friend void deleteNode(Node* delete_Node);
		friend void inorder(Node* temp);
	private:
		//	father node
		Node* parent;
		//	son node
		Node* left;
		Node* right;
		
		int number;
};


//	list data
struct Data{
	//	number: current node number
	//	left: left subtree node number
	//	right: right subtree node number
	Node* current;
	int number;
	int left;
	int right;
};


/*-----------------------------------------------------------*/
/*global data*/

//	store output data
vector<Data> list;

//	the root of the tree
Node* root = nullptr;

/*-----------------------------------------------------------*/

Node::Node(int n)
{
	this->number = n;
	this->left = nullptr;
	this->right = nullptr;
}


//	insert a number into the binary tree
void insert(int n)
{
	if(root == nullptr)
	{
		Node* newNode = new Node(n);
		newNode->parent = newNode->left = newNode->right = nullptr;
		root = newNode;
	}
	else
	{
		//	用於走訪二元樹
		Node* visit = root;
		
		//	暫存指標visit的值
		Node* temp = nullptr;
		
		while(visit != nullptr)
		{
			temp = visit;
			if(n == visit->number)
			{
				// delete node
				deleteNode(visit);
				return;
			}
			//	left leaf
			else if(n < visit->number)
				visit = visit->left;
			//	right leaf
			else
				visit = visit->right;
		}
		
		Node* newNode = new Node(n);
		newNode->parent = temp;
		
		if(n < temp->number)
			temp->left = newNode;
		else
			temp->right = newNode;
	}
}


//	刪除特定節點
//	delete_Node: 待刪除的節點
void deleteNode(Node* delete_Node)
{
	//	待刪除節點沒有任何子樹
	if(delete_Node->left == nullptr && delete_Node->right == nullptr)
	{
		if(delete_Node == root)
			root = nullptr;
		else
		{
			if(delete_Node->number < delete_Node->parent->number)
				delete_Node->parent->left = nullptr;
			else
				delete_Node->parent->right = nullptr;
		}
		
		delete delete_Node;
	}
	//	待刪除節點只有右子樹
	else if(delete_Node->left == nullptr)
	{
		if(delete_Node == root)
		{
			root = delete_Node->right;
			delete_Node->right->parent = nullptr;
		}
		else
		{
			if(delete_Node->number < delete_Node->parent->number)
				delete_Node->parent->left = delete_Node->right;
			else
				delete_Node->parent->right = delete_Node->right;
			
			delete_Node->right->parent = delete_Node->parent;
		}
		
		delete delete_Node;
	}
	//	待刪除節點只有左子樹
	else if(delete_Node->right == nullptr)
	{
		if(delete_Node == root)
		{
			root = delete_Node->left;
			delete_Node->right->parent = nullptr;
		}
		else
		{
			if(delete_Node->number < delete_Node->parent->number)
				delete_Node->parent->left = delete_Node->left;
			else
				delete_Node->parent->right = delete_Node->left;
			
			delete_Node->left->parent = delete_Node->parent;
		}
		
		delete delete_Node;
	}
	//	待刪除節點擁有兩個子樹
	else
	{
		/*
			找到待刪除節的右子樹中的擁有最小值的節點
			將該節點的值代入待刪除節點
			
			最後再把擁有最小值的節點刪除
			它有可能發生以上兩種情況之一：沒有子樹、僅有右子樹
			但不會再進入else迴圈中
		*/
		
		//	temp用於找最右子樹中最小的節點
		Node* temp = delete_Node->right;
		while(temp->left != nullptr)
			temp = temp->left;
		
		delete_Node->number = temp->number;
		
		//	刪除最小值的節點
		deleteNode(temp);
	}
}

//	將二元樹中的值以中序表示法存入global list中
void inorder(Node* temp)
{
	if(temp == nullptr)
		return;
	else
	{
		inorder(temp->left);
		
		//	節點資料
		//	(若節點子樹為空，則顯示為0)
		Data data;
		data.current = temp;
		data.number = temp->number;
		data.left = (temp->left == nullptr) ? 0 : (temp->left->number);
		data.right = (temp->right == nullptr) ? 0 : (temp->right->number);
		
		list.push_back(data);
		
		inorder(temp->right);
	}
}

int main()
{
	//	the input number
	int n;
	list.clear();
	
	do
	{
		//	input
		while( (cin >> n) && (n != -1) )
		{
			insert(n);
		}
		
		// end program
		if(cin.eof())
			return 0;
		
		//	sort
		inorder(root);
		
		//	output
		cout << "node:";
		for(int i = 0; i < list.size(); i++)
			cout << " " << list[i].number;
		cout << '\n';
		
		cout << "left:";
		for(int i = 0; i < list.size(); i++)
			cout << " " << list[i].left;
		cout << '\n';
		
		cout << "right:";
		for(int i = 0; i < list.size(); i++)
			cout << " " << list[i].right;
		cout << '\n' << endl;
		
		//	clear
		for(int i = 0; i < list.size(); i++)
			delete list[i].current;
		root = nullptr;
		list.clear();
		
	}while(true);
}
