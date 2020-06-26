#include <functional>
#include <iostream>
#include <memory>
#include <optional>
#include <string>

using namespace std;

struct DebugStruct
{
    DebugStruct() { cout << "Creating new struct..." << endl; }
    ~DebugStruct() { cout << "Deleting struct..." << endl; }
};

template <typename T>
struct Node : DebugStruct
{
    T value;
    shared_ptr<Node<T>> ptr;
    Node(T value, shared_ptr<Node<T>> ptr) : value(value), ptr(move(ptr))
    {
        cout << "Creating new node with value: " << value << endl;
    }
};

template <typename T>
struct Stack
{
    shared_ptr<Node<T>> end = nullptr;

    void push(T value)
    {
        // Create a new node which points to the previous end node
        // and assign it to the end value
        end = make_shared<Node<T>>(value, end);
    }
    optional<T> pop()
    {
        if (end != nullptr)
        {
            T val = end->value;
            // Put the previous pointer from the end into end
            end = end->ptr;
            return val;
        }
        else
        {
            // Return nullopt
            return {};
        }
    }

    int count()
    {
        int counter = 0;
        // Get the pointer at the end
        auto countPtr = end;
        // Keep moving forwards until it reaches the start
        while (countPtr != nullptr)
        {
            counter++;
            countPtr = countPtr->ptr;
        }
        return counter;
    }

    template <typename U>
    Stack<U> map(function<U(T)> f)
    {
        // This naive method leads to the output stack being the reverse of the input stack
        Stack<U> result;
        auto mapPtr = end;
        while (mapPtr != nullptr)
        {
            result.push(f(mapPtr->value));
            mapPtr = mapPtr->ptr;
        }
        return result;
    }
};

int main()
{
    Stack<string> s1;
    s1.push("One");
    s1.push("Two");
    s1.push("Three");

    cout << "Stack has size of: " << s1.count() << endl;

    auto s2 = s1.map<int>([](string x) { return x.length(); });

    cout << s1.pop().value_or("(none)") << endl;
    cout << s2.pop().value_or(0) << endl;
    cout << s1.pop().value_or("(none)") << endl;
    cout << s2.pop().value_or(0) << endl;
    cout << s1.pop().value_or("(none)") << endl;
    cout << s2.pop().value_or(0) << endl;
    cout << s1.pop().value_or("(none)") << endl;
    cout << s2.pop().value_or(0) << endl;
}