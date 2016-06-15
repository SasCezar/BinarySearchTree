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
	bst<int, compare_int> tree;
	
	try{
		tree.insert(50);
		tree.insert(30);
		tree.insert(60);
		tree.insert(80);
		tree.insert(90);
		tree.insert(65);
	}catch(duplicate_value &e) {
		std::cout<<e.what()<<std::endl;
	}
	
	int values_to_remove[3] = {50, 30, 80};

	for (int i = 0; i < 3; ++i)
	{
		std::cout << "Size: " << tree.get_size() << std::endl;
		std::cout << tree;
		std::cout << "removing " << values_to_remove[i] << std::endl;  
		tree.remove(values_to_remove[i]);
	}
	std::cout << "Size: " << tree.get_size() << std::endl;
	std::cout << tree;
	return;
}

void test_bst_2(){
	bst<int, compare_int> tree;

	try{
		tree.insert(50);
		tree.insert(30);
		tree.insert(60);
		tree.insert(80);
		tree.insert(90);
		tree.insert(65);
	}catch(duplicate_value &e) {
		std::cout<<e.what()<<std::endl;
	}

	bst<int, compare_int> copy_tree(tree);
	tree.remove(50);
	std::cout << "Original - Size: " << tree.get_size() << std::endl;
	std::cout << tree;
	
	std::cout << "Copy - Size: " << copy_tree.get_size() << std::endl;
	std::cout << copy_tree;
	

	bst<int, compare_int> third_tree;

	third_tree = copy_tree;

	third_tree.remove(50);		
	std::cout << "3 - Size: " << third_tree.get_size() << std::endl;
	std::cout << third_tree;
	

	std::cout << "Copy - Size: " << copy_tree.get_size() << std::endl;
	std::cout << copy_tree;
	
}


int main(){
	test_bst_1();
	std::cout << "-----Test 2-----"<< std::endl;
	test_bst_2();

	return 0;
}