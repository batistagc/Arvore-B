//  Fabio SIlveira Tanikawa
//  TIA: 32092563
//  Gabriel Batista Cristiano
//  TIA: 32090722
//  Julia carvalho de Souza Castro
//  TIA: 32022298

//  Referências
//  https://www.programiz.com/dsa/deletion-from-a-b-tree - Implementação da árvore
//  https://www.youtube.com/watch?v=38RM8_VMIcI
//  

#include <iostream>
#include "BTree.hpp"

using namespace std;

int main() {

    BTree t(3);
    t.insertion(8);
    t.insertion(9);
    t.insertion(10);
    t.insertion(11);
    t.insertion(15);
    t.insertion(16);
    t.insertion(17);
    t.insertion(18);
    t.insertion(20);
    t.insertion(23);

    cout << "Arvore B: ";
    t.traverse();

    t.deletion(20);

    cout << "\nArvore B: ";
    t.traverse();
    cout << "\n";
    
}

