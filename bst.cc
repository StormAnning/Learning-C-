#include <iostream>

template<class T>
class BinaryTree{
public:
	BinaryTree(const T& value): left(NULL), right(NULL), data(value){}
	~BinaryTree(){}
	BinaryTree *leftChild() const { return left;}
	BinaryTree *rightChild() const { return right;}
	const T& value() const{return data;}
	void setValue(const T& value){ data = value;}
	void setLeftChild(BinaryTree<T> *leftChild){left = leftChild;}
	void setRightChild(BinaryTree<T> *rightChild){right = rightChild;}
private:
	BinaryTree *left;
	BinaryTree *right;
	T data;
};

template<class T>
bool insert(BinaryTree<T> **root, const T& value){
	BinaryTree<T> *child = new BinaryTree<T>(value);
	BinaryTree<T> *current = *root;
	while(current){
		if(current->value() <= value && current->leftChild()){
			current = current->leftChild();
		}else if(current->value() > value && current->rightChild()){
			current = current->rightChild();
		}else{
			break;
		}
	}

	if(current->value() <= value){
		current->setLeftChild(child);
		return true;
	}else{
		current->setRightChild(child);
		return true;
	}
	return false;
}

void printBST(BinaryTree<int> *root){
	if(!root) return;
	printBST(root->leftChild());
	printf("%d\n", root->value());
	printBST(root->rightChild());
}

int main(int argc, char const *argv[]){
	BinaryTree<int> *root = new BinaryTree<int>(52);
	insert(&root, 33);
	insert(&root, 38);
	insert(&root, 64);
	insert(&root, 98);
	insert(&root, 17);
	insert(&root, 88);
	insert(&root, 3);
	printBST(root); 

	return 0;
}