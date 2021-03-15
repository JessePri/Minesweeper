#include "huffman_tree.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;


/* TO DO:
    - Debug where you are crashing
        - Probably when you are reading the file
        - But it could always be the functor being weird
            - pq being weird aswell
        - Perhaps the node traversal is leadig to a seg fault
*/


int main() {
    huffman_tree ht("hufftext.txt");
    ht.PrintDictionary();
    cout << ht.encode("hufftext.txt") << endl;
    cout << "DECODE TEST: " << ht.decode("1000011101001000110010011101100111001001000111110010011111011111100010001111110100111001001011111011101000111111001") << endl;
    cout << "Not a crash" << endl;
    return 0;
}