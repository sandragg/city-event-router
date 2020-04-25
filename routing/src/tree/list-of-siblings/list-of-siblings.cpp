#include "list-of-siblings.h"


namespace list_of_siblings
{

template<class _Tp>
typename Tree<_Tp>::iterator Tree<_Tp>::Append(value_type root_value)
{
	throw std::out_of_range("aaa");
}

template<class _Tp>
typename Tree<_Tp>::iterator Tree<_Tp>::Append(iterator root_node, std::vector<value_type> &children)
{
	throw std::out_of_range("aaa");
}

template<class _Tp>
typename Tree<_Tp>::iterator Tree<_Tp>::Root()
{
	return iterator(this, root);
}

template<class _Tp>
typename Tree<_Tp>::const_iterator Tree<_Tp>::Root() const
{
	return const_iterator(this, root);
}

template<class _Tp>
typename Tree<_Tp>::reference
Tree<_Tp>::Find(Tree::iterator position)
{
	throw std::out_of_range("aaa");
}

template<class _Tp>
typename Tree<_Tp>::const_reference
Tree<_Tp>::Find(Tree::const_iterator position) const
{
	throw std::out_of_range("aaa");
}

template<class _Tp>
typename Tree<_Tp>::iterator
Tree<_Tp>::GetParent(Tree::iterator position)
{
	throw std::out_of_range("aaa");
}

template<class _Tp>
typename Tree<_Tp>::const_iterator
Tree<_Tp>::GetParent(Tree::const_iterator position) const
{
	throw std::out_of_range("aaa");
}

template<class _Tp>
typename Tree<_Tp>::iterator
Tree<_Tp>::GetLeftMostChild(Tree::iterator position)
{
	throw std::out_of_range("aaa");
}

template<class _Tp>
typename Tree<_Tp>::const_iterator
Tree<_Tp>::GetLeftMostChild(Tree::const_iterator position) const
{
	throw std::out_of_range("aaa");
}

template<class _Tp>
typename Tree<_Tp>::iterator
Tree<_Tp>::GetRightSibling(Tree::iterator position)
{
	throw std::out_of_range("aaa");
}

template<class _Tp>
typename Tree<_Tp>::const_iterator
Tree<_Tp>::GetRightSibling(Tree::const_iterator position) const
{
	throw std::out_of_range("aaa");
}

template<class _Tp>
void Tree<_Tp>::Clear()
{
}

template<class _Tp>
size_t Tree<_Tp>::Depth() const
{
	throw std::out_of_range("aaa");
}

template<class _Tp>
size_t Tree<_Tp>::Size() const
{
	throw std::out_of_range("aaa");
}

template<class _Tp>
typename Tree<_Tp>::iterator Tree<_Tp>::End()
{
	return iterator(nullptr);
}

template<class _Tp>
typename Tree<_Tp>::const_iterator Tree<_Tp>::End() const
{
	return const_iterator(nullptr);
}

} // namespace list_of_siblings
