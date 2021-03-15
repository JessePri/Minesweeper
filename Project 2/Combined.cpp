#include <cstddef>
#include <sstream>
using std::stringstream;

struct TreeNode {
        TreeNode* left;
        TreeNode* right;
        char value;
        size_t prob;
        TreeNode(char value, size_t prob = 0, TreeNode* left = nullptr, TreeNode* right = nullptr) {
            this->left = left;
            this->right = right;
            this->value = value;
            this->prob = prob;
    }
};

struct GreaterThanPointers {
    GreaterThanPointers() = default;
    bool operator()(TreeNode* lhs, TreeNode* rhs) {
        return lhs->prob > rhs->prob;
    }
};


#include <string>
#include <unordered_map>
#include <queue> 
#include <vector>

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

#include <string>
#include <queue>
#include <vector>
#include <fstream>
#include <iostream>

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


// int main() {
//     huffman_tree ht("/hufftext.txt");
//     ht.PrintDictionary();
//     cout << ht.encode("/hufftext.txt") << endl;
//     cout << "DECODE TEST: " << endl << ht.decode("1010101000111111100101010100101111100111101011001011110100000000110111011101100000101110010111110111110011010111101101000011011111010101011000110100010111101001111000001010000111110111111001111100001010111001010101011000111110111010010110011100111010110101101011111001111010110010111101000000001011111101101011100111001110100110000111001010001001110011101001011111001111010110010111101000000001100111001110100110000111001010000010101110000111111100111001101000111100100111001100011001110101101111101110011010111111000100111011010100000110011001111101111111010010000011111111010000110000011000001101111101110100100000011001100010011011111011001011011011001011011011000011111011001011000100101011000100110011111100001101101100101111100111101011001011110100000000100100101011000100110011111100001101101100011011010010101001001010001101111110111100100011011011001000011011111111011111111001011000111110000111000001011000100011100101010100100111011110111110100110110100101011011101111101110001110100010011100011101011111001000100011100101010101010101000011111011001011010111011100001111101100101100111100110101000000100111011000001100010100101011100101010100011111001100100011000001101000100011100101010101010101000011111011001011010111011100001111101100101100111100110101001000011011011101010010101110010101010001111111001010101001001110111101111101000111110110010110101110111110111000011110100100001000001011010100001111100100010001110010101010101010100011100000111000001101101001010100101011100101010100011111001100100011000001101000100011100101010101010101001011111001111010110010111101000000001101110111000011111011001011001111001101010110100011111101000111010011000101011100101010101010101001000011011111111011110111011100001111101100101100111100110101001000011011011101011011101111101110000111101001000010000010110101000010110110111011011000011111011001011001111001101010000001001110110000011000101101110111110111000011110100100001000001011010100000010101110010101010001111111000011111110011100111001110011010001111001001110011000110011101011011111011100110101111110001001110110101000001100110011111011111001001111000001001000101010011100110100111000101010100111110000111111100001101100111111101111110010001000111001010101011011111110000010111110100101111111101001000001110110001001100111111000000100101011000001010000010010001110110001101010101100100101110011111101100101001110001010101001111100001111111000011011001111111001000100011100101010101010101011000111110111010010110011100111010110101100100110000110011111100001111111100010101011000000111111011010111001110011101011001001011110100111101110100100001100000101100111001110101101011100011100100100101011100000111111011010111001110011101011001001011110100111100000110110001111100001110011001110011101001100001110010100000101011100101010100011111110000111111100") << endl;
//     cout << "Not a crash" << endl;
//     return 0;
// }


