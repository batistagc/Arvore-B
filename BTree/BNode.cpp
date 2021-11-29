//  Fabio SIlveira Tanikawa
//  TIA: 32092563
//  Gabriel Batista Cristiano
//  TIA: 32090722
//  Julia carvalho de Souza Castro
//  TIA: 32022298

#include "BNode.hpp"
#include <iostream>

using namespace std;

BNode::BNode(int degree1, bool leaf1)
{
    degree = degree1;
    leaf = leaf1;

    keys = new int[2 * degree - 1];
    ChildP = new BNode *[2 * degree];

    m = 0;
}

void BNode::setkey(int value, int i)
{
    keys[i] = value;
}

int BNode::getKey(int i)
{
    return keys[i];
}

void BNode::setOrder(int value)
{
    m = value;
}

int BNode::getOrder()
{
    return m;
}

void BNode::setChild(BNode* node, int i)
{
    ChildP[i] = node;
}

BNode* BNode::getChild(int i)
{
    return ChildP[i];
}

bool BNode::getLeaf()
{
    return leaf;
}


int BNode::searchKey(int key)
{
    int i = 0;
      while (i < m && keys[i] < key)
        ++i;
      return i;
}

void BNode::deletion(int key)
{
    int id = searchKey(key);

     if (id < m && keys[id] == key) {
       if (leaf)
         removeFromLeaf(id);
       else
         removeFromNonLeaf(id);
     } else {
       if (leaf) {
         cout << "A chave " << key << " não foi encontrada na árvore\n";
         return;
       }

       bool flag = ((id == m) ? true : false);

       if (ChildP[id]->m < degree)
         fill(id);

       if (flag && id > m)
         ChildP[id - 1]->deletion(key);
       else
         ChildP[id]->deletion(key);
     }
     return;
}

void BNode::removeFromLeaf(int id)
{
    for (int i = id + 1; i < m; ++i)
        keys[i - 1] = keys[i];

      m--;

      return;
}

void BNode::removeFromNonLeaf(int id)
{
    int key = keys[id];

      if (ChildP[id]->m >= degree) {
        int parent = getPredecessor(id);
        keys[id] = parent;
        ChildP[id]->deletion(parent);
      }

      else if (ChildP[id + 1]->m >= degree) {
        int child = getSuccessor(id);
        keys[id] = child;
        ChildP[id + 1]->deletion(child);
      }

      else {
        merge(id);
        ChildP[id]->deletion(key);
      }
      return;
}

int BNode::getPredecessor(int id)
{
    BNode *current = ChildP[id];
      while (!current->leaf)
        current = current->ChildP[current->m];

      return current->keys[current->m - 1];
}

int BNode::getSuccessor(int id)
{
    BNode *current = ChildP[id + 1];
      while (!current->leaf)
        current = current->ChildP[0];

      return current->keys[0];
}

void BNode::fill(int id)
{
    if (id != 0 && ChildP[id - 1]->m >= degree)
        borrowFromPrev(id);

      else if (id != m && ChildP[id + 1]->m >= degree)
        borrowFromNext(id);

      else {
        if (id != m)
          merge(id);
        else
          merge(id - 1);
      }
      return;
}

void BNode::borrowFromPrev(int id)
{
    BNode *child = ChildP[id];
    BNode *sibling = ChildP[id - 1];

    for (int i = child->m - 1; i >= 0; --i)
      child->keys[i + 1] = child->keys[i];

    if (!child->leaf) {
      for (int i = child->m; i >= 0; --i)
        child->ChildP[i + 1] = child->ChildP[i];
    }

    child->keys[0] = keys[id - 1];

    if (!child->leaf)
      child->ChildP[0] = sibling->ChildP[sibling->m];

    keys[id - 1] = sibling->keys[sibling->m - 1];

    child->m += 1;
    sibling->m -= 1;

    return;
}

void BNode::borrowFromNext(int id)
{
    BNode *child = ChildP[id];
    BNode *sibling = ChildP[id + 1];

    child->keys[(child->m)] = keys[id];

    if (!(child->leaf))
      child->ChildP[(child->m) + 1] = sibling->ChildP[0];

    keys[id] = sibling->keys[0];

    for (int i = 1; i < sibling->m; ++i)
      sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->leaf) {
      for (int i = 1; i <= sibling->m; ++i)
        sibling->ChildP[i - 1] = sibling->ChildP[i];
    }

    child->m += 1;
    sibling->m -= 1;

    return;
}

void BNode::merge(int id)
{
    BNode *child = ChildP[id];
    BNode *sibling = ChildP[id + 1];

    child->keys[degree - 1] = keys[id];

    for (int i = 0; i < sibling->m; ++i)
      child->keys[i + degree] = sibling->keys[i];

    if (!child->leaf) {
      for (int i = 0; i <= sibling->m; ++i)
        child->ChildP[i + degree] = sibling->ChildP[i];
    }

    for (int i = id + 1; i < m; ++i)
      keys[i - 1] = keys[i];

    for (int i = id + 2; i <= m; ++i)
      ChildP[i - 1] = ChildP[i];

    child->m += sibling->m + 1;
    m--;

    delete (sibling);
    return;
}

void BNode::insertNonFull(int key) {
  int i = m - 1;

  if (leaf == true) {
    while (i >= 0 && keys[i] > key) {
      keys[i + 1] = keys[i];
      i--;
    }

    keys[i + 1] = key;
    m = m + 1;
  } else {
    while (i >= 0 && keys[i] > key)
      i--;

    if (ChildP[i + 1]->m == 2 * degree - 1) {
      splitChild(i + 1, ChildP[i + 1]);

      if (keys[i + 1] < key)
        i++;
    }
    ChildP[i + 1]->insertNonFull(key);
  }
}

void BNode::splitChild(int i, BNode *node) {
  BNode *newNode = new BNode(node->degree, node->leaf);
  newNode->m = degree - 1;

  for (int j = 0; j < degree - 1; j++)
    newNode->keys[j] = node->keys[j + degree];

  if (node->leaf == false) {
    for (int j = 0; j < degree; j++)
      newNode->ChildP[j] = node->ChildP[j + degree];
  }

  node->m = degree - 1;

  for (int j = m; j >= i + 1; j--)
    ChildP[j + 1] = ChildP[j];

  ChildP[i + 1] = newNode;

  for (int j = m - 1; j >= i; j--)
    keys[j + 1] = keys[j];

  keys[i] = node->keys[degree - 1];

  m = m + 1;
}

void BNode::traverse() {
  int i;
  for (i = 0; i < m; i++) {
    if (leaf == false)
      ChildP[i]->traverse();
    cout << " " << keys[i];
  }

  if (leaf == false)
    ChildP[i]->traverse();
}


