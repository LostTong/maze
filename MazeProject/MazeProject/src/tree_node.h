#pragma once

template <typename ValueType>
class TreeNode
{
public:
	TreeNode(const ValueType *value);
	~TreeNode();

	TreeNode<ValueType> *left;
	TreeNode<ValueType> *right;
	TreNode<ValueType> *prev;
	ValueType *value;
};


