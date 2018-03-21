#pragma once
#include <iostream>
using namespace std;

// ����������� ������� ������ BinarySearchTree
template <class T>
class BinarySearchTree {
private:
	// �������� ��������� ���� �� �������� �� �����
	struct Node {
		T  key_;            // �������� �����, ������������ � ����
		Node *left_;		// ��������� �� ����� ���������
		Node *right_;		// ��������� �� ������ ���������
		Node *p_;			// ��������� �� ��������
		Node(const T& key, Node *left = 0, Node *right = 0, Node *p = 0) :	// ����������� ����
			key_(key), left_(left), right_(right), p_(p) {}
	};

	// ������ ����������� � ���� ��������� �� �������� ����.
	Node *root_;

public:

	// ����������� "�� ���������" ������� ������ ������
	BinarySearchTree() : root_(0) {}

	// ���������� ����������� ������, ������� ������ ������
	~BinarySearchTree() { 
		deleteSubtree(root_); 
	}

	// ������ ���������� ����������� ������ � �������� ����� out
	void print(ostream & out) const { 
		printNode(out, root_); 
		out << endl; 
	}

	// ������� ������ �� ����� � �������� ������ ������
	bool iterativeSearch(const T & key)  const {
		return (iterativeSearchNode(key) != 0);
	}

	// ������� ������ �������� � ������, �� ���������� �������
	// ���������. ������� ������������ � ���� ������
	bool insert(const T& key){
		if (iterativeSearch(key))
			return 0;
		Node* newNode = new Node(key);
		Node* pNode = 0;
		Node* node = root_;
		while (node != 0){
			pNode = node;
			if (key < node->key_)
				node = node->left_;
			else
				node = node->right_;
		}
		newNode->p_ = pNode;
		if (pNode == 0)
			root_ = newNode;
		else if (key < pNode->key_)
			pNode->left_ = newNode;
		else
			pNode->right_ = newNode;
		return 1;
	}

	// �������� �������� �� ������, �� ���������� ������� ���������
	bool deleteKey(const T & key){
		Node* node = iterativeSearchNode(key);
		if (node == 0)
			return 0;
		if (node->left_ == 0 && node->right_ == 0){
			if (node == root_){
				root_ = 0;
			}
			else{
				if (node->p_->left_ == node){
					node->p_->left_ = 0;
				}
				else{
					node->p_->right_ = 0;
				}
			}
		}
		else if (node->left_ != 0 && node->right_ != 0){
			T temp = minNode(node->right_)->key_;
			deleteKey(temp);
			node->key_ = temp;
			return 1;
		}
		else{
			if (node == root_){
				node->left_ != 0 ? root_ = node->left_ : root_ = node->right_;
			}
			node->left_ != 0 ? node->left_->p_ = node->p_ : node->right_->p_ = node->p_;
			if (node->p_->left_ == node){
				node->p_->left_ = node->left_ != 0 ? node->left_ : node->right_;
			}
			else{
				node->p_->right_ = node->left_ != 0 ? node->left_ : node->right_;
			}
			
		}
		delete node;
		return 1;
	}

	// ����������� ���������� ����� ������
	int count() const {
		return countSubTree(this->root_);
	}
	// ����������� ������ ������
	int height() const {
		return heightSubTree(this->root_);
	}
	void walk(){
		inorderWalk(root_);
		cout << endl;
	}

private:

	// ������� ������ ������ ���� �� ����� � �������� ������ ������
	Node* iterativeSearchNode(const T & key) const {
		Node* node = root_;
		while (node != 0 && key != node->key_){
			if (key < node->key_)
				node = node->left_;
			else
				node = node->right_;
		}
		return node;
	}

	//
	// ����������� �������, ��������������  
	// ����������� ���� �������� ������������ �������
	//

	// ����������� ������� ��� ������������ ������
	void deleteSubtree(Node *node) {
		if (node != 0){
			deleteSubtree(node->left_);
			deleteSubtree(node->right_);
			delete node;
		}
	}

	// ����������� ������� ����������� ���������� ����� ������
	int countSubTree(Node *node) const {
		if (node == 0)
			return 0;
		return (1 + countSubTree(node->left_) +	countSubTree(node->right_));
	}

	// ����������� ������� ����������� ������ ������
	int heightSubTree(Node *node) const {
		if (node != 0){
			int left = heightSubTree(node->left_);
			int right = heightSubTree(node->right_);
			return left > right ? left + 1 : right + 1;
		}
		return -1;
	}

	// ����������� ������� ��� ������ ����������� ������ � �������� �����
	void printNode(ostream & out, Node *root) const  {
		// ����������� ������ ����������� � ������� ������.
		out << '(';
		if (root) {
			// ��� ����� ������ ������ ���� ���������� (��� ��������������)
			// �������� ������ � �������� ����� <<
			out << root->key_;
			printNode(out, root->left_);
			printNode(out, root->right_);
		}
		out << ')';
	}

	// ����������� ������� ��� ����������� ������ ����� ������.
	void inorderWalk(Node *node) const {
		if (node != 0){
			inorderWalk(node->left_);
			cout << node->key_ << " ";
			inorderWalk(node->right_);
		}
	}
	// ����� ������������ ��������
	Node* minNode(Node *node){
		if (node != 0){
			while (node->left_ != 0)
				node = node->left_;
		}
		return node;
	}
	Node* maxNode(Node *node){
		if (node != 0){
			while (node->right_ != 0)
				node = node->right_;
		}
		return node;
	}
}; // ����� ������� ������ TreeBinarySearchTree
