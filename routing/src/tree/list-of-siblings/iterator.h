#ifndef ROUTING_ITERATOR_H
#define ROUTING_ITERATOR_H

#include <iterator>
#include "list-of-siblings.h"


namespace list_of_siblings
{

template<class _Tp>
struct TreeIterator : public std::iterator_traits<_Tp> {};

template<class _Tp>
class TreeIterator<_Tp*> : public std::iterator_traits<_Tp*>
{
	using base				= std::iterator_traits<_Tp*>;
	using position			= size_t;

	public:
		using value_type	= typename base::value_type;
		using reference		= typename base::reference;
		using pointer		= typename base::pointer;

		TreeIterator(const Tree<_Tp>& tree);
		TreeIterator(const Tree<_Tp>& tree, position p);
		reference operator*() const;
		TreeIterator<_Tp>& operator++(int);

	private:
		Tree<_Tp>* tree;
		position cursor;
};

#include "iterator.cpp"

} // namespace list_of_siblings


#endif //ROUTING_ITERATOR_H
