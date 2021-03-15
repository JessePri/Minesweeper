#include <iostream>
#include <vector>


using namespace std;

class Node {
    public:
        int value;
        Node* next = NULL;
};

float interQuartile(Node* head) {
    /* Key:
        qN: the  Nth quartile
        pN: the term before qN
        fN: the term forward of qN
        T: The tracker that goes up 4 each iteration (every 4 cycles of the while loop)
    */
    
    int count = 1;
    unsigned char iteration = 0;
    Node* T = head;
    Node* p1;
    Node* q1 = head;
    Node* p3;
    Node* q3 = head;
    Node* newHead = new Node;
    newHead->next = head;
    p1 = newHead;
    p3 = newHead;
    int size = 0;
    while (T != nullptr) {
        if (count == 4) {
            p1 = p1->next;
            q1 = q1->next;
            T = T->next;
            count = 1;
            ++size;
            continue;
        }
        p3 = p3->next;
        q3 = q3->next;
        T = T->next;
        ++count;
        ++size;
        cout << "p1,q1: " << p1->value << ","<< q1->value << " p3: " << p3->value << endl;
    }
    float trueQ1;
    float trueQ3;
    cout << size << endl;
    size /= 2;
    if (size % 2 == 0) {
        trueQ1 = (static_cast<float>(p1->value) + static_cast<float>(q1->value))/2;
        trueQ3 = (static_cast<float>(p3->value) + static_cast<float>(q3->value))/2;
    } else {
        trueQ1 = q1->value;
        trueQ3 = p3->value;
    } 
    cout << "Count: " << count << endl;
    cout << trueQ3 << ", " << trueQ1 << endl;
    return  (trueQ3 - trueQ1);
}


float median(Node* head) {
    /* Key:
        qN: the  Nth quartile
        pN: the term before qN
        fN: the term forward of qN
        T: The tracker that goes up 4 each iteration (every 4 cycles of the while loop)
    */
    
    int count = 1;
    unsigned char iteration = 0;
    Node* T = head;
    Node* p1;
    Node* q1 = head;
    Node* p3;
    Node* q3 = head;
    Node* newHead = new Node;
    newHead->next = head;
    p1 = newHead;
    p3 = newHead;
    int size = 0;
    while (T != nullptr) {
        if (count == 2) {
            p1 = p1->next;
            q1 = q1->next;
            T = T->next;
            count = 1;
            ++size;
            continue;
        }
        p3 = p3->next;
        q3 = q3->next;
        T = T->next;
        ++count;
        ++size;
        cout << "p1,q1: " << p1->value << ","<< q1->value << " p3: " << p3->value << endl;
    }
    float trueQ1;
    float trueQ3;
    cout << size << endl;
    //size /= 2;
    if (size % 2 == 0) {
        trueQ1 = (static_cast<float>(p1->value) + static_cast<float>(q1->value))/2;
        trueQ3 = (static_cast<float>(p3->value) + static_cast<float>(q3->value))/2;
    } else {
        trueQ1 = q1->value;
        trueQ3 = p3->value;
    } 
    cout << "Count: " << count << endl;
    cout << trueQ3 << ", " << trueQ1 << endl;
    return  (trueQ1);
}

void PrintAll(Node* head) {
    Node* node = head;
    while (node != nullptr) {
        cout << node->value << ", ";
        node = node->next;
    }
    cout << endl;
}

Node* MakeList (vector<int> list) {
    int index = 0;
    Node* head = new Node;
    head->value = list[index++];
    Node* tracer = head;
    for (int i = 1; i < list.size(); ++i) {
        Node* newNode = new Node;
        newNode->value = list[i];
        tracer->next = newNode;
        tracer = newNode;
    }
    return head;
}


int main() {
    vector<int> list2;
    for (int i = 1; i < 2; ++i) {
        list2.push_back(i);
    }
    vector<int> list = {1,8,15,43,82,101,110,2456,55345,137556};
    vector<int> list3 = {2,4,4,5,6,7,8};
    Node* node1 = MakeList(list);
    PrintAll(node1);
    cout << median(node1) << endl;

    return 0;
}
