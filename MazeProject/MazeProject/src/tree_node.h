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
};


template <typename ValueType>
TreeNode<typename ValueType>::TreeNode(const ValueType *value)
{
	left = nullptr;
	right = nullptr;
	prev = nullptr;
	this->value = const_cast<ValueType *>(value);
}

template <typename ValueType>
TreeNode<typename ValueType>::~TreeNode()
{
}