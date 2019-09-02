#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <map>
#include "Trietree.h"

void TrieNode::DFS_Vist(std::vector<TrieNode*>& node_list)
{
	node_list.push_back(this);
	for (auto iter = next.begin(); iter != next.end(); ++iter) {
		iter->second->DFS_Vist(node_list);
	}
}
std::vector<TrieNode*> TrieNode::GetNextAll() {
	std::vector<TrieNode*> list;
	for (auto iter = next.begin(); iter != next.end(); ++iter) {
		list.push_back(iter->second);
	}
	return list;
}

std::vector<char> TrieNode::Getchar() {
	std::vector<char> list;
	for (auto iter = next.begin(); iter != next.end(); ++iter) {
		list.push_back(iter->first);
	}
	return list;
}

void Trietree::Insert(const std::string word) {
	if (word.size() == 0) {
		return;
	}
	TrieNode *Node = root;
	std::string str = "";
	for (int i = 0; i < word.size(); i++) {
		Node->count++;
		if (!Node->Contain(word[i])) {
			Node->AddNode(word[i]);			
		}
		Node = Node->SetNext(word[i]);
		str += word[i];
		Node->word = str;
	}
	Node->SetEnd();
	Node->word = word;
}

bool Trietree::Search(const std::string word) {
	if (word.size() == 0) {
		return false;
	}
	TrieNode* node = root;
	for (int i = 0; i < word.size(); i++) {
		if (node->Contain(word[i])) {
			node = node->SetNext(word[i]);
		}
		else {
			return false;
		}
	}
	return true;
}

int Trietree::Edit_distance(std::string &word1,std::string &word2) {
	int m = word1.size();
	int n = word2.size();
	std::vector<std::vector<int>>dist(m + 1, std::vector<int>(n + 1, 0));

	for (int i = 1; i <= m; i++) {
		dist[i][0] = i;
	}
	for (int i = 1; i <= n; i++) {
		dist[0][i] = i;
	}
	dist[0][0] = 0;

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (word1[i - 1] == word2[j - 1]) {
				dist[i][j] = dist[i - 1][j - 1];
			}
			else {
				int tmp = std::min(dist[i][j - 1], dist[i - 1][j]);
				dist[i][j] = std::min(tmp, dist[i - 1][j - 1]) + 1;
			}
		}
	}
	return dist[m][n];
}

std::string Trietree::SimilarWord(std::string word) {
	TrieNode* node = root;
	std::stack<TrieNode*> sta;
	std::vector <char> str;
	sta.push(node);
	int dist = 0;
	int mindist = INT_MAX;
	std::string result;
	while (!sta.empty()) {
		node = sta.top();
		sta.pop();
		std::vector<TrieNode*> tmp = node->GetNextAll();
		for (int no = 0; no < tmp.size(); no++) {
			if (!tmp[no]->Ifend()) {
				sta.push(tmp[no]);
			}
			else {
				sta.push(tmp[no]);
				dist = Edit_distance(tmp[no]->word, word);
				if (dist < mindist) {
					mindist = dist;
					result = tmp[no]->word;
				}
			}
		}
	}
	return result;
}

void Trietree::DFSTrie() {
	std::stack<TrieNode*> sta;
	TrieNode* node = root;
	sta.push(node);
	while (!sta.empty()) {
		node = sta.top(); 
		sta.pop();
		std::vector<TrieNode* >tmp = node->GetNextAll();
		for (int i = 0; i < tmp.size(); i++) {
			sta.push(tmp[i]);
		}
	}
}

void Trietree::BFSTrie() {
	std::queue<TrieNode*> que;
	TrieNode* node = root;
	que.push(node);
	while (!que.empty()) {
		node = que.front();
		std::vector<TrieNode* >tmp = node->GetNextAll();
		for (int i = 0; i < tmp.size(); i++) {
			que.push(tmp[i]);
		}
		que.pop();
	}
}

TrieNode* Trietree::Getprenode(const std::string pre) {
	if (pre.size() == 0) {
		return nullptr;
	}
	TrieNode* node = root;
	for (int i = 0; i < pre.size(); i++) {
		if (node->Contain(pre[i])) {
			node = node->SetNext(pre[i]);
		}
		else {
			return nullptr;
		}
	}
	return node;
}

std::vector<std::string> Trietree::Getpreword(const std::string pre) {
	std::vector<std::string> result;
	TrieNode* node = Getprenode(pre);
	if (node == nullptr) {
		return result;
	}
	std::vector<TrieNode*>node_list;
	node->DFS_Vist(node_list);
	for (auto& n : node_list) {
		if (n->Ifend()) {
			result.push_back(n->word);
		}
	}
	return result;
	
}