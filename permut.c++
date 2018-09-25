#include <time.h>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <stack>
#include <algorithm>
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

const int size = 10;
int maxStack = 1;
void bfs(int *, int);
void ids(int *, int);
void printPath(std::vector<Node *> );
void printArray(int *arr);
bool dfs(Node *, int,std::vector<Node *>&);
bool generateChilds(Node *,std::vector<Node *> &, std::queue<Node *> &, std::stack<Node *> &,int);
bool inOrder(int *);
int *flip(int *,int, int);

int main()
{
  int vals[size] = {12,12,5,7,2,4,8,10,1,5};
  std::cout << "\nRunning bfs... \n";
  bfs(vals, 3);
  std::cout << "\nRunning ids... \n";
  ids(vals,10);
  return 0;
}

void ids(int *permutation, int maxDepth)
{
  double cpu0 = clock();
  for(int i = 0 ; i < maxDepth; i ++){
    std::vector<Node *> pointers;
    Node *node = new Node(permutation, -1);
    pointers.push_back(node);
    if(dfs(node, i, pointers))
    {
      double cpu1 = clock();
      printPath(pointers);
      std::cout << "Total cpu time for ids: " << (cpu1 - cpu0) /CLOCKS_PER_SEC << "seconds \n";
      std::cout << "Total numer of visited states: " << pointers.size() << std::endl;
      std::cout << "Max size of Queue: " << maxStack << std::endl;
      return;
    }
  }
  std::cout << "Could not find.. max depth should increase\n";
  
}

bool dfs(Node *node,int n,std::vector<Node *> &pointers)
{
  if(n == 0)
    return false;
  
  int *currentPerm;
  std::stack<Node *> myStack;
  std::queue<Node *> myQueue;

  //Node *node = new Node(permutation, -1);
  pointers.push_back(node);
  myStack.push(node);
  
  node = myStack.top();
  myStack.pop();
  if(generateChilds(node, pointers, myQueue, myStack,0))
    return true;
  if(maxStack < myStack.size())
	  maxStack = myStack.size();
  for(int i = 0; i < myStack.size(); i++)
  {
    node = myStack.top();
    myStack.pop();
    if (dfs(node, n - 1,pointers))
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
  int maxSize = 1;
  std::vector<Node *> pointers;
  std::queue<Node *> myQueue;
  std::stack<Node *> myStack;
  int *currentPerm;

  Node *node = new Node(permutation, -1);
  Node *currentNode;

  double cpu0 = clock();
  pointers.push_back(node);
  myQueue.push(node);

  while (!myQueue.empty()) {
    if(myQueue.size() > maxSize)
       maxSize = myQueue.size();

    node = myQueue.front();
    myQueue.pop();
    if(generateChilds(node, pointers, myQueue, myStack , 1))
    {
      double cpu1 = clock();
      printPath(pointers);
      std::cout << "Total cpu time for bfs: " << (cpu1 - cpu0) /CLOCKS_PER_SEC << "seconds \n";
      std::cout << "Total numer of visited states: " << pointers.size() << std::endl;
      std::cout << "Max size of Queue: " << maxSize << std::endl;
      return;
    }
  }
}

bool generateChilds(Node *node, std::vector<Node *> &pointers, std::queue<Node *> &myQueue, std::stack<Node *> &myStack,int ch)
{
  int parentIdx = find(pointers.begin(), pointers.end(), node) - pointers.begin();
  int *perm = node->getPermutation();
  for(int i = 1 ; i < size; i++) {
    for(int j = 0 ; j < size ; j ++) {	
      if( (j + i ) > size - 1) 
	break;

      int *newPerm = flip(perm, i + j, j);
      int intVal = 0;
      int oldVal = 1;

      if(intVal != oldVal) {
	Node *leaf = new Node(newPerm, parentIdx);
	pointers.push_back(leaf);

	if(inOrder(newPerm))
	{
	  //std::cout << parentIdx << std::endl;
	  //printArray(newPerm);
          return true;
	}

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
}

void printPath(std::vector<Node *> pointers)
{
  std::vector<int *> vals;
  Node *node = pointers.at(pointers.size() - 1);
  while(node->getParent() != -1)
  {
    //printArray(node->getPermutation());
    vals.push_back(node->getPermutation());
    node = pointers.at(node->getParent());
  }
  //printArray(node->getPermutation());
  vals.push_back(node->getPermutation());
  for(int i = vals.size() - 1; i > -1 ; i--)
  {
    printArray(vals.at(i));
    std::cout << "-> ";
  }
  std::cout<< "\n";
}
