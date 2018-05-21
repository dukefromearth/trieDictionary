#ifndef dictionary_h
#define dictionary_h

#include "Trie.h"
#include <vector>
#include <iostream>

class Dictionary{
private:
    StringTrie dictionary_;
public:
    Dictionary() {}
    Dictionary(std::string file) : dictionary_(StringTrie(file)) {}
    ~Dictionary() { dictionary_.clear(); }
    void load(std::string file);
    bool isLegalWord(std::string word);
    void suggest(std::string s, int n);
    int numWords();
    void print();
};

#endif /* dictionary_h */
