#include <iostream>
#include <thread>

using namespace std;

static const int N = 100000000;

int value;
int lock;

void LockedInc()
{
    for (int i = 0; i < N; ++i)
    {
        while (1 == lock);
        lock = 1;
        ++value;
        lock = 0;
    }
}

void NonLockedInc()
{
    for (int i = 0; i < N; ++i)
    {
        ++value;
    }
}

int main()
{
    {
        thread t1(NonLockedInc);
        thread t2(NonLockedInc);

        t1.join();
        t2.join();
        
        cout << "not locked: " << value << endl;
    }

    value = 0;
    {
        lock = 1;

        thread t1(LockedInc);
        thread t2(LockedInc);

        lock = 0;
        t1.join();
        t2.join();
        
        cout << "locked: " << value << endl;
    }

    return 0;
}
