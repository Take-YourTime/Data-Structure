# Data-Structure

資料結構課程作業（C++）  
Data Structure course homework assignments written in C++.

> **Copyright Notice**: The assignment specification PDF files (`ds_ex*.pdf`, `ReadMe.pdf`) in each folder are course materials whose copyright belongs to the course professor. They are included solely for reference.

---

## 📁 Folder Structure

| Folder | Topic |
|--------|-------|
| [hw1.1 - magic square](#hw11---magic-square-魔方陣) | Print odd-order magic squares |
| [hw1.2 - factorial](#hw12---factorial-階乘) | Compute large factorials (N < 50) |
| [hw2 - 建造C++的集合類別](#hw2---建造c的集合類別-set-class) | Build a C++ Set class |
| [hw3 - stack之應用](#hw3---stack之應用-knights-tour-with-stack) | Knight's Tour using a stack |
| [hw4 - recursion之應用](#hw4---recursion之應用-knights-tour-with-recursion) | Knight's Tour using recursion |
| [hw5 - linked list之應用](#hw5---linked-list之應用-polynomial-operations) | Polynomial addition & multiplication via linked list |
| [hw6 - binary tree之應用](#hw6---binary-tree之應用-binary-search-tree) | Binary Search Tree with inorder traversal |
| [hw7 - sorting演算法執行效率](#hw7---sorting演算法執行效率-sorting-benchmark) | Sorting algorithm performance comparison |
| [hw8 - 製作 Huffman 壓縮軟體](#hw8---製作-huffman-壓縮軟體-huffman-compression) | Huffman compression & decompression tool |

---

## hw1.1 - magic square (魔方陣)

**Files**
- `ds_ex1a.pdf` — assignment specification *(copyright: course professor)*
- `hw1.1-b113040045.cpp` — solution source code
- `hw1.1-b113040045.out` — sample output

**Description**  
Prints odd-order magic squares of sizes 1, 3, 5, 7, and 9 using a dynamic 2-D array. The algorithm places integers 1–N² so that the sum of every row, column, and main diagonal is equal.

**Sample Output**
```
三階魔方陣

  6  1  8
  7  5  3
  2  9  4
```

---

## hw1.2 - factorial (階乘)

**Files**
- `ds_ex1b.pdf` — assignment specification *(copyright: course professor)*
- `hw1.2-b113040045.cpp` — solution source code
- `hw1.2-b113040045.out` — sample output

**Description**  
Reads integers N from standard input (until 0 is entered) and prints the factorials 1! through N! for each N. Because N can be up to 49, a digit-array technique is used to handle arbitrarily large numbers.

**Sample Output**
```
6
1!=1
2!=2
3!=6
4!=24
5!=120
6!=720
```

---

## hw2 - 建造C++的集合類別 (Set Class)

**Files**
- `ds_ex2.pdf` — assignment specification *(copyright: course professor)*
- `hw2-b113040045.cpp` — solution source code
- `hw2-b113040045.out` — sample output
- `vector寫法(不完全正確)/` — an alternative vector-based attempt (incomplete)

**Description**  
Implements a `Set` class in C++ that supports the following five operations through operator overloading:

| Operator | Operation |
|----------|-----------|
| `A + B`  | Union (聯集) |
| `A * B`  | Intersection (交集) |
| `A - B`  | Difference (差集) |
| `A >= B` | Containment — checks whether A contains B (包含) |
| `find_key(c)` | Membership — checks whether character c is in the set (屬於) |

**Sample Output**
```
A: {abcdef}
B: {cefhi}
A+B: {abcdefhi}
A*B: {cef}
A-B: {abd}
B-A: {hi}
```

---

## hw3 - stack之應用 (Knight's Tour with Stack)

**Files**
- `ds_ex3.pdf` — assignment specification *(copyright: course professor)*
- `hw3-b113040045.cpp` — solution source code
- `hw3-b113040045.out` — sample output

**Description**  
Solves the **Knight's Tour** problem on an n×n chessboard using an explicit **stack** (linked-list implementation). The program finds a path for a chess knight that visits every square exactly once, and backtracks when no valid move exists.

**Sample Output**
```
【n = 5】
  1 20 17 12  3
 16 11  2  7 18
 21 24 19  4 13
 10 15  6 23  8
 25 22  9 14  5
```

---

## hw4 - recursion之應用 (Knight's Tour with Recursion)

**Files**
- `ds_ex4.pdf` — assignment specification *(copyright: course professor)*
- `hw4-b113040045.cpp` — solution source code
- `hw4-b113040045.out` — sample output

**Description**  
Solves the same **Knight's Tour** problem as hw3, but implemented using **recursion** instead of an explicit stack. The dynamic 2-D board is allocated globally; the recursive function `knight()` returns `true` when a complete tour is found.

**Sample Output**
```
[ n = 5 ]
  1 20 17 12  3
 16 11  2  7 18
 21 24 19  4 13
 10 15  6 23  8
 25 22  9 14  5
```

---

## hw5 - linked list之應用 (Polynomial Operations)

**Files**
- `ds_ex5.pdf` — assignment specification *(copyright: course professor)*
- `hw5-b113040045.cpp` — solution source code
- `hw5-b113040045.out` — sample output

**Description**  
Represents polynomials as **doubly-linked lists** of `(coefficient, exponent)` nodes and supports:
- **Addition** (加法): merges two polynomial linked lists
- **Multiplication** (乘法): multiplies two polynomial linked lists term by term

**Sample Output**
```
【Case 2】
ADD
 3 5
 1 2
MULTIPLY
 3 7
-6 6
 2 3
-4 2
```

---

## hw6 - binary tree之應用 (Binary Search Tree)

**Files**
- `ds_ex6.pdf` — assignment specification *(copyright: course professor)*
- `hw6-b113040045.cpp` — solution source code
- `hw6-b113040045.out` — sample output

**Description**  
Builds a **Binary Search Tree (BST)** from a sequence of integers read from standard input (terminated by -1). After construction the program prints each node together with its left and right children using **inorder traversal**. Duplicate values are discarded.

**Sample Output**
```
node: 4 7 8 10 11 12
left: 0 4 0 7 0 11
right: 0 8 0 12 0 0
```

---

## hw7 - sorting演算法執行效率 (Sorting Benchmark)

**Files**
- `ds_ex7.pdf` — assignment specification *(copyright: course professor)*
- `hw7-b113040045.cpp` — solution source code
- `hw7-b113040045.docx` — written report
- `random.cpp` — helper program to generate random test data
- `input.txt` — 10 test cases of random integers
- `outputA.txt` ~ `outputE.txt` — sorted output from each algorithm
- `PleaseReadMe.txt` — notes on how to use the helper and input files

**Description**  
Reads 10 test cases of random integers from `input.txt` and measures the wall-clock time each of the following sorting algorithms takes to sort all 10 cases:

| Label | Algorithm |
|-------|-----------|
| A | Insertion Sort |
| B | Merge Sort |
| C | Quick Sort |
| D | C++ `std::sort` |
| E | C `qsort` |

Results (sorted arrays) are written to `outputA.txt` – `outputE.txt`.

**Note**: Edit `random.cpp` line 11 (`test_case`) to change the number of random integers generated. The current `input.txt` contains 10 × 10 = 100 integers.

---

## hw8 - 製作 Huffman 壓縮軟體 (Huffman Compression)

**Files**
- `ds_ex8.pdf` — assignment specification *(copyright: course professor)*
- `ReadMe.pdf` — detailed usage documentation *(copyright: course professor)*
- `hw8-b113040045.cpp` — solution source code (requires C++17)
- `hw8-b113040045.out` — sample terminal session
- `a.txt`, `b.txt`, `c.txt`, `d.jpg` — sample input files
- `a2.bin`, `b2.bin`, `c2.bin`, `d2.bin` — compressed output files
- `a3.txt`, `b3.txt`, `c3.txt`, `d3.jpg` — decompressed output files (should match originals)

**Description**  
An interactive command-line tool that implements the **Huffman coding** algorithm to:
1. **Compress** an arbitrary file (`-c -i <input> -o <output>`)
2. **Decompress** a previously compressed file (`-u -i <input> -o <output>`)

The Huffman tree is serialised into the compressed file's header so that decompression does not require a separate key file. Compile with `-std=c++17`.

**Sample compression stats for `a.txt`**
```
Input file size:            9 bytes
Compressed file size:      46 bits (incl. header)
File size ratio:          516%    (> 100% means the compressed file is larger than the original — expected overhead for very small files)
```

---

*Student: 許育菖 (B113040045)*