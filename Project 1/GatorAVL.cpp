#include "GatorAVL.h"
#include <iostream>
#include <queue>
#include <string>


using std::string;
using std::cout;
using std::endl;

GatorAVL::GatorAVL() {
    root = nullptr;
}

/* Balancing, Height, And Related Functions */

void GatorAVL::Balance() {
    BalanceRecursive(root);
    Update(root);
}

/* Problems
    - Current is that balance factor is called first then the balancing
    - SOLUTIONS:
        -check for balance again
        -check for balance when you are going to balance (LETS THROOOOWWWW)
            -IT WORKED
        -change markers
*/



void GatorAVL::BalanceRecursive(Student*& node) {
    if (node == nullptr || !(node->marker)) {
        return;
    }
    BalanceRecursive(node->left);
    BalanceRecursive(node->right);
    // cout << node->id << endl;
    if (IsBalanced(node)) {
        return;
    }
    if (LeftLeft(node)) {
        // cout << "LL" << endl;
        RotateRight(node);
    } else if (LeftRight(node)) {
        // cout << "LR" << endl;
        RotateLeftRight(node);
    } else if (RightLeft(node)) {
        // cout << "RL" << endl;
        RotateRightLeft(node);
    } else if (RightRight(node)) {
        // cout << "RR" << endl;
        RotateLeft(node);
    }
}




// void GatorAVL::BalanceRecursive(Student*& node) {
//     if (node == nullptr || !(node->marker)) {
//         return;
//     } else if (IsBalanced(node)) {
//         BalanceRecursive(node->left);
//         BalanceRecursive(node->right);
//         cout << node->id << endl;
//         PrintChildren(node);
//         return;
//     }
//     BalanceRecursive(node->left);
//     BalanceRecursive(node->right);
//     cout << node->id << endl;
//     if (LeftLeft(node)) {
//         cout << "LL" << endl;
//         RotateRight(node);
//     } else if (LeftRight(node)) {
//         cout << "LR" << endl;
//         RotateLeftRight(node);
//     } else if (RightLeft(node)) {
//         cout << "RL" << endl;
//         RotateRightLeft(node);
//     } else if (RightRight(node)) {
//         cout << "RR" << endl;
//         RotateLeft(node);
//     }
// }

void GatorAVL::Update(Student*& node) {
    if (node == nullptr) {
        return;
    }
    node->marker = false;
    Update(node->left);
    Update(node->right);
}

bool GatorAVL::IsBalanced(Student* node) {
    // cout << "BALANCE FACTOR: " << 
    //     AbsoluteValue(Height(node->left) - Height(node->right)) << endl;
    return AbsoluteValue(Height(node->left) - Height(node->right)) 
            < BALANCE_FACTOR;
}

GatorAVL::Student* GatorAVL::RotateLeft(Student*& node) {
    // cout << "ROTATE LEFT" << endl;
    Student* temp = node->right;
    node->right = node->right->left;
    temp->left = node;
    // node->heightUpdateMarker = true;  /* WARNING: THESE BREAK CODE!!!! */
    // node->left->heightUpdateMarker = true;
    Height(temp); 
    node = temp;
    return temp;
}

GatorAVL::Student* GatorAVL::RotateRight(Student*& node) {
    // cout << "ROTATE Right" << endl;
    Student* temp = node->left;
    node->left = node->left->right;
    temp->right = node;
    // node->heightUpdateMarker = true; // Markers set to true when 
    // node->right->heightUpdateMarker = true;
    Height(temp); // May not be necessary?
    node = temp;
    return temp;
}


GatorAVL::Student* GatorAVL::RotateLeftRight(Student*& node) {
    RotateLeft(node->left);
    RotateRight(node);
    return node;
}

GatorAVL::Student* GatorAVL::RotateRightLeft(Student*& node) {
    RotateRight(node->right);
    RotateLeft(node);
    return node;
}

short GatorAVL::Height(Student* node) {
    if (node == nullptr) {
        return 0;
    } else {
        node->height =  1 + Max(Height(node->left), Height(node->right));
        return node->height;
    } 
    // else {
    //     return node->height;
    // }
}


/* Misc And Helpers */

string GatorAVL::IdTo8Digit(int id) {
    string tempID = std::to_string(id);
    int numZeros = 8 - tempID.size();
    string toReturn = "";
    for (int i = 0; i < numZeros; ++i) {
        toReturn += "0";
    }
    toReturn += tempID;
    return toReturn;
}

short GatorAVL::Max(short n1, short n2) {
    if (n1 > n2) {
        return n1;
    } else {
        return n2;
    }
}

short GatorAVL::AbsoluteValue(short n) {
    if (n < 0) {
        return -n;
    } else {
        return n;
    }
}

bool GatorAVL::LeftLeft(Student* node) {
    return Left(node) && Left(node->left);
}

bool GatorAVL::LeftRight(Student* node) {
    return Left(node) && Right(node->left);
}

bool GatorAVL::RightLeft(Student* node) {
    return Right(node) && Left(node->right);
}

bool GatorAVL::RightRight(Student* node) {
    return Right(node) && Right(node->right);
}

bool GatorAVL::Right(Student* node) {
    return (node->right != nullptr && node->right->marker);
}

bool GatorAVL::Left(Student* node) {
    return (node->left != nullptr && node->left->marker);
}

void GatorAVL::PrintInorderHelper(Student* node, std::string& toPrint) {
    if (node == nullptr) {
        return;
    }
    PrintInorderHelper(node->left, toPrint);
    toPrint += node->name + ", ";
    PrintInorderHelper(node->right, toPrint);
}
void GatorAVL::PrintPreorderHelper(Student* node, std::string& toPrint) {
    if (node == nullptr) {
        return;
    }
    toPrint += node->name + ", ";
    PrintPreorderHelper(node->left, toPrint);
    PrintPreorderHelper(node->right, toPrint);
}
void GatorAVL::PrintPostorderHelper(Student* node, std::string& toPrint) {
    if (node == nullptr) {
        return;
    }
    PrintPostorderHelper(node->left, toPrint);
    PrintPostorderHelper(node->right, toPrint);
    toPrint += node->name + ", ";
}

void GatorAVL::PrintIDofName(Student* node, const std::string& name, string& toPrint) {
    if (node == nullptr) {
        return;
    } else if (node->name == name) {
        toPrint += IdTo8Digit(node->id) + "\n";
        PrintIDofName(node->left, name, toPrint);
        PrintIDofName(node->right, name, toPrint);
    } else {
        // cout << "NO MATCH node->name: " << node->name << " name: " << name << endl;
        PrintIDofName(node->left, name, toPrint);
        PrintIDofName(node->right, name, toPrint);
    }
}

void GatorAVL::FindInOrderNthID(Student* node, unsigned short& n, 
    int& id) {
    if (node == nullptr) {
        return;
    }
    FindInOrderNthID(node->left, n, id);
    if (n == 0) {
        id = node->id;
    }
    --n;
    FindInOrderNthID(node->right, n, id);
}

void GatorAVL::MarkAll(Student* node) {
    if (node == nullptr) {
        return;
    }
    node->marker = true;
    MarkAll(node->left);
    MarkAll(node->right);
}

void GatorAVL::MarkLeft(Student* node) {
    if (node == nullptr) {
        return;
    }
    node->marker = true;
    MarkAll(node->left);
}

void GatorAVL::MarkRight(Student* node) {
    if (node == nullptr) {
        return;
    }
    node->marker = true;
    MarkAll(node->right);
}

/* Functionality */

void GatorAVL::PrintInorder() {
    string toPrint = "";
    PrintInorderHelper(root, toPrint);
    toPrint.pop_back();
    toPrint.pop_back();
    cout << toPrint << endl;
}
void GatorAVL::PrintPreorder() {
    string toPrint = "";
    PrintPreorderHelper(root, toPrint);
    toPrint.pop_back();
    toPrint.pop_back();
    cout << toPrint << endl;
}
void GatorAVL::PrintPostorder() {
    string toPrint = "";
    PrintPostorderHelper(root, toPrint);
    toPrint.pop_back();
    toPrint.pop_back();
    cout << toPrint << endl;
}
void GatorAVL::PrintLevelCount() {
    cout << Height(root) << endl;
}

void GatorAVL::InsertNameID(const std::string& name, int id) {
    Student* student = new Student;
    student->id = id;
    student->name = name;
    student->marker = true;
    if (root == nullptr) {
        root = student;
        cout << "successful" << endl;
        return;
    }
    Student* prev;
    Student* node = root;
    bool greater = false;
    while (node != nullptr) {
        prev = node;
        prev->marker = true;
        if (id > node->id) {
            node = node->right;
            greater = true;
        } else {
            node = node->left;
            greater = false;
        }
    }
    if (prev == nullptr) {
        // cout << "WOW THAT SUCkS" << endl;
    }
    if (prev->id == id) {
        cout << "unsuccessful" << endl;
        Update(root);
        return;
    } else if (greater) {
        prev->right = student;
    } else {
        prev->left = student;
    }
    cout << "successful" << endl;
    Balance();
}
/* GOALS:
    - Turn this spaghetti into fettuccine, that is...
    - Test this on a single node 
    - Test this on two nodes
    - Test this on three nodes
    - Do the above after you have finished messing about with current spaghetti
        - Spaghetti seems to work, perform the above tests now.
*/
void GatorAVL::RemoveID(int id) {
    
    if (root == nullptr) {
        cout << "unsuccessful" << endl;
        return;
    }
    Student* prev;
    Student* node = root;
    bool greater = false;
    while (node != nullptr && node->id != id) {
        prev = node;
        prev->marker = true;
        if (id > node->id) {
            node = node->right;
            greater = true;
        } else {
            node = node->left;
            greater = false;
        }
    }
    if (node == nullptr) {
        cout << "unsuccessful" << endl;
        return;
    }
    bool left = !(node->left == nullptr);
    bool right = !(node->right == nullptr);
    // cout << "Print 1" << endl;
    // PrintChildren(root);
    /* Handels cases of 0 or 1 children */
    if (!left && !right) {
        delete node;
        if (node == root) {
            root = nullptr;
        } else if (greater) {
            prev->right = nullptr;
        } else {
            prev->left = nullptr;
        }
        Update(root);
        return;
    } else if (left && !right) {
        Student* temp = node->left;
        delete node;
        if (node == root) {
            root = temp;
        } else if (greater) {
            prev->right = temp;
        } else {
            prev->left = temp;
        }
        Update(root);
        return;
    } else if (!left && right) {
        Student* temp = node->right;
        delete node;
        if (node == root) {
            root = temp;
        } else if (greater) {
            prev->right = temp;
        } else {
            prev->left = temp;
        }
        Update(root);
        return;
    }
    /* Handles two children */
    Student* prev2 = node;
    prev2->marker = true;
    Student* node2 = node->right;
    bool wentRight = false;
    while (node2->left != nullptr) {
        prev2 = node2;
        prev2-> marker = true;
        node2 = node2->left;
        wentRight = true;
    }
    // cout << "Print 2" << endl;
    // PrintChildren(root);
    if (prev2 != root) {
        prev2->left = node2->right;
    }
    if (wentRight) {
        node2->right = node->right;
    }
    node2->left = node->left;
    // cout << "node->id" << node->id << endl;
    // cout << "prev->id" << prev->id << endl;
    // cout << "node2->id" << node2->id << endl;
    // cout << "prev2->id" << prev2->id << endl;
    // cout << "Print 3" << endl;
    // PrintChildren(node2);
    if (node == root) {
        // cout << "HIT" << endl;
        delete root;
        root = node2;
    } else if (greater) {
        prev->right = node2;
    } else {
        prev->left = node2;
    }
    // cout << "Print 4" << endl;
    // PrintChildren(root);
    // PrintLevelOrder();
    cout << "successful" << endl;
    /* code to ensure a nearly empty root gets balanced upon removal of the 
        previous root */
    if (root != nullptr) {
        // cout << "YIKES" << endl;
        left = !(root->left == nullptr);
        right = !(root->right == nullptr);
        // cout << std::boolalpha << left << endl;
        // cout << std::boolalpha << right << endl;
        if (left && !right) {
            MarkLeft(root);
        } else if (!left && right) {
            MarkRight(root);
        }
    }
    Balance();
}
// void GatorAVL::RemoveID(int id) {
    
//     if (root == nullptr) {
//         cout << "unsuccessful" << endl;
//         return;
//     }
//     Student* prev;
//     Student* node = root;
//     bool greater = false;
//     while (node != nullptr && node->id != id) {
//         prev = node;
//         prev->marker = true;
//         if (id > node->id) {
//             node = node->right;
//             greater = true;
//         } else {
//             node = node->left;
//             greater = false;
//         }
//     }
//     if (node == nullptr) {
//         cout << "unsuccessful" << endl;
//         return;
//     }
//     bool left = !(node->left == nullptr);
//     bool right = !(node->right == nullptr);
//     cout << "Print 1" << endl;
//     PrintChildren(root);
//     /* Handels cases of 0 or 1 children */
//     if (!left && !right) {
//         delete node;
//         if (node == root) {
//             root = nullptr;
//         } else if (greater) {
//             prev->right = nullptr;
//         } else {
//             prev->left = nullptr;
//         }
//         return;
//     } else if (left && !right) {
//         Student* temp = node->left;
//         delete node;
//         if (node == root) {
//             root = temp;
//         } else if (greater) {
//             prev->right = temp;
//         } else {
//             prev->left = temp;
//         }
//         return;
//     } else if (!left && right) {
//         Student* temp = node->right;
//         delete node;
//         if (node == root) {
//             root = temp;
//         } else if (greater) {
//             prev->right = temp;
//         } else {
//             prev->left = temp;
//         }
//         return;
//     }
//     /* Handles two children */
//     Student* prev2 = node;
//     prev2->marker = true;
//     Student* node2 = node->left;
//     bool wentRight = false;
//     while (node2->right != nullptr) {
//         prev2 = node2;
//         prev2-> marker = true;
//         node2 = node2->right;
//         wentRight = true;
//     }
//     cout << "Print 2" << endl;
//     PrintChildren(root);
//     if (prev2 != root) {
//         prev2->right = node2->left;
//     }
//     if (wentRight) {
//         node2->left = node->left;
//     }
//     node2->right = node->right;
//     cout << "node->id" << node->id << endl;
//     cout << "prev->id" << prev->id << endl;
//     cout << "node2->id" << node2->id << endl;
//     cout << "prev2->id" << prev2->id << endl;
//     cout << "Print 3" << endl;
//     PrintChildren(node2);
//     if (node == root) {
//         cout << "HIT" << endl;
//         delete root;
//         root = node2;
//     } else if (greater) {
//         prev->right = node2;
//     } else {cout << "HIT" << endl;
//         prev->left = node2;
//     }
//     cout << "Print 4" << endl;
//     PrintChildren(root);
//     // PrintLevelOrder();
//     cout << "successful" << endl;
//     /* code to ensure a nearly empty root gets balanced upon removal of the 
//         previous root */
//     if (root != nullptr) {
//         cout << "YIKES" << endl;
//         left = !(root->left == nullptr);
//         right = !(root->right == nullptr);
//         cout << std::boolalpha << left << endl;
//         cout << std::boolalpha << right << endl;
//         if (left && !right) {
//             MarkLeft(root);
//         } else if (!left && right) {
//             MarkRight(root);
//         }
//     }
//     Balance();
// }


void GatorAVL::SearchID(int id) {
    if (root == nullptr) {
        cout << "unsuccessful" << endl;
        return;
    }
    Student* prev;
    Student* node = root;
    bool greater = false;
    while (node != nullptr && node->id != id) {
        prev = node;
        prev->marker = true;
        if (id > node->id) {
            node = node->right;
            greater = true;
        } else {
            node = node->left;
            greater = false;
        }
    }
    if (node == nullptr) {
        cout << "unsuccessful" << endl;
        return;
    }
    cout << node->name << endl;
}

void GatorAVL::SearchName(const std::string& name) {
    string toPrint = "";
    // cout << "SEARCH NAME: " << name << endl;
    PrintIDofName(root, name, toPrint);
    // cout << "toPrint: " << toPrint << endl;
    if (toPrint.empty()) {
        cout << "unsuccessful" << endl;
    } else {
        toPrint.pop_back();
        cout << toPrint << endl;
    }
}

void GatorAVL::RemoveInorder(unsigned short n) {
    int id = -1;
    FindInOrderNthID(root, n, id);
    RemoveID(id);
}

void GatorAVL::PrintLevelOrder() {
    Student* node = root;
    if (node == nullptr) {
        std::cout << "EMPTY!"<< std::endl;
    }
    std::queue<Student*> treeQ;
    treeQ.push(node);
    Student* temp;
    unsigned int levelNumber = 1;
    while (!treeQ.empty())  {
        size_t count = treeQ.size();
        std::cout << "Level: " << levelNumber++ << std::endl;
        while (count != 0) {
            temp = treeQ.front();
            if (temp == nullptr) {
                treeQ.pop();
                --count;
                continue;
            }
            std::cout << std::boolalpha << temp->id << " marker: "<< temp->marker << ", ";
            treeQ.push(temp->left);
            treeQ.push(temp->right);
            treeQ.pop();
            --count;
        }
        std::cout << std::endl;
    }
}

void GatorAVL::PrintChildren(Student* node) {
        bool left = !(node->left == nullptr);
        bool right = !(node->right == nullptr);
        cout << "Left Child: ";
        if (!left) {
            cout << "nullptr ";
        } else {
            cout << node->left->id;
        }
        cout << endl;
        cout << "Right Child: ";
        if (!right) {
            cout << "nullptr ";
        } else {
            cout << node->right->id;
        }
        cout << endl;
}