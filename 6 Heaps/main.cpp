#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void HasChildren(int n, bool& left, bool& right, int size) {
    left = (2*n + 1) < size;
    right = (2*n + 2) < size;
}

int Min(int n1, int n2) {
    if (n1 < n2) {
        return n1;
    } else {
        return n2;
    }
}

int readHeap(int* theheap)
{
    int size = 0;
    int i;
    while (cin >> i) {
        if (i == -1) {
            break;
        }
        *theheap = i;
        ++size;
        ++theheap;
    }
    return size;
}




void heapRemove(int* theheap, int& size) {
    /* Heap Notes
        - Let index = n
        - parrent (n - 1)/2
        - left child (2n + 1)/2
        - right child (2n + 2)/2
    */
    cout << theheap[0] << endl;
    theheap[0] = theheap[--size];
    int n = 0;
    bool hasLeft = false;
    bool hasRight = false;
    HasChildren(n, hasLeft, hasRight, size);
    int left = -1;
    int right = -1;
    int min = -1;
    int swapIndex = -1;
    int temp = -1;
    while (hasLeft || hasRight) {
        left = 2*n + 1;
        right = 2*n + 2;
        // cout << "--------------------------------" << endl;
        // cout << "Left: " << left << endl;
        // cout << "Right: " << right << endl;
        if (hasLeft && hasRight) {
           swapIndex = Min(theheap[left], theheap[right]);
        //    cout << "Swap Value: " << swapIndex << endl;
        //    cout << "Left Value: " << theheap[left] << endl;
        //    cout << "Right value: " << theheap[right] << endl;
           if (swapIndex == theheap[left]) {
               swapIndex = left;
           } else {
               swapIndex = right;
           }
        //    cout << "Swap Index: " << swapIndex << endl;
        } else if (hasRight) {
            swapIndex = right;
        } else if (hasLeft) {
            swapIndex = left;
        } else {
            break;
        }
        // if (theheap[n] > theheap[swapIndex]) {
        temp = theheap[swapIndex];
        theheap[swapIndex] = theheap[n];
        theheap[n] = temp;
        n = swapIndex;
        HasChildren(n, hasLeft, hasRight, size);
    }
}

void heapPrint(int* theheap, int size)
{
    for (int i = 0; i < size; ++i) {
        cout << theheap[i] << " ";
    }
    cout << endl;
}

int kthlargest(vector<int>& nums, int k) {
    priority_queue<int> pq(nums.begin(), nums.end());
    while (k > 1) {
        pq.pop();
        --k;
    }
    return pq.top();
}

void RemoveElements(size_t n, priority_queue<int>& pq) {
    while (n > 0) {
        pq.pop();
        --n;
    }
}
/* Why this doesn't work...
    - I assumed the vector would come in ordered
    - I assumed the the medians that I would need to find 
        would be for that ordered vector
*/

/* Look at stack overflow for the solution */
vector<double> findMedian(vector<int> arr) {
    vector<double> toReturn;
    if (arr.empty()) {
        return toReturn;
    }
    bool even = (arr.size() % 2) == 0; 
    double vals[2];
    priority_queue<int> pq(arr.begin(), arr.end());
    size_t n = pq.size();
    if (even) {
        RemoveElements(n/2 - 1, pq);
        vals[0] = pq.top();
        RemoveElements(1, pq);
        vals[1] = pq.top();
        toReturn.push_back((static_cast<double>(vals[0]) +
            static_cast<double>(vals[1]))/2.0f);
    } else {
        RemoveElements(n/2, pq);
        toReturn.push_back(pq.top());
    }
    while (!pq.empty()) {
        even = !even;
        if (even) {
            vals[0] = pq.top();
            RemoveElements(1,pq);
            vals[1] = pq.top();
            toReturn.push_back((static_cast<double>(vals[0]) +
                static_cast<double>(vals[1]))/2.0f);
        } else {
            toReturn.push_back(pq.top());
        }
    }
    reverse(toReturn.begin(), toReturn.end());
    return toReturn;
}


void HasChildren(int n, int size, bool& hasLeft, bool& hasRight) {
    hasLeft = (2 * n + 1) < size;
    hasRight = (2 * n + 2) < size;
}

int Max(int n1, int n2) {
    if (n1 > n2) {
        return n1;
    } else {
        return n2;
    }
}

int* extractMax(int arr[], int size) {
    arr[0] = arr[--size];
    int n = 0;
    bool hasLeft;
    bool hasRight;
    HasChildren(n, size, hasLeft, hasRight);
    int left;
    int right;
    int swapIndex;
    int temp;
    while (hasLeft || hasRight) {
        left = 2 * n + 1;
        right = 2 * n + 2;
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
        if (arr[n] < arr[swapIndex]) {
            temp = arr[n];
            arr[n] = arr[swapIndex];
            arr[swapIndex] = temp;
            n = swapIndex;
            HasChildren(n, size, hasLeft, hasRight);
        } else {
            break;
        }
    }
    return arr;
}


int main() {
    int x[6] = {1,4,3,10,12,6};
    int size = 6;
    heapRemove(x, size);
    // cout << "###########################" << endl;
    heapRemove(x, size);
    heapPrint(x, size);
    return 0;
}

bool InArray(int n, int size) {
    return n < size;
}

int GetLeftChildIndex(int n) {
    return (2*n + 1);
}

int GetRightChildIndex(int n) {
    return (2*n + 2);
}

bool IsMinHeapNode(int arr[], int n, int size) {
    int left = GetLeftChildIndex(n);
    int right = GetRightChildIndex(n);
    bool hasLeft = InArray(left, size);
    bool hasRight = InArray(right, size);
    if (hasLeft && hasRight) {
        return (arr[n] <= arr[left] && arr[n] <= arr[right]);
    } else if (hasLeft) {
        return arr[n] <= arr[left];
    } else if (hasRight) {
        return arr[n] <= arr[right];
    } else {
        return true;
    }
}

bool IsMaxHeapNode(int arr[], int n, int size) {
    int left = GetLeftChildIndex(n);
    int right = GetRightChildIndex(n);
    bool hasLeft = InArray(left, size);
    bool hasRight = InArray(right, size);
    if (hasLeft && hasRight) {
        return (arr[n] >= arr[left] && arr[n] >= arr[right]);
    } else if (hasLeft) {
        return arr[n] >= arr[left];
    } else if (hasRight) {
        return arr[n] >= arr[right];
    } else {
        return true;
    }
}


bool isMinHeap(int arr[],int size) {
    bool toReturn = true;
    for (int i = 0; i < size; ++i) {
        toReturn = toReturn && IsMinHeapNode(arr, i, size);
    }
    return toReturn;
}

bool isMaxHeap(int arr[],int size) {
    bool toReturn = true;
    for (int i = 0; i < size; ++i) {
        toReturn = toReturn && IsMaxHeapNode(arr, i, size);
    }
    return toReturn;
}

int heapPlay(int arr[],int size) {
    bool min = isMinHeap(arr, size);
    bool max = isMaxHeap(arr, size);
    if (min && max) {
        return 0;
    } else if (min || max) {
        return arr[0];
    } else {
        return -1;
    }
}


vector<double> findMedian(vector<int> arr) {
    size_t size = arr.size();
    int pair[2];
    vector<double> toReturn;
    bool odd = false;
    unsigned int index = 0;
    for (unsigned int i = 0; i < size; ++i) {
        odd = !odd;
        if (odd) {
            pair[0] = arr[index++];
            toReturn.push_back(pair[0]);
        } else {
            pair[1] = arr[index];
            toReturn.push_back((static_cast<double>(pair[0]) +
                static_cast<double>(pair[1]))/2.0f);
        }
    }
    return toReturn;
}