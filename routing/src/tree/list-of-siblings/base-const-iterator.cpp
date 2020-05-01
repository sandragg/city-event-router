#include "base-const-iterator.h"


namespace list_of_siblings
{

template<class _Tp>
ConstTreeIterator<_Tp>::ConstTreeIterator(std::nullptr_t)
{
	this->tree = nullptr;
	this->cursor = 0;
}

template<class _Tp>
ConstTreeIterator<_Tp>::ConstTreeIterator(const Tree<_Tp> &tree)
{
	this->tree = &tree;
	this->cursor = tree.root;
}

template<class _Tp>
ConstTreeIterator<_Tp>::ConstTreeIterator(const Tree<_Tp> &tree, position p)
{
	this->tree = &tree;
	this->cursor = p;
}

template<class _Tp>
typename ConstTreeIterator<_Tp>::reference
ConstTreeIterator<_Tp>::operator*() const
{
	return tree->nodes[cursor].value;
}

template<class _Tp>
typename ConstTreeIterator<_Tp>::pointer
ConstTreeIterator<_Tp>::operator->() const
{
	return &*(*this);
}

template<class _Tp>
ConstTreeIterator<_Tp>& ConstTreeIterator<_Tp>::operator++()
{
	cursor++;
	return *this;
}

template<class _Tp>
bool ConstTreeIterator<_Tp>::operator==(const ConstTreeIterator<_Tp> &rhs) const
{
	return tree == rhs.tree && cursor == rhs.cursor;
}

template<class _Tp>
bool ConstTreeIterator<_Tp>::operator!=(const ConstTreeIterator<_Tp> &rhs) const
{
	return !(*this == rhs);
}

} // namespace list_of_siblings
