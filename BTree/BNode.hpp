//  Fabio SIlveira Tanikawa
//  TIA: 32092563
//  Gabriel Batista Cristiano
//  TIA: 32090722
//  Julia carvalho de Souza Castro
//  TIA: 32022298

#ifndef BNode_hpp
#define BNode_hpp

#include <stdio.h>

class BNode {
  int *keys;
  int degree;
  BNode **ChildP;
  int m; //ordem da árvore
  bool leaf;

   public:
  
  BNode(int degree, bool leaf);
    
  void setkey(int value, int i);
  int getKey(int i);
    
  void setOrder(int value);
  int getOrder();
    
  void setChild(BNode* node, int i);
  BNode* getChild(int i);
    
  bool getLeaf();

  void traverse();

  int searchKey(int key);
  void insertNonFull(int key);
  void splitChild(int i, BNode *node);
  void deletion(int key);
  void removeFromLeaf(int id);
  void removeFromNonLeaf(int id);
  int getPredecessor(int id);
  int getSuccessor(int id);
  void fill(int id);
  void borrowFromPrev(int id);
  void borrowFromNext(int id);
  void merge(int id);
};

#endif /* BNode_hpp */
