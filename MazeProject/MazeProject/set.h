#pragma once

#include "tree_node.h"

template <typename ValueType>
class Set
{
public:
	Set();
	~Set();

	void add(const ValueType &value);
	bool contain(const ValueType &value) const;
	void remove(const ValueType &value);
	void clear();
	int get_size() const;
	TreeNode<ValueType> *get_last_node() const;

private:
	void add_recursive(const ValueType &value, TreeNode<ValueType> *cur_node);
	bool contain_recursive(const ValueType &value, TreeNode<ValueType> *cur_node) const;
	void remove_recursive(const ValueType &value, TreeNode<ValueType> *cur_node, TreeNode<ValueType> *prev_node);
	void clear_recursive(const TreeNode<ValueType> *cur_node);

	int size;
	TreeNode<ValueType> *root;
	TreeNode<ValueType> *last;
};

