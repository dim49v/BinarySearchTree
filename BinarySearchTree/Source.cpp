#include "BinarySearchTree.h"

#include <iostream>
using namespace std;

int main() {

	BinarySearchTree <int> t; // ������� ������ ������
	// ��������� ���� 
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

	// ����� ����� ������ � �������� ����� 
	t.print(cout);
	t.deleteKey(30);
	t.print(cout);
	// ����� � ������ �� �����

	int  keyFound = t.iterativeSearch(15); // ����� ������ ���� ��������
	cout << "Key " << 15 <<
		(keyFound ? " found successfully" : " not found") <<
		" in the tree" << endl;

	keyFound = t.iterativeSearch(23);      // ����� ������ ���� ���������
	cout << "Key " << 23 <<
		(keyFound ? " found successfully" : " not found") <<
		" in the tree" << endl;

	// ����������� ������ � ���������� ����� ������
	cout << "height = " << t.height() << endl;
	cout << "count =  " << t.count() << endl;

	// . . .
	system("pause");
	return 0;
}
