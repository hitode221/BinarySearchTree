
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
  BinarySearhTree <int> tree(5);
  tree.addElement(6);
  tree.addElement(3);
  REQUIRE(tree.get_root()->left == 3);
  REQUIRE(tree.get_root()->right == 6);
}
