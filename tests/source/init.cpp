
#include "tree.h"
#include <catch.hpp>
#include <fstream>

SCENARIO("Tree init", "[init]") {
  BinarySearchTree <int> tree(5);
  BinarySearchTree <int> empty_tree;
  REQUIRE(tree.get_root()->data == 5);
  REQUIRE(empty_tree.get_root() == nullptr);
}

SCENARIO("Adding element", "[add]"){
  BinarySearchTree <int> tree(5);
  bool flag = false;
  tree.addElement(6);
  tree.addElement(3);
  REQUIRE(tree.get_root()->left->data == 3);
  REQUIRE(tree.get_root()->right->data == 6);
  try{
    tree.addElement(6);
  }
  catch(std::exception &e){
    flag = true;
  }
  REQUIRE(flag);
}

SCENARIO("fstream", "[fstream]"){
  fstream filein("1.txt");
  fstream fileout("out.txt");
  BinarySearchTree <int> tree(5);
  file >> tree;
  REQUIRE(tree.get_root()->left->data == 4);
  REQUIRE(tree.get_root()->right->data == 6);
  fileout << tree;
  
}

SCENARIO("Search element", "[search]"){
  BinarySearchTree <int> tree(5);
  tree.addElement(6);
  tree.addElement(3);
  REQUIRE(tree.searchElement(6)->data == 6);
  REQUIRE(tree.searchElement(221) == nullptr;)
}
