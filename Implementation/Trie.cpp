#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/**
 * This isn't an actual template, but it like
 * gets the basic trie stuff down...
 * 
 * Binary trie is basically the same thing, just
 * change up some stuff.
 */
struct TrieNode {
	int cnt = 0;
	array<TrieNode*, 26> ch;
};

TrieNode* new_node() {
	TrieNode* cur = new TrieNode;
	(cur -> ch).fill(nullptr);
	return cur;
}

TrieNode* root = new_node();
void insert(const string &s) {
	TrieNode* cur = root;
	for (int i = 0; i < s.size(); i++) {
		int x = s[i] - 'a';
		if ((cur -> ch)[x] == nullptr) {
			(cur -> ch)[x] = new_node();
		}
		cur = (cur -> ch)[x];
		(cur -> cnt)++;
	}
}