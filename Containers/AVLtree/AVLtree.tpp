#include "AVLtree.h"

namespace s21 {

template <typename T, typename Comporator>
Tree<T, Comporator>::Tree(const Tree& other) : Tree() {
  *this = other;
}

template <typename T, typename Comporator>
Tree<T, Comporator>::Tree(Tree&& other) : Tree() {
  *this = std::move(other);
}

template <typename T, typename Comporator>
Tree<T, Comporator>::~Tree() {
  clear();
  delete endNode_;
}

template <typename T, typename Comporator>
void Tree<T, Comporator>::swap(Tree& other) {
  std::swap(root_, other.root_);
  std::swap(endNode_, other.endNode_);
  std::swap(size_, other.size_);
}

/*
merge
*/

template <typename T, typename Comporator>
void Tree<T, Comporator>::merge(Tree& other) {
  if (this != &other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      insert(*it);
    }
    other.clear();
  }
}

template <typename T, typename Comporator>
void Tree<T, Comporator>::mergeNonUniq(Tree& other) {
  if (this != &other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      insertNonUniq(*it);
    }
    other.clear();
  }
}

/*
insertNonUniq
Ввод в дерево неуникальных значений
*/

template <typename T, typename Comparator>
std::pair<typename Tree<T, Comparator>::iterator, bool>
Tree<T, Comparator>::insertNonUniq(const value_type& value) {
  Node* NewNode = new Node(value);

  if (root_ == nullptr) {
    root_ = NewNode;
  } else {
    Node* node = root_;
    while (true) {
      if (comp_(value, node->value_)) {
        if (node->leftNode_ == nullptr) {
          NewNode->parent_ = node;
          node->leftNode_ = NewNode;
          break;
        } else {
          node = node->leftNode_;
        }
      } else {
        if (node->rightNode_ == nullptr) {
          NewNode->parent_ = node;
          node->rightNode_ = NewNode;
          break;
        } else {
          node = node->rightNode_;
        }
      }
    }

    Node* currentNode = NewNode;
    while (currentNode != nullptr && currentNode != endNode_) {
      updateHeight(currentNode);
      balancingTree(&currentNode);

      currentNode = currentNode->parent_;
    }
  }

  ++size_;
  root_->parent_ = endNode_;
  endNode_->parent_ = find_max(root_);
  return std::make_pair(iterator(NewNode, endNode_), true);
}

/*
insert
Ввод в дерево уникальных значений
*/

template <typename T, typename Comparator>
std::pair<typename Tree<T, Comparator>::iterator, bool>
Tree<T, Comparator>::insert(const value_type& value) {
  Node* NewNode = new Node(value);

  if (root_ == nullptr) {
    root_ = NewNode;
  } else {
    Node* node = root_;
    while (true) {
      if (comp_(value, node->value_)) {
        if (node->leftNode_ == nullptr) {
          NewNode->parent_ = node;
          node->leftNode_ = NewNode;
          break;
        } else {
          node = node->leftNode_;
        }
      } else if (comp_(node->value_, value)) {
        if (node->rightNode_ == nullptr) {
          NewNode->parent_ = node;
          node->rightNode_ = NewNode;
          break;
        } else {
          node = node->rightNode_;
        }
      } else {
        delete NewNode;
        return std::make_pair(iterator(node, endNode_), false);
      }
    }

    Node* currentNode = NewNode;
    while (currentNode != nullptr && currentNode != endNode_) {
      updateHeight(currentNode);
      balancingTree(&currentNode);

      currentNode = currentNode->parent_;
    }
  }

  ++size_;
  root_->parent_ = endNode_;
  endNode_->parent_ = find_max(root_);
  return std::make_pair(iterator(NewNode, endNode_), true);
}

/*
erase
Удаление элемента по положению итератора
*/

template <typename T>
typename Iterator<T>::Node* Iterator<T>::getCurNode() {
  return curent_node_;
}

template <typename T, typename Comporator>
void Tree<T, Comporator>::erase(iterator pos) {
  Node* node = pos.getCurNode();
  if (!node || node == endNode_) return;

  Node* parent = node->parent_;
  Node* nodeToBalanceFrom = nullptr;

  if (!node->leftNode_ && !node->rightNode_) {
    if (parent && node != root_) {
      if (parent->leftNode_ == node)
        parent->leftNode_ = nullptr;
      else
        parent->rightNode_ = nullptr;
      nodeToBalanceFrom = parent;
    } else {
      root_ = nullptr;
    }
  } else if (node->leftNode_ && !node->rightNode_) {
    if (parent && node != root_) {
      if (parent->leftNode_ == node)
        parent->leftNode_ = node->leftNode_;
      else
        parent->rightNode_ = node->leftNode_;
      nodeToBalanceFrom = parent;
    } else {
      root_ = node->leftNode_;
    }
    node->leftNode_->parent_ = parent;
  } else if (!node->leftNode_ && node->rightNode_) {
    if (parent && node != root_) {
      if (parent->leftNode_ == node)
        parent->leftNode_ = node->rightNode_;
      else
        parent->rightNode_ = node->rightNode_;
      nodeToBalanceFrom = parent;
    } else {
      root_ = node->rightNode_;
    }
    node->rightNode_->parent_ = parent;
  } else {
    Node* successor = find_min(node->rightNode_);
    SwapNode(node, successor);
    erase(pos);
    return;
  }

  delete node;

  Node* current = nodeToBalanceFrom;
  while (current && current != endNode_) {
    updateHeight(current);
    balancingTree(&current);
    current = current->parent_;
  }

  --size_;
  if (root_) {
    root_->parent_ = endNode_;
    endNode_->parent_ = find_max(root_);
  } else {
    size_ = 0U;
  }
}

/*
size
*/

template <typename T, typename Comporator>
typename Tree<T, Comporator>::size_type Tree<T, Comporator>::size() const {
  return size_;
}

/*
max_size
*/

template <typename T, typename Comparator>
typename Tree<T, Comparator>::size_type Tree<T, Comparator>::max_size() const {
#if defined(__linux__)
  return (std::numeric_limits<std::ptrdiff_t>::max()) / sizeof(Node);
#else
  return std::numeric_limits<std::ptrdiff_t>::max() / (sizeof(Node) / 2U);
#endif
}

/*
heightTree
*/

template <typename T, typename Comporator>
int Tree<T, Comporator>::heightTree(Node* node) {
  if (node == nullptr || node == endNode_) {
    return 0;
  }

  int hLeft = heightTree(node->leftNode_);
  int hRight = heightTree(node->rightNode_);
  return std::max(hLeft, hRight) + 1;
}

/*
updateHeight(Node* node)
*/

template <typename T, typename Comporator>
void Tree<T, Comporator>::updateHeight(Node* node) {
  if (root_ == nullptr) {
    throw std::logic_error("The tree is empty");
  }
  if (node == nullptr || node == endNode_) {
    return;
  }
  int leftHeight = (node->leftNode_ && node->leftNode_ != endNode_)
                       ? heightTree(node->leftNode_)
                       : 0;
  int rightHeight = (node->rightNode_ && node->rightNode_ != endNode_)
                        ? heightTree(node->rightNode_)
                        : 0;
  node->height_ = std::max(leftHeight, rightHeight) + 1;
}

template <typename T, typename Comparator>
void Tree<T, Comparator>::SwapNode(Node* firstNode, Node* secondNode) {
  Node* root_tmp = root_;
  if (firstNode == root_tmp) {
    root_ = secondNode;
  } else {
    if (firstNode->parent_->leftNode_ == firstNode) {
      firstNode->parent_->leftNode_ = secondNode;
    } else {
      firstNode->parent_->rightNode_ = secondNode;
    }
  }
  if (secondNode == root_tmp) {
    root_ = firstNode;
  } else {
    if (secondNode->parent_->leftNode_ == secondNode) {
      secondNode->parent_->leftNode_ = firstNode;
    } else {
      secondNode->parent_->rightNode_ = firstNode;
    }
  }

  std::swap(firstNode->parent_, secondNode->parent_);
  std::swap(firstNode->leftNode_, secondNode->leftNode_);
  std::swap(firstNode->rightNode_, secondNode->rightNode_);
  std::swap(firstNode->height_, secondNode->height_);

  if (firstNode->leftNode_) {
    firstNode->leftNode_->parent_ = firstNode;
  }
  if (firstNode->rightNode_) {
    firstNode->rightNode_->parent_ = firstNode;
  }
  if (secondNode->leftNode_) {
    secondNode->leftNode_->parent_ = secondNode;
  }
  if (secondNode->rightNode_) {
    secondNode->rightNode_->parent_ = secondNode;
  }
  root_->parent_ = endNode_;
  endNode_->parent_ = find_max(root_);
}

/*
begin
*/

template <typename T, typename Comporator>
typename Tree<T, Comporator>::iterator Tree<T, Comporator>::begin() {
  if (root_) {
    return Iterator(find_min(root_), endNode_);
  } else {
    return end();
  }
}

template <typename T, typename Comporator>
typename Tree<T, Comporator>::const_iterator Tree<T, Comporator>::begin()
    const {
  if (root_) {
    return ConstIterator(find_min(root_), endNode_);
  } else {
    return end();
  }
}

/*
end
*/

template <typename T, typename Comporator>
typename Tree<T, Comporator>::iterator Tree<T, Comporator>::end() {
  return Iterator(endNode_, endNode_);
}

template <typename T, typename Comporator>
typename Tree<T, Comporator>::const_iterator Tree<T, Comporator>::end() const {
  return ConstIterator(endNode_, endNode_);
}

/*
find_min
*/

template <typename T, typename Comporator>
typename Tree<T, Comporator>::Node* Tree<T, Comporator>::find_min(
    Node* node) const {
  while (node->leftNode_ != nullptr) {
    node = node->leftNode_;
  }
  return node;
}

/*
find_max
*/

template <typename T, typename Comporator>
typename Tree<T, Comporator>::Node* Tree<T, Comporator>::find_max(
    Node* node) const {
  while (node->rightNode_ != nullptr) {
    node = node->rightNode_;
  }
  return node;
}

/*
empty
*/

template <typename T, typename Comporator>
bool Tree<T, Comporator>::empty() const {
  return root_ == nullptr;
}

/*
clear
*/

template <typename T, typename Comporator>
void Tree<T, Comporator>::clear() {
  if (root_ != nullptr) {
    deleteTree(root_);
  }
  root_ = nullptr;
  size_ = 0U;
}

template <typename T, typename Comporator>
typename Tree<T, Comporator>::iterator Tree<T, Comporator>::find(
    const_reference key) {
  auto foundIt = lower_bound(key);
  if (foundIt != end() && !(comp_(*foundIt, key) || comp_(key, *foundIt))) {
    return foundIt;
  } else {
    return end();
  }
}

template <typename T, typename Comporator>
bool Tree<T, Comporator>::contains(const_reference key) {
  if (!empty()) {
    return find(key) != end();
  } else
    return false;
}

template <typename T, typename Comparator>
typename Tree<T, Comparator>::iterator Tree<T, Comparator>::lower_bound(
    const_reference key) {
  Node* res = endNode_;
  Node* cur_node = root_;
  while (cur_node) {
    if (!comp_(cur_node->value_, key)) {
      res = cur_node;
      cur_node = cur_node->leftNode_;
    } else {
      cur_node = cur_node->rightNode_;
    }
  }
  return iterator(res, endNode_);
}

template <typename T, typename Comparator>
typename Tree<T, Comparator>::iterator Tree<T, Comparator>::upper_bound(
    const_reference key) {
  Node* res = endNode_;
  Node* cur_node = root_;
  while (cur_node) {
    if (comp_(key, cur_node->value_)) {
      res = cur_node;
      cur_node = cur_node->leftNode_;
    } else {
      cur_node = cur_node->rightNode_;
    }
  }
  return iterator(res, endNode_);
}

template <typename T, typename Comporator>
void Tree<T, Comporator>::deleteTree(Node* node) {
  if (node != nullptr) {
    deleteTree(node->leftNode_);
    deleteTree(node->rightNode_);
    delete node;
  }
}

template <typename T, typename Comporator>
Tree<T, Comporator>& Tree<T, Comporator>::operator=(const Tree& other) {
  if (this != &other) {
    clear();
    for (auto it = other.begin(); it != other.end(); ++it) {
      insertNonUniq(*it);
    }
  }
  return *this;
}

template <typename T, typename Comporator>
Tree<T, Comporator>& Tree<T, Comporator>::operator=(Tree&& other) {
  if (this != &other) {
    clear();
    std::swap(root_, other.root_);
    std::swap(endNode_, other.endNode_);
    std::swap(size_, other.size_);
  }
  return *this;
}

// -----------------------------------------------------------------------------------------------
// BALANCE

template <typename T, typename Comporator>
int Tree<T, Comporator>::getTreeBalance(Node* node) {
  if (node == nullptr || node == endNode_) {
    return 0;
  }
  return heightTree(node->rightNode_) - heightTree(node->leftNode_);
}

template <typename T, typename Comporator>
void Tree<T, Comporator>::turnLeft(Node** node) {
  Node* subR = (*node)->rightNode_;
  Node* subRL = subR->leftNode_;

  (*node)->rightNode_ = subRL;
  if (subRL) {
    subRL->parent_ = (*node);
  }

  subR->leftNode_ = (*node);
  Node* pParent = (*node)->parent_;
  (*node)->parent_ = subR;
  subR->parent_ = pParent;

  if ((*node) == root_) {
    root_ = subR;
  } else {
    if (pParent->leftNode_ == (*node)) {
      pParent->leftNode_ = subR;
    } else {
      pParent->rightNode_ = subR;
    }
  }
}

template <typename T, typename Comporator>
void Tree<T, Comporator>::turnRight(Node** node) {
  Node* subL = (*node)->leftNode_;
  Node* subLR = subL->rightNode_;

  (*node)->leftNode_ = subLR;
  if (subLR) {
    subLR->parent_ = (*node);
  }

  subL->rightNode_ = (*node);
  Node* pParent = (*node)->parent_;
  (*node)->parent_ = subL;
  subL->parent_ = pParent;

  if ((*node) == root_) {
    root_ = subL;
  } else {
    if (pParent->leftNode_ == (*node)) {
      pParent->leftNode_ = subL;
    } else {
      pParent->rightNode_ = subL;
    }
  }
}

template <typename T, typename Comporator>
void Tree<T, Comporator>::turnRightLeft(Node** node) {
  turnRight(&(*node)->rightNode_);
  turnLeft(&(*node));
}

template <typename T, typename Comporator>
void Tree<T, Comporator>::turnLeftRight(Node** node) {
  turnLeft(&(*node)->leftNode_);
  turnRight(&(*node));
}

template <typename T, typename Comporator>
void Tree<T, Comporator>::balancingTree(Node** node) {
  if (*node == nullptr || *node == endNode_) {
    return;
  }
  int leftBalance = getTreeBalance((*node)->leftNode_);
  int rightBalance = getTreeBalance((*node)->rightNode_);
  int rootBalance = getTreeBalance((*node));

  if (rootBalance == 2 && rightBalance == 1) {
    turnLeft(&(*node));
  }

  if (rootBalance == -2 && leftBalance == -1) {
    turnRight(&(*node));
  }

  if (rootBalance == 2 && rightBalance == -1) {
    turnRightLeft(&(*node));
  }

  if (rootBalance == -2 && leftBalance == 1) {
    turnLeftRight(&(*node));
  }
}

// -----------------------------------------------------------------------------------------------
// PRINT

template <typename T, typename Comporator>
void Tree<T, Comporator>::printTree() {
  std::cout << "==== TREE ====" << std::endl;
  printTree(root_);
  std::cout << std::endl << "==== TREE ====" << std::endl;
}

template <typename T, typename Comporator>
void Tree<T, Comporator>::printTree(Node* node) {
  if (node != nullptr) {
    static int depth = 0;
    if (depth == 0) {
      std::cout << "root -> ";
      std::cout << node->value_ << " ";
      std::cout << "<- root " << std::endl;
    }
    depth++;

    printTree(node->leftNode_);
    std::cout << node->value_ << " ";
    printTree(node->rightNode_);

    depth--;
  }
}

// -----------------------------------------------------------------------------------------------
// ITERATOR

template <typename T>
Iterator<T>::Iterator(const Iterator& other) {
  *this = other;
}

template <typename T>
Iterator<T>::Iterator(Iterator&& other) {
  if (this != &other) {
    curent_node_ = other.curent_node_;
    end_node_ = other.end_node_;
    other.curent_node_ = nullptr;
    other.end_node_ = nullptr;
  }
}

template <typename T>
Iterator<T>& Iterator<T>::operator=(const Iterator& other) {
  if (this != &other) {
    curent_node_ = other.curent_node_;
    end_node_ = other.end_node_;
  }
  return *this;
}

template <typename T>
bool Iterator<T>::operator==(Iterator& other) const {
  return curent_node_ == other.curent_node_;
}

template <typename T>
bool Iterator<T>::operator==(const Iterator& other) const {
  return curent_node_ == other.curent_node_;
}

template <typename T>
bool Iterator<T>::operator!=(Iterator& other) const {
  return curent_node_ != other.curent_node_;
}

template <typename T>
bool Iterator<T>::operator!=(const Iterator& other) const {
  return curent_node_ != other.curent_node_;
}

template <typename T>
Iterator<T>& Iterator<T>::operator++() {
  if (curent_node_ && curent_node_->rightNode_) {
    Node* rightNode = curent_node_->rightNode_;
    while (rightNode->leftNode_) {
      rightNode = rightNode->leftNode_;
    }
    curent_node_ = rightNode;
  } else if (curent_node_) {
    Node* parent = curent_node_->parent_;
    while (parent && parent->rightNode_ == curent_node_) {
      curent_node_ = parent;
      parent = curent_node_->parent_;
    }
    curent_node_ = parent;
  }
  return *this;
}

template <typename T>
Iterator<T>& Iterator<T>::operator--() {
  if (curent_node_ && curent_node_->leftNode_) {
    Node* leftNode = curent_node_->leftNode_;
    while (leftNode->rightNode_) {
      leftNode = leftNode->rightNode_;
    }
    curent_node_ = leftNode;
  } else if (curent_node_) {
    Node* parent = curent_node_->parent_;
    while (parent && parent->leftNode_ == curent_node_) {
      curent_node_ = parent;
      parent = curent_node_->parent_;
    }
    curent_node_ = parent;
  }
  return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator++(int) {
  Iterator tmp(*this);
  ++(*this);
  return tmp;
}

template <typename T>
Iterator<T> Iterator<T>::operator--(int) {
  Iterator tmp(*this);
  --(*this);
  return tmp;
}

template <typename T>
typename Iterator<T>::reference Iterator<T>::operator*() {
  return curent_node_->value_;
}

template <typename T>
typename Iterator<T>::value_type* Iterator<T>::operator->() {
  return &curent_node_->value_;
}

}  // namespace s21