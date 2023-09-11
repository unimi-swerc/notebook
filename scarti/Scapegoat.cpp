#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <queue>
#include <vector>

namespace ostuni {
template <typename T> class scapegoat;

template <typename T> class _scapegoat_node {
protected:
  unsigned tree_size;
  T value;
  int left_child;
  int right_child;
  int parent;
  void reset(const T& v = T()) {
    tree_size = 1;
    value = v;
    left_child = -1;
    right_child = -1;
    parent = -1;
  }
  _scapegoat_node(const T& v) { reset(v); }

public:
  friend class scapegoat<T>;
};

template <typename T> class scapegoat {
protected:
  double a;
  std::vector<_scapegoat_node<T>> nodes;
  std::queue<int> unused_nodes;
  int root_node;
  unsigned max_size;
  int _find(const T& v, int node) {
    if(nodes[node].value == v)
      return node;
    if(v < nodes[node].value) {
      if(nodes[node].left_child == -1)
        return -1;
      return _find(v, nodes[node].left_child);
    } else {
      if(nodes[node].right_child == -1)
        return -1;
      return _find(v, nodes[node].right_child);
    }
  }
  int _get_node_size(int node) {
    if(node == -1)
      return 0;
    return nodes[node].tree_size;
  }
  int _find_scapegoat(int node) {
    if(node == root_node)
      return node;
    bool e1 =
        _get_node_size(nodes[node].left_child) <= a * _get_node_size(node);
    bool e2 =
        _get_node_size(nodes[node].right_child) <= a * _get_node_size(node);
    if(!(e1 && e2))
      return node;
    return _find_scapegoat(nodes[node].parent);
  }
  int _get_free_node(const T& v = T()) {
    if(!unused_nodes.empty()) {
      int tmp = unused_nodes.front();
      unused_nodes.pop();
      nodes[tmp].reset(v);
      return tmp;
    } else {
      nodes.push_back(_scapegoat_node<T>(v));
      return nodes.size() - 1;
    }
  }
  void _inorder(int node, std::vector<int>& v) {
    if(node == -1)
      return;
    _inorder(nodes[node].left_child, v);
    v.push_back(node);
    _inorder(nodes[node].right_child, v);
  }
  void _rr(int s, int e, std::vector<int>& r, int parent, bool left) {
    if(s == e)
      return;
    int m = (s + e) / 2;
    nodes[r[m]].left_child = -1;
    nodes[r[m]].right_child = -1;
    nodes[r[m]].parent = parent;
    nodes[r[m]].tree_size = e - s;
    if(parent == -1)
      root_node = r[m];
    if(left) {
      if(parent != -1)
        nodes[parent].left_child = r[m];
    } else {
      if(parent != -1)
        nodes[parent].right_child = r[m];
    }
    if(s == e - 1)
      return;
    _rr(s, m, r, r[m], true);
    _rr(m + 1, e, r, r[m], false);
  }
  void _rebalance(int node) {
    int scp = node;
    int scp_parent = nodes[node].parent;
    std::vector<int> rebalanced;
    _inorder(node, rebalanced);
    _rr(0, rebalanced.size(), rebalanced, scp_parent,
        (scp_parent == -1) || (scp == nodes[scp_parent].left_child));
  }
  void _insert(const T& v) {
    if(!nodes.size() || (nodes.size() == unused_nodes.size())) {
      root_node = _get_free_node(v);
      return;
    }
    int node = root_node;
    int depth = 1;
    while(true) {
      nodes[node].tree_size++;
      if(v < nodes[node].value) {
        if(nodes[node].left_child == -1) {
          int tmp = _get_free_node(v);
          nodes[tmp].parent = node;
          nodes[node].left_child = tmp;
          break;
        } else {
          node = nodes[node].left_child;
        }
      } else {
        if(nodes[node].right_child == -1) {
          int tmp = _get_free_node(v);
          nodes[tmp].parent = node;
          nodes[node].right_child = tmp;
          break;
        } else {
          node = nodes[node].right_child;
        }
      }
      depth++;
    }
    bool balanced =
        depth <= ((log(nodes[root_node].tree_size) / log(1.0 / a)) + 1.0);
    if(balanced)
      return;
    int scp = _find_scapegoat(node);
    _rebalance(scp);
  }
  void _decrease(int node) {
    if(node == -1)
      return;
    nodes[node].tree_size--;
    _decrease(nodes[node].parent);
  }
  void _erase(int node) {
    if(nodes[node].left_child == -1 && nodes[node].right_child == -1) {
      int parent = nodes[node].parent;
      if(parent == -1) {
        unused_nodes.push(node);
        return;
      }
      if(node == nodes[parent].left_child) {
        nodes[parent].left_child = -1;
      } else {
        nodes[parent].right_child = -1;
      }
      _decrease(parent);
      unused_nodes.push(node);
      bool balanced = nodes[root_node].tree_size > a * max_size;
      if(!balanced) {
        _rebalance(root_node);
        max_size = nodes[root_node].tree_size;
      }
      return;
    } else if(nodes[node].left_child != -1) {
      int rnode = nodes[node].left_child;
      while(nodes[rnode].right_child != -1)
        rnode = nodes[rnode].right_child;
      std::swap(nodes[rnode].value, nodes[node].value);
      _erase(rnode);
    } else {
      int rnode = nodes[node].right_child;
      while(nodes[rnode].left_child != -1)
        rnode = nodes[rnode].left_child;
      std::swap(nodes[rnode].value, nodes[node].value);
      _erase(rnode);
    }
  }

public:
  scapegoat(double balance_factor = 2.0 / 3.0) {
    assert(balance_factor > 0.5 && balance_factor < 1.0);
    a = balance_factor;
    root_node = -1;
    max_size = 0;
  }
  bool find(const T& v) {
    return nodes.size() && (nodes.size() != unused_nodes.size()) &&
           (_find(v, root_node) != -1);
  }
  bool insert(const T& v) {
    if(find(v))
      return false;
    _insert(v);
    max_size = std::max(max_size, nodes[root_node].tree_size);
    return true;
  }
  bool erase(const T& v) {
    if(!nodes.size())
      return false;
    int node = _find(v, root_node);
    if(node == -1)
      return false;
    _erase(node);
    return true;
  }
  size_t size() {
    if(nodes.size() == 0 || (nodes.size() == unused_nodes.size()))
      return 0;
    return nodes[root_node].tree_size;
  }
};
} // namespace ostuni
