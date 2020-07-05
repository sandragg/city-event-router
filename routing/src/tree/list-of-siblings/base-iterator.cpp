#include "base-iterator.h"


namespace list_of_siblings
{

template<class Tp>
TreeIterator<Tp>::TreeIterator(std::nullptr_t)
{
	this->tree = nullptr;
	this->cursor = 0;
}

template<class Tp>
TreeIterator<Tp>::TreeIterator(Tree<Tp> &tree)
{
	this->tree = &tree;
	this->cursor = tree.root;
}

template<class Tp>
TreeIterator<Tp>::TreeIterator(Tree<Tp> &tree, position p)
{
	this->tree = &tree;
	this->cursor = p;
}

template<class Tp>
typename TreeIterator<Tp>::reference TreeIterator<Tp>::operator*() const
{
	return tree->nodes[cursor].value;
}

template<class Tp>
typename TreeIterator<Tp>::pointer TreeIterator<Tp>::operator->() const
{
	return &*(*this);
}

template<class Tp>
TreeIterator<Tp>& TreeIterator<Tp>::operator++()
{
	cursor++;
	return *this;
}

template<class Tp>
bool TreeIterator<Tp>::operator==(const TreeIterator<Tp> &rhs) const
{
	return tree == rhs.tree && cursor == rhs.cursor;
}

template<class Tp>
bool TreeIterator<Tp>::operator!=(const TreeIterator<Tp> &rhs) const
{
	return !(*this == rhs);
}

template<class Tp>
TreeIterator<Tp>::operator ConstTreeIterator<Tp>() const
{
	return ConstTreeIterator(*tree, cursor);
}

} // namespace list_of_siblings
