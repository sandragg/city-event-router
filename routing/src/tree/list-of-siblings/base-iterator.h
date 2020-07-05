#ifndef ROUTING_LIST_OF_SIBLINGS_BASE_ITERATOR_H
#define ROUTING_LIST_OF_SIBLINGS_BASE_ITERATOR_H

#include <iostream>
#include "../tree.h"


namespace list_of_siblings
{

template<class Tp>
class Tree;

template<class Tp>
class ConstTreeIterator;

template<class Tp>
class TreeIterator : public tree::TreeIterator<Tp>
{
		using base			= tree::TreeIterator<Tp>;
		using position		= size_t;

	public:
		using value_type	= typename base::value_type;
		using reference		= typename base::reference;
		using pointer		= typename base::pointer;

		explicit TreeIterator(std::nullptr_t);
		explicit TreeIterator(Tree<Tp> &tree);
		explicit TreeIterator(Tree<Tp> &tree, position p);
		reference operator*() const;
		pointer operator->() const;
		TreeIterator<Tp>& operator++();
		bool operator==(const TreeIterator<Tp>& rhs) const;
		bool operator!=(const TreeIterator<Tp>& rhs) const;

		operator ConstTreeIterator<Tp>() const;

	private:
		Tree<Tp> *tree;
		position cursor;
};

} // namespace list_of_siblings


#endif //ROUTING_LIST_OF_SIBLINGS_BASE_ITERATOR_H
