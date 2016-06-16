#include <iostream>
#include "bst.h"

struct compare_int {
	int operator()(int a, int b) const {
		if(a == b){
			return 0;
		}
		if(a>b){
			return -1;
		}else{
			return 1;
		}
	}
};


void test_bst_1(){
	std::cout << "--- TEST 1---" << std::endl;
	std::cout << "- Inserimento - (con duplicato) -" << std::endl;
	
	bst<int, compare_int> tree;

	try{
		tree.insert(50);
		tree.insert(60);
		tree.insert(30);
		tree.insert(40);
		tree.insert(20);
		tree.insert(70);
		tree.insert(20);
	}catch(duplicate_value &e){
		std::cout << e.what() << std::endl;
	}

	std::cout << "- Stampa -" << std::endl;
	std::cout << "Size: " << tree.get_size() << std::endl;
	std::cout << tree << std::endl;			

	std::cout << "- Copia -" << std::endl;
	bst<int, compare_int> copy_tree(tree);

	
	std::cout << "- Rimozione originale ( con valore inesistente) -" << std::endl;
	try{
		tree.remove(70); 
		tree.remove(30); 
		tree.remove(50);
		//tree.remove(100);
	}catch(value_not_found &e){
		std::cout << e.what() << std::endl;
	}
	
	std::cout << "- Stampa originale (post rimozione) -" << std::endl;
	std::cout << "Size: " << tree.get_size() << std::endl;
	std::cout << tree << std::endl;
	
	std::cout << "- Stampa copia -" << std::endl;
	std::cout << "Size: " << copy_tree.get_size() << std::endl;
	std::cout << copy_tree << std::endl;


	std::cout << "- Subtree -" << std::endl;
	bst<int, compare_int> sub_tree = subtree(copy_tree, 50);
	std::cout << "Size: " << sub_tree.get_size() << std::endl;
	std::cout << sub_tree << std::endl;
	std::cout << "- Subtree remove -" << std::endl;
	sub_tree.remove(50);
	std::cout << "Size: " << sub_tree.get_size() << std::endl;
	std::cout << sub_tree << std::endl;

}
	
int main(){
	test_bst_1();
	return 0;
}