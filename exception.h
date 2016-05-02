#pragma once
#include <exception>
using namespace std;

class TreeException : public std::exception{
public:
	TreeException() : std::exception(invalid_argument("Unknown exception")){};
	TreeException(const char *_message) : exception(invalid_argument(_message)){};
};

class EmptyTree : public TreeException{
public:
	EmptyTree() : TreeException("Tree is empty"){};
};

class AddingElementException : public TreeException{
public:
	AddingElementException() : TreeException("Cannot adding element"){};
};
