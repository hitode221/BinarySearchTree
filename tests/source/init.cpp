#include <tree.h>
#include <catch.hpp>
#include <fstream>
#include <iostream>

SCENARIO("Init", "[Tree init]") {
  BinarySearchTree <int> tree(5);
  BinarySearchTree <int> empty_tree;
  //REQUIRE(tree.get_root()->data == 5);
  //REQUIRE(empty_tree.get_root() == nullptr);
}
