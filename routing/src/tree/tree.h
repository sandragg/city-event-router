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
		/**
		 * Create root node.
		 * If tree isn't empty then clear tree and create new root node.
		 *
		 * @param root_value Root node value
		 * @return Iterator to the root node.
		 */
		virtual iterator Append(value_type root_value) = 0;
		/**
		 * Append node descendants.
		 * If subtree isn't empty then clear all descendants and create new ones.
		 *
		 * @param root Subtree root node
		 * @param descendants Descendants values
		 * @return Iterator to the changed node.
		 */
		virtual iterator Append(iterator root, std::vector<value_type>& descendants) = 0;
		/**
		 * Append node descendants.
		 * If subtree isn't empty then clear all descendants and create new ones.
		 *
		 * @param root Subtree root node
		 * @param descendants Descendants values
		 * @return Iterator to the changed node.
		 */
		virtual iterator Append(iterator root, std::vector<value_type>&& descendants) = 0;
		/**
		 * Get #iterator to the root.
		 */
		virtual iterator Root() = 0;
		/**
		 * Get #const_iterator to the root.
		 */
		virtual const_iterator Root() const = 0;
		/**
		 * Find node in the tree.
		 * @param position Iterator to the checked node
		 * @return If node exists - #iterator to the node, otherwise - #End.
		 */
		virtual iterator Find(const_iterator position) const = 0;
		/**
		 * Find node by label.
		 * @param value_type Node label
		 * @return If node exists - #iterator to the node, otherwise - #End.
		 */
		virtual iterator Find(value_type value) const = 0;
		/**
		 * Get node's parent.
		 * @param position Iterator to the node
		 * @return If parent exists - #iterator to the node, otherwise - #End.
		 */
		virtual iterator GetParent(const_iterator position) const = 0;
		/**
		 * Get the first descendant of the node.
		 * @param position Iterator to the node
		 * @return If descendant exists - #iterator to the node, otherwise - #End.
		 */
		virtual iterator GetLeftMostChild(const_iterator position) const = 0;
		/**
		 * Get the next sibling of the node.
		 * @param position Iterator to the node
		 * @return If sibling exists - #iterator to the node, otherwise - #End.
		 */
		virtual iterator GetRightSibling(const_iterator position) const = 0;
		/**
		 * Clear tree.
		 */
		virtual void Clear() = 0;
		/**
		 * Check the emptiness of the tree.
		 * @return If empty - **true**, otherwise - **false**.
		 */
		virtual bool Empty() const = 0;
		/**
		 * Get #iterator to the End node (fake node).
		 */
		virtual iterator End() const = 0;
};

}


#endif //ROUTING_TREE_H
