#include <fstream>
#include <iostream>
#include <string>
#include "Trietree.h"


int main() {
	
	std::ifstream Lexicon;
	Lexicon.open("./lexicon.txt");
	std::string line;
	if (!Lexicon) {
		std::cout << "Cann't open lexicon file" << std::endl;
		return 0;
	}
	Trietree trie;
	while (getline(Lexicon, line)) {
		trie.Insert(line);
	}
	Lexicon.close();
	//bool a = trie.Search("yesokkk");
	//trie.BFSTrie();
	//int b = trie.Edit_distance("yes", "yesokkk");
	auto a = trie.Getpreword("a");
	line = trie.SimilarWord("a_couple_ofhh");
	return 0;
}