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


struct compare_str {
	int operator()(const std::string &a, const std::string &b) const {
		std::string ua = ucase(a);
		std::string ub = ucase(b);
		if(ua == ub){
			return 0;
		}
		if(ua > ub){
			return -1;
		}else{
			return 1;
		}
	}
private:
	std::string ucase(const std::string &str) const {
		std::string tmp(str);
		for(int i=0; i< tmp.size(); ++i)
			tmp[i]=std::toupper(tmp[i]);
	
		return tmp;
	}
};

void test_bst_1(){
	std::cout << "--- TEST 1 (INT)---" << std::endl;
	std::cout << "- Inserimento - (con duplicato) -" << std::endl;
	
	bst<int, compare_int> tree;
	
	try{
		tree.insert(50);
		tree.insert(60);
		tree.insert(30);
		tree.insert(40);
		tree.insert(70);
		tree.insert(50);
	}catch(duplicate_value &e){
		std::cout << e.what() << std::endl;
	}

	std::cout << "- Stampa -" << std::endl;
	std::cout << "Size: " << tree.get_size() << std::endl;
	std::cout << tree << std::endl;			

	std::cout << "- Copia -" << std::endl;
	bst<int, compare_int> copy_tree(tree);
	std::cout << "Size: " << copy_tree.get_size() << std::endl;
	std::cout << copy_tree << std::endl;			


	std::cout << "- Rimozione originale ( con valore inesistente) -" << std::endl;
	try{
		tree.remove(70); 
		tree.remove(30); 
		tree.remove(50);
		tree.remove(100);
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
	
	std::cout << "- Subtree clear -" << std::endl;
	sub_tree.clear();
	std::cout << "Size: " << sub_tree.get_size() << std::endl;
	std::cout << sub_tree << std::endl;
}
	

void test_bst_2(){
	std::cout << "--- TEST 2 (Stringhe)---" << std::endl;
	std::cout << "- Inserimento - (con duplicato) -" << std::endl;
	
	bst<std::string, compare_str> tree;
	
	try{
		tree.insert("az");
		tree.insert("bfs");
		tree.insert("c");
		tree.insert("de");
		tree.insert("e");
		tree.insert("az");
	}catch(duplicate_value &e){
		std::cout << e.what() << std::endl;
	}

	std::cout << "- Stampa -" << std::endl;
	std::cout << "Size: " << tree.get_size() << std::endl;
	std::cout << tree << std::endl;			

	std::cout << "- Copia -" << std::endl;
	bst<std::string, compare_str> copy_tree(tree);
	std::cout << copy_tree << std::endl;			

	std::cout << "- Rimozione originale ( con valore inesistente) -" << std::endl;
	try{
		tree.remove("e"); 
		tree.remove("c"); 
		tree.remove("az");
		//tree.remove("h");
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
	std::string az = "az";
	bst<std::string, compare_str> sub_tree = subtree(copy_tree, az);
	std::cout << "Size: " << sub_tree.get_size() << std::endl;
	std::cout << sub_tree << std::endl;
	std::cout << "- Subtree remove -" << std::endl;
	sub_tree.remove("az");
	std::cout << "Size: " << sub_tree.get_size() << std::endl;
	std::cout << sub_tree << std::endl;
	
	std::cout << "- Subtree clear -" << std::endl;
	sub_tree.clear();
	std::cout << "Size: " << sub_tree.get_size() << std::endl;
	std::cout << sub_tree << std::endl;
	
}


int main(){
	test_bst_1();
	test_bst_2();
	
	return 0;
}