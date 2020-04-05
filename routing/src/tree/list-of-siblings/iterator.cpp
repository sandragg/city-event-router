#include "iterator.h"
#include "list-of-siblings.h"
using namespace list_of_siblings;


template<class _Tp>
TreeIterator<_Tp*>::TreeIterator(const Tree<_Tp>& tree)
{
	this->tree = tree;
	this->cursor = tree.root;
}

template<class _Tp>
TreeIterator<_Tp*>::TreeIterator(
	const Tree<_Tp>& tree,
	typename TreeIterator<_Tp*>::position p)
{
	this->tree = tree;
	this->cursor = p;
}

template<class _Tp>
typename TreeIterator<_Tp*>::reference TreeIterator<_Tp*>::operator*() const
{

}

template<class _Tp>
TreeIterator<_Tp>& TreeIterator<_Tp*>::operator++(int)
{

}


