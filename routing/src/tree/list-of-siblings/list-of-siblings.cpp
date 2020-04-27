#include "list-of-siblings.h"


namespace list_of_siblings
{

template<class _Tp>
Tree<_Tp>::Tree(size_t size)
{
	nodes.resize(size);
	init_space_cursor(0);
	root = space_cursor;
}

template<class _Tp>
typename Tree<_Tp>::iterator Tree<_Tp>::Append(value_type root_value)
{
	Clear();

	root = allocate_node();
	nodes[root].value = root_value;
}

template<class _Tp>
typename Tree<_Tp>::iterator Tree<_Tp>::Append(iterator root_node, std::vector<value_type> &descendants)
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
	if (!Empty())
	{
		clear(root);
		init_space_cursor(0);
		root = space_cursor;
	}
}

template<class _Tp>
size_t Tree<_Tp>::Depth() const
{
	throw std::out_of_range("aaa");
}

template<class _Tp>
bool Tree<_Tp>::Empty() const
{
	return root == space_cursor;
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

template<class _Tp>
void Tree<_Tp>::init_space_cursor(position begin)
{
	space_cursor = begin;

	for (size_t i = begin; i < nodes.size();)
		nodes[i].next_free = ++i;
}

template<class _Tp>
void Tree<_Tp>::clear(Tree::position root_node)
{

}

template<class _Tp>
typename Tree<_Tp>::position Tree<_Tp>::allocate_node()
{
	if (space_cursor == nodes.size())
	{
		nodes.resize(nodes.size() * 2);
		init_space_cursor(space_cursor);
	}
	auto position = space_cursor;
	space_cursor = nodes[space_cursor].next_free;

	return position;
}

template<class _Tp>
void Tree<_Tp>::erase_node(position p)
{
	nodes[p].descendants.clear();
	nodes[p].next_free = space_cursor;
	space_cursor = p;
}

} // namespace list_of_siblings
