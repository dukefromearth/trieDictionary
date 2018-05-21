#include <iostream>
#include "dictionary.h"

int main(){
    Dictionary dic("/Users/stephenduke/Documents/School/trieDictionary/trieDictionary/words.txt");
//    dic.load("/Users/stephenduke/Documents/School/trieDictionary/trieDictionary/words.txt");
    dic.suggest("car", 10);
}
