//  Fabio SIlveira Tanikawa
//  TIA: 32092563
//  Gabriel Batista Cristiano
//  TIA: 32090722
//  Julia carvalho de Souza Castro
//  TIA: 32022298

#ifndef BTree_hpp
#define BTree_hpp

#include <stdio.h>
#include "BNode.hpp"

class BTree {
  BNode *root;
  int order;

   public:
  BTree(int value) {
    root = NULL;
    order = value;
  }

  void traverse() {
    if (root != NULL)
      root->traverse();
  }

  void insertion(int key);

  void deletion(int key);
};

#endif /* BTree_hpp */
