//  Fabio SIlveira Tanikawa
//  TIA: 32092563
//  Gabriel Batista Cristiano
//  TIA: 32090722
//  Julia carvalho de Souza Castro
//  TIA: 32022298

#include "BTree.hpp"
#include <iostream>

using namespace std;

void BTree::insertion(int key) {
  if (root == nullptr)
  {
    root = new BNode(order, true);
    root->setkey(key, 0);
    root->setOrder(1);
  } else {
    if (root->getOrder() == 2 * order - 1) {
      BNode *newNode = new BNode(order, false);

      newNode->setChild(root, 0);

      newNode->splitChild(0, root);

      int i = 0;
      if (newNode->getKey(0) < key)
        i++;
      newNode->getChild(i)->insertNonFull(key);

      root = newNode;
    } else
      root->insertNonFull(key);
  }
}

void BTree::deletion(int key) {
  if (!root) {
    cout << "The tree is empty\n";
    return;
  }

  root->deletion(key);

  if (root->getOrder() == 0) {
    BNode *temp = root;
    if (root->getLeaf())
      root = NULL;
    else
      root = root->getChild(0);

    delete temp;
  }
  return;
}

