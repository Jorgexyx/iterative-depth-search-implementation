#include <iostream>
#include <vector>
#include <queue>
class Node 
{
	public: Node(int *perm, int par): permutation(perm), parent(par) {}
		int getParent()       { return parent;}
		int *getPermutation() { return permutation; }
		void printPerm() { 
			for(int i =0 ; i <4; i++){
				std::cout << permutation[i] << ", "; }
			std::cout << "" <<std::endl;
			}
	private:
		int parent;
		int *permutation;
}; 

void BFS(int[4], int);
void printArray(int *arr);
bool inOrder(int *);
int *flip(int *,int, int);

int main()
{
	int vals[4] = {4,3,6,2};
	BFS(vals, 3);
	return 0;
}


void BFS(int permutation[4], int n)
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
		if(inOrder(currentPerm))
		{
			std::cout << "FOUND\n";
			return;
		}

		//create permutation as nodes 
		/**
		for(int i = 0; i < 4; i++)
		{
			int *newPerm = flip(currentPerm, i);
			if(newPerm != currentPerm){
			Node *leaf = new Node(newPerm, 4);
			pointers.push_back(leaf);
			myQueue.push(leaf);
			leaf->printPerm();}

		} **/
	}
	std::cout << "out\n";
	for(int i = 1 ; i < 4; i++)
	{
		for(int j = 0 ; j < 4 ; j ++)
		{	
			if( (j + i ) > 3)
				break;
			int *arr = flip(permutation,i + j, j);
			printArray(arr);
		}
	}
	int *newPerm = flip(currentPerm,0,2);
}

int *flip(int *permutation, int endIdx,int startingIdx)
{
	int *tempArr = (int *)malloc(sizeof(int)* 4); //store array
	for(int i = 0; i < 4; i ++) 
		tempArr[i] = permutation[i]; 
	
	int tempVal = 0;
	while(startingIdx < endIdx)
	{	
		tempVal = tempArr[startingIdx];
		tempArr[startingIdx] = tempArr[endIdx];
		tempArr[endIdx] = tempVal;
		endIdx --;
		startingIdx ++;
	}	

	return tempArr;
}

bool inOrder(int *perm)
{
	for(int i = 0; i < 4; i++)
		if(perm[i] > perm[i + 1])
			return false;
	return true;
}

void printArray(int *arr)
{
	for(int i = 0; i < 4; i ++)
		std::cout << arr[i] << ",";
	std::cout << "\n";
}
