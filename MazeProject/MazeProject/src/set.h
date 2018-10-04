#pragma once

#include <unordered_map>

#include "tree_node.h"

template <typename ValueType>
class Set
{
public:
	Set();
	~Set();

	void add(const ValueType *value);
	bool contain(const ValueType *value) const;
	void remove(const ValueType *value);
	void clear();
	TreeNode<ValueType> *pop();
	int get_size() const;
	ValueType *get_value(int idx);

private:
	void add_recursive(const ValueType &value, TreeNode<ValueType> *cur_node);
	bool contain_recursive(const ValueType &value, TreeNode<ValueType> *cur_node) const;
	void remove_recursive(const ValueType &value, TreeNode<ValueType> *cur_node, TreeNode<ValueType> *prev_node);
	void clear_recursive(const TreeNode<ValueType> *cur_node);
	TreeNode<ValueType> *get_last_node() const;

	int size;
	TreeNode<ValueType> *root;
	TreeNode<ValueType> *last;
	std::unordered_map<ValueType *, int> value_map;
};

