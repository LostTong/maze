#include "set.h"


template <typename ValueType>
Set::Set()
{
}

template <typename ValueType>
Set::~Set()
{
}

template <typename ValueType>
void Set::add(const ValueType &value) {
	add_rescusive(value, root);
}

template <typename ValueType>
void Set::add_recursive(const ValueType &value, TreeNode<ValueType> *cur_node) {
	if (curr == nullptr) {
		root = new TreeNode<ValueType>(value);
	}
	else {
		if (value > cur_node->value) {
			if (cur_node->right == nullptr) {
				curr_node->right = new TreeNode<ValueType>(value);
			}
			else {
				add_rescursive(value, cur_node->right);
			}
		}
		else {
			if (value < cur_node->left) {
				if (cur_node->left == nullptr) {
					cur_node->left = TreeNode<ValueType>(value);
				}
				else {
					add_rescursive(value, cur_node->left);
				}
			}
		}
	}
}

template <typename ValueType>
bool Set::contain(const ValueType &value) const {
	return contains_recursive(value, root);
}

template <typename ValueType>
bool Set::contain_recursive(const ValueType &value, TreeNode<ValueType> *cur_node) const {
	if (cur_node == nullptr) {
		return false;
	}
	else if(value == cur_node->value){
		return true;
	}
	else {
		if (value > curr_node->value) {
			return contain_recursive(value, cur_node->right);
		}
		else {
			return contain_recursive(value, cur_node->left);
		}
	}
}

template <typename ValueType>
void Set::remove(const ValueType &value) {
	remove_recursive(value, root, nullptr);
}

template <typename ValueType>
void Set::remove_recursive(const ValueType &value, TreeNode<ValueType> *cur_node, )