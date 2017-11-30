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
	if(!*root)return false;
	BinaryTree<T> *child = new BinaryTree<T>(value);
	BinaryTree<T> *current = *root;
	while(current){
		if(current->value() >= value && current->leftChild()){
			current = current->leftChild();
		}else if(current->value() < value && current->rightChild()){
			current = current->rightChild();
		}else{
			break;
		}
	}

	if(current->value() >= value){
		current->setLeftChild(child);
		return true;
	}else{
		current->setRightChild(child);
		return true;
	}
	return false;
}


template<class T>
BinaryTree<T>* insertRec(BinaryTree<T> *node, const T& value){
	if(!node){
		return new BinaryTree<T>(value);
	}

	if(node->value() >= value){
		node->setLeftChild(insertRec(node->leftChild(),value));
	}

	if(node->value() < value){
		node->setRightChild(insertRec(node->rightChild(), value));
	}
	return node; //return unchanged node pointer
}

template<class T>
bool find(BinaryTree<T> *root, const T& value){
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

template<class T>
int findLowestCommonAncestor(BinaryTree<T> *head, const T& value1, const T& value2){
	BinaryTree<T> *current = head;
	while(current){
		int currentVal = current->value();
		if(value1 <= currentVal && value2 <= currentVal){
			current = current->leftChild();
		}else if(value1 <= currentVal && value2 <= currentVal){
			current = current->rightChild();
		}else{
			return current->value();
		}
	}
	return 0; // couldn't find lowest common ancestor
}

void printBST(BinaryTree<int> *root){
	if(!root) return;
	printBST(root->leftChild());
	printf("%d\n", root->value());
	printBST(root->rightChild());
}

void printPreOrderBST(BinaryTree<int> *root){
	if(!root) return;
	printf("%d\n", root->value());
	printPreOrderBST(root->leftChild());
	printPreOrderBST(root->rightChild());
}

void printPostOrderBST(BinaryTree<int> *root){
	if(!root) return;
	printPostOrderBST(root->leftChild());
	printPostOrderBST(root->rightChild());
	printf("%d\n", root->value());
}

int main(int argc, char const *argv[]){
	BinaryTree<int> *root = new BinaryTree<int>(50);
	insert(&root, 30);
	insert(&root, 20);
	insert(&root, 40);
	insert(&root, 70);
	insert(&root, 60);
	insert(&root, 80);

	printBST(root);
	printf("---------\n");
	printPreOrderBST(root); 

	//printf("%d\n", findLowestCommonAncestor(root, 4, 12));
	return 0;
}