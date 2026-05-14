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
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
      if (ch >= 'A' && ch <= 'Z') {
        word += ch + ('a' - 'A');
      } else {
        word += ch;
      }
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
  int size = tree.size();
  if (size == 0) return;

  std::string* words = new std::string[size];
  int* counts = new int[size];

  tree.getWordsAndCounts(words, counts);
  tree.sortWordsByFrequency(words, counts, size);

  std::ofstream out_file("result/freq.txt");

  for (int i = 0; i < size; i++) {
    std::cout << words[i] << ": " << counts[i] << std::endl;
    out_file << words[i] << ": " << counts[i] << std::endl;
  }

  out_file.close();
  delete[] words;
  delete[] counts;
}
