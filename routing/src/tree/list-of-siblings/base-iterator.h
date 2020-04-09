#ifndef ROUTING_LIST_OF_SIBLINGS_BASE_ITERATOR_H
#define ROUTING_LIST_OF_SIBLINGS_BASE_ITERATOR_H

#include <iterator>
#include "list-of-siblings.h"
#include "../tree.h"


namespace list_of_siblings
{

template<class _Tp>
class TreeIterator : public tree::TreeIterator<_Tp>
{
	using base				= tree::TreeIterator<_Tp>;
	using position			= size_t;

	public:
		using value_type	= typename base::value_type;
		using reference		= typename base::reference;
		using pointer		= typename base::pointer;

		explicit TreeIterator(Tree<_Tp>& tree);
		explicit TreeIterator(Tree<_Tp>& tree, position p);
		reference operator*() const;
		TreeIterator<_Tp>& operator++();

	private:
		Tree<_Tp> *tree;
		position cursor;
};

template<class _Tp>
class ConstTreeIterator : public TreeIterator<const _Tp> {};

#include "base-iterator.cpp"

} // namespace list_of_siblings


#endif //ROUTING_LIST_OF_SIBLINGS_BASE_ITERATOR_H
