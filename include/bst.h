// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <algorithm>

template<typename T>
class BST {
 public:
  BST() : root_(nullptr), size_(0) {}

  ~BST() {
    clear(root_);
  }

  void insert(const T& value) {
    insert(root_, value);
  }

  int search(const T& value) const {
    return search(root_, value);
  }

  int depth() const {
    return depth(root_) - 1;
}

  bool empty() const {
    return root_ == nullptr;
  }

  int size() const {
    return size_;
  }

 private:
  struct Node {
    T data;
    int count;
    Node* left;
    Node* right;
    explicit Node(const T& value) : data(value), count(1), left(nullptr), right(nullptr) {}
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

  int search(Node* node, const T& value) const {
    if (node == nullptr) return 0;
    if (value == node->data) return node->count;
    if (value < node->data) return search(node->left, value);
    return search(node->right, value);
  }

  int depth(Node* node) const {
    if (node == nullptr) return 0;
    int left_depth = depth(node->left);
    int right_depth = depth(node->right);
    return std::max(left_depth, right_depth) + 1;
}

  void clear(Node* node) {
    if (node == nullptr) return;
    clear(node->left);
    clear(node->right);
    delete node;
  }
};

#endif  // INCLUDE_BST_H_
