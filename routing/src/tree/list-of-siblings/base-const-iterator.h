#ifndef ROUTING_LIST_OF_SIBLINGS_BASE_CONST_ITERATOR_H
#define ROUTING_LIST_OF_SIBLINGS_BASE_CONST_ITERATOR_H

#include <iostream>
#include "../tree.h"


namespace list_of_siblings
{

template<class Tp>
class Tree;

template<class Tp>
class ConstTreeIterator : public tree::TreeIterator<const Tp>
{
		using base			= tree::TreeIterator<const Tp>;
		using position		= size_t;

	public:
		using value_type	= typename base::value_type;
		using pointer		= typename base::pointer;
		using reference		= typename base::reference;

		explicit ConstTreeIterator(std::nullptr_t);
		explicit ConstTreeIterator(const Tree<Tp> &tree);
		explicit ConstTreeIterator(const Tree<Tp> &tree, position p);
		reference operator*() const;
		pointer operator->() const;
		ConstTreeIterator<Tp>& operator++();
		bool operator==(const ConstTreeIterator<Tp>& rhs) const;
		bool operator!=(const ConstTreeIterator<Tp>& rhs) const;

	private:
		const Tree<Tp> *tree;
		position cursor;
};

} // namespace list_of_siblings


#endif //ROUTING_LIST_OF_SIBLINGS_BASE_CONST_ITERATOR_H
