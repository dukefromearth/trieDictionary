#include "dictionary.h"

void Dictionary::load(std::string file){
    dictionary_.clear();
    dictionary_ = StringTrie(file);
}

bool Dictionary::isLegalWord(std::string word){
    return dictionary_.contains(word);
}

int Dictionary::numWords(){
    return dictionary_.numWords();
}

void Dictionary::suggest(std::string s, int n){
    std::vector<std::string> suggestions = dictionary_.getSuffix(s);
    for (int i=0; i < n; ++i){
        std::cout << suggestions[i] << std::endl;
    }
}

