#pragma once
#include "iostream"
#include "fstream"
#include "exception.h"
using namespace std;

template <class T>
class Element;

template <class T>
class BinarySearchTree;

template<class T>
fstream & operator >>(fstream & stream, BinarySearchTree<T> & tree);

template<class T>
ostream & operator <<(ostream & stream, const BinarySearchTree<T> & tree);

template<class T>
class Element{
public:
	Element(): data(0) {};
	Element(T _data): data(_data), left(nullptr), right(nullptr){};
	~Element(){
		left = right = nullptr;
	}

	T data;
	Element* left;
	Element* right;
};

template<class T>

class BinarySearchTree{
public:
	BinarySearchTree(): root(nullptr){};
	BinarySearchTree(T _root): root(new Element<T>(_root)){};
	Element <T>* get_root() const {return root; };
	void addElement(T _data);
	Element<T>* searchElement(T _data);
	void deleteElementChilds(T _data);
	void out(Element <T>* element, ostream & stream);
	~BinarySearchTree();

	friend fstream & operator >> <>(fstream & stream, BinarySearchTree<T> & tree);
	friend ostream & operator << <>(ostream & stream, const BinarySearchTree<T> & tree);
private:
	Element<T>* root;
};

template<class T>
void BinarySearchTree<T>:: addElement(T _data){
	Element<T> *new_element = new Element<T>(_data);
	if (root == nullptr) {
		root = new_element;
		return;
	}
	if(searchElement(_data) != nullptr) throw AddingElementException();
	Element<T> *iterator = root;
	Element<T> *iterator_parent;
	while (iterator != nullptr){
		iterator_parent = iterator;
		if (_data < iterator->data) iterator = iterator->left;
		else iterator = iterator->right;
	}
	if(_data < iterator_parent->data ) iterator_parent->left = new_element;
	else iterator_parent->right = new_element;
}

template<class T>
void BinarySearchTree<T> :: out(Element <T>* element, ostream & stream){
	if (element == nullptr) return;
	out(element->left, stream);
	stream << element->data << " ";
	out(element->right, stream);
}

template <class T>
Element<T>* BinarySearchTree<T> :: searchElement(T _data){
	Element<T> *iterator = root;
	while (iterator != nullptr){
		if (iterator->data == _data) return iterator;
		if (iterator->data > _data) iterator = iterator->left;
		else iterator = iterator->right;
	}
	return nullptr;
}

template<typename T>
void BinarySearchTree<T>::deleteElementChilds(T _data){
	Element<T> *element = searchElement(_data);
	if(element->left != nullptr) deleteElementChilds(element->left->data);
	if(element->right !=nullptr) deleteElementChilds(element->right->data);
	element->left = element->right = nullptr;
	
}

template<typename T>
fstream & operator >>(fstream & stream, BinarySearchTree<T> & tree){
	T temp;
	while(!stream.eof()){
		if (stream >> temp) tree.addElement(temp);
		else{ 
			throw AddingElementException();
			return stream; 
		}
	}
	return stream;
}

template <typename T>
ostream & operator << (ostream & stream, BinarySearchTree<T> & tree){
	tree.out(tree.get_root(), stream);
	return stream;
}

template <typename T>
BinarySearchTree<T> :: ~BinarySearchTree(){
	deleteElementChilds(root->data);
}
