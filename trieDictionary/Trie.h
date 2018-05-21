#ifndef STRINGTRIE_H
#define STRINGTRIE_H

#include <fstream>
#include <string>
#include <queue>

const int SIZE = 26;
struct TrieNode
{
    TrieNode* parent;
    int index;
	TrieNode* children[SIZE];
	bool endOfWord;
	TrieNode();
    TrieNode(TrieNode* p, int i);
};

class StringTrie
{
private:
	TrieNode* root_;
	int size_;//number of Words
	bool traverse(TrieNode * & root, const std::string& s, bool create=false);
	int countNodes(TrieNode* root);
	void clear(TrieNode* root);
    TrieNode* getNode(std::string s);//returns address of last letter in s
    
public:
	StringTrie();
	StringTrie(std::string s);//paramter is name of text file
	void load(std::string s);
	bool insert(const std::string& s);
	bool contains(const std::string& s);
	bool remove(const std::string& s);
	void clear();
	int numWords();
	int countNodes();
    ~StringTrie() {}
    std::vector<std::string> getSuffix(std::string prefix);
};
#endif
