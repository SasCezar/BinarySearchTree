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

/**
	Class that implements a not found value exception
*/
class value_not_found : public std::runtime_error {
public:
	/**
		Secondary constructor, takes a message
		@param msg Message of error
	*/
	value_not_found(const char *msg) :std::runtime_error(msg) {}
};

/**
	Class that implements a duplicated value exception
*/
class duplicate_value : public std::runtime_error {
public:
	/**
		Secondary constructor, takes a message
		@param msg Message of error
	*/
	duplicate_value(const char *msg) :std::runtime_error(msg) {}
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
		~node(){
			parent = 0;
			delete right;
			delete left;
		}


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
		delete _root;
	}

	void clear(){
		delete _root;
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
		@throws TODO
	*/	
	void insert(const T &val){
		compT comp;
		if (_root == 0)
		{
			_root = new node(val);
			_size++;
		} else {
			node *curr = _root;
			while(curr != 0){
				switch(comp(curr->value, val)){
					case 0:
						throw duplicate_value("Value already exist");
						break;
					case 1:
						if(curr->right != 0){
							curr = curr->right;
						}else{
							node *tn = new node(val);
							tn->parent = curr;
							curr->right = tn;
							_size++;
							return;
						}
						break;
					case -1:
						if(curr->left != 0){
							curr = curr->left;
						}else{
							node *tn = new node(val);
							tn->parent = curr;
							curr->left = tn;
							_size++;
							return;
						}
						break;
					default:
						throw not_valid_comparator("Unable to compare the values");
				}	
			}
		}
	}

	void remove(const T &val){
		node *removed = remove_helper(*find(val));
		if(removed == 0){
			return;
		}
		if(removed->parent->left == removed){
			removed->parent->left = 0;
		}
		if(removed->parent->right == removed){
			removed->parent->right = 0;
		}
		std::cout << "rem out" << removed->value << std::endl;		
		removed->parent = 0;
		removed->left = 0;
		removed->right = 0;
		delete removed;
	}

	node* remove_helper(const node &n){
		node *to_remove = find(n.value);
		if(to_remove == 0){
			throw value_not_found("Unable to find the value to remove");
		}
		node *parent = to_remove->parent;
		if(to_remove->left == 0 && to_remove->right == 0){
			return to_remove;
		}

		
		if(to_remove->left != 0 && to_remove->right != 0){
			node *n = to_remove->right;
			T min;
			if(n->left == 0){
				min = n->value;
			}else{
				node *curr = n->left;
				while(curr->left != 0){
					curr = curr->left;
				}
				min = curr->value;
				curr->value = to_remove->value;
				curr = remove_helper(*curr);
				curr->parent = 0;
				curr->left = 0;
				curr->right = 0;
				delete curr;
			}
			std::swap(to_remove->value,min);
			return 0;
		}else{
			node *substitute = (to_remove->left != 0) ? to_remove->left : to_remove->right;
			substitute->parent = parent;
			if(parent->left == to_remove){
				parent->left == substitute;
			}else{
				parent->right == substitute;
			}
			return to_remove;
		}
	}


	node *find_min(const node &n)const{
		if(n.left == 0){
			return n;
		}
		node *curr = n.left;
		while(curr->left != 0){
			curr = curr->left;
		}
		return curr;
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
						return 0;
					}
					break;
				case -1:
					if(curr->left != 0){
						curr = curr->left;
					}else{
						return 0;
					}
					break;
				default:
					throw not_valid_comparator("Unable to compare the values");
			}	
		}
		return 0;
	}

	int get_size(){
		return _size;
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
			n = get_next_node();
			return tmp;
		}

		/**
			Pre-increment operator
			
			@return The iteretor to the next node of the tree
		*/
		const_iterator& operator++(){
			n = get_next_node();
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
		node* get_next_node() {
			if(n->parent == 0 && n->left == 0 && n->right == 0){
				return 0;
			}

			if(n->left != 0){
				return n->left;
			}
			if(n->right != 0){
				return n->right;
			}

			while(n->parent != 0){
				if(n->parent->right != 0 && n->parent->right != n){
					n = n->parent;
					return n->right;
				}
				n = n->parent;
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

/**
	Operatore di stream di output per la stampa di un avector
	@param os stream di output
	@param av avector da scrivere
	@return lo stream di output
*/
template <typename T, typename C>
std::ostream & operator<<(std::ostream &os, const bst<T,C> &tree) {
	
	typename bst<T,C>::const_iterator i,ie;
	
	for(i=tree.begin(), ie=tree.end(); i != ie; i++){ 
		 os << *i << " ";
	}
	os << std::endl;
	
	return os;
}
#endif