
#include "tree.h"
#include <catch.hpp>
#include <fstream>

SCENARIO("Tree: init, getCount(), getNumber()", "[init, getCount(), getNumber()]") {
  BinarySearchTree <int> tree(5);
  BinarySearchTree <int> empty_tree;
  REQUIRE(tree.get_root()->data == 5);
  REQUIRE(empty_tree.get_root() == nullptr);
}
