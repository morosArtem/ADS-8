// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

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
      current_word += ch;
    } else {
      if (!current_word.empty()) {
        std::string cleaned = clean_word(current_word);
        if (!cleaned.empty()) {
          tree.insert(cleaned);
        }
        current_word.clear();
      }
    }
  }

  if (!current_word.empty()) {
    std::string cleaned = clean_word(current_word);
    if (!cleaned.empty()) {
      tree.insert(cleaned);
    }
  }

  file.close();
}

void printFreq(BST<std::string>& tree) {
  int size = tree.getSize();
  if (size == 0) {
    return;
  }

  std::string* words = new std::string[size];
  int* counts = new int[size];

  tree.getWordsAndCounts(words, counts);
  tree.sortWordsByFrequency(words, counts, size);

  std::ofstream outFile("result/freq.txt");
  if (!outFile) {
    delete[] words;
    delete[] counts;
    return;
  }

  for (int i = 0; i < size; i++) {
    std::cout << words[i] << ": " << counts[i] << std::endl;
    outFile << words[i] << ": " << counts[i] << std::endl;
  }

  outFile.close();
  delete[] words;
  delete[] counts;
}
