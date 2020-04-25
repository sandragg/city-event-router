#ifndef ROUTING_LIST_OF_SIBLINGS_BASE_ITERATOR_H
#define ROUTING_LIST_OF_SIBLINGS_BASE_ITERATOR_H

#include <iostream>
#include "../tree.h"


namespace list_of_siblings
{

template<class _Tp>
class Tree;

template<class _Tp>
class TreeIterator : public tree::TreeIterator<_Tp>
{
		using base			= tree::TreeIterator<_Tp>;
		using position		= size_t;

	public:
		using value_type	= typename base::value_type;
		using reference		= typename base::reference;
		using pointer		= typename base::pointer;

		explicit TreeIterator(std::nullptr_t);
		explicit TreeIterator(Tree<_Tp> *tree);
		explicit TreeIterator(Tree<_Tp> *tree, position p);
		reference operator*() const;
		pointer operator->() const;
		TreeIterator<_Tp>& operator++();
		bool operator==(const TreeIterator<_Tp>& rhs) const;
		bool operator!=(const TreeIterator<_Tp>& rhs) const;

	private:
		Tree<_Tp> *tree;
		position cursor;
};

} // namespace list_of_siblings


#endif //ROUTING_LIST_OF_SIBLINGS_BASE_ITERATOR_H
