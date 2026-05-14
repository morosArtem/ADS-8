// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

template<typename T>
class BST {
 private:
  struct Node {
    T data;
    int count;
    Node* left;
    Node* right;
    Node(const T& value) : data(value), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root_;
  int size_;

  void insert(Node*& node, const T& value) {
    if (node == nullptr) {
      node = new Node(value);
      size_++;
      return;
    }
    if (value < node->data) {
      insert(node->left, value);
    } else if (value > node->data) {
      insert(node->right, value);
    } else {
      node->count++;
    }
  }

  bool search(Node* node, const T& value) const {
    if (node == nullptr) return false;
    if (value == node->data) return true;
    if (value < node->data) return search(node->left, value);
    return search(node->right, value);
  }

  int depth(Node* node) const {
    if (node == nullptr) return 0;
    int left_depth = depth(node->left);
    int right_depth = depth(node->right);
    return 1 + (left_depth > right_depth ? left_depth : right_depth);
  }

  void clear(Node* node) {
    if (node == nullptr) return;
    clear(node->left);
    clear(node->right);
    delete node;
  }

  void copyToArray(Node* node, std::string* words, int* counts,
                   int& index) const {
    if (node == nullptr) return;
    copyToArray(node->left, words, counts, index);
    words[index] = node->data;
    counts[index] = node->count;
    index++;
    copyToArray(node->right, words, counts, index);
  }

  void sortByFrequency(std::string* words, int* counts, int n) {
    for (int i = 0; i < n - 1; i++) {
      for (int j = i + 1; j < n; j++) {
        if (counts[i] < counts[j]) {
          int temp_count = counts[i];
          counts[i] = counts[j];
          counts[j] = temp_count;
          std::string temp_word = words[i];
          words[i] = words[j];
          words[j] = temp_word;
        }
      }
    }
  }

 public:
  BST() : root_(nullptr), size_(0) {}

  ~BST() {
    clear(root_);
  }

  void insert(const T& value) {
    insert(root_, value);
  }

  bool search(const T& value) const {
    return search(root_, value);
  }

  int depth() const {
    return depth(root_);
  }

  bool isEmpty() const {
    return root_ == nullptr;
  }

  int getCount(const T& value) const {
    Node* node = root_;
    while (node != nullptr) {
      if (value == node->data) return node->count;
      if (value < node->data) {
        node = node->left;
      } else {
        node = node->right;
      }
    }
    return 0;
  }

  int getSize() const {
    return size_;
  }

  void getWordsAndCounts(std::string* words, int* counts) const {
    int index = 0;
    copyToArray(root_, words, counts, index);
  }

  void sortWordsByFrequency(std::string* words, int* counts, int n) {
    sortByFrequency(words, counts, n);
  }
};

#endif  // INCLUDE_BST_H_
