#include <stack>
#include <queue>
#include <iostream>
#include <string>

using namespace std;

class Node 
{
    public: 
       int name; // The name serves as the node's value.
       Node* left = NULL;
       Node* right = NULL;
};


// We have provided for you a diagram to aid with visualization/debugging :)
/*

     30       right      20
    /  \     ------>    /  \
  20   34              10  30
 /  \         left        /  \
10  25      <------      25  34 

*/

void LevelPrint(Node* node) {
    if (node == nullptr) {
        cout << "EMPTY!"<< endl;
    }
    queue<Node*> treeQ;
    treeQ.push(node);
    Node* temp;
    unsigned int levelNumber = 1;
    while (!treeQ.empty())  {
        size_t count = treeQ.size();
        cout << "Level: " << levelNumber++ << endl;
        while (count != 0) {
            temp = treeQ.front();
            if (temp == nullptr) {
                treeQ.pop();
                --count;
                continue;
            }
            cout << temp->name << ", ";
            treeQ.push(temp->left);
            treeQ.push(temp->right);
            treeQ.pop();
            --count;
        }
        cout << endl;
    }
}

Node* rotateLeft(Node* node) {
    Node* temp = node->right;
    node->right = node->right->left;
    temp->left = node;
    return temp;
}

Node* rotateRight(Node* node) {
    Node* temp = node->left;
    node->left = node->left->right;
    temp->right = node;
    return temp;
}

Node* rotateLeftRight(Node* node) {
    node->left = rotateLeft(node->left);
    node = rotateRight(node);
    return node;
}

void Insert(int val, Node*& root) {
    Node* newNode = new Node;
    newNode->name = val;
    if (root == nullptr) {
        root = newNode;
        return;
    }
    Node* prev;
    Node* node = root;
    bool greater = false;
    while (node != nullptr) {
        prev = node;
        if (val < node->name) {
            node = node-> left;
        } else {
            node = node->right;
            greater = true;
        }
    }
    if (greater) {
        prev->right = newNode;
    } else {
        prev->left = newNode;
    }
}



/* 5.1.2 ################################################# */\
class TreeNode {
 public:
   int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode() : val(0), left(nullptr), right(nullptr) {}
   TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
   TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void LevelPrint(TreeNode* node) {
    if (node == nullptr) {
        cout << "EMPTY!"<< endl;
    }
    queue<TreeNode*> treeQ;
    treeQ.push(node);
    TreeNode* temp;
    unsigned int levelNumber = 1;
    while (!treeQ.empty())  {
        size_t count = treeQ.size();
        cout << "Level: " << levelNumber++ << endl;
        while (count != 0) {
            temp = treeQ.front();
            if (temp == nullptr) {
                treeQ.pop();
                --count;
                continue;
            }
            cout << temp->val << ", ";
            treeQ.push(temp->left);
            treeQ.push(temp->right);
            treeQ.pop();
            --count;
        }
        cout << endl;
    }
}

void InOrderVectorMaker(vector<TreeNode*>& InOrderVec, TreeNode* node) {
    if (node == nullptr) {
        return;
    }
    InOrderVectorMaker(InOrderVec, node->left);
    InOrderVec.push_back(node);
    InOrderVectorMaker(InOrderVec, node->right);
}

void InOrderVectorPointerClearer(vector<TreeNode*>& InOrderVec
    , vector<TreeNode*>& toReturn) {
    for (TreeNode* node : InOrderVec) {
        TreeNode* newNode = new TreeNode (node->val);
        toReturn.push_back(newNode);
        LevelPrint(newNode);
    }
}

TreeNode* Insert(TreeNode* root, TreeNode* node) {
    if (root == nullptr) {
        return node;
    }
    TreeNode* prev;
    TreeNode* temp = root;
    bool greater = false;
    while (temp != nullptr) {
        prev = temp;
        if (node->val > temp->val) {
            temp = temp->right;
            greater = true;
        } else {
            temp = temp->left;
            greater = false;
        }

    }        
    if (greater) {
        prev->right = node;
    } else {
        prev->left = node;
    }
    return root;
}

void TreeMaker(bool first, vector<TreeNode*>& InOrderVec,
    vector<TreeNode*>::const_iterator front,
    vector<TreeNode*>::const_iterator back, TreeNode* root = nullptr) {
    auto middle = front + (back - front)/2;
    if (back - front <= 0) {
        return;
    } else if (first) {
        cout << "MIDDLE: " << (*middle)->val << endl;
        root = *middle;
        first = false;
        TreeMaker(first, InOrderVec, front, middle, root);
        TreeMaker(first, InOrderVec, middle + 1, back, root);
        return;
    }
    cout << "MIDDLE: " << (*middle)->val << endl;
    Insert(root, *middle);
    TreeMaker(first, InOrderVec, front, middle, root);
    TreeMaker(first, InOrderVec, middle + 1, back, root); 
}

TreeNode* convertToBBST(TreeNode* root) {
    vector<TreeNode*> InOrderVec;
    InOrderVectorMaker(InOrderVec, root);
    if (InOrderVec.empty()) {
        return nullptr;
    }
    vector<TreeNode*> cleanVec;
    InOrderVectorPointerClearer(InOrderVec, cleanVec);
    auto front = cleanVec.cbegin();
    auto back = cleanVec.cend();
    auto middle = front + (back - front)/2;
    TreeNode* toReturn = *middle;
    TreeMaker(true, cleanVec, front, back, toReturn);
    return toReturn;
}

int main() {
    vector<TreeNode> data;
    data.emplace_back(4);
    data.emplace_back(8);
    data.emplace_back(7);
    data.emplace_back(1);
    data.emplace_back(9);
    data.emplace_back(10);
    data.emplace_back(12);
    TreeNode* root = &data.front();
    for (int i = 1; i < data.size(); ++i) {
        Insert(root, &data[i]);
    }
    LevelPrint(root);
    root = convertToBBST(root);
    LevelPrint(root);
    // data.push_back();
    // data.push_back();
    // data.push_back();
    return 0;
}

/* 5.1.3 ################################################################################ */


Node* rotateLeft(Node* node) {
    Node* temp = node->right;
    node->right = node->right->left;
    temp->left = node;
    return temp;
}

Node* rotateRight(Node* node) {
    Node* temp = node->left;
    node->left = node->left->right;
    temp->right = node;
    return temp;
}

Node* rotateRightLeft(Node* node) {
    node->right = rotateRight(node->right);
    node = rotateLeft(node);
    return node;
}

/* 5.2.4 ########################################################################### */
int ABS(int x) {
    if (x < 0) {
        return -x;
    } else {
        return x;
    }
}

int Max(int x, int y) {
    if (x > y) {
        return x;
    } else {
        return y;
    }
}

int Height(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + Max(Height(node->left),Height(node->right));
}

bool isAVL(Node* root) {
    if (root == nullptr) {
        return true;
    }
    bool current = (ABS(Height(root->left) - Height(root->right))) < 2;
    if (current) {
        return isAVL(root->left) && isAVL(root->right);
    } else {
        return false;
    }
}