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
		tree.insert(40);
		tree.insert(60);
		tree.insert(70);
		tree.insert(20);
		tree.insert(90);
		tree.insert(550);
	}catch(duplicate_value &e) {
		std::cout<<e.what()<<std::endl;
	}
	
	std::cout << tree.find(50)->left->value << tree.find(50)->right->value;
	std::cout << "Size:" << tree.get_size() << std::endl;
	std::cout << tree;
	tree.remove(30);
	std::cout << tree;
	//int x = tree.find(7)->value;
	//tree.clear();
	//tree.find(7);
	return;
}


int main(){
	test_bst_1();

	return 0;
}