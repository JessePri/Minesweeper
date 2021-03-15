#include <vector>
#include <iostream>
using namespace std;


bool ValidIndex(int n, int size) {
    return (n > -1) && (n < size);
}

int Left(int n) {
    return 2*n + 1;
}

int Right(int n) {
    return 2*n + 2;
}

int Max(int n1, int n2) {
    if (n1 > n2) {
        return n1;
    } else {
        return n2;
    }
}


void heapify_down(vector<int>& arr, int size, int root) {
    int index = root;
    int left = Left(index);
    int right = Right(index);
    bool hasLeft = ValidIndex(left, size);
    bool hasRight = ValidIndex(right, size);
    int swapIndex;
    while (true) {
        if (hasLeft && hasRight) {
            swapIndex = Max(arr[left], arr[right]);
            if (swapIndex == arr[left]) {
                swapIndex = left;
            } else {
                swapIndex = right;
            }
        } else if (hasLeft) {
            swapIndex = left;
        } else if (hasRight) {
            swapIndex = right;
        } else {
            break;
        }
        if (arr[index] < arr[swapIndex]) {
            int temp = arr[index];
            arr[index] = arr[swapIndex];
            arr[swapIndex] = temp;
            index = swapIndex;
            left = Left(index);
            right = Right(index);
            hasLeft = ValidIndex(left, size);
            hasRight = ValidIndex(right, size);
        } else {
            break;
        }
    }
}

class Node {
public:
        int value;
        Node* next;
        Node() {next = nullptr;}
        Node(int val) {value = val; next = nullptr;}
};

void Printer(Node* node) {
    for (;node != nullptr; node = node->next) {
        cout << node->value << ", ";
    }
    cout << endl;
}

Node* MergeSort() {
    
} 

Node* sortList(Node* head) {
    vector<Node*> vec;
    while (head != nullptr) {
        vec.push_back(head);
        head = head->next;
    }
    if (vec.size() == 0) {
        return head;
    }

}



Node* MakeList(vector<int> vec) {
    Node* toReturn = new Node(vec[0]);
    Node* temp = toReturn;
    for (int i = 1; i < vec.size(); ++i) {
        Node* node = new Node(vec[i]);
        temp->next = node;
        temp = temp->next;
    }
    return toReturn;
}

int main() {
    vector<int> vec = {1,2,3,20,5,6,7,9,10,11,12};
    Node* root = MakeList(vec);
    Printer(root);
    root = sortList(root);
    Printer(root);
    return 0;
}




