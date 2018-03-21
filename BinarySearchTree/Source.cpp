#include "BinarySearchTree.h"

#include <iostream>
using namespace std;

int main() {

	BinarySearchTree <int> t; // создаем пустое дерево
	// добавляем узлы 
	t.print(cout);
	t.insert(10);
	t.insert(3);
	t.insert(20);
	t.insert(15);
	t.insert(30);
	t.insert(2);
	t.insert(5);
	t.insert(32);
	t.insert(22);
	t.insert(17);

	// Вывод узлов дерева в выходной поток 
	t.print(cout);
	t.deleteKey(30);
	t.print(cout);
	// Поиск в дереве по ключу

	int  keyFound = t.iterativeSearch(15); // поиск должен быть успешным
	cout << "Key " << 15 <<
		(keyFound ? " found successfully" : " not found") <<
		" in the tree" << endl;

	keyFound = t.iterativeSearch(23);      // поиск должен быть неудачным
	cout << "Key " << 23 <<
		(keyFound ? " found successfully" : " not found") <<
		" in the tree" << endl;

	// определение высоты и количества узлов дерева
	cout << "height = " << t.height() << endl;
	cout << "count =  " << t.count() << endl;

	// . . .
	system("pause");
	return 0;
}
