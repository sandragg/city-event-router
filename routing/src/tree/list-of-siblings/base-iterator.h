#ifndef ROUTING_LIST_OF_SIBLINGS_BASE_ITERATOR_H
#define ROUTING_LIST_OF_SIBLINGS_BASE_ITERATOR_H

#include <iterator>
#include "list-of-siblings.h"


namespace list_of_siblings
{

template<class _Tp>
class TreeIterator : public std::iterator_traits<_Tp> {};

template<class _Tp>
class TreeIterator<_Tp*> : public std::iterator_traits<_Tp*>
{
	using base				= std::iterator_traits<_Tp*>;
	using position			= size_t;

	public:
		using value_type	= typename base::value_type;
		using reference		= typename base::reference;
		using pointer		= typename base::pointer;

		explicit TreeIterator(const Tree<_Tp>& tree);
		explicit TreeIterator(const Tree<_Tp>& tree, position p);
		reference operator*() const;
		TreeIterator<_Tp>& operator++();

	private:
		Tree<_Tp> *tree;
		position cursor;
};

#include "base-iterator.cpp"

} // namespace list_of_siblings


#endif //ROUTING_LIST_OF_SIBLINGS_BASE_ITERATOR_H
