// Copyright 2021 NNTU-CS
#include <fstream>
#include <cctype>
#include <string>
#include <iostream>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) return;

  std::string word;
  char ch;

  while (file.get(ch)) {
    if (std::isalpha(ch)) {
      word += std::tolower(ch);
    } else {
      if (!word.empty()) {
        tree.insert(word);
        word.clear();
      }
    }
  }

  if (!word.empty()) {
    tree.insert(word);
  }

  file.close();
}

void printFreq(BST<std::string>& tree) {
  std::cout << "Tree size: " << tree.size() << std::endl;
  std::cout << "Tree depth: " << tree.depth() << std::endl;
}
