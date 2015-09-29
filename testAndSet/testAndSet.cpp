#include <iostream>
#include <thread>

using namespace std;

static const int N = 100000000;

int value;

int lockWanna;
int lockGotcha;
int turn;

void LockedInc1()
{
    for (int i = 0; i < N; ++i)
    {
        lockWanna = 1;
        while (lockGotcha)
        {
            if (0 != turn)
            {
                lockWanna = 0;
                while (0 != turn);
                lockWanna = 1;
            }
        }

        ++value;
        
        turn = 1;
        lockWanna = 0;
    }
}

void LockedInc2()
{
    for (int i = 0; i < N; ++i)
    {
        lockGotcha = 1;
        while (lockWanna)
        {
            if (1 != turn)
            {
                lockGotcha = 0;
                while (1 != turn);
                lockGotcha = 1;
            }
        }

        ++value;
        
        turn = 0;
        lockGotcha = 0;
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
        lockWanna = 0;
        lockGotcha = 0;
        turn = 0;

        thread t1(LockedInc1);
        thread t2(LockedInc2);

        t1.join();
        t2.join();
        
        cout << "locked: " << value << endl;
    }

    return 0;
}
