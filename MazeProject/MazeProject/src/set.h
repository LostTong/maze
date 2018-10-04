#pragma once

#include <iostream>
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
	void remove(ValueType *value);
	void clear();
	ValueType *pop();
	ValueType *get_last();
	int get_size() const;
	ValueType *get_value(int idx);

private:
	void add_recursive(const ValueType &value, TreeNode<ValueType> *cur_node);
	bool contain_recursive(const ValueType &value, TreeNode<ValueType> *cur_node) const;
	void remove_recursive(ValueType *value, TreeNode<ValueType> *cur_node, TreeNode<ValueType> *prev_node);
	void clear_recursive(const TreeNode<ValueType> *cur_node);
	TreeNode<ValueType> *get_last_node() const;

	int size;
	TreeNode<ValueType> *root;
	TreeNode<ValueType> *last;
	std::unordered_map<const ValueType *, int> value_map;
};

template <typename ValueType>
Set<ValueType>::Set()
{
}

template <typename ValueType>
Set<ValueType>::~Set()
{
	clear();
}

template <typename ValueType>
void Set<ValueType>::add(const ValueType *value) {
	add_recursive(*value, root);
	value_map.insert({value, get_size() - 1});
}

template <typename ValueType>
void Set<ValueType>::add_recursive(const ValueType &value, TreeNode<ValueType> *cur_node) {
	// root
	if (cur_node == nullptr) {
		cur_node = new TreeNode<ValueType>(&value);
		last = cur_node;
		size += 1;
		root = cur_node;
	}
	else {
		// left
		if (value < *(cur_node->value)) {
			if (cur_node->left == nullptr) {
				cur_node->left = new TreeNode<ValueType>(&value);
				cur_node->left->prev = last;
				last = cur_node->left;
				size += 1;
				//std::cout << "prev x,y:" << cur_node->value->get_x_position() << ", " << cur_node->value->get_y_position() << std::endl;
				//std::cout << "left value x,y:" << cur_node->left->value->get_x_position() << ", " << cur_node->left->value->get_y_position() << std::endl;
			}
			else {
				add_recursive(value, cur_node->left);
			}
		}
		// right
		else {
			if (cur_node->right == nullptr) {
				cur_node->right = new TreeNode<ValueType>(&value);
				cur_node->right->prev = last;
				last = cur_node->right;
				size += 1;
				//std::cout << "prev x,y:" << cur_node->value->get_x_position() << ", " << cur_node->value->get_y_position() << std::endl;
				//std::cout << "right value x,y:" << cur_node->right->value->get_x_position() << ", " << cur_node->right->value->get_y_position() << std::endl;
			}
			else {
				add_recursive(value, cur_node->right);
			}
		}
	}
}

template <typename ValueType>
bool Set<ValueType>::contain(const ValueType *value) const {
	return contain_recursive(*value, root);
}

template <typename ValueType>
bool Set<ValueType>::contain_recursive(const ValueType &value, TreeNode<ValueType> *cur_node) const {
	if (cur_node == nullptr) {
		return false;
	}
	if (&value == cur_node->value) {
		return true;
	}
	if (value < *(cur_node->value)) {
		return contain_recursive(value, cur_node->left);
	}
	return contain_recursive(value, cur_node->right);
}

template <typename ValueType>
void Set<ValueType>::remove(ValueType *value) {
	remove_recursive(value, root, nullptr);
}

template <typename ValueType>
void Set<ValueType>::remove_recursive(ValueType *value, TreeNode<ValueType> *cur_node, TreeNode<ValueType> *prev_node) {
	//std::cout << "value x, y:" << value->x_pos << ", " << value->y_pos << " cur_node x,y:" << cur_node->value->x_pos << ", " << cur_node->value->y_pos << std::endl;
	if (cur_node != nullptr) {
		if (value == cur_node->value) {
			if (value == last->value) {
				last = last->prev;
			}
			size -= 1;

			//std::cout << "value x, y:" << value->x_pos << ", " << value->y_pos << " cur_node x,y:" << cur_node->value->x_pos << ", " << cur_node->value->y_pos << std::endl;

			// left
			if (cur_node->left != nullptr) {
				// root     
				if (prev_node == nullptr) {
					root = cur_node->left;
				}
				// left
				else if (prev_node->left == cur_node) {
					prev_node->left = cur_node->left;
				}
				// right
				else {
					prev_node->right = cur_node->left;
				}
				if (cur_node->right != nullptr) {
					TreeNode<ValueType> *tmp_node = cur_node->left;
					while (tmp_node->right != nullptr) {
						tmp_node = tmp_node->right;
					}
					tmp_node->right = cur_node->right;
				}
			}
			// right
			else if (cur_node->right != nullptr) {
				// root
				if (prev_node == nullptr) {
					root = cur_node->right;
				}
				// left
				else if (prev_node->left == cur_node) {
					prev_node->left = cur_node->right;
				}
				// right
				else {
					prev_node->right = cur_node->right;
				}
			}
			// leaf
			else {
				// root
				if (prev_node == nullptr) {
					root = nullptr;
				}
				// left
				else if (prev_node->left == cur_node) {
					prev_node->left = nullptr;
				}
				// right
				else {
					prev_node->right = nullptr;
				}
			}
			value_map.erase(value);
			delete cur_node;
		}
		else {
			if (*(cur_node->value) > *value) {
				remove_recursive(value, cur_node->left, cur_node);
			}
			else {
				remove_recursive(value, cur_node->right, cur_node);
			}
		}
	}
}

template <typename ValueType>
void Set<ValueType>::clear() {
	clear_recursive(root);
	root = last = nullptr;
}

template <typename ValueType>
void Set<ValueType>::clear_recursive(const TreeNode<ValueType> *cur_node) {
	if (cur_node == nullptr) {
		return;
	}
	if (cur_node->left != nullptr) {
		clear_recursive(cur_node->left);
	}
	if (cur_node->right != nullptr) {
		clear_recursive(cur_node->right);
	}
	delete curr_node;
}

template <typename ValueType>
TreeNode<ValueType> *Set<ValueType>::get_last_node() const {
	return last;
}

template <typename ValueType>
int Set<ValueType>::get_size() const {
	return size;
}

template <typename ValueType>
ValueType *Set<ValueType>::pop() {
	if (last == nullptr) {
		return nullptr;
	}
	TreeNode<ValueType> *tmp = last;
	remove(last->value);
	last = last->prev;
	return tmp->value;
}

template <typename ValueType>
ValueType *Set<ValueType>::get_last() {
	if (last == nullptr) {
		return nullptr;
	}
	return last->value;
}


template <typename ValueType>
ValueType *Set<ValueType>::get_value(int idx) {
	int tmp = idx % value_map.size();
	std::unordered_map<const ValueType *, int>::iterator it = value_map.begin();
	std::advance(it, tmp);
 	return const_cast<ValueType *>(it->first);
}