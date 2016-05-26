#ifndef BST_H
#define BST_H

#include <stdexcept>
#include <algorithm>


/**
	Class that implement a binary search tree
*/

template <typename T, typename compT>
class bst
{
	/**
		Struct that rappresent a node of a binary tree.
		A node contains a value, a left child, and a right child
	*/
	struct node
	{
		T value;		///< Value of the node
		node *left;		///< Pointer to the left child
		node *right;	///< Pointer to the right child


		/**
			Constructor that builds a node without childs

			@param pt Value of the node	
		*/
		node(const T &pt) : value(pt), left(0), right(0){}


		/**
			Constructor that initialize a node with a value and childs
			
			@param pt Value of node
			@param l Left child
			@param r Right child
		*/
		node(const T &pt, node *l, node *r) : value(pt), left(l), right(r) {}


		/**
			Default constructor
		*/
		node() : left(0), right(0) {}

		/**
			Destructor
		*/
		~node(){}


		/**
			Copy constructor

			@param other Node to be copied
		*/
		node(const node &other) : value(other.value), left(other.left), right(other.right) {}


		/**
			Assignment operator

			@param other Nodo to be copied
		*/
		node& operator=(const node &other){
			if(this != &other) {
				value = other.value;
				left = other.left;
				right = other.right;				
			}
			return *this;
		}
	};  // End of node struct


	node *_root; 	///< Pointer to the first node of the tree
	int _size; 		///< Number of nodes in the tree

public:
	/**
		Default constructor
	*/
	bst() : node(0), _size(0) {}

	/**
		Destructor

		TODO
	*/
	~bst();

	
	
};


#endif