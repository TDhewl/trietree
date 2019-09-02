#pragma once
#include <string>
#include <map>
#include <vector>


class TrieNode
{
public:
	int count = 0;
	std::string word;
	char ch = '\0';
private:
	bool isEnd = false;
	std::map<char, TrieNode*> next;
public:
	/***
	***The constructor
	****/
	TrieNode() {};
	TrieNode(char character) :ch(character) {};

	/***
	***Set the end
	****/
	void SetEnd() { isEnd = true; return; }

	/***
	***Whether the node ends
	****/
	bool Ifend() { return isEnd; }

	/***
	*** whether the child of this node contains character
	****/
	bool Contain(char character) { return next.count(character) != 0; }

	/***
	***Add the new node
	****/
	void AddNode(char character) { next[character] = new TrieNode(ch); }

	/***
	***Returns the next node starting with character
	****/
	TrieNode* SetNext(char character) { return next.at(character); }

	/***
	***Returns all children of the node
	****/
	std::vector<TrieNode*> GetNextAll();

	/***
	***Returns the key values of all the child nodes of the node
	****/
	std::vector<char> Getchar();

	/***
	***DFS
	****/
	void DFS_Vist(std::vector<TrieNode*>& node_list);
};

class Trietree
{
private:
	TrieNode* root;
public:

	Trietree() { root = new TrieNode(); }

	/***
	***insert word and build bktree
	****/
	void Insert(const std::string word);

	/***
	***search word
	****/
	bool Search(const std::string word);

	/***
	***calculate edit distance
	****/
	int Edit_distance(std::string &word, std::string &word2);

	/***
	***DFS
	****/
	void DFSTrie();

	/***
	***BFS
	****/
	void BFSTrie();

	/***
	***Find the most similar word 
	****/
	std::string SimilarWord(std::string word);

	/***
	***return the node starting with word pre
	****/
	TrieNode* Getprenode(const std::string pre);

	/***
	***return all words starting with word pre
	****/
	std::vector<std::string> Getpreword(const std::string pre);
	
};