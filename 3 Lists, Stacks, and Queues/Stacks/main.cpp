#include <iostream>
//#include "Stack_ll.h"
#include <stack>

using std::stack;
using std::cout;
using std::endl;

bool inLanguage(char* theString) {
    stack<char> charStk;
    char* ptr = theString;
    while (*ptr != '\0') {
        charStk.push(*ptr++);
    }
    unsigned int countA = 0;
    unsigned int countB = 0;
    while (!charStk.empty()) {
        if (charStk.top() == 'A') {
            ++countA;
        } else if (charStk.top() == 'B') {
            ++countB;
        } else {
            return false;
        }
        charStk.pop();
    }
    return countA == countB;
}

int main() {
    char* str = "ABBA";
    cout << std::boolalpha << inLanguage(str) << endl;
    return 0;
}