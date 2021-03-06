#pragma once

template <typename ValueType>
class TreeNode
{
public:
	TreeNode(const ValueType *value);
	~TreeNode();

	
	TreeNode<ValueType> *left;
	TreeNode<ValueType> *right;
	TreeNode<ValueType> *prev;
	ValueType *value;
	int height;

	bool operator == (const TreeNode<ValueType> *node) const {
		return (node != nullptr && this->value == node->value);
	}
};

template <typename ValueType>
TreeNode<ValueType>::TreeNode(const ValueType *value)
{
	left = nullptr;
	right = nullptr;
	prev = nullptr;
	this->value = const_cast<ValueType *>(value);
	height = 0;
}

template <typename ValueType>
TreeNode<ValueType>::~TreeNode()
{
}