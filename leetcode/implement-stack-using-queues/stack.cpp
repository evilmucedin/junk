#include <queue>

using namespace std;

class Stack {
private:
    typedef queue<int> TIntQueue;

    TIntQueue _q1;
    TIntQueue _q2;

    void move1()
    {
        while (_q1.size() != 1)
        {
            _q2.push(_q1.front());
            _q1.pop();
        }
    }
    
    void move2()
    {
        while (_q2.size())
        {
            _q1.push(_q2.front());
            _q2.pop();
        }
    }

public:
    // Push element x onto stack.
    void push(int x)
    {
        _q1.push(x);
    }

    // Removes the element on top of the stack.
    void pop()
    {
        move1();
        _q1.clear();
        move2();
    }

    // Get the top element.
    int top()
    {
        move1();
        int res = _q1.front();
        _q1.pop();
        move2();
        _q1.push(res);
        return res;
    }

    // Return whether the stack is empty.
    bool empty()
    {
        return _q1.empty();
    }
};
