#ifndef ROUTING_LIST_OF_SIBLINGS_BASE_CONST_ITERATOR_H
#define ROUTING_LIST_OF_SIBLINGS_BASE_CONST_ITERATOR_H

#include <iostream>
#include "list-of-siblings.h"
#include "../tree.h"


namespace list_of_siblings
{

template<class _Tp>
class ConstTreeIterator : public tree::TreeIterator<const _Tp>
{
		using base			= tree::TreeIterator<const _Tp>;
		using position		= size_t;

	public:
		using value_type	= typename base::value_type;
		using pointer		= typename base::pointer;
		using reference		= typename base::reference;

		explicit ConstTreeIterator(std::nullptr_t);
		explicit ConstTreeIterator(const Tree<_Tp> *tree);
		explicit ConstTreeIterator(const Tree<_Tp> *tree, position p);
		reference operator*() const;
		pointer operator->() const;
		ConstTreeIterator<_Tp>& operator++();
		bool operator==(const ConstTreeIterator<_Tp>& rhs) const;
		bool operator!=(const ConstTreeIterator<_Tp>& rhs) const;

	private:
		const Tree<_Tp> *tree;
		position cursor;
};

#include "base-const-iterator.cpp"

} // namespace list_of_siblings


#endif //ROUTING_LIST_OF_SIBLINGS_BASE_CONST_ITERATOR_H
