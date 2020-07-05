#include "base-const-iterator.h"


namespace list_of_siblings
{

template<class Tp>
ConstTreeIterator<Tp>::ConstTreeIterator(std::nullptr_t)
{
	this->tree = nullptr;
	this->cursor = 0;
}

template<class Tp>
ConstTreeIterator<Tp>::ConstTreeIterator(const Tree<Tp> &tree)
{
	this->tree = &tree;
	this->cursor = tree.root;
}

template<class Tp>
ConstTreeIterator<Tp>::ConstTreeIterator(const Tree<Tp> &tree, position p)
{
	this->tree = &tree;
	this->cursor = p;
}

template<class Tp>
typename ConstTreeIterator<Tp>::reference
ConstTreeIterator<Tp>::operator*() const
{
	return tree->nodes[cursor].value;
}

template<class Tp>
typename ConstTreeIterator<Tp>::pointer
ConstTreeIterator<Tp>::operator->() const
{
	return &*(*this);
}

template<class Tp>
ConstTreeIterator<Tp>& ConstTreeIterator<Tp>::operator++()
{
	cursor++;
	return *this;
}

template<class Tp>
bool ConstTreeIterator<Tp>::operator==(const ConstTreeIterator<Tp> &rhs) const
{
	return tree == rhs.tree && cursor == rhs.cursor;
}

template<class Tp>
bool ConstTreeIterator<Tp>::operator!=(const ConstTreeIterator<Tp> &rhs) const
{
	return !(*this == rhs);
}

} // namespace list_of_siblings
