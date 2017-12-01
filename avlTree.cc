#include <iostream>
#include <stdlib.h>

template<class T>
class AVLTree{
public:
	AVLTree(const T& value): left(NULL), right(NULL), data(value){height = 1;}
	~AVLTree(){}
	AVLTree *leftChild() const { return left;}
	AVLTree *rightChild() const { return right;}
	const T& value() const{return data;}
	const int& getHeight() const{return height;}
	void setValue(const T& value){ data = value;}
	void setLeftChild(AVLTree<T> *leftChild){ left = leftChild; }
	void setRightChild(AVLTree<T> *rightChild){ right = rightChild; }
	void setHeight(const int& value){ height = value; }
private:
	AVLTree *left;
	AVLTree *right;
	T data;
	int height;
};

int max(int a, int b){
	return (a >= b ? a : b);
}

//returns new root
template<class T>
AVLTree<T>* leftRotation(AVLTree<T> *root){
	if(!root || !(root)->rightChild()) return NULL;
	AVLTree<T> *oldRoot = root;
	AVLTree<T> *newRoot = oldRoot->rightChild();
	oldRoot->setRightChild(newRoot->leftChild());
	newRoot->setLeftChild(oldRoot);
	updateHeight(oldRoot);
	updateHeight(newRoot);
	return newRoot;
}

//returns new root
template<class T>
AVLTree<T>* rightRotation(AVLTree<T> *root){
	if(!root || !(root)->leftChild()) return NULL;

	AVLTree<T> *oldRoot = root;
	AVLTree<T> *newRoot = oldRoot->leftChild();
	oldRoot->setLeftChild(newRoot->rightChild());
	newRoot->setRightChild(oldRoot);
	updateHeight(oldRoot);
	updateHeight(newRoot);
	return newRoot;
}

template<class T>
bool find(AVLTree<T> *root, const T& value){
	while(root){
		int current = root->value();
		if(current == value) break;
		if(current <= value){
			root = root->leftChild();
		}else{
			root = root->rightChild();
		}
	}
	return root;
}

//negative if right heavy (>-1 doubly right heavy), positive if left heavy (>1 doubly heavy)
template<class T>
int checkIfLeftOrRightHeavy(AVLTree<T> *node){
	if(!node) return 0;

	int leftHeight =0; 
	int rightHeight = 0;
	if(node->leftChild())
		leftHeight = node->leftChild()->getHeight();
	if(node->rightChild())
		rightHeight = node->rightChild()->getHeight();
	return leftHeight - rightHeight;
}

template<class T>
AVLTree<T>* rebalanceTree(AVLTree<T> *root){
	int balance = checkIfLeftOrRightHeavy(root);
	//4 Cases:

/*
-----------------
RIGHT ROTATION
-----------------
    X            Y
   /            / \
  Y       ->   Z   X
 /
Z
-----------------
LEFT ROTATION
-----------------
X                Y
 \              / \
  Y       ->   X   Z
   \
    Z
-----------------
RIGHT -> LEFT
-----------------
	X              X              
	  \             \  
	   Y   ->        Y    ->  LEFT ROTATION 
	  /               \     
	Z                  Z         
-------------------
LEFT -> RIGHT
--------------------
	X                          
	/                    
  Y                       
    \                     
     Z                    
-------------------
*/

	//L OR RL
	if(balance < -1){ //grand-parent is doubly right heavy (NEEDS A LEFT ROTATION):
		if(checkIfLeftOrRightHeavy(root->rightChild()) > 0){ //if node's direct parent is left heavy - need a double rotation R->L
			root->setRightChild(rightRotation(root->rightChild())); //RIGHT ROTATION
		}
		return leftRotation(root); //LEFT ROTATION
	}

	//R OR LR
	if(balance > 1){ //grand-parent is doubly left heavy (NEEDS A RIGHT ROTATION):
		if(checkIfLeftOrRightHeavy(root->leftChild()) < 0){ //if grand-parent right tree is left heavy
			root->setLeftChild(leftRotation(root->leftChild())); //LEFT ROTATION
		}
		return rightRotation(root);
	}
	return root;
}

template<class T>
int heightOfTree(AVLTree<T> *node){
	if(!node) return 0;
	return max(heightOfTree(node->leftChild()) + 1, heightOfTree(node->rightChild()) + 1);
}

template<class T>
void updateHeight(AVLTree<T> *node){
	int leftHeight =0; 
	int rightHeight = 0;
	if(node->leftChild())
		leftHeight = node->leftChild()->getHeight();
	if(node->rightChild())
		rightHeight = node->rightChild()->getHeight();
	node->setHeight(1 + max(leftHeight,rightHeight));
}

template<class T>
void insert(AVLTree<T> **node, const T& value){
	*node = insertRec(*node, value);
}

//returns new root
template<class T>
AVLTree<T>* insertRec(AVLTree<T> *node, const T& value){
	if(!node) {
		return new AVLTree<T>(value);
	}
	if(value <= node->value()){
		node->setLeftChild(insertRec(node->leftChild(), value));
	}else{
		node->setRightChild(insertRec(node->rightChild(), value));
	}

	updateHeight(node);
	node = rebalanceTree(node); //rebalance and set new root for any rotations that occured
	return node;
}



void printBST(AVLTree<int> *root){
	if(!root) return;
	printBST(root->leftChild());
	printf("%d - height: %d\n", root->value(), root->getHeight());
	printBST(root->rightChild());
}

void printPreOrderBST(AVLTree<int> *root){
	if(!root) return;
	printf("%d - height: %d\n", root->value(), root->getHeight());
	printPreOrderBST(root->leftChild());
	printPreOrderBST(root->rightChild());
}

void printPostOrderBST(AVLTree<int> *root){
	if(!root) return;
	printPostOrderBST(root->leftChild());
	printPostOrderBST(root->rightChild());
	printf("%d - height: %d\n", root->value(), root->getHeight());
}

int main(int argc, char const *argv[]){
	AVLTree<int> *root = new AVLTree<int>(20);
	insert(&root, 28);
	insert(&root, 22);
	insert(&root, 8);
	insert(&root, 4);
	insert(&root, 12);
	insert(&root, 11);
	insert(&root, 14);
	insert(&root, 15);
	insert(&root, 16);
	insert(&root, 17);
	insert(&root, 18);

	printPreOrderBST(root); 
	
	return 0;
}