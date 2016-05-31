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
		node *parent;	///< Pointer to the parent of the node

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
		// TODO Check compare
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

			@param other Node to be copied
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

	/**
		Copy constructor

		@param other The BST to be copied

		TODO
	*/
	bst(const bst& other) : _root(0), _size(0) {

	}

	/**
		Assignment operator

		@param other The BST to be copied
	*/
	bst& operator=(const bst &other){
		if(this != &other){
			bst tmp_bst(other) // Calling the copy constructor
			std::swap(this->_root, tmp_bst._root);
			std::swap(this->_size, tmp_bst._size);
		}

		return *this;
	}

	

	/**
		Inserts a value in the tree

		@param val Value of type T to be inserted
	*/	
	void insert(const T &val){
		if(!exist(val)){
			if (_root = 0)
			{
				_root = new node(val)
			}else{
				// TODO Insertion
			}
		}
	}

	

	/**
		Checks if the value exist or not in the BST

		@param val Value to check if exist
		@return True if the value exist, false otherwise
	*/
	bool exist(const T &val) const {
		node *n = find(val);

		return (n != 0)
	}


	/**
		Contstant forward iterator 
	*/
	class const_iterator {
	public:
		typedef std::forward_iterator_tag iterator_category;
		// typedef T value_type; Controllare se ridondante
		typedef const T* pointer;
		typedef const T& reference;

		/**
			Default constructor
		*/
		const_iterator(){
			n = 0;
		}

		/**
			Copy constructor

			@param other Iterator to be copied
		*/
		const_iterator(const const_iterator &other){
			n = other.n
		}

		/**
			Assignment operator

			@param other Iterator to be copied
			@return *this
		*/
		const_iterator& operator=(const const_iterator &other){
			n = other.n;
			return *this;
		}


		/**
			Destructor
		*/
		~const_iterator(){}

		/**
			Dereference by reference
			@return Constant reference to the value
		*/
		const T& operator*() const {
			return n->value;
		}

		/**
			Dereference by pointer
		*/
		const T* operator->() const {
			return &(n->value);
		}

		/**
			Post-increment
			@ret	urn Iterator to the previous value in the tree
		*/
		const_iterator operator++(int){
			const_iterator tmp(*this);

			n = get_next_node(n);
			return *this
		}


		node* get_next_node(const &node n){
			
		}



	private:
		const node *n; ///< Pointer to the current node of the tree

		// Friend class for allowing it to use the initialization constructor
		friend class bst;

		//TODO Second constructor

	}; // End of class const_iterator


	

};


#endif