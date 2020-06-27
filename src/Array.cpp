// Implementation of stack and queue using an array with resizing
#include <algorithm>
#include <iostream>
#include <memory>

using namespace std;

struct Stack
{
    int size = 0;
    int capacity = 1;
    int *start = {new int[1]{}};

    int *resize(int *oldStart, int newSize)
    {
        // Creates a new array and copies the old values into it
        int *newStart = {new int[newSize]{}};
        for (auto i = 0; i < size; i++)
        {
            newStart[i] = start[i];
        }
        delete[] oldStart;
        return newStart;
    }

    void push(int val)
    {
        cout << "Adding value: " << val << endl;
        // If the array is full, create a new array, fill it with the old values and assign start to it
        if (size == capacity)
        {
            cout << "Doubling size of container to " << (capacity << 1) << endl;
            capacity = capacity << 1;
            start = resize(start, capacity);
        }

        // Put the value in and increment size
        start[size] = val;
        size++;
    }

    int pop()
    {
        // Get the values form the end and decrement size
        int val = start[size - 1];
        size--;

        // If the stack is less than a quarter full, make it smaller by half
        if (capacity >= 4 && size <= capacity >> 2)
        {
            cout << "Halving size of container to " << (capacity >> 1) << endl;
            capacity = capacity >> 1;
            start = resize(start, capacity);
        }

        return val;
    }
};

int main()
{
    Stack s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    s1.push(5);
    s1.push(6);
    s1.push(7);
    s1.push(8);

    cout << s1.pop() << endl;
    cout << s1.pop() << endl;
    cout << s1.pop() << endl;
    cout << s1.pop() << endl;
    cout << s1.pop() << endl;
    cout << s1.pop() << endl;
    cout << s1.pop() << endl;
    cout << s1.pop() << endl;
}