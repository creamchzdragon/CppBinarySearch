#include <iostream>
#include <math.h>
using namespace std;

template <class T>
struct Node {
	T value;
	Node *left=NULL;
	Node *right=NULL;

	Node(T val) {
		this->value = val;
	}

	Node(T val, Node<T> left, Node<T> right) {
		this->value = val;
		this->left = left;
		this->right = right;
	}
};

template <class T>
class BST {

private:
	Node<T> *root;
	T* inOrder;
	int count;

	void addHelper(Node<T> *root, T val) {
		if (root->value > val) {
			if (!root->left) {
				root->left = new Node<T>(val);
			}
			else {
				addHelper(root->left, val);
			}
		}
		else {
			if (!root->right) {
				root->right = new Node<T>(val);
			}
			else {
				addHelper(root->right, val);
			}
		}
	}

	void printHelper(Node<T> *root) {
		if (!root) return;
		printHelper(root->left);
		cout << root->value << ' ';
		printHelper(root->right);
	}

	int nodesCountHelper(Node<T> *root) {
		if (!root) return 0;
		else return 1 + nodesCountHelper(root->left) + nodesCountHelper(root->right);
	}
	
	int heightHelper(Node<T> *root) {
		if (!root) return 0;
		else return 1 + max(heightHelper(root->left), heightHelper(root->right));
	}

	void printMaxPathHelper(Node<T> *root) {
		if (!root) return;
		cout << root->value << ' ';
		if (heightHelper(root->left) > heightHelper(root->right)) {
			printMaxPathHelper(root->left);
		}
		else {
			printMaxPathHelper(root->right);
		}
	}
	int max(int x, int y) {
		if (x > y) {
			return x;

		}
		else {
			return y;
		}
	}

	bool deleteValueHelper(Node<T>* parent, Node<T>* current, T value) {
		if (!current) return false;
		if (current->value == value) {
			if (current->left == NULL || current->right == NULL) {
				Node<T>* temp = current->left;
				if (current->right) temp = current->right;
				if (parent) {
					if (parent->left == current) {
						parent->left = temp;
					}
					else {
						parent->right = temp;
					}
				}
				else {
					this->root = temp;
				}
			}
			else {
				Node<T>* validSubs = current->right;
				while (validSubs->left) {
					validSubs = validSubs->left;
				}
				T temp = current->value;
				current->value = validSubs->value;
				validSubs->value = temp;
				return deleteValueHelper(current, current->right, temp);
			}
			delete current;
			return true;
		}
		return deleteValueHelper(current, current->left, value) ||
			deleteValueHelper(current, current->right, value);
	}
	T getLowestHelper(Node<T> *root) {
		if (!root->left) {
			return root->value;
			
		}
		else {
			return getLowestHelper(root->left);
		}
	}
	T getHighestHelper(Node<T> *root) {
		if (!root->right) {
			return root->value;

		}
		else {
			return getHighestHelper(root->right);
		}
	}
	void getInOrderHelper(Node<T> *root){
		if (!root) return;
		getInOrderHelper(root->left);
		inOrder[count]=root->value;
		cout<<count<<endl;
		count++;
		getInOrderHelper(root->right);
	}

public:
	void add(T val) {
		if (root) {
			this->addHelper(root, val);
		}
		else {
			root = new Node<T>(val);
		}
	}

	void print() {
		printHelper(this->root);
	}

	int nodesCount() {
		return nodesCountHelper(root);
	}

	int height() {
		return heightHelper(this->root);
	}

	void printMaxPath() {
		printMaxPathHelper(this->root);
	}

	bool deleteValue(T value) {
		return this->deleteValueHelper(NULL, this->root, value);
	}
	T getLowest() {
		
		
		
		
		
		if (root) {
			return this->getLowestHelper(root);
		}
		else {
			return 0;
		}
	}
	T getHighest() {
		if (root) {
			return this->getHighestHelper(root);
		}
		else {
			return 0;
		}
	}
	T* getInorder(){
		inOrder=new T[nodesCount()];
		count=0;
		getInOrderHelper(root);
		return inOrder;
	}

};

int main() {
	BST<int> *bst = new BST<int>();
	bst->add(11);
	bst->add(1);
	bst->add(6);
	bst->add(-1);
	bst->add(-10);
	bst->add(100);
	bst->print();
	cout << endl;
	cout << "Nodes count: " << bst->nodesCount();
	cout << endl;
	cout << "Height: " << bst->height();
	cout << endl;
	cout << "Max path: ";
	bst->printMaxPath();
	cout << endl;
	cout << "lowest " << bst->getLowest() << endl;
	cout << "Highest " << bst->getHighest() << endl;
	int* temp=bst->getInorder();
	for(int i=0;i<sizeof(temp)-2;i++){
		cout<<temp[i]<<endl;
	}
	bst->deleteValue(11);
	cout << "11 removed: ";
	bst->print();
	cout << endl;
	cout << "1 removed: ";
	bst->deleteValue(1);
	bst->print();
	cout << endl;
	
	cout << "-1 removed: ";
	bst->deleteValue(-1);
	bst->print();
	cout << endl;
	cout << "6 removed: ";
	bst->deleteValue(6);
	bst->print();
	cout << endl;
	cout << "-10 removed: ";
	bst->deleteValue(-10);
	bst->print();
	cout << endl;
	cout << "100 removed: ";
	bst->deleteValue(100);
	bst->print();
	cout << endl;
	
	system("pause");
	return 0;
}
