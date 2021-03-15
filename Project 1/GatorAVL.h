#pragma once
#include <string>
#include <iostream>

class GatorAVL {
private:
    const char BALANCE_FACTOR = 2;
    /* These two variables are used to keep track where the rotation occurs */
    /* Notes on Student
        - above is used to lay markers
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
        bool heightUpdateMarker = true;
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
    //GatorAVL(const GatorAVL& other);
    // GatorAVL& operator=(const GatorAVL& rhs);
    // ~GatorAVL();
    

    

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