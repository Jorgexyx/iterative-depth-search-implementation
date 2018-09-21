#include <iostream>
#include <vector>
#include <queue>
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
bool inOrder(int *);
int *flip(int *,int, int);

int main()
{
	int vals[4] = {4,3,6,2};
	//int vals[4] = {1,2,3,4};
	//std::cout <<  inOrder(vals) << std::endl;
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
		//std::cout << "Current permutation: \n";
		//printArray(currentPerm);
		//std::cout << "\n";
			
		if(inOrder(currentPerm)) {
			std::cout << "Goal node found \n";
			printArray(currentPerm);
			return;	}

		//generate child nodes
		for(int i = 1 ; i < 4; i++) {
			for(int j = 0 ; j < 4 ; j ++) {	
				if( (j + i ) > 3) break;
				int *newPerm = flip(currentPerm,i + j, j);
				if(newPerm != currentPerm) { //have to add checking
					Node *leaf = new Node(newPerm, 4);
					pointers.push_back(leaf);
					myQueue.push(leaf);
					//printArray(newPerm); 
				}
			}
		}
		//std::cout << "Checking again..." << std::endl;
	}
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

bool inOrder(int *arr)
{
	for(int i = 0; i < 3; i++)
		if(arr[i] > arr[i + 1])
			return false;
	return true;
}

void printArray(int *arr)
{
	for(int i = 0; i < 4; i ++)
		std::cout << arr[i] << ",";
	std::cout << "\n";
}
