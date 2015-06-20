#include <string>
#include <stack>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstdlib>
#include <ctime>
#include <bitset>

/*typedef enum {RED, BLACK} NodeColor;

struct RBTreeNode {
	int data;
	NodeColor color;
	RBTreeNode *parent;
	RBTreeNode *left, *right;
};

RBTreeNode *insert(RBTreeNode *root, RBTreeNode *data)
{
	RBTreeNode *y = nullptr;
	RBTreeNode *x = root;
	while(x) {
		y = x;
		if (data->data < x->data) {
			x = x->left;
		} else {
			x = x->right;
		}
	}
	data->parent = y;
	if (!y) {
		return data;
	} else if(data->data < y->data) {
		y->left = data;
	} else {
		y->right = data;
	}
	return root;
}

RBTreeNode *leftRotate(RBTreeNode *root, RBTreeNode *x)
{
	RBTreeNode *y = x->right;
	x->right = y->left;
	if (y->left) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (!x->parent) {
		root = y;
	} else if(x == x->parent->left) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
	return root;
}

RBTreeNode *rightRotate(RBTreeNode *root, RBTreeNode *x)
{
	RBTreeNode *y = x->left;
	x->left = y->right;
	if(y->right) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if(!y->parent) {
		root = y;
	} else if(x == x->parent->right) {
		x->parent->right = y;
	} else {
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
	return root;
}

RBTreeNode *rbInsert(RBTreeNode *root, RBTreeNode *x)
{
	root = insert(root, x);
	x->color = RED;
	while (x != root && x->parent->color == RED) {
		if(x->parent == x->parent->parent->left) {
			RBTreeNode *y = x->parent->parent->right;
			if (y->color == RED) {
				x->parent->color = BLACK;
				y->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			} else if(x == x->parent->right) {
				x = x->parent;
				root = leftRotate(root, x);
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				root = rightRotate(root, x->parent->parent);
			}
		}
	}
	root->color = BLACK;
	return root;
}

std::string toRPN(const std::string &expr) {
    std::stack<char> expStack;
    std::string rpnStr;
    int nesting = 0;
    char prevChar;
    for(size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];
        switch (c) {
            case ')':
                expStack.pop();
				if(!expStack.empty()) {
					prevChar = expStack.top();
					if (prevChar == '+' || prevChar == '-' || prevChar == '*' || prevChar == '/' || prevChar == '^') {
						rpnStr += prevChar;
						expStack.pop();
					}
				}
                break;
            case '(':
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                expStack.push(c);
                break;
            default:
                rpnStr += c; 
				if (!expStack.empty()) {
					prevChar = expStack.top();
					if (prevChar == '+' || prevChar == '-' || prevChar == '*' || prevChar == '/' || prevChar == '^') {
						rpnStr += prevChar;
						expStack.pop();
					}
				}
				break;
        }
    }
	return rpnStr;
}

void nextPALIN(std::string &num) {
	if(num.size() < 2UL) {
		return;
	}
	size_t size = num.size();
	size_t midPoint = (size)/2;
	bool modified = false;
	if(size%2 == 1 && num[midPoint] != '9') {
		num[midPoint] = num[midPoint] + 1;
		modified = true;
	}
	for(size_t i = midPoint-1; i >= 0; --i) {
		if(modified) {
			num[size-i-1] = num[i];
		} else {
			if(num[i] != '9') {
				num[i] = num[i] + 1;
				modified = true;
			}
			num[size-i-1] = num[i];
		}
		if(i == 0UL) {
			break;
		}
	}
}

std::string cellHeading(int N) {
	std::stack<char> heading;
	while(N > 0) {
		int rem = N%26;
		if(rem != 0) {
			N = N/26;
			heading.push('A' + rem - 1);
		} else {
			N = (N-26)/26;
			heading.push('Z');
		}
	}
	std::string ch;
	while(!heading.empty()) {
		ch += heading.top();
		heading.pop();
	}
	return ch;
}

void shiftArray(int ip[], size_t len) {
	if(len == 0UL) {
		return;
	}
	size_t leftIndex = 0UL, rightIndex = len -1UL;
	while(leftIndex < rightIndex) {
		//find zero item from right
		while(ip[leftIndex] != 0 && leftIndex < rightIndex) {
			++leftIndex;
		}
		//find non-zero item from left
		while(ip[rightIndex] == 0 && rightIndex > leftIndex) {
			--rightIndex;
		}
		//swap if indices are valid
		if(leftIndex < rightIndex) {
			ip[leftIndex] = ip[rightIndex];
			ip[rightIndex] = 0;
			leftIndex++;
			rightIndex--;
		}
	}
}

void minLengthUnsortedArray(int ip[], size_t len, size_t &left, size_t &right) {
	//if there is no or one element in the array
	if(len <= 1UL) {
		return;
	}
	size_t leftEdge = 0UL, rightEdge = len-1;
	for(size_t i = 1UL; i < len; ++i) {
		if(ip[leftEdge] <= ip[i]) {
			leftEdge = i;
		} else {
			break;
		}
	}
	//if the array is sorted already
	if(leftEdge == len-1) {
		left = leftEdge;
		right = leftEdge;
		return;
	}
	for(size_t i = 1UL; i < len; ++i) {
		if(ip[rightEdge] >= ip[len-1-i]) {
			rightEdge = len-1-i;
		} else {
			break;
		}
	}
	if(leftEdge < rightEdge) {
		int leftMax = ip[leftEdge-1], rightMin = ip[rightEdge+1];
		int midMin = ip[leftEdge], midMax = ip[leftEdge];
		for(size_t i = leftEdge+1; i <= rightEdge; ++i) {
			if(ip[i] < midMin) {
				midMin = ip[i];
			}
			if(ip[i] > midMax) {
				midMax = ip[i];
			}
		}
		for(size_t i = leftEdge-1; i > 0UL; --i) {
			if(ip[i] <= midMin) {
				left = i+1;
				break;
			}
		}
		for(size_t i = rightEdge+1; i < len; ++i) {
			if(ip[i] >= midMax) {
				right = i-1;
				break;
			}
		}
	}
}

int findSum(int a[], int len) {
	int sum = 0;
	for(int i = 0; i < len; ++i) {
		for(int j = 0; j < len - i; ++j) {
			int partialSum = 0;
			for(int k = j; k <= j+i; ++k) {
				partialSum += a[k];
			}
			sum += partialSum;
		}
	}
	return sum;
}


double getExpectation(int a, int b) {
	std::vector<double> numerator(a);
	double denom = 0.0;
	for(int i = 0; i < a; ++i) {
		numerator[i] = i*1.0/b;
		denom += numerator[i];
	}
	double expectedValue = 0.0;
	for(int i = 0; i < a; ++i) {
		expectedValue += (i+1)*numerator[i]/denom;
	}
	return expectedValue;
}

std::vector<int> makeExpression(int y) {
	for(int i = -1000; i <= 1000; ++i) {
		if(i == 0 || i == 1) continue;
		for(int j = -1000; j <= 1000; ++j) {
			if(j == 0 || j == 1) continue;
			for(int k = -1000; k <= 1000; ++k) {
				if(k == 0 || k == 1) continue;
				if((i*j+k) == y) {
					std::vector<int> result;
					result.push_back(i);
					result.push_back(j);
					result.push_back(k);
					return result;
				}
			}
		}
	}
	return std::vector<int>();
}

int stringlen(const char *str) {
    int len = 0;
    while(*str++)
        ++len;
    return len;
}

void reverse(char *str) {
    int len = stringlen(str);
    int halfLen = len >> 1;
	char *end = str+len-1;
    for(int i = 0; i < halfLen; ++i) {
        char c = *str;
        *str++ = *end;
        *end-- = c;
    }
}

void zeroOutRowsAndColumns(int m[5][4], int rows, int cols) {
	std::vector<bool> rowsWithZero(rows), colsWithZero(cols);
	for(int i = 0; i < rows; ++i) {
		for(int j = 0; j < cols; ++j) {
			if(m[i][j] == 0) {
				rowsWithZero[i] = true;
				colsWithZero[j] = true;
			}
		}
	}

	for(size_t r = 0UL; r < rows; ++r) {
		if(rowsWithZero[r]) {
			for(int i = 0; i < cols; ++i) {
				m[r][i] = 0;
			}
		}
	}
	for(size_t c = 0UL; c < cols; ++c) {
		if(colsWithZero[c]) {
			for(int i = 0; i < rows; ++i) {
				m[i][c] = 0;
			}
		}
	}
}

class KeyNotFound : public std::exception {
public:
	const char *what() {
		return "Key not found";
	}
};

class HashTable {
	struct HashNode;
	size_t m_size;
	std::vector<HashNode *> m_table;
	struct HashNode {
		std::string m_key;
		std::string m_value;
		HashNode *next;
	};

	HashNode *makeNode(const std::string &key, const std::string &value) {
		HashNode *node = new HashNode;
		node->m_key = key;
		node->m_value = value;
		node->next = 0;
		return node;
	}

	size_t hash(const std::string &key) const {
		return 0UL;
	}

	HashTable(const HashTable &);
	HashTable& operator=(HashTable&);
public:
	explicit HashTable(size_t size) : m_size(size), m_table(size, 0) {
	}

	void insertKey(const std::string &key, const std::string &value) {
		HashNode *node = makeNode(key, value);
		size_t index = hash(key);
		//Insert at the head
		if(m_table[index]) {
			node->next = m_table[index];
		}
		m_table[index] = node;
	}

	void deleteKey(const std::string &key) {
		size_t index = hash(key);
		if(m_table[index] == 0) {
			return;
		}
		HashNode *node = m_table[index];
		if(node->m_key == key) {
			m_table[index] = node->next;
			delete(node);
			return;
		}
		while(node->next) {
			if(node->next->m_key == key) {
				HashNode *temp = node->next;
				node->next = node->next->next;
				delete(temp);
				return;
			}
			node = node->next;
		}
	}

	const std::string &searchKey(const std::string &key) {
		size_t index = hash(key);
		HashNode *node = m_table[index];
		while(node) {
			if(node->m_key == key) {
				return node->m_value;
			}
			node = node->next;
		}
		throw KeyNotFound();
	}
};

class Tree {
	struct TreeNode {
		int value;
		TreeNode *left, *right;
	};
	TreeNode *m_root;
	bool _isBST(TreeNode *root) {
		if(root == 0) {
			return true;
		} else {
			bool bst = true;
			if(root->left) {
				bst = bst && (root->value >= root->left->value);
			}
			if(root->right) {
				bst = bst && (root->value < root->right->value);
			}
			if(bst) {
				return _isBST(root->left) && _isBST(root->right);
			}
			return bst;
		}
	}

	TreeNode *makeNode(int value) {
		TreeNode *node = new TreeNode;
		node->value = value;
		node->left = 0;
		node->right = 0;
		return node;
	}

	TreeNode *_insertNode(TreeNode *root, TreeNode *node) {
		if(!root) {
			root = node;
		} else if(root->value >= node->value) {
			root->left = _insertNode(root->left, node);
		} else {
			root->right = _insertNode(root->right, node);
		}
		return root;
	}
public:
	explicit Tree() : m_root(0) {}
	bool isBST() {
		if (!m_root) {
			return true;
		}
		if(m_root->left && m_root->right) {
			if (m_root->value >
		return _isBST(m_root);
	}
	void insertValue(int value) {
		TreeNode *node = makeNode(value);
		m_root = _insertNode(m_root, node);
	}
};

std::vector<int> COMPUTE_PREFIX_FUNCTION(const std::string &p) {
	int m = p.size();
	std::vector<int> prefixFunction(m);
	prefixFunction[0] = -1;
	int k = -1;
	for(int q = 1; q < m; ++q) {
		while(k > -1 && p[k+1] != p[q]) {
			k = prefixFunction[k];
		}
		if(p[k+1] == p[q]) {
			k = k + 1;
		}
		prefixFunction[q] = k;
	}
	return prefixFunction;
}

void KMP_MATCHER(const std::string &t, const std::string &p) {
	int n = t.size();
	int m = p.size();
	std::vector<int> prefix = COMPUTE_PREFIX_FUNCTION(p);
	int q = -1;
	for(int i = 0; i < n; ++i) {
		while(q > -1 && p[q+1] != t[i]) {
			q = prefix[q];
		}
		if(p[q+1] == t[i]) {
			q = q+1;
		}
		if(q == m-1) {
			std::cout << "Pattern occurs with shift " << i-m+1 << std::endl;
			q = prefix[q];
		}
	}
}

double myPow(double x, int n) {
	if(n == 0) {
		return 1.0;
	} else if(n == 1) {
		return x;
	} else {
		double temp = myPow(x, n/2);
		if(n%2 == 0) 
			return temp*temp;
		else 
			return temp*temp*x;
	}
}
//number is represented as vector of digits
std::vector<int> add(std::vector<int> a, std::vector<int> b) {
	std::vector<int> result;
	//assume a and b contain same number of elements, this will be relaxed
	//later
	if(a.size() != b.size()) {
		return result;
	}
	size_t idx = 0UL, n = a.size();
	int carry = 0;
	result.resize(a.size() + 1);
	for(size_t idx = 0UL; idx < n; ++idx) {
		result[idx] = (a[idx] + b[idx] + carry)%10;
		carry = (a[idx]+b[idx]+carry)/10;
	}
	result[n] = carry;
	return result;
}

struct Node {
	int sum;
	Node *left, *right;
};
Node * BST2GST(Node *root, int sum, int &tempSum) {
	if(root == 0) {
		tempSum = sum;
		return root;
	} else {
		Node *nextNode = BST2GST(root->right, sum, tempSum);
		if(nextNode) {
			root->sum = tempSum;
		} else {
			root->sum = tempSum + nextNode->sum;
		}
		return BST2GST(root->left, root->sum, tempSum);
	}
}

class Trie {
	struct TrieNode {
		bool isLeaf;
		char c;
		TrieNode *nodes[26];
		TrieNode(char _c) : isLeaf(false), c(_c) {
			for(size_t i = 0UL; i < 26UL; ++i) {
				nodes[i] = 0;
			}
		}
	};
	TrieNode *root;
public:
	Trie() : root(0) {}
};

void partition(int c, const std::vector<int>& s, std::vector<int>& p, size_t idx) {
	if(c == 0) {
		std::cout << "Pattern: ";
		for(size_t j = 0UL; j < p.size(); ++j) {
			std::cout << p[j] << " ";
		}
		std::cout << std::endl;
		return;
	}
	for(size_t i = idx; i < s.size(); ++i) {
		int dividend = c/s[i];
		if(dividend > 0) {
			for(int j = 1; j <= dividend; ++j) {
				p[i] += j;
				partition(c%s[i] + (dividend-j)*s[i], s, p, i+1);
				p[i] -= j;
			}
		}
	}
}

int division(int dividend, int divisor) {
	int quotient = 0;
	int numShifts = 0;
	int tempDivisor = divisor;
	while(dividend > tempDivisor) {
		++numShifts;
		tempDivisor <<= 1;
	}
	tempDivisor >>= 1;
	--numShifts;

	do {
		int t = dividend - tempDivisor;
		if(t >= 0) {
			quotient |= 1;
			dividend = t;
		} else {
			dividend <<= 1;
			quotient <<= 1;
			--numShifts;
		}
	} while(dividend >= divisor);
	if(numShifts > 0) {
		quotient <<= numShifts;
	}
	return quotient;
}

void merge(std::vector<int> &a, size_t startIndex, size_t midPoint, size_t endIndex) {
	std::vector<int> result(endIndex-startIndex+1);
	size_t idx = 0UL;
	size_t i = startIndex, j = midPoint+1;
	while(true) {
		if(a[i] <= a[j]) {
			result[idx++] = a[i];
			i++;
			if(i > midPoint) {
				break;
			}
		} else {
			result[idx++] = a[j];
			j++;
			if(j > endIndex) {
				break;
			}
		}
	}
	if(i > midPoint) {
		while(j <= endIndex)
			result[idx++] = a[j++];
	} else if(j > endIndex) {
		while(i <= midPoint)
			result[idx++] = a[i++];
	}
	for(i = startIndex, j = 0UL; i <= endIndex; ++i, ++j) {
		a[i] = result[j];
	}
}

void mergeSort(std::vector<int> &a, size_t startIndex, size_t endIndex) {
	if(startIndex != endIndex) {
		size_t midPoint = (startIndex+endIndex)/2;
		mergeSort(a, startIndex, midPoint);
		mergeSort(a, midPoint+1, endIndex);
		merge(a, startIndex, midPoint, endIndex);
	}
}

class HeapFull : public std::exception {
	const std::string m_exceptionMessage;
public:
	HeapFull() : m_exceptionMessage("Heap is full") {}
	const char *what() {
		return m_exceptionMessage.c_str();
	}
};

class HeapEmpty : public std::exception {
	const std::string m_exceptionMessage;
public:
	HeapEmpty() : m_exceptionMessage("Heap is empty"){}
	const char *what() {

	}
};

class Heap {
#define MAX_HEAP_SIZE 511
	int _a[MAX_HEAP_SIZE];
	int m_heapSize;
	void _swap(int &a, int &b) {
		int temp = a;
		a = b;
		b = temp;
	}

	void _heapify() {
		int index = 0;
		while(index < m_heapSize) {
			int leftChild = 2*index + 1;
			int rightChild = 2*index+2;
			if(leftChild >= m_heapSize) return;
			if(rightChild >= m_heapSize) {
				if(_a[index] > _a[leftChild]) {
					_swap(_a[leftChild], _a[index]);
				}
				return;
			} else {
				if(_a[index] > _a[leftChild] || _a[index] > _a[rightChild]) {
					if (_a[leftChild] < _a[rightChild]) {
						_swap(_a[leftChild], _a[index]);
						index = leftChild;
					} else {
						_swap(_a[rightChild], _a[index]);
						index = rightChild;
					}
				} else {
					return;
				}
			}
		}
	}

	void _bubbleUp() {
		int childIndex = m_heapSize-1;
		while(childIndex > 0) {
			int parentIndex = (childIndex-1) >> 1;
			if(_a[childIndex] < _a[parentIndex]) {
				_swap(_a[childIndex], _a[parentIndex]);
				childIndex = parentIndex;
			} else {
				return;
			}
		}
	}
public:
	Heap() : m_heapSize(0) {}
	void insert(int data) {
		if (m_heapSize >= MAX_HEAP_SIZE) {
			throw HeapFull();
		}
		_a[m_heapSize++] = data;
		_bubbleUp();
	}

	int extractMin() {
		if (isEmpty()) {
			throw HeapEmpty();
		}
		int minItem = _a[0];
		m_heapSize -= 1;
		if(m_heapSize > 0) {
			_a[0] = _a[m_heapSize];
			_heapify();
		}
		return minItem;
	}

	bool isEmpty() {
		return m_heapSize == 0;
	}
};

void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

int partition(std::vector<int> &a, int startIndex, int endIndex) {
	int highIndex = startIndex;
	int pivot = endIndex;
	for(int i = startIndex; i < endIndex; ++i) {
		if(a[i] < a[pivot]) {
			swap(a[i], a[highIndex]);
			highIndex++;
		}
	}
	swap(a[pivot], a[highIndex]);
	return highIndex;
}

void quickSort(std::vector<int> &a, int startIndex, int endIndex) {
	if(startIndex < endIndex) {
		int pivot = partition(a, startIndex, endIndex);
		quickSort(a, startIndex, pivot-1);
		quickSort(a, pivot+1, endIndex);
	}
}

int findMaxConsecutiveSum(std::vector<int> &a) {
	int s0 = a[0];
	int s = s0;
	for(size_t i = 1; i < a.size(); ++i) {
		if(a[i] < 0) {
			if(s0 < a[i]) {
				s0 = a[i];
			} else {
				s0 += a[i];
			}
		} else {
			if(s0 < 0) {
				s0 = a[i];
			} else {
				s0 += a[i];
			}
		}
		if(s < s0) {
			s = s0;
		}
	}
	return s;
}

void randomSelection(std::vector<int> &a, std::vector<int> &selected, int m) {
	int n = a.size();
	selected.resize(m);
	int t = 0, selectedSoFar = 0;
	srand(time(NULL));

	while(selectedSoFar < m) {
		int randomIndex = rand()%(n-t);
		if(randomIndex < (m-selectedSoFar)) {
			selected[selectedSoFar] = a[t];
			++selectedSoFar;
		}
		++t;
	}
}

int addIntegers(int x, int y) {
	int sum, carry;
	do {
		sum = x^y;
		carry = (x&y)<<1;
		x = sum;
		y = carry;
	} while(carry);
	return sum;
}

void findPrime(int n) {
	std::vector<bool> isComposite(n);
	int sqrtN = (int)sqrt(n);
	std::vector<int> primeList;
	for(int i = 2; i <= sqrtN; ++i) {
		if (!isComposite[i-2]) {
			primeList.push_back(i);
			for(int j = 2*i; j <= n; j += i) {
				isComposite[j-2] = true;
			}
		}
	}
	for(int i = sqrtN; i <= n; ++i) {
		if(!isComposite[i-2]) {
			primeList.push_back(i);
		}
	}
	std::cout << "Number of Primes: " << primeList.size() << std::endl;
	for(size_t idx = 0UL; idx < primeList.size(); ++idx) {
		std::cout << primeList[idx] << ", ";
	}
	std::cout << std::endl;
}

int my_strlen(const char *s) {
	char *t = (char *)s;
	int len = 0;
	while(*t) {
		++len;
		++t;
	}
	return len;
}

#include <algorithm>

struct ArrayNode {
	int index;
	char *s;
};

struct Compare {
	bool operator()(ArrayNode &left, ArrayNode &right) {
		int c = strcmp(left.s, right.s);
		if (c < 0) {
			return true;
		}
		return false;
	}
};

void creatSuffixArray(char *s) {
	int length = my_strlen(s);
	ArrayNode *a = new ArrayNode[length];
	for(int i = 0; i < length; ++i) {
		a[i].index = i;
		a[i].s = s+i;
	}
	Compare comp;
	std::sort(a, a+length, comp);
	std::cout << "Sorted Array: " << std::endl;
	for(int i = 0; i < length; ++i) {
		std::cout << a[i].index << ", ";
	}
	std::cout << std::endl;
}
*/
int minNumCoins(const int value, const std::vector<int> &coins)
{
  std::vector<int> changes(value+1, 10000);

  changes[0] = 0;
  for(int i = 1; i <= value; ++i) 
  {
    for(int j = 0; j <= i - 1; ++j)
    {
      for(int k = 0; k < coins.size(); ++k)
      {
        if ((j + coins[k]) == i && changes[i] > changes[j] + 1)
        {
          changes[i] = changes[j] + 1;
        }
      }
    }
  }
  return changes[value];
}

void printNum(int num, const int maxNum)
{
  std::cout << num << std::endl;
  if(num < maxNum) {
    printNum(num+1, maxNum);
    std::cout << num << std::endl;
  }
}

void buildRMQTable(const std::vector<int> input)
{
  const int inputSize = input.size();
  std::vector<std::vector<int>> rmqTable;
  rmqTable.resize(inputSize);
  for(size_t i = 0; i < rmqTable.size(); ++i)
  {
    rmqTable[i].resize(inputSize, 10000);
  }
  rmqTable[0] = input;
  if (inputSize > 0)
  {
    for(int i = 1; i < inputSize-1; ++i)
    {
      for(int j = 0; j < inputSize-i; ++j)
      {
        rmqTable[i][j] = std::min(rmqTable[i-1][j], rmqTable[i-1][j+1]);
      }
    }
  }
}

int main(int argc, char **argv) {
	//const std::string expr = "((a+t)*((b+(a+c))^(c+d)))";
	//std::cout << toRPN(expr) << std::endl;
	//std::string num = "149234567890123456788751";
	//nextPALIN(num);
	//std::cout << num << std::endl;
	//std::string heading = cellHeading(1396);
	//std::cout << "Heading: " << heading << std::endl;
	//int ip[] = { 0, 0, 0, 1, 2, 3, 4};
	//size_t len = sizeof(ip)/sizeof(int);
	//shiftArray(ip, len);
	//std::cout << std::endl << "Array: ";
	//for(size_t i = 0UL; i < len; ++i) {
	//	std::cout << ip[i] << " ";
	//}
	//std::cout << std::endl;
	//int ip[] = {10, 12, 20, 30, 25, 40, 32, 31, 35, 50, 60};
	//int ip[] = { 0, 1, 15, 25, 6, 7, 30, 40, 50};
	//size_t len = sizeof(ip)/sizeof(int);
	//size_t left = 0UL, right = len-1;
	//minLengthUnsortedArray(ip, len, left, right);
	//std::cout << "[" << left << ", " << right << "]" << std::endl;
	//int a[] = {1,2,3,4,5,6,7,8,9,10};
	//int size = sizeof(a)/sizeof(int);
	//std::cout << "Sum: " << findSum(a, size) << std::endl;
	//std::cout << "Expected Value: " << getExpectation(2, 2) << std::endl;
	//std::cout << "Expected Value: " << getExpectation(4, 2) << std::endl;
	//std::cout << "Expected Value: " << getExpectation(3, 3) << std::endl;
	//std::cout << "Expected Value: " << getExpectation(11, 13) << std::endl;
	//std::vector<int> expr = makeExpression(5);
	//char str[] = "this is   a te st string";
	//std::cout << "Original String: " << str << std::endl;
	//reverse(str);
	//std::cout << "Reversed String: " << str << std::endl;
	//int m[5][4] = {
	//	{0, 2, 3, 4},
	//	{5, 6, 7, 9},
	//	{1, 1, 2, 3},
	//	{4, 0, 6, 7},
	//	{8, 9, 2, 1}
	//};
	//int rows = 5, cols = 4;
	//std::cout << "Original Matrix: " << std::endl;
	//for(int i = 0; i < rows; ++i) {
	//	for(int j = 0; j < cols; ++j) {
	//		std::cout << m[i][j] << " ";
	//	}
	//	std::cout << std::endl;
	//}
	//std::cout << "Zeroed Matrix: " << std::endl;
	//zeroOutRowsAndColumns(m, rows, cols);
	//for(int i = 0; i < rows; ++i) {
	//	for(int j = 0; j < cols; ++j) {
	//		std::cout << m[i][j] << " ";
	//	}
	//	std::cout << std::endl;
	//}
	//HashTable table(512UL);
	//table.insertKey("test", "key");
	//table.insertKey("another", "keyAnother");
	//std::cout << "Value for \"test\": " << table.searchKey("test") << std::endl;
	//std::cout << "Value for \"another\": " << table.searchKey("another") << std::endl;
	//try {
	//	table.deleteKey("another");
	//	table.searchKey("another");
	//} catch(KeyNotFound e) {
	//	std::cout << "Exception thrown: " << e.what() << std::endl;
	//}

	//const std::string text = "bacbababababcaabcbab";
	//const std::string pattern = "ababababca";
	//const std::string text = "this is a test string";
	//const std::string pattern = "test string";
	//KMP_MATCHER(text, pattern);
	//std::cout << "Division(12, 2): " << division(12, 2) << std::endl;
	//std::cout << "Division(12, 4): " << division(12, 4) << std::endl;
	//std::cout << "Division(25, 5): " << division(25, 5) << std::endl;
	//std::cout << "Division(100, 5): " << division(100, 5) << std::endl;
	//std::cout << "Division(1000, 5): " << division(1000, 5) << std::endl;
	//std::cout << "Division(1525, 25): " << division(1525, 25) << std::endl;
	//int c = 70;
	//const int _s[] = {7, 5, 4, 3, 2};
	//std::vector<int> s(&_s[0], &_s[5]);
	//std::vector<int> p(5);
	//std::vector<std::vector<int> > patterns;
	//size_t idx = 0UL;
	//partition(c, s, p, idx);
	//const int _s[] = {-1, 1, 10, 9, 6, 12, 7, 5, 4, 3, 2, 30, 9, 1, 2, -20, 25, 34, 15, 17};
	//std::vector<int> s(&_s[0], &_s[20]);
	//std::cout << "Unsorted Array: ";
	//for(size_t idx = 0UL; idx < s.size(); ++idx) {
	//	std::cout << s[idx] << " ";
	//}
	//std::cout << std::endl;
	////mergeSort(s, 0UL, s.size() - 1);
	//quickSort(s, 0, s.size()-1);
	//std::cout << "Sorted Array: ";
	//for(size_t idx = 0UL; idx < s.size(); ++idx) {
	//	std::cout << s[idx] << " ";
	//}
	//std::cout << std::endl;
	//const int _s[] = {-2, -3, -10, -9, -1, 1};
	//std::vector<int> s(&_s[0], &_s[6]);
	//double sum = findMaxConsecutiveSum(s);
	//std::cout << "Max consecutive sum: " << sum << std::endl;
	//const int _s[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	//std::vector<int> s(&_s[0], &_s[14]);
	//std::vector<int> selected;
	//randomSelection(s, selected, 5);
	//std::cout << "Selected Array: ";
	//for(size_t idx = 0UL; idx < selected.size(); ++idx) {
	//	std::cout << selected[idx] << " ";
	//}
	//std::cout << std::endl;

	//int x = 2345, y = 1890;
	//std::cout << "add(" << x << ", " << y << "): " << addIntegers(x, y) << std::endl;
	/*const int _s[] = {-2, -3, -10, -9, -1, 1};
	std::vector<int> s(&_s[0], &_s[6]);
	Heap h;
	for(size_t i = 0UL; i < s.size(); ++i) {
		h.insert(s[i]);
	}
	while(!h.isEmpty()) {
		std::cout << "Min: " << h.extractMin() << std::endl;
	}*/
	//findPrime(10000);
	//char *s = "Thisisateststring\0";
	//std::cout << "Length: " << my_strlen(s) << std::endl;
	//std::cout << "String: " << s << std::endl;
	//creatSuffixArray(s);
  //std::vector<int> coins;
  //coins.push_back(1);
  //coins.push_back(2);
  //coins.push_back(3);
  //coins.push_back(4);
  //coins.push_back(7);
  //coins.push_back(13);
  //int coin = 25;
  //int numRequiredCoins = minNumCoins(coin, coins);
  //std::cout << "Number of Coins: " << numRequiredCoins << std::endl;
  //printNum(1, 10);
  const int a[] = {20, 1, 30, -30, 4, 9, 2, 11, 3, -4};
  const std::vector<int> v(&a[0], &a[9]);
  buildRMQTable(v);
	return 0;
}