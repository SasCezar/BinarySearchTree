#include <iostream>
#include "bst.h"

struct compare_int {
	int operator()(int a, int b) const {
		if(a==b){
			return 0;
		}
		if(a>b){
			return 1;
		}else{
			return -1;
		}
	}
};


void test_bst_1(){
	bst<int, compare_int> tree;
	int i = 5;
	tree.insert(i);
	
	int x = tree.find(52)->value;
	std::cout << x;
}


int main(){
	test_bst_1();

	return 0;
}
