#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <stack>

class Node 
{
	public: 
	  Node(int *perm, int par): permutation(perm), parent(par) {} 
	  int getParent()       { return parent; }
	  int *getPermutation() { return permutation; }
	private:
          int parent;
	  int *permutation;
}; 

const int size = 4;
void bfs(int *, int);
void ids(int *, int);
void printPath(std::vector<Node *> );
void printArray(int *arr);
bool dfs(int *, int);
bool generateChilds(Node *,std::vector<Node *> &, std::queue<Node *> &, std::stack<Node *> &,int);
bool inOrder(int *);
int *flip(int *,int, int);

int main()
{
  int vals[size] = {3,10,7,2};
  bfs(vals, 3);
  ids(vals,10);
  return 0;
}

void ids(int *permutation, int maxDepth)
{
  for(int i = 0 ; i < maxDepth; i ++)
    if(dfs(permutation,i))
      return;
  std::cout << "Could not find.. max depth should increase\n";
  
}

bool dfs(int *permutation,int n)
{
  if(n == 0)
    return false;
  
  int *currentPerm;
  std::vector<Node *> pointers;
  std::stack<Node *> myStack;
  std::queue<Node *> myQueue;

  Node *node = new Node(permutation,-1);
  pointers.push_back(node);
  myStack.push(node);
  
  node = myStack.top();
  myStack.pop();
  if(generateChilds(node, pointers, myQueue, myStack,0))
    return true;
  
  for(int i = 0; i < myStack.size(); i++)
  {
    node = myStack.top();
    myStack.pop();
    currentPerm = node->getPermutation();
    if (dfs(currentPerm, n - 1))
      return true;
  }
  return false;
}

int getInput()
{
  std::string xin;
  std::cout << "please enter values to sort: "; 
  std::getline(std::cin,xin);
  std::stringstream stream(xin);
  int n;
  int *arr;
  int cnt = 0;
  return 1;
}


void bfs(int *permutation, int n)
{
  std::vector<Node *> pointers;
  std::queue<Node *> myQueue;
  std::stack<Node *> myStack;
  int *currentPerm;

  Node *node = new Node(permutation, -1);
  Node *currentNode;

  pointers.push_back(node);
  myQueue.push(node);

  while (!myQueue.empty()) {
    node = myQueue.front();
    myQueue.pop();
    if(generateChilds(node, pointers, myQueue, myStack , 1))
    {
      printPath(pointers);
      return;
    }
  }
}

bool generateChilds(Node *node, std::vector<Node *> &pointers, std::queue<Node *> &myQueue, std::stack<Node *> &myStack,int ch)
{
  int parentIdx = pointers.size() - 1;
  int *perm = node->getPermutation();
  for(int i = 1 ; i < size; i++) {
    for(int j = 0 ; j < size ; j ++) {	
      if( (j + i ) > size - 1) 
	break;

      int *newPerm = flip(perm, i + j, j);
      if(inOrder(newPerm))
      {
	int x = node ->getParent();
	std::cout << x << std::endl;
        printArray(newPerm);
        return true;
      }

      int intVal = 0;
      int oldVal = 1;
      if(intVal != oldVal) {
	Node *leaf = new Node(newPerm, parentIdx);
	pointers.push_back(leaf);

        if(ch == 1)
	  myQueue.push(leaf);
        else
	  myStack.push(leaf);

      }
    }
  }
  return false;
}

int *flip(int *permutation, int endIdx,int startingIdx)
{
  int *tempArr = (int *)malloc(sizeof(int)* size); 
  for(int i = 0; i < size; i ++) 
    tempArr[i] = permutation[i]; 
	
  int tempVal = 0;
  while(startingIdx < endIdx) {	
    tempVal = tempArr[startingIdx];
    tempArr[startingIdx] = tempArr[endIdx]; 
    tempArr[endIdx] = tempVal;
    endIdx --;
    startingIdx ++;
   }	
   return tempArr;
}

bool inOrder(int *arr)
{
  for(int i = 0; i < size - 1; i++)
    if(arr[i] > arr[i + 1])
      return false;
   return true;
}


void printArray(int *arr)
{
  for(int i = 0; i < size; i ++)
    std::cout << arr[i] << ",";
  std::cout << "\n";
}

void printPath(std::vector<Node *> pointers)
{
  
}
