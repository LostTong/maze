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
	void remove_recursive(const ValueType &value, TreeNode<ValueType> *cur_node, TreeNode<ValueType> *prev_code);
	void clear();
	void clear_recursive(const TreeNode<ValueType> *cur_node);
	int get_size() const;
	TreeNode<ValueType> *get_last_node() const;

private:
	int size;
	
	TreeNode<ValueType> *root;
	TreeNode<ValueType> *last;
};

