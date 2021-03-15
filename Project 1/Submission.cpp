#include <string>
#include <iostream>
#include <queue>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::vector;
using std::stoi;
 
class GatorAVL {
private:
    const char BALANCE_FACTOR = 2;
    /* Notes on Student
        - marker is used as bread crumbs for the balance function 
            to follow
    */

    struct Student {
        std::string name = "";
        int id = 0;
        short height = 1;
        Student* left = nullptr;
        Student* right = nullptr;
        /* Shows when a node need to be handeled carefully
            - When it is rotated (have to update height)
            - When a node is part of the path of insertion/removal
                (rebalancing)
        */
        bool marker = false;
    };

    Student* root = nullptr;

    /* Balancing, Height, And Related Functions */

    Student* RotateLeft(Student*& node);
    Student* RotateRight(Student*& node);
    
    Student* RotateLeftRight(Student*& node);
    Student* RotateRightLeft(Student*& node);

    /* Balances the tree
        - In the proccess of going throught he nodes that need balancing
            it removes markers and allows height to become efficient again
    */
    void Balance();

    void BalanceRecursive(Student*& node);
    void Update(Student*& node);

    bool IsBalanced(Student* node);

    short Height(Student* node);

    /* Misc And Helpers */
    short Max(short n1, short n2);
    short AbsoluteValue(short n1);

    bool LeftLeft(Student* node);
    bool LeftRight(Student* node);
    bool RightLeft(Student* node);
    bool RightRight(Student* node);

    bool Right(Student* node);
    bool Left(Student* node);

    void PrintInorderHelper(Student* node, std::string& toPrint);
    void PrintPreorderHelper(Student* node, std::string& toPrint);
    void PrintPostorderHelper(Student* node, std::string& toPrint);
    
    void PrintChildren(Student* node);

    void PrintIDofName(Student* node, const std::string& name, std::string& toPrint);

    void FindInOrderNthID(Student* node, unsigned short& n, int& id);

    void MarkAll(Student* node);
    void MarkRight(Student* node);
    void MarkLeft(Student* node);

    std::string IdTo8Digit(int id);

public:

    /* Constructor */

    GatorAVL(); 

    /* Functionality */

    void InsertNameID(const std::string& name, int id);
    void RemoveID(int id);
    void SearchID(int id);
    void SearchName(const std::string& name);
    void PrintInorder();
    void PrintPreorder();
    void PrintPostorder();
    void PrintLevelCount();
    void RemoveInorder(unsigned short n);

    /* Other Printing */
    void PrintLevelOrder();

};


GatorAVL::GatorAVL() {
    root = nullptr;
}

/* Balancing, Height, And Related Functions */

void GatorAVL::Balance() {
    BalanceRecursive(root);
    Update(root);
}

/* BalanceRecursive(Student*& node)
    - Balances the function in the post order
    - Checks if the node is null of if it was in the path of change
        - whether or not node->marker == true
    - Balances the nodes with rotations after if they are not balanced
*/
void GatorAVL::BalanceRecursive(Student*& node) {
    if (node == nullptr || !(node->marker)) {
        return;
    }
    BalanceRecursive(node->left);
    BalanceRecursive(node->right);
    if (IsBalanced(node)) {
        return;
    }
    if (LeftLeft(node)) {
        RotateRight(node);
    } else if (LeftRight(node)) {
        RotateLeftRight(node);
    } else if (RightLeft(node)) {
        RotateRightLeft(node);
    } else if (RightRight(node)) {
        RotateLeft(node);
    }
}


/* Update(Student*& node)
    - This would turn off all the markers in the tree
        - In this tree that would mean it would go down one branch.
*/
void GatorAVL::Update(Student*& node) {
    if (node == nullptr) {
        return;
    }
    node->marker = false;
    Update(node->left);
    Update(node->right);
}

bool GatorAVL::IsBalanced(Student* node) {
    return AbsoluteValue(Height(node->left) - Height(node->right)) 
            < BALANCE_FACTOR;
}

GatorAVL::Student* GatorAVL::RotateLeft(Student*& node) {
    Student* temp = node->right;
    node->right = node->right->left;
    temp->left = node;
    node = temp;
    return temp;
}

GatorAVL::Student* GatorAVL::RotateRight(Student*& node) {
    Student* temp = node->left;
    node->left = node->left->right;
    temp->right = node;
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
}


/* Misc And Helpers */

/* IdTo8Digit(int id)
    - Reformats the ID tha is stored as an int into a 8 digit string
*/
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


/* PrintInorderHelper(Student* node, std::string& toPrint)
    - This is the function that does the traversal from the wrapper function that calls it
    - changes a formated string with the names of the nodes
*/
void GatorAVL::PrintInorderHelper(Student* node, std::string& toPrint) {
    if (node == nullptr) {
        return;
    }
    PrintInorderHelper(node->left, toPrint);
    toPrint += node->name + ", ";
    PrintInorderHelper(node->right, toPrint);
}

/* PrintInorderHelper(Student* node, std::string& toPrint)
    - This is the function that does the traversal from the wrapper function that calls it
    - changes a formated string with the names of the nodes
*/
void GatorAVL::PrintPreorderHelper(Student* node, std::string& toPrint) {
    if (node == nullptr) {
        return;
    }
    toPrint += node->name + ", ";
    PrintPreorderHelper(node->left, toPrint);
    PrintPreorderHelper(node->right, toPrint);
}

/* PrintInorderHelper(Student* node, std::string& toPrint)
    - This is the function that does the traversal from the wrapper function that calls it
    - changes a formated string with the names of the nodes
*/
void GatorAVL::PrintPostorderHelper(Student* node, std::string& toPrint) {
    if (node == nullptr) {
        return;
    }
    PrintPostorderHelper(node->left, toPrint);
    PrintPostorderHelper(node->right, toPrint);
    toPrint += node->name + ", ";
}

/* PrintIDofName(Student* node, const std::string& name, string& toPrint)
    - Helps print the IDs in preorder when the a search for and ID is done
*/
void GatorAVL::PrintIDofName(Student* node, const std::string& name, string& toPrint) {
    if (node == nullptr) {
        return;
    } else if (node->name == name) {
        toPrint += IdTo8Digit(node->id) + "\n";
        PrintIDofName(node->left, name, toPrint);
        PrintIDofName(node->right, name, toPrint);
    } else {
        
        PrintIDofName(node->left, name, toPrint);
        PrintIDofName(node->right, name, toPrint);
    }
}

/* FindInOrderNthID(Student* node, unsigned short& n, int& id)
    - This find the Nth id in terms of an inorder traversal
    - Used to remove a kth item in the tree
*/
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


/* MarkAll(Student* node)
    - Marks all the nodes in the tree as true
    - Not used in the implentation
*/
void GatorAVL::MarkAll(Student* node) {
    if (node == nullptr) {
        return;
    }
    node->marker = true;
    MarkAll(node->left);
    MarkAll(node->right);
}

/* MarkLeft(Student* node) 
    - Marks all the nodes in the left most path
    - Used in the remove function when the root is left without a right node for rebalancing
*/
void GatorAVL::MarkLeft(Student* node) {
    if (node == nullptr) {
        return;
    }
    node->marker = true;
    MarkAll(node->left);
}

/* MarkRight(Student* node) 
    - Marks all the nodes in the left most path
    - Used in the remove function when the root is right without a left node for rebalancing
*/
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
    if (toPrint.empty()) {
        cout << endl;
        return;
    }
    toPrint.pop_back();
    toPrint.pop_back();
    cout << toPrint << endl;
}
void GatorAVL::PrintPreorder() {
    string toPrint = "";
    PrintPreorderHelper(root, toPrint);
    if (toPrint.empty()) {
        cout << endl;
        return;
    }
    toPrint.pop_back();
    toPrint.pop_back();
    cout << toPrint << endl;
}
void GatorAVL::PrintPostorder() {
    string toPrint = "";
    PrintPostorderHelper(root, toPrint);
    if (toPrint.empty()) {
        cout << endl;
        return;
    }
    toPrint.pop_back();
    toPrint.pop_back();
    cout << toPrint << endl;
}
void GatorAVL::PrintLevelCount() {
    std::cout << Height(root) << std::endl;
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
    /* Finds the previous node to insert the new node */
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
        cout << "successful" << endl;
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
        cout << "successful" << endl;
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
        cout << "successful" << endl;
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
    if (prev2 != root) {
        prev2->left = node2->right;
    }
    if (wentRight) {
        node2->right = node->right;
    }
    node2->left = node->left;
    if (node == root) {
        delete root;
        root = node2;
    } else if (greater) {
        prev->right = node2;
    } else {
        prev->left = node2;
    }
    cout << "successful" << endl;
    /* Handels a special case when the root is left without a left or right element */
    if (root != nullptr) {
        left = !(root->left == nullptr);
        right = !(root->right == nullptr);
        if (left && !right) {
            MarkLeft(root);
        } else if (!left && right) {
            MarkRight(root);
        }
    }
    Balance();
}

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
    PrintIDofName(root, name, toPrint);
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

/* PrintLevelOrder()
    - This is not part of the main functionality
    - Primary used a debug function
*/
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

/* PrintChildren(Student* node)
    - Also used in debugging
    - Prints the left and right child of the node
*/
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




/* Parsers */


/* VecPrinter(vector<string> cmd) 
    - Used for debugging
    - Not used in the parser or any other main functionality
*/
void VecPrinter(vector<string> cmd) {
    for (string str : cmd) {
        cout << str << " ";
    }
    cout << endl;
}

#include <cctype>
bool IsValidChar(char c) {
    return isalpha(c) || isblank(c);
}

bool IsValidName(string name) {
    bool toReturn = true;
    for (char c : name) {
        toReturn = IsValidChar(c) && toReturn;
    }
    return toReturn;
}

bool IsValidID (string id) {
    if (id.size() != 8) {
        return false;
    }
    bool toReturn = true;
    for (char c : id) {
        toReturn = isdigit(c) && toReturn;
    }
    return toReturn;
}

/* Splitter(const string& cmdString, bool& containsString)
    - This takes an input a string and a boolean
    - cmdString
        - The function turns this into a vector of meaningful strings for gatorAVL
        - The boolean determines whether or not a the input contains a string
*/
vector<string> Splitter(const string& cmdString, bool& containsString) {
    vector<string> inputs;
    string toAdd = "";
    size_t size = cmdString.size();
    bool inQuote = false;
    bool first = true;
    for (size_t i = 0; i < size; ++i) {
        char c = cmdString[i];
        if (!inQuote && c == ' ' && !toAdd.empty()) {
            inputs.push_back(toAdd);
            toAdd.clear();
        } else if (c == '\"') {
            inQuote = !inQuote;
            containsString = true;
            if (i == size - 1) {
                inputs.push_back(toAdd);
            }
        } else {
            toAdd += c;
            if (i == size - 1) {
                inputs.push_back(toAdd);
            }
        }
    }
    return inputs;
}


/* ExecuteCommand(GatorAVL& gatorAVL, const vector<string>& cmd, bool containsString)
    - Takes gatorAVL, the command vector, and a boolean
    - Based on the command vector it executes certain commands
        - Different versions of the same command are run dependent
         on the containsString boolean

*/
void ExecuteCommand(GatorAVL& gatorAVL, const vector<string>& cmd, bool containsString) {
    string commandName = cmd[0];
    if (commandName == "insert") {
        if (IsValidName(cmd[1]) && IsValidID(cmd[2])) {
           gatorAVL.InsertNameID(cmd[1], stoi(cmd[2])); 
        } else {
            cout << "unsuccessful" << endl;
        }
    } else if (commandName == "remove") {
        if (IsValidID(cmd[1])) {
            gatorAVL.RemoveID(stoi(cmd[1]));
        } else {
            cout << "unsuccessful" << endl;
        }
    } else if (commandName == "search") {
        if (containsString) {
            gatorAVL.SearchName(cmd[1]);
        } else {
            if (IsValidID(cmd[1])) {
                gatorAVL.SearchID(stoi(cmd[1]));
            } else {
                cout << "unsuccessful" << endl;
            }
        }
    } else if (commandName == "printInorder") {
        gatorAVL.PrintInorder();
    } else if (commandName == "printPreorder") {
        gatorAVL.PrintPreorder();
    } else if (commandName == "printPostorder") {
        gatorAVL.PrintPostorder();
    } else if (commandName == "printLevelCount") {
        gatorAVL.PrintLevelCount();
    } else if (commandName == "removeInorder") {
        gatorAVL.RemoveInorder(stoi(cmd[1]));
    }
}


/* Parser(GatorAVL& gatorAVL)
    - This function takes in cin inputs
    - For each input it runs the command if it is valid
*/
void Parser(GatorAVL& gatorAVL) {
    string cmdString = "";
    unsigned int commandCount = 0;
    cin >> commandCount;
    string empty;
    getline(cin, empty);
    while (commandCount > 0 && getline(cin, cmdString)) {
        bool containsString = false;
        vector<string> cmd = Splitter(cmdString, containsString);
        ExecuteCommand(gatorAVL, cmd, containsString);
        --commandCount;
    }
}


int main() {
    GatorAVL gatorAVL;
    Parser(gatorAVL);
    return 0;
}