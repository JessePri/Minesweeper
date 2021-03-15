#include <vector>
#include <iostream>
#include <queue>
#include <string>
#include <stack>

using namespace std;

class Node {
public:
   int val;
   vector<Node*> children;
   Node() {}
   Node(int _val) {
      val = _val;
   }
   Node(int _val, vector<Node*> _children) {
      val = _val;
      children = _children;
   }
};

void preorder(Node* root) { 
    if (root == nullptr) {
        return;
    }
    cout << root->val << " ";
    for (Node* node : root->children) {
        preorder(node);
    }
}

void leveler(queue<Node*>& levelQ, unsigned int levelCount) {
    queue<Node*> nextLevel;
    cout << "Level: " << levelCount << endl;
    while(!levelQ.empty()) {
        Node* node = levelQ.front();
        for (Node* n : node->children) {
            nextLevel.push(n);
        }
        cout << node->val << " ";
        levelQ.pop();
    }
    cout << endl;
    levelQ = move(nextLevel);
}

void levelOrder(Node* root) {
    unsigned int levelCount = 1;
    queue<Node*> levelQ;
    levelQ.push(root);
    while (!levelQ.empty()) {
        leveler(levelQ, levelCount++);
    }
}
/* Problem 2 #################################################### */
 class TreeNode {
 public:
   int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode() : val(0), left(nullptr), right(nullptr) {}
   TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
   TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

void MaxLeft(std::stack<TreeNode*>& q, TreeNode* node) {
    while(node != nullptr) {
        q.push(node);
        node = node->left;
    }
}

void JuggleQ(std::stack<TreeNode*>& q, string& toReturn) {
    if (q.empty()) {
        return;
    }
    while (!q.empty() && q.top()->right == nullptr) {
        TreeNode* node = q.top();
        toReturn += to_string(node->val);
        q.pop();
    }
    if (q.empty()) {
        return;
    } else {
        toReturn += to_string(q.top()->val);
        TreeNode* temp = q.top()->right;
        q.pop();
        MaxLeft(q, temp);
    }
}

std::string traverse(TreeNode* root) {
    std::string toReturn = "";
    std::stack<TreeNode*> q;
    MaxLeft(q, root);
    while (!q.empty()) {
        JuggleQ(q, toReturn);
    }
    return toReturn;
}
/* Part 2 ################################# */
void Flip(TreeNode* node) {
    if (node == nullptr) {
        return;
    } else {
        TreeNode* temp = node->right;
        node->right = node->left;
        node->left = temp;
        Flip(node->right);
        Flip(node->left);
    }
}


/* Part 3 ################################### */

int MaxRight(std::stack<TreeNode*>& treeStk, TreeNode* node) {
    unsigned char count = 0;
    while(node != nullptr) {
        ++count;
        treeStk.push(node);
        node = node->right;
    }
    if (count < 2) {
        return 0;
    } else {
        node = treeStk.top();
        if (node->left == nullptr) {
            return node->val;
        } else {
            return 0;
        }
    }
}

void JuggleStk(std::stack<TreeNode*>& treeStk, int& toReturn) {
    while (!treeStk.empty() && treeStk.top()->left == nullptr) {
        treeStk.pop();
    }
    if (treeStk.empty()) {
        return;
    } else {
        TreeNode* temp = treeStk.top()->left;
        treeStk.pop();
        toReturn += MaxRight(treeStk, temp);
    }
}

void sumOfRightLeaves(TreeNode* root) {
    int toReturn = 0;
    stack<TreeNode*> treeStk;
    toReturn += MaxRight(treeStk, root);
    while (!treeStk.empty()) {
        JuggleStk(treeStk, toReturn);
    }
    cout << toReturn << endl;
}

/* Binary Search Trees ####################################################*/

/* Part 1 ################################## */


void printLeaves(TreeNode* node) {
    if (node == nullptr) {
        return;
    } else if (node->right == nullptr && node->left == nullptr) {
        cout << node->val << " ";
    }
    printLeaves(node->right);
    printLeaves(node->left);
}


TreeNode* insert(TreeNode* node, int key) {
    TreeNode* toInsert = new TreeNode(key);
    if (node == nullptr) {
        return toInsert;
    }
    TreeNode* head = node;
    TreeNode* prev;
    bool greater = false;
    while (node != nullptr) {
        prev = node;
        if (key > node->val) {
            node = node->right;
            greater = true;
        } else if (key < node->val) {
            node = node->left;
            greater = false;
        }
    }
    if (greater) {
        prev->right = toInsert;
    } else {
        prev->left = toInsert;
    }
    return head;
}

bool BothLess(TreeNode* node, TreeNode* n1, TreeNode* n2) {
    return (n1->val < node->val) && (n2->val < node->val);
}

bool BothGreater(TreeNode* node, TreeNode* n1, TreeNode* n2) {
    return (n1->val > node->val) && (n2->val > node->val);
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* n1, TreeNode* n2) {
    TreeNode* node = root;
    while (node != nullptr) {
        if (BothLess(node, n1, n2)) {
            node = node->left;
        } else if (BothGreater(node, n1, n2)) {
            node = node->right;
        } else {
            break;
        }
    }
    return node;
}


/* QUIZ */

void LevelSum(vector<int>& levelSums, queue<TreeNode*>& treeQ) {\
    levelSums.push_back(0);
    queue<TreeNode*> newTreeQ;
    while (!treeQ.empty()) {
        TreeNode* node = treeQ.front();
        levelSums.back() += node->val;
        if (node->left != nullptr) {
            newTreeQ.push(node->left);
        }
        if (node->right != nullptr) {
            newTreeQ.push(node->right);
        }
        treeQ.pop();
    }
    treeQ = std::move(newTreeQ);
}

vector<int> levelOrder(TreeNode* root) {
    vector<int> levelSums;
    if (root == nullptr) {
        return levelSums;
    }
    queue<TreeNode*> treeQ;
    treeQ.push(root);
    do {
        LevelSum(levelSums, treeQ);
    } while (!treeQ.empty());
    return levelSums;
}