#ifndef BST_H
#define BST_H

#include <stdexcept>
#include <algorithm>


/**
	Class that implements an unvalid comparator exception
*/
class not_valid_comparator : public std::runtime_error {
public:
	/**
		Secondary constructor, takes a message
		@param msg Message of error
	*/
	not_valid_comparator(const char *msg) :std::runtime_error(msg) {}
};

class value_not_found : public std::runtime_error {
public:
	/**
		Secondary constructor, takes a message
		@param msg Message of error
	*/
	value_not_found(const char *msg) :std::runtime_error(msg) {}
};



/**
	Class that implement a binary search tree
*/

template <typename T, typename compT>
class bst
{
	/**
		Struct that rappresent a node of a binary tree.
		A node contains a value, a parent, a left child, and a right child
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
	bst() : _root(0), _size(0) {}

	/**
		Destructor

		TODO
	*/
	~bst(){
		clear();
	}

	/**
		Removes the tree
		TODO
	*/
	void clear(){

	}

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
			bst tmp_bst(other); // Calling the copy constructor
			std::swap(this._root, tmp_bst._root);
			std::swap(this._size, tmp_bst._size);
		}
		return *this;
	}

	/**
		Inserts a value in the tree

		@param val Value of type T to be inserted
	*/	
	void insert(const T &val){
		compT comp;
		if(!exist(val)){
			if (_root == 0)
			{
				_root = new node(val);
			} else {
				node *curr = _root;
				while(curr != 0){
					switch(comp(curr->value, val)){
						case 0:
							break;
						case 1:
							if(curr->right != 0){
								curr = curr->right;
							}else{
								curr->right = new node(val); //Check if new is required
								_size++;
							}
							break;
						case -1:
							if(curr->left != 0){
								curr = curr->left;
							}else{
								curr->left = new node(val); //Check if new is required
								_size++;
							}
							break;
						default:
							throw not_valid_comparator("Unable to compare the values");
					}	
				}
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
		return (n != 0);
	}

	/**
		Search for the node that has the given value

		@param val Value to search
		@return If exist, the pointer to the node with the specified value, 0 otherwise
	*/
	node *find(const T &val) const {
		node *curr = _root;
		compT comp;
		while(curr != 0){
			switch(comp(curr->value, val)){
				case 0:
					return curr;
					break;
				case 1:
					if(curr->right != 0){
						curr = curr->right;
					}else{
						throw value_not_found("Unable to find the value");
					}
					break;
				case -1:
					if(curr->left != 0){
						curr = curr->left;
					}else{
						throw value_not_found("Unable to find the value");
					}
					break;
				default:
					throw not_valid_comparator("Unable to compare the values");
			}	
		}
		return 0;
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
			n = other.n;
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
			
			@return Constant pointer to the value
		*/
		const T* operator->() const {
			return &(n->value);
		}

		/**
			Post-increment operator
			
			@return The iterator to the previous value in the tree
		*/
		const_iterator operator++(int){
			if(n == 0){
				return 0;
			}
			const_iterator tmp(*this);
			n = get_next_node(n);
			return tmp;
		}

		/**
			Pre-increment operator
			
			@return The iteretor to the next node of the tree
		*/
		const_iterator& operator++(){
			n = get_next_node(n);
			return *this;
		}

		/**
			Equality comparison
			
			@other Iterator to compare
			@return True if the two iterators point to the same node of the tree, false otherwise
		*/
		bool operator==(const const_iterator &other){
			return n == other.n;
		}

		/**
			Not equal comparison
			
			@other Iterator to compare
			@return True if the two iterators point to diffrent node in the tree, false otherwise
		*/
		bool operator!=(const const_iterator &other){
			return n != other.n;
		}


	private:
		const node *n; ///< Pointer to the current node of the tree

		// Friend class for allowing it to use the initialization constructor
		friend class bst;

		/**
			Secondary constructor
			@param pn Pointer to a node in the tree
		*/
		const_iterator(const node *pn){
			n = pn;
		}

		/**
			Finds the next node in the pre-order tree visit
			
			@return The pointer to the node
		*/
		node* get_next_node(const node &n){
			if(n.parent == n.left == n.right == 0){
				return 0;
			}
			if(n->left != 0){
				return n.left;
			}else{
				return first_right(n.parent);
			}
		}

		/**
			Finds the first node with a not null right child

			@return The pointer to the node
		*/		
		node* first_right(const node &n){
			if(n == 0){
				return 0;
			}

			if(n.right != 0){
				return n.right;
			}else{
				return first_right(n.parent);
			}
		}

	}; // End of class const_iterator

	/**
		Iterator of the begin of the tree

		@return The iterator of the begin of the tree
	*/
	const_iterator begin() const {
		return const_iterator(_root);
	}

	/**
		Iterator of the end of the tree

		@return Iterator to the end of the tree
	*/
	const_iterator end() const {
		return const_iterator(0);
	}

};
#endif