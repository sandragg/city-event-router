#include "base-iterator.h"
using namespace list_of_siblings;


template<class _Tp>
TreeIterator<_Tp>::TreeIterator(std::nullptr_t)
{
	this->tree = nullptr;
	this->cursor = 0;
}

template<class _Tp>
TreeIterator<_Tp>::TreeIterator(Tree<_Tp> *tree)
{
	this->tree = tree;
	this->cursor = tree->root;
}

template<class _Tp>
TreeIterator<_Tp>::TreeIterator(Tree<_Tp> *tree, position p)
{
	this->tree = tree;
	this->cursor = p;
}

template<class _Tp>
typename TreeIterator<_Tp>::reference TreeIterator<_Tp>::operator*() const
{
	return (*tree->nodes)[cursor].value;
}

template<class _Tp>
TreeIterator<_Tp>& TreeIterator<_Tp>::operator++()
{
	cursor++;
	return *this;
}

template<class _Tp>
bool TreeIterator<_Tp>::operator==(const TreeIterator<_Tp> &rhs) const
{
	return tree == rhs.tree && cursor == rhs.cursor;
}

template<class _Tp>
bool TreeIterator<_Tp>::operator!=(const TreeIterator<_Tp> &rhs) const
{
	return !(*this == rhs);
}
