#pragma once
#include <iostream>
using namespace std;

// Определение шаблона класса BinarySearchTree
template <class T>
class BinarySearchTree {
private:
	// Описание структуры узла со ссылками на детей
	struct Node {
		T  key_;            // значение ключа, содержащееся в узле
		Node *left_;		// указатель на левое поддерево
		Node *right_;		// указатель на правое поддерево
		Node *p_;			// указатель на родителя
		Node(const T& key, Node *left = 0, Node *right = 0, Node *p = 0) :	// Конструктор узла
			key_(key), left_(left), right_(right), p_(p) {}
	};

	// Дерево реализовано в виде указателя на корневой узел.
	Node *root_;

public:

	// Конструктор "по умолчанию" создает пустое дерево
	BinarySearchTree() : root_(0) {}

	// Деструктор освобождает память, занятую узлами дерева
	~BinarySearchTree() { 
		deleteSubtree(root_); 
	}

	// Печать строкового изображения дерева в выходной поток out
	void print(ostream & out) const { 
		printNode(out, root_); 
		out << endl; 
	}

	// Функция поиска по ключу в бинарном дереве поиска
	bool iterativeSearch(const T & key)  const {
		return (iterativeSearchNode(key) != 0);
	}

	// Вставка нового элемента в дерево, не нарушающая порядка
	// элементов. Вставка производится в лист дерева
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

	// Удаление элемента из дерева, не нарушающее порядка элементов
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

	// Определение количества узлов дерева
	int count() const {
		return countSubTree(this->root_);
	}
	// Определение высоты дерева
	int height() const {
		return heightSubTree(this->root_);
	}
	void walk(){
		inorderWalk(root_);
		cout << endl;
	}

private:

	// Функция поиска адреса узла по ключу в бинарном дереве поиска
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
	// Рекурсивные функции, представляющие  
	// рекурсивные тела основных интерфейсных методов
	//

	// Рекурсивная функция для освобождения памяти
	void deleteSubtree(Node *node) {
		if (node != 0){
			deleteSubtree(node->left_);
			deleteSubtree(node->right_);
			delete node;
		}
	}

	// Рекурсивная функция определения количества узлов дерева
	int countSubTree(Node *node) const {
		if (node == 0)
			return 0;
		return (1 + countSubTree(node->left_) +	countSubTree(node->right_));
	}

	// Рекурсивная функция определения высоты дерева
	int heightSubTree(Node *node) const {
		if (node != 0){
			int left = heightSubTree(node->left_);
			int right = heightSubTree(node->right_);
			return left > right ? left + 1 : right + 1;
		}
		return -1;
	}

	// Рекурсивная функция для вывода изображения дерева в выходной поток
	void printNode(ostream & out, Node *root) const  {
		// Изображение дерева заключается в круглые скобки.
		out << '(';
		if (root) {
			// Для узлов дерева должна быть определена (или переопределена)
			// операция вывода в выходной поток <<
			out << root->key_;
			printNode(out, root->left_);
			printNode(out, root->right_);
		}
		out << ')';
	}

	// Рекурсивная функция для организации обхода узлов дерева.
	void inorderWalk(Node *node) const {
		if (node != 0){
			inorderWalk(node->left_);
			cout << node->key_ << " ";
			inorderWalk(node->right_);
		}
	}
	// Поиск минимального значения
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
}; // конец шаблона класса TreeBinarySearchTree
