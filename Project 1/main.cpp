#include "GatorAVL.h"
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::vector;
using std::stoi;


/* Parsers */
/* To do for tommorrow:
    - Finish string parsers
    - Get it working on stepik
    - Clean code and do the above step again
    - Make documentation
    - You got a segmentation fault
        - Run the input in the main to figure it out...
*/

void VecPrinter(vector<string> cmd) {
    for (string str : cmd) {
        cout << str << " ";
    }
    cout << endl;
}

vector<string> Splitter(const string& cmdString, bool& containsString) {
    vector<string> inputs;
    string toAdd = "";
    size_t size = cmdString.size();
    for (size_t i = 0; i < size; ++i) {
        char c = cmdString[i];
        if (c == ' ' && !toAdd.empty()) {
            inputs.push_back(toAdd);
            toAdd.clear();
        } else if (c == '\"') {
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

void ExecuteCommand(GatorAVL& gatorAVL, const vector<string>& cmd, bool containsString) {
    string commandName = cmd[0];
    if (commandName == "insert") {
        gatorAVL.InsertNameID(cmd[1], stoi(cmd[2]));
    } else if (commandName == "remove") {
        gatorAVL.RemoveID(stoi(cmd[1]));
    } else if (commandName == "search") {
        if (containsString) {
            // cout << cmd[1] << endl;
            gatorAVL.SearchName(cmd[1]);
        } else {
            gatorAVL.SearchID(stoi(cmd[1]));
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

void Parser(GatorAVL& gatorAVL) {
    string cmdString = "";
    unsigned int commandCount = 0;
    cin >> commandCount;
    string empty;
    // cout << "emtpy: " << empty << endl;
    getline(cin, empty);
    while (commandCount > 0 && getline(cin, cmdString)) {
        // cout << "HIT" << endl;
        // cout << "cmdString: " << cmdString << endl;
        bool containsString = false;
        vector<string> cmd = Splitter(cmdString, containsString);
        // cout << std::boolalpha << containsString << endl;
        // VecPrinter(cmd);
        ExecuteCommand(gatorAVL, cmd, containsString);
        gatorAVL.PrintLevelOrder();
        --commandCount;
        // cout << "COMMAND COUNT: " << commandCount << endl;
    }
}









int main() {
    GatorAVL gatorAVL;
    Parser(gatorAVL);
    cout << "TEST" << endl;
    string str = "000030000";
    int i = stoi(str);
    cout << "i:" << i << endl;










    // gatorAVL.InsertNameID("20", 20);
    // cout << "############################" << endl;

    // gatorAVL.InsertNameID("asdf", 30);
    // cout << "############################" << endl;

    // gatorAVL.InsertNameID("3333", 40);
    // cout << "############################" << endl;

    // gatorAVL.InsertNameID("asrrRRRRRRRdf", 21);
    // cout << "############################" << endl;

    // gatorAVL.RemoveID(30);
    // cout << "############################" << endl;

    // gatorAVL.RemoveID(21);
    // cout << "############################" << endl;

    // gatorAVL.RemoveID(40);
    // cout << "############################" << endl;

    // gatorAVL.RemoveID(20);
    // cout << "############################" << endl;

    // gatorAVL.InsertNameID("20", 20);
    // cout << "############################" << endl;

    // gatorAVL.InsertNameID("asdf", 30);
    // cout << "############################" << endl;
    
    // gatorAVL.InsertNameID("3333", 40);
    // cout << "############################" << endl;

    // gatorAVL.PrintLevelOrder();
    // cout << "############################" << endl;

    // gatorAVL.PrintPreorder();
    // gatorAVL.PrintInorder();
    // gatorAVL.PrintPostorder();
    // cout << "############################" << endl;
    return 0;
}