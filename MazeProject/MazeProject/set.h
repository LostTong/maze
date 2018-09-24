#pragma once

template <typename ValueType>
class Set
{
public:
	Set();
	~Set();

	void add(const ValueType &value);
	void add_recusive(const ValueType &value, TreeNode<ValueType> *cur_node);
	void contains(const ValueType &value) const;
	void contains_recursive(const ValueType &value, TreeNode<ValueType> *cur_node) const;
	void remove(const ValueType &value);
	int get_size() const;
	int size;
	
	TreeNode<ValueType> *root;
};

