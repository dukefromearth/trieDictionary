#include "Trie.h"
#include <algorithm>

std::string toLower(std::string s){
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

TrieNode::TrieNode()
{//sets everything to null
	for (int i = 0; i < SIZE; i++)
	{
		children[i] = NULL;
	}
	endOfWord = false;
}

TrieNode::TrieNode(TrieNode* p, int i){
    for (int i = 0; i < SIZE; i++)
    {
        children[i] = NULL;
    }
    endOfWord = false;
    parent = p;
    index = i;
}

StringTrie::StringTrie()
{
	root_ = new TrieNode;
	size_ = 0;
}

StringTrie::StringTrie(std::string s)
{//string parameter is name of text file to be opened
	root_ = NULL;
	size_ = 0;
	std::ifstream mystream;
	std::string toInsert;
	mystream.open(s.c_str());
	while (!mystream.eof())
	{
		mystream >> toInsert;
		insert(toLower(toInsert));
	}
	mystream.close();
}

void StringTrie::load(std::string s)
{
	clear();
	std::ifstream mystream;
	std::string toInsert;
	mystream.open(s.c_str());
	while (!mystream.eof())
	{
		mystream >> toInsert;
		insert(toInsert);
	}
	mystream.close();
}

bool StringTrie::insert(const std::string& s)
{
	if (root_ == NULL)//root is a dummy node that points to children
	{
		root_= new TrieNode;
	}
	TrieNode* toTraverse = root_;
	traverse(toTraverse, s, true);
    if (toTraverse->endOfWord)
        return false;
	toTraverse->endOfWord = true;//finished string, now at end of word
	size_++;
    return true;
}

bool StringTrie::contains(const std::string& s)
{
	if (root_ == NULL)
		return false;//empty tree
	TrieNode* toTraverse = root_;
	if (!traverse(toTraverse, s))
		return false;
	return (toTraverse->endOfWord);
}

bool StringTrie::remove(const std::string& s)
{//lazy delete
	if (root_ == NULL)
		return false;
	TrieNode* toTraverse = root_;
	if (!traverse(toTraverse, s))
		return false;
	toTraverse->endOfWord = false;
	return true;
}

void StringTrie::clear()
{
	clear(root_);
	size_ = 0;
}

void StringTrie::clear(TrieNode* root)
{
	for (int i = 0; i < SIZE; i++)
	{
		if (root->children[i] != NULL)
			clear(root->children[i]);
	}
    delete root;
}

int StringTrie::numWords()
{
	return size_;
}


int StringTrie::countNodes()
{
	return countNodes(root_);
}

int StringTrie::countNodes(TrieNode* root)
{
	int count = 1;
	for (int i = 0; i < SIZE; i++)
	{
		if (root->children[i] != NULL)
		{
			count += countNodes(root->children[i]);
		}
	}
	return count;
}

bool StringTrie::traverse(TrieNode* &root, const std::string& s, bool create)
{//traverses the string s path in root
	//if inserting, create== true
	//returns false if hits null before end of string
	for (int i = 0; i < s.length(); i++)
	{
		int index = s[i] - 'a';
		if (root->children[index] == NULL)
		{
			if (create)
				root->children[index] = new TrieNode(root,index);
			else
				return false;
		}
        root = root->children[index];
	}
	return true;
}

//traverses to the node at the end of the string
TrieNode* StringTrie::getNode(std::string s){
    TrieNode* toGet = root_;
    for (int i=0; i<s.length(); ++i){
        int index = s[i] - 'a';
        toGet = toGet->children[index];
    }
    return toGet;
}

//reverses a string
std::string reverseString(std::string s){
    std::string newString = "";
    if (s.length() > 0){
        for (int i=(int)s.length()-1; i>=0; --i){ //typecast to make compiler stfu
            newString += s[i];
        }
    }
    return newString;
}

//crawls up from child to parent, returns string from root to leaf
std::string crawlUp(TrieNode* startOfWord, TrieNode* endOfWord){
    std::string word;
    char letter = 0;
    while (startOfWord != endOfWord){
        letter = endOfWord->index + 'a';
        word += letter;
        endOfWord = endOfWord->parent;
    }
    if (word.length() > 1)
        word = reverseString(word);
    return word;
}

//returns of vector of strings that start with the specified prefix
std::vector<std::string> StringTrie::getSuffix(std::string prefix)
{
    std::queue <TrieNode*> myQueue;
    std::vector <std::string> vec;
    TrieNode* root = getNode(prefix);
    
    myQueue.push(root);
    while(!myQueue.empty())
	{
		TrieNode* top = myQueue.front();
		for (int i = 0; i < SIZE; i++)
		{
            if (top->children[i] != NULL){
                myQueue.push(top->children[i]);
            }
		}
        if(root_ != top && top->endOfWord)
            vec.push_back(crawlUp(root_,myQueue.front()));
		myQueue.pop();
	}
    return vec;
}
