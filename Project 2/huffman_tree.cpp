#include "huffman_tree.h"
#include "GreaterThanPointers.h"
#include <string>
#include <queue>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

using std::stringstream;
using std::getline;
using std::ifstream;
using std::unordered_map;
using std::priority_queue;
using std::string;
using std::greater;
using std::vector;
using std::pair;
using std::cout;
using std::endl;

void HitList() {
    static unsigned int hitNum = 1;
    cout << "HIT #" << hitNum++ << endl;
}


huffman_tree::huffman_tree(const string& input) {
    root = nullptr;
    MakeTree(input);
    if (root != nullptr) {
        if (root->left == nullptr && root->right == nullptr) {
            dictionary.emplace(root->value, "0");
        } else {
            MakeDictionary(root, "");
        }
    }    
}
    

string huffman_tree::get_character_code(char character) const {
    auto iter = dictionary.find(character);
    if (iter != dictionary.end()) {
        return iter->second;
    } else {
        return "";
    }
}

string huffman_tree::encode(const string& input) const {
    string toReturn = "";
    string fileContents = "";
    ReadFile(input, fileContents);
    if (fileContents.empty()) {
        return toReturn;
    }
    for (char c : fileContents) {
        auto iter = dictionary.find(c);
        if (iter == dictionary.end()) {
            return "";
        } else {
            toReturn += iter->second;
        }
    }
    return toReturn;
}

string huffman_tree::decode(const string& string_to_decode) const {
    char toCompare;
    string toReturn = "";
    if (root == nullptr) {
        return toReturn;
    } else if (root->left == nullptr && root->right == nullptr) {
        toCompare = dictionary.find(root->value)->second[0];
        for (char bit : string_to_decode) {
            if (bit != toCompare) {
                return "";
            } else {
                toReturn += root->value;
            }
        }
        return toReturn;
    }
    TreeNode* node = root;
    char letter;
    char temp;
    bool leaf;
    for (char bit : string_to_decode) {
        leaf = false;
        toCompare = bit;
        Traverse(node, letter, bit, leaf);
        if (bit != toCompare) {
            return "";
        } else if (leaf) {
            toReturn += letter;
            node = root;
        }
    } 
    if (leaf) {
        return toReturn;
    } else {
        return "";
    }
}

/* Helper Functions */

void huffman_tree::MakeTree(const std::string& input) {
    GreaterThanPointers gp;
    string fileStr;
    priority_queue<TreeNode*, vector<TreeNode*>, GreaterThanPointers> q;
    ReadFile(input, fileStr);
    CreateNodeQueue(q, fileStr);
    while (q.size() > 1) {
        TreeNode* node1 = q.top();
        q.pop();
        TreeNode* node2 = q.top();
        q.pop();
        TreeNode* internalNode = new TreeNode('~');
        if (gp(node1, node2)) {  
            internalNode->left = node2;
            internalNode->right = node1;
        } else {
            internalNode->left = node1;
            internalNode->right = node2;
        }
        internalNode->prob = node1->prob + node2->prob;
        q.push(internalNode);
    }
    root = q.top();
}

void huffman_tree::CreateNodeQueue(priority_queue<TreeNode*, vector<TreeNode*>, GreaterThanPointers>& q, const string& fileStr) {
    unordered_map<char, unsigned int> charProbs;
    CreateCharProbs(charProbs, fileStr);
    if (charProbs.empty()) {
        q.emplace(nullptr);
        return;
    }
    for (pair<char, unsigned int> p : charProbs) {
        TreeNode* node = new TreeNode(p.first, p.second);
        q.emplace(node);
    }
}

void huffman_tree::CreateCharProbs(unordered_map<char, unsigned int>& charProbs, const std::string& fileStr) {
    unordered_map<char, unsigned int>::iterator iter;
    for (char c : fileStr) {
        iter = charProbs.find(c);
        if (iter == charProbs.end()) {
            charProbs.emplace(c,1);
        } else {
            ++(iter->second);
        }
    }
}


void huffman_tree::MakeDictionary(TreeNode* node, string code) {
    if (node->left == nullptr && node->right == nullptr) {
        dictionary.emplace(node->value, code);
    } else if (node->right == nullptr) {
        MakeDictionary(node->left, code + '0');
    } else if (node->left == nullptr) {
        MakeDictionary(node->right, code + "1");
    } else {
        MakeDictionary(node->left, code + '0');
        MakeDictionary(node->right, code + '1');
    }
}

void huffman_tree::ReadFile(const string& input, string& toReturn) const {
    if (input[0] != '/') {
        toReturn = input;
        return;
    }
    string file (input.cbegin() + 1, input.cend());
    ifstream fileStream;
    fileStream.open(file);
    stringstream temp;
    bool first = true;
    if (fileStream.is_open()) {
        while (temp << fileStream.rdbuf()) {
            first = false;
        }
    }
    toReturn = std::move(temp.str());
    cout << "toReturn: " << endl << toReturn << endl;
}

void huffman_tree::Traverse(TreeNode*& node, char& toReturn, char& bit, bool& leaf) const {
    if (bit == '1') {
        node = node->right;
    } else {
        node = node->left;
    }
    if (node == nullptr) {
        ++bit;
    } else {
        toReturn = node->value;
        leaf = node->left == nullptr && node->right == nullptr;
    }
}



void huffman_tree::PrintDictionary() {
    for (pair<char, string> dp : dictionary) {
        cout << "Character: " << dp.first << " Bits: " << dp.second << endl;
    }
}







