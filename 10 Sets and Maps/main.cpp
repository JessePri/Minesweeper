#include <string>
#include <map>
#include <stack>
#include <vector>
#include <unordered_map>
using namespace std;

map<int,stack<string>> createMap(string* arr, int len) {
    int length;
    map<int, stack<string>> toReturn;
    for (int i = 0; i < len; ++i) {
        length = arr[i].size();
        if (toReturn.find(length) != toReturn.end()) {
            toReturn[length].push(arr[i]);
        } else {
            stack<string> toPush;
            toPush.push(arr[i]);
            toReturn[length] = std::move(toPush);
        }
    }
    return toReturn;
}

bool isPresent(map<int,stack<string>> obj, string value) {
    int length = value.size();
    if (obj.find(length) == obj.end()) {
        return false;
    } else {
        while (!obj[length].empty()) {
            if (obj[length].top() == value) {
                return true;
            }
            obj[length].pop();
        }
        return false;
    }
}

pair<int, int> two_sum(vector<int>& arr, int target) {
    unordered_map<int,int> map;
    int size = arr.size();
    for (int i = 0; i < size; ++i) { 
        map[arr[i]] = i;
    }
    pair<int,int> toReturn;
    toReturn.first = -1;
    toReturn.second = -1;
    int toFind;
    for (int i = 0; i < size; ++i) {
        toFind = target - arr[i];
        if (map.find(toFind) != map.end()) {
            if (map[toFind] == i) {
                continue;
            }
            toReturn.first = i;
            toReturn.second = map[toFind];
            break;
        }
    }
    return toReturn;
}


#include <functional>
#include <list>
class unorderedMap {
public:
    unsigned int countElements = 0;
    const int SIZE = 100;
    hash<int> HashInt;
    int KeyToIndex(int key) {
        return HashInt(key) % (SIZE + 1);
    }
    list<int> arr[101]; 
    bool FindInList(list<int>& subList, int toFind) {
        for (int n : subList) {
            if (n == toFind) {
                return true;
            }
        }
        return false;
    }

    list<int>::iterator GetIter(list<int>& subList, int toFind) {
        auto iter = subList.begin();
        auto end = subList.end();
        for (; iter != end; ++iter) {
            if (*iter == toFind) {
                return iter;
            }
        }
        return end;
    }
    
public:
    unorderedMap(){}

    void insert(int val) {
        if (has(val)) {
            return;
        }
        int index = KeyToIndex(val);
        arr[index].push_back(val);
        ++countElements;
    }
    

    bool has(int val) {
        return FindInList(arr[KeyToIndex(val)], val);
    }

    void rem(int val) {
        int index = KeyToIndex(val);
        auto iter = GetIter(arr[index], val);
        if (iter == arr[index].end()) {
            return;
        }
        arr[index].erase(iter);
        --countElements;
    }

    int size() {
        return countElements;
    }
};

#include <iostream>


int main() {
    unorderedMap map;
    cout << "Size: " << map.size() << endl;
    map.insert(1);
    cout << "Size: " << map.size() << endl;
    cout << boolalpha << map.has(1) << endl;
    map.insert(1);
    cout << "Size: " << map.size() << endl;
    cout << boolalpha << map.has(1) << endl;

    return 0;
}

