#include "tree_node.h"


template <typename ValueType>
TreeNode<typename ValueType>::TreeNode(const ValueType &value)
{
	left = nullptr;
	right = nullptr;
	this->value = value;
}

template <typename ValueType>
TreeNode<typename ValueType>::~TreeNode()
{
}

template <typename ValueType>
bool operator < (const TreeNode<ValueType> &left_node, const TreeNode<ValueType> &right_node) {
	return left_node.value < right_node.value;
}

template <typename ValueType>
bool operator > (const TreeNode<ValueType> &left_node, const TreeNode<ValueType> &right_node) {
	return left_node.value > right_node.value;
}

template <typename ValueType>
bool operator == (const TreeNode<ValueType> &left_node, const TreeNode<ValueType> &right_node) {
	return left_node.value == right_node.value;
}