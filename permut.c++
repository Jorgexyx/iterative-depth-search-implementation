#include <iostream>
#include <vector>
#include <queue>
#include <string>
class Node 
{
	public: 
	  Node(int *perm, int par): permutation(perm), parent(par) {} 
	  int getParent()       { return parent;}
	  int *getPermutation() { return permutation; }

	private:
          int parent;
	  int *permutation;
}; 

void BFS(int *, int);
void printArray(int *arr);
void generateChilds(int *,std::vector<Node *> &, std::queue<Node *> &);
bool inOrder(int *);
int *flip(int *,int, int);
int arrayToInt(int *);

int main()
{
  int vals[4] = {4,3,6,2};
  BFS(vals, 3);
  return 0;
}


void BFS(int *permutation, int n)
{
  std::vector<Node *> pointers;
  std::queue<Node *> myQueue;
  Node *node = new Node(permutation, 1);
  Node *currentNode;
  int *currentPerm;
  pointers.push_back(node);
  myQueue.push(node);

  while (!myQueue.empty()) {
    node = myQueue.front();
    currentPerm = node->getPermutation();
    myQueue.pop();

    if(inOrder(currentPerm)) {
      std::cout << "Goal node found \n";
      printArray(currentPerm);
      return; }
    //generate child nodes
    generateChilds(currentPerm, pointers, myQueue);
		
  }
}

void generateChilds(int *perm,std::vector<Node *> &pointers, std::queue<Node *> &myQueue)
{
  for(int i = 1 ; i < 4; i++) {
    for(int j = 0 ; j < 4 ; j ++) {	
      if( (j + i ) > 3) 
	break;

      int *newPerm = flip(perm,i + j, j);
      if(newPerm != perm) { //have to add checking
	Node *leaf = new Node(newPerm, 4);
	pointers.push_back(leaf);
	myQueue.push(leaf);
	//printArray(newPerm); 
      }
    }
  }
}

int *flip(int *permutation, int endIdx,int startingIdx)
{
  int *tempArr = (int *)malloc(sizeof(int)* 4); 
  for(int i = 0; i < 4; i ++) 
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
  for(int i = 0; i < 3; i++)
    if(arr[i] > arr[i + 1])
      return false;
   return true;
}
int arrayToInt(int *arr)
{
  return 1;
}

void printArray(int *arr)
{
  for(int i = 0; i < 4; i ++)
    std::cout << arr[i] << ",";
  std::cout << "\n";
}
