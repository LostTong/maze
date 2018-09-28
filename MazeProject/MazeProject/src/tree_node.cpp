#include "tree_node.h"


template <typename ValueType>
TreeNode<typename ValueType>::TreeNode(const ValueType *value)
{
	left = nullptr;
	right = nullptr;
	prev = nullptr;
	this->value = value;
}

template <typename ValueType>
TreeNode<typename ValueType>::~TreeNode()
{
}