/*	c++ version : -std=c++17	*/
/*
	許育菖 B113040045
	Dec. 29, 2023
	1、以huffman algorithm將輸入的檔案壓縮	2、將已壓縮的檔案解壓縮回原檔
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <filesystem>
#include <climits>

using namespace std;

/*COMMAND*/
//	hw8-b113040045 -c -i data.bin -o data2.bin
//	hw8-b113040045 -u -i data2.bin -o data3.txt

//	hw8-b113040045 -c -i a.txt -o a2.bin
//	hw8-b113040045 -u -i a2.bin -o a3.txt

//	hw8-b113040045 -c -i b.txt -o b2.bin
//	hw8-b113040045 -u -i b2.bin -o b3.txt

//	hw8-b113040045 -c -i c.txt -o c2.bin
//	hw8-b113040045 -u -i c2.bin -o c3.txt

//	hw8-b113040045 -c -i d.jpg -o d2.bin
//	hw8-b113040045 -u -i d2.bin -o d3.jpg

class Node {
public:
	Node() = default;
	Node(unsigned char c, int f)
	{
		ch = c;
		frequency = f;
		parent = leftChild = rightChild = nullptr;
	};
	Node(int f)
	{
		frequency = f;
		parent = leftChild = rightChild = nullptr;
	}

	Node* parent;
	Node* leftChild;
	Node* rightChild;

	unsigned char ch;
	int frequency;
	string code;
};

/*-----------------global value-----------------------*/

bool ONE = true;
bool ZERO = false;

class Node* root = nullptr;

/*----------------------------------------------------*/

//	use for "sort" function
bool comp(Node* a, Node* b)
{
	return (a->frequency) < (b->frequency);
}

//	以前序遍歷huffman tree，並為每個節點設置Huffman code
void preorder(Node* temp, string str, int& outputfile_size, int frequency[])
{
	if (temp != nullptr)
	{
		temp->code = str;
		if (temp->ch != '\0')
		{
			outputfile_size += str.size() * frequency[int(temp->ch)];
		}

		preorder(temp->leftChild, str + '0', outputfile_size, frequency);
		preorder(temp->rightChild, str + '1', outputfile_size, frequency);
	}
}

//	use postorder to clear the tree
void delete_tree(Node* temp)
{
	if (temp->leftChild)
		delete_tree(temp->leftChild);
	if (temp->rightChild)
		delete_tree(temp->rightChild);
	delete temp;
}

//	將一個位元輸入進byte的第一位
//		bitValue = 1, input 1
//		bitValue = 0, input 0
void setBit(unsigned char& byte, int bitValue) {
	// 左移1位
	byte = byte << 1;

	// 將bit讀進byte中
	byte |= bitValue;
}

int main(int argc, char* argv[])
{
	//	檢測是否有命令列
	bool cmd = false;
	//	命令列處理
	if (argc > 1)
	{
		cmd = true;
		cout << "CMD: ";
		for (int i = 0; i < argc; i++)
			cout << argv[i] << " ";
		cout << "\n";
	}

	//	功能選擇
	char mode;

	//	寫入檔案
	ofstream out_t_f;

	//	讀取檔案
	ifstream in_f_f;
	while (true)
	{
		if (cmd)
		{
			if (strcmp(argv[1], "-c") == 0)
				mode = '2';
			else if (strcmp(argv[1], "-u") == 0)
				mode = '3';
		}
		else
		{
			cout << "What do you want to do?\n";
			cout << "\t0. End program.\n";
			cout << "\t1. Create a new file and wirte it.\n";
			cout << "\t2. Compress a file.\n";
			cout << "\t3. Extraction a file.\n";
			cin >> mode;
			if (cin.eof())
				exit(EXIT_SUCCESS);
		}

		switch (mode)
		{
		//	End program
		case '0': {
			cout << "Program end!\n";
			exit(EXIT_SUCCESS);
		}
		//	Write words into a binary file
		case '1': {
			//	create a file and set the name of file
			cout << "Please input the name of the file: ";
			string file_name;
			cin >> file_name;
			out_t_f.open(file_name, ios::out | ios::binary);
			if (!out_t_f.is_open())
			{
				cout << "Can't create the file: " << file_name << '\n';
				exit(EXIT_FAILURE);
			}

			//	write into the file
			cout << "Input to the file until input a line only has \'-\'\n";
			char ch;
			cin.ignore();
			while ((ch = cin.get()) && ch != '-')
				out_t_f.write(reinterpret_cast<char*> (&ch), sizeof(ch));

			cout << "File created.\n";
			out_t_f.close();
			break;
		}
		//	Compress a file
		case '2': {
			/*	binary讀檔  → 以vector article儲存檔案資料，以int陣列紀錄每個字元出現的次數
							→ 為每個「有出現過」的字元建立tree Node，每個Node儲存「該字元」及其「出現過的次數」
							→ 將所有的Node依出現次數由小到大存入vector list和vector leaf_node_list

							→ 取最前方的兩個Node相加，並以相加後的值建立NewNode，NewNode為最前方兩個Node的parent
							→ 將NewNode push進vector list，並將除最前方兩個Node外的所有Node(包含NewNode)由小到大進行排序
							→ 重複上一步，直到可排序的Node只剩一個(root)，完成建立huffman tree

							→ preorder遍歷huffman tree，為每個leaf Node中的字元編上huffman code

							→ 將檔頭資料寫入壓縮檔
							→ 遍歷vector leaf_node_list，將每個「字元」、「該字元的huffman code長度」以及「該字元的huffman code」寫入壓縮檔
							→ 將vector article中的每個字元依照其huffman code寫入壓縮檔中(每個bit需先讀取進一個char變數中，讀取完8bits後才能寫進壓縮檔，c++真麻煩==)
							→ 將最後一個char變數中不足8bits的部分補上0，寫入最後一個byte，完成檔案壓縮
			*/

			cout << "Whitch file do you want to compress?\n";
			cout << "\tCompressed file name: ";
			string file_name = "";
			if (cmd)
			{
				file_name = string(argv[3]);
				cout << file_name << '\n';
			}
			else
				cin >> file_name;

			in_f_f.open(file_name, ios::in | ios::binary);
			if (!in_f_f.is_open())
			{
				cout << "Can't open the file: " << file_name << '\n';
				exit(EXIT_FAILURE);
			}

			//	get the size of input file
			int input_file_size = std::filesystem::file_size(file_name);

			//	calculate frequency
			int frequency[UCHAR_MAX + 1] = { 0 };

			//	input character
			unsigned char ch;
			//	store the input data
			vector<unsigned char> article;

			//	input from the file
			while (in_f_f.read(reinterpret_cast<char*>(&ch), sizeof(ch)))
			{
				if (in_f_f.eof())
					break;
				article.push_back(ch);
				frequency[int(ch)] += 1;
			}
			in_f_f.close();

			//	record the charctor which appear frequency is larger than zero
			vector<Node*> list;
			vector<Node*> leaf_node_list;
			for (int i = 0; i < UCHAR_MAX + 1; i++)
			{
				if (frequency[i] > 0)
				{
					Node* newNode = new Node(char(i), frequency[i]);
					list.push_back(newNode);
					leaf_node_list.push_back(newNode);
				}
			}

			//	sorting:  small to big
			sort(list.begin(), list.end(), comp);


			//	create a huffman tree;
			int index = 0;
			while (index < list.size() - 1)
			{
				Node* newNode = new Node('\0', list[0 + index]->frequency + list[1 + index]->frequency);
				newNode->parent = nullptr;
				newNode->leftChild = list[0 + index];
				newNode->rightChild = list[1 + index];

				list[0 + index]->parent = newNode;
				list[1 + index]->parent = newNode;

				//	push新增的節點
				list.push_back(newNode);
				index += 2;

				sort(list.begin() + index, list.end(), comp);
				//	( 	If we use insertion sort at here, the program will be more efficient,
				//		since the new node is generated by the two smallest nodes in the sequence.
				//		However, I was lazy.	)
			}

			root = list[list.size() - 1];

			int output_file_size = 0;

			//	設置每個節點的編碼表
			preorder(root, "", output_file_size, frequency);

			cout << "The name of new compressed file: ";
			string file_name2;
			if (cmd)
			{
				file_name2 = string(argv[5]);
				cout << file_name2 << '\n';
				cmd = false;
			}
			else
				cin >> file_name2;
			out_t_f.open(file_name2, ios::out | ios::binary);
			if (!out_t_f.is_open())
			{
				cout << "Can't create the file: " << file_name2 << '\n';
				exit(EXIT_FAILURE);
			}
		
			//	output the head of file
			cout << "[Compressed File Head]\n";
			
			//	原始檔案大小
			out_t_f.write(reinterpret_cast<char*> (&input_file_size), sizeof(input_file_size));
			cout << "\tInput file size: " << input_file_size << " bits\n";
			
			//	壓縮後檔案大小
			//		檔案結尾補0數量
			cout << "\tCompressed file size(No filehead): " << output_file_size / 8 << " bits\n";
			output_file_size += (output_file_size % 8);
		
			//		檔頭大小
			output_file_size += (8 * sizeof(int)) * 4;
			
			//		字元編碼大小
			for (int i = 0; i < leaf_node_list.size(); i++)
				output_file_size += (8 + 8 * sizeof(int) + (8 * sizeof(bool)) * leaf_node_list[i]->code.size());
			out_t_f.write(reinterpret_cast<char*> (&output_file_size), sizeof(output_file_size));
			cout << "\tCompressed file size: " << output_file_size / 8 << " bit\n";
			
			//	壓縮率
			int rate = (output_file_size * 100) / (input_file_size * 8);
			out_t_f.write(reinterpret_cast<char*> (&rate), sizeof(rate));
			cout << "\tCompressed rate: " << rate << "%\n";
			
			//	編碼字元數
			int key_code_quantity = leaf_node_list.size();
			out_t_f.write(reinterpret_cast<char*> (&key_code_quantity), sizeof(key_code_quantity));
			cout << "\tKey huffman character quantity: " << key_code_quantity << " bits\n";

			//	字元編碼表
			cout << "\tCompressed code:\n";
			cout << "\t(character | huffman compression code)\n";
			for (int i = 0; i < leaf_node_list.size(); i++)
			{
				//	印出字元編碼表
				cout << "\t\t";
				for (int j = 7; j >= 0; j--)
					cout << (((leaf_node_list[i]->ch) >> j) & 1);
				cout << " " << leaf_node_list[i]->code << '\n';

				/* 輸出字元編碼表到檔案中 */
				//	字元
				out_t_f.write(reinterpret_cast<char*> (&(leaf_node_list[i]->ch)), sizeof(leaf_node_list[i]->ch));

				//	字元的huffman code長度
				int length = leaf_node_list[i]->code.length();
				out_t_f.write(reinterpret_cast<char*> (&length), sizeof(int));

				//	huffman code
				for (auto j : leaf_node_list[i]->code)
				{
					(j == '0') ? (out_t_f.write(reinterpret_cast<char*> (&ZERO), sizeof(bool))) : (out_t_f.write(reinterpret_cast<char*> (&ONE), sizeof(bool)));
				}
			}

			//	count = 8, output a character
			unsigned char byte = '\0';
			int count = 0;

			//	output compressed information
			for (int k = 0; k < article.size(); k++)
			{
				//	將每個字元的huffman編碼寫入壓縮檔
				for (int i = 0; i < leaf_node_list.size(); i++)
				{
					if (leaf_node_list[i]->ch == article[k])
					{
						for (auto j : leaf_node_list[i]->code)
						{
							(j == '0') ? setBit(byte, 0) : setBit(byte, 1);
							if (count == 7)
							{
								out_t_f.write(reinterpret_cast<char*> (&byte), sizeof(char));
								count = 0;
								byte = '\0';
							}
							else
								count++;
						}
					}
				}
			}

			//	最後一個輸出字元，不足的8bits的部分補上0
			byte = byte << (8 - count);
			//	輸出最後8bits
			out_t_f.write(reinterpret_cast<char*> (&byte), sizeof(char));

			out_t_f.close();
			delete_tree(root);
			root = nullptr;
			cout << "Finfish compression!\n";
			break;
		}
		//	Extration a file
		case '3': {
			/*
				binary模式讀取壓縮檔	→ 讀取檔頭資料(input_file_size, output_file_size, compression rate, key_code_quantity)
									
									→ 依key_code_quantity的值，讀取接下來的huffman編碼表
									→ 每次依序讀取「字元」、「字元的huffman code長度」、「字元的huffman code」
									→ 每讀取完一次，便建立一個tree Node，同時依照該字元的huffman code將Node放入huffman tree中

									→ 讀取壓縮後的檔案資料，並從tree root開始走訪huffman tree
									→ 遇到leaf Node時，將該Node儲存的字元輸出至解壓縮檔中，並重新從root開始走訪tree
									→ 直到檔案結尾，完成解壓縮
			*/
			cout << "Whitch file do you want to extract?\n";
			cout << "\tExtraction file name: ";
			string file_name;
			if (cmd)
			{
				file_name = string(argv[3]);
				cout << file_name << '\n';
			}
			else
				cin >> file_name;

			in_f_f.open(file_name, ios::in | ios::binary);
			if (!in_f_f.is_open())
			{
				cout << "Can't open the file: " << file_name << '\n';
				exit(EXIT_FAILURE);
			}

			//	read the head of file
			//	原始檔案大小
			int input_file_size = 0;
			in_f_f.read(reinterpret_cast<char*> (&input_file_size), sizeof(input_file_size));
			//	壓縮後檔案大小
			int output_file_size = 0;
			in_f_f.read(reinterpret_cast<char*> (&output_file_size), sizeof(output_file_size));
			//	壓縮率
			int rate = 0;
			in_f_f.read(reinterpret_cast<char*> (&rate), sizeof(rate));
			//	編碼字元數
			int key_code_quantity = 0;
			in_f_f.read(reinterpret_cast<char*> (&key_code_quantity), sizeof(key_code_quantity));

			cout << "[File Head]\n";
			cout << "\tInput file size: " << input_file_size << " bits\n";
			cout << "\tCompressed file size: " << output_file_size / 8 << " bits\n";
			cout << "\tCompressed rate: " << rate << "%\n";
			cout << "\tKey huffman character quantity: " << key_code_quantity << " bits\n";
			
			
			//	set a new huffman tree
			root = new Node();
			root->ch = '\0';
			root->parent = root->leftChild = root->rightChild = nullptr;

			//	use for input form file
			unsigned char ch;

			//	input the huffman code from file and recreate the huffman tree
			while (key_code_quantity > 0)
			{
				in_f_f.read(reinterpret_cast<char*> (&ch), sizeof(char));

				int length;
				in_f_f.read(reinterpret_cast<char*> (&length), sizeof(int));

				//	the element of huffman code
				unsigned char single_code;

				//	huffman code
				string code = "";

				//	暫存前一個處理的node的address
				Node* pre = root;

				while (length > 0)
				{
					in_f_f.read(reinterpret_cast<char*> (&single_code), sizeof(single_code));

					if (single_code == false)
					{
						code += "0";

						if (pre->leftChild == nullptr)
						{
							Node* temp = new Node();
							temp->parent = pre;
							temp->leftChild = temp->rightChild = nullptr;
							pre->leftChild = temp;

							if (length == 1)
							{
								temp->ch = ch;
							}
							else
							{
								temp->ch = '\0';
								pre = temp;
							}
						}
						else
							pre = pre->leftChild;
					}
					else
					{
						code += "1";

						if (pre->rightChild == nullptr)
						{
							Node* temp = new Node();
							temp->parent = pre;
							temp->leftChild = temp->rightChild = nullptr;
							pre->rightChild = temp;

							if (length == 1)
							{
								temp->ch = ch;
							}
							else
							{
								temp->ch = '\0';
								pre = temp;
							}
						}
						else
							pre = pre->rightChild;
					}
					length--;
				}
				key_code_quantity--;
			}

			//	create a new file for extraction
			cout << "The new file name: ";
			string new_file_name;
			if (cmd)
			{
				new_file_name = string(argv[5]);
				cout << new_file_name << '\n';
				cmd = false;
			}
			else
				cin >> new_file_name;
			out_t_f.open(new_file_name, ios::out | ios::binary);
			if (!out_t_f.is_open())
			{
				cout << "Can't create the file: " << new_file_name << '\n';
				exit(EXIT_FAILURE);
			}
			
			
			//	store the input binary value
			unsigned char byte;

			//	use for find the character in the leaf node of huffman tree
			Node* temp = root;

			//	extraction
			while (in_f_f.read(reinterpret_cast<char*> (&byte), sizeof(char)) && (!in_f_f.eof()))
			{
				for (int i = 7; i >= 0; i--)
				{
					//	the moving way in huffman tree
					bool move = (byte >> i) & 1;
					if (move == false)
					{
						temp = temp->leftChild;
						if (temp->leftChild == nullptr && temp->rightChild == nullptr)
						{
							out_t_f.write(reinterpret_cast<char*> (&(temp->ch)), sizeof(char));
							temp = root;

							if (input_file_size <= 1) // input_file_size = 1的話，代表已全部解壓縮完畢
								goto END_EXTRACTION;
							else
								input_file_size--;
						}
					}
					else
					{
						temp = temp->rightChild;
						if (temp->leftChild == nullptr && temp->rightChild == nullptr)
						{
							out_t_f.write(reinterpret_cast<char*> (&(temp->ch)), sizeof(char));
							temp = root;

							if (input_file_size <= 1) // input_file_size = 1的話，代表已全部解壓縮完畢
								goto END_EXTRACTION;
							else
								input_file_size--;
						}
					}
				}
			}
		
		//	解壓縮完畢
		END_EXTRACTION:
			cout << "Finfish extration!\n";
			in_f_f.close();
			out_t_f.close();

			delete_tree(root);
			root = nullptr;
			break;
		}
		default:
			cout << "Wrong mode selection!\n";
			break;
		}
		cout << endl;

		//	clear file stream
		out_t_f.clear();
		in_f_f.clear();
	}
}