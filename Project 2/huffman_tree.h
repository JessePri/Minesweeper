#pragma once

#include <string>
#include <unordered_map>
#include <queue> 
#include <vector>
#include "TreeNode"
#include "GreaterThanPointers.h"

class huffman_tree {
private:
    //add your data structures here
    std::unordered_map<char, std::string> dictionary;
    TreeNode* root;

    /* Helper Functions */
    void MakeTree(const std::string& input);
    void CreateNodeQueue(std::priority_queue<TreeNode*, std::vector<TreeNode*>, GreaterThanPointers>& q, const std::string& fileStr);
    void CreateCharProbs(std::unordered_map<char, unsigned int>& charProbs, const std::string& fileStr);

    void MakeDictionary(TreeNode* node, std::string code);
   
    void ReadFile(const std::string& input, std::string& toReturn) const;

    void Traverse(TreeNode*& node, char& toReturn, char& bit, bool& child) const;
public:

    /*
    Preconditions: input is a string of characters with ascii values 0-127
    Postconditions: Reads the characters of input and constructs a
    huffman tree based on the character frequencies of the file contents
    */

    huffman_tree(const std::string& input);


    /*
    Preconditions: input is a character with ascii value between 0-127
    Postconditions: Returns the Huffman code for character if character is in the tree
    and an empty string otherwise.
    */

    std::string get_character_code(char character) const;


    /*
    Preconditions: input is a string of characters with ascii values 0-127
    Postconditions: Returns the Huffman encoding for the contents of file_name
    if file name exists and an empty string otherwise.
    If the file contains letters not present in the huffman_tree,
    return an empty string
    */

    std::string encode(const std::string& input) const;


    /*
    Preconditions: string_to_decode is a string containing Huffman-encoded text
    Postconditions: Returns the plaintext represented by the string if the string
    is a valid Huffman encoding and an empty string otherwise
    */

    std::string decode(const std::string& string_to_decode) const;

    /* Debugging Functions */
    void PrintDictionary();
};