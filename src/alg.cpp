// Copyright 2021 NNTU-CS
#include <fstream>
#include <cctype>
#include <string>
#include <iostream>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  auto is_latin_letter = [](char c) -> bool {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
  };

  auto to_lower = [](char c) -> char {
    if (c >= 'A' && c <= 'Z') {
      return c + ('a' - 'A');
    }
    return c;
  };

  auto clean_word = [&](const std::string& word) -> std::string {
    std::string result;
    for (char c : word) {
      if (is_latin_letter(c)) {
        result += to_lower(c);
      }
    }
    return result;
  };

  std::ifstream file(filename);
  if (!file) {
    return;
  }

  std::string current_word;
  char ch;

  while (file.get(ch)) {
    if (is_latin_letter(ch)) {
      current_word += to_lower(ch);
    } else {
      if (!current_word.empty()) {
        tree.insert(current_word);
        current_word.clear();
      }
    }
  }

  if (!current_word.empty()) {
    tree.insert(current_word);
  }

  file.close();
}

void printFreq(BST<std::string>& tree) {
  int size = tree.size();
  if (size == 0) {
    return;
  }

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
