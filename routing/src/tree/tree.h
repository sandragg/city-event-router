#ifndef ROUTING_TREE_H
#define ROUTING_TREE_H

#include <iterator>


namespace tree
{

template<class _Tp>
class TreeIterator : public std::iterator_traits<_Tp*> {};

template<class _Iter, class _ConstIter>
class Tree
{
	public:
		using iterator			= _Iter;
		using const_iterator	= _ConstIter;
		using value_type		= typename iterator::value_type;
		using reference			= typename iterator::reference;
		using const_reference	= typename const_iterator::reference;
		using difference_type	= typename iterator::difference_type;

		virtual iterator Root() = 0;
		virtual const_iterator Root() const = 0;
		virtual reference Find(const_iterator position) = 0;
		virtual const_reference Find(const_iterator position) const = 0;
		virtual iterator GetParent(const_iterator position) = 0;
		virtual const_iterator GetParent(const_iterator position) const = 0;
		virtual iterator GetLeftMostChild(const_iterator position) = 0;
		virtual const_iterator GetLeftMostChild(const_iterator position) const = 0;
		virtual iterator GetRightSibling(const_iterator position) = 0;
		virtual const_iterator GetRightSibling(const_iterator position) const = 0;
		virtual void Clear() = 0;
		virtual size_t Depth() const = 0;
		virtual size_t Size() const = 0;
		virtual iterator End() = 0;
		virtual const_iterator End() const = 0;
};

}


#endif //ROUTING_TREE_H
