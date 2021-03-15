#include <vector>
#include <iostream>
class CircularArrayQueue {

public:
	int* array;
    size_t length;
public:    
    size_t front;
    size_t back;
    size_t capacity;

	CircularArrayQueue();
    ~CircularArrayQueue();
	bool isEmpty() const;
	void enqueue(int x);
	void dequeue();
	int peekFront() const;
    bool full() const;
    void PrintAll() const;
    void PPModulus(size_t& a, const size_t& m, const size_t& amount) const;
    bool GreaterModulus(const size_t& lhs, const size_t& rhs) const;
};

CircularArrayQueue::~CircularArrayQueue() {
    delete[] array;
}

CircularArrayQueue::CircularArrayQueue() {
    array = new int[0];
    length = 0;
    capacity = 0;
    front = 0;
    back = 0;
}

bool CircularArrayQueue::isEmpty() const {
    if (capacity == 0) {
        return true;
    }
    size_t copyBack = back;
    PPModulus(copyBack, capacity, 1);
    return front == copyBack;
}

void CircularArrayQueue::enqueue(int x) { 
    if (capacity == 0) {
        int* newArray = new int[5];
        delete[] array;
        array = newArray;
        array[front] = x;
        capacity = 5;
        ++length;
        return;
    } else if (full()) {
        int* newArray = new int[2*capacity];
        for (size_t i = front; GreaterModulus(back,i); PPModulus(i,capacity,1)) {
            newArray[i] = array[i];
        }
        newArray[back] = array[back];
        delete[] array;
        array = newArray;
        capacity = 2*capacity;
    }
    PPModulus(back, capacity, 1);
    array[back] = x;
    ++length;
}

void CircularArrayQueue::dequeue() {
    PPModulus(front,capacity,1);
    --length;
}

int CircularArrayQueue::peekFront() const {
    return array[front];
}

bool CircularArrayQueue::full() const {
    return length == capacity;
}

void CircularArrayQueue::PrintAll() const {
    std::cout << "Printing..." << std::endl;
    for (size_t i = front; !GreaterModulus(i,back); ++i) {
        std::cout << array[i] << ", ";
    }
    std::cout << std::endl;
}

void CircularArrayQueue::PPModulus(size_t& a, const size_t& m, const size_t& amount) const {
    a = (a + amount) % m;
}

bool CircularArrayQueue::GreaterModulus(const size_t& lhs, const size_t& rhs) const {
    if (back >= front) {
        return lhs > rhs;
    } else {
        size_t lhsCopy = lhs;
        size_t rhsCopy = rhs;
        PPModulus(lhsCopy, capacity, capacity - front);
        PPModulus(rhsCopy, capacity, capacity - front);
        return lhsCopy > rhsCopy;
    }
}