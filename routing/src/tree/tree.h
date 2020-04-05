#ifndef ROUTING_TREE_H
#define ROUTING_TREE_H

#include <iterator>


namespace tree
{

template<class _Tp>
class Tree
{
	public:
		using value_type		= _Tp;
		using reference			= value_type&;
		using const_reference	= const value_type&;
		using iterator			= std::iterator_traits<value_type>;
		using const_iterator	= std::iterator_traits<const value_type>;
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
};

}


#endif //ROUTING_TREE_H
