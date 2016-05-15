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
	void addElement(T _data) throw(AddingElementException);
	Element<T>* searchElement(T _data) const;
	Element<T>* searchParent(T _data) const;
	void deleteElementChilds(T _data);
	void deleteElement(T _data);
	void out(Element <T>* element, ostream & stream, int level) const;
	~BinarySearchTree();

	friend fstream & operator >> <>(fstream & stream, BinarySearchTree<T> & tree);
	friend ostream & operator << <>(ostream & stream, const BinarySearchTree<T> & tree) throw(EmptyTree);
private:
	Element<T>* root;
};

template<class T>
void BinarySearchTree<T>:: addElement(T _data) throw(AddingElementException) {
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
void BinarySearchTree<T> :: out(Element <T>* element, ostream & stream, int level) const{
	if (element == nullptr) return;
	out(element->left, stream, level + 1);
    for(int i = 0; i< level; i++){ 
		cout << "   ";
	}
	stream << element->data << endl;
    out(element->right,stream, level + 1);
}

template <class T>
Element<T>* BinarySearchTree<T> :: searchElement(T _data) const{
	Element<T> *iterator = root;
	while (iterator != nullptr){
		if (iterator->data == _data) return iterator;
		if (iterator->data > _data) iterator = iterator->left;
		else iterator = iterator->right;
	}
	return nullptr;
}

template <class T>
Element<T>* BinarySearchTree<T> :: searchParent(T _data) const{
	if(root->data == _data) return nullptr;
	Element<T> *iterator = root;
	Element<T> *iterator_parent = root;
	while (iterator != nullptr){
		if (iterator->data == _data) return iterator_parent;
		iterator_parent = iterator;
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

template <typename T>
void BinarySearchTree<T>::deleteElement(T _data){
	if (_data == root->data){
		deleteElementChilds(root->data);
		root = nullptr;
		return;
	}
	Element<T> *element = searchElement(_data);
	if (element == nullptr) throw NoSuchElement();
	Element<T> *element_parent = searchParent(_data);
	if (element->right == nullptr){
		if (element->left == nullptr) {
			if(_data > element_parent->data)
				element_parent->right = nullptr;
			else element_parent->left = nullptr;
			return;
		}
		if(_data > element_parent->data)
			element_parent->right = element->left;
		else element_parent->left = element->left;
		return;
	}
	Element<T> *iterator_parent = element;
	Element<T> *iterator = element->right;
	if(iterator->left == nullptr){
		if(_data > element_parent->data)
			element_parent->right = iterator;
		else element_parent->left = iterator;
		iterator->left = element->left;
		return;
	}
	while (iterator->left != nullptr){
		iterator_parent = iterator;
		iterator = iterator->left;
	}
	element->data = iterator->data;
	iterator_parent->left = iterator->right; 
}

template<typename T>
fstream & operator >>(fstream & stream, BinarySearchTree<T> & tree){
	T temp;
	while(!stream.eof()){
		if (stream >> temp) tree.addElement(temp);
		else{ 
			return stream; 
		}
	}
	return stream;
}

template <typename T>
ostream & operator << (ostream & stream, BinarySearchTree<T> & tree) throw(EmptyTree){
	if(tree.get_root() == nullptr) throw EmptyTree();
	tree.out(tree.get_root(), stream, 1);
	return stream;
}

template <typename T>
BinarySearchTree<T> :: ~BinarySearchTree(){
	if(root!= nullptr) deleteElementChilds(root->data);
	root = nullptr;
}
