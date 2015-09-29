#include <iostream>
#include <thread>
#include <atomic>

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

//////////////////////////////////////////////////////////////////////////////////////

void LockedSyncedInc1()
{
    for (int i = 0; i < N; ++i)
    {
        lockWanna = 1;
        __sync_synchronize();
        while (lockGotcha)
        {
            __sync_synchronize();
            if (0 != turn)
            {
                lockWanna = 0;
                __sync_synchronize();
                while (0 != turn);
                lockWanna = 1;
            }
        }

        ++value;
        
        turn = 1;
        lockWanna = 0;
    }
}

void LockedSyncedInc2()
{
    for (int i = 0; i < N; ++i)
    {
        lockGotcha = 1;
        __sync_synchronize();
        while (lockWanna)
        {
            __sync_synchronize();
            if (1 != turn)
            {
                lockGotcha = 0;
                __sync_synchronize();
                while (1 != turn);
                lockGotcha = 1;
            }
        }

        ++value;
        
        turn = 0;
        lockGotcha = 0;
    }
}

//////////////////////////////////////////////////////////////////////////////////////

void NonLockedInc()
{
    for (int i = 0; i < N; ++i)
    {
        ++value;
    }
}

//////////////////////////////////////////////////////////////////////////////////////

atomic_flag aLock(ATOMIC_FLAG_INIT);

void LockedAtomicInc()
{
    for (int i = 0; i < N; ++i)
    {
        while (aLock.test_and_set(std::memory_order_acquire))
        {
        }
        ++value;
        aLock.clear(std::memory_order_release);
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

    value = 0;
    {
        lockWanna = 0;
        lockGotcha = 0;
        turn = 0;

        thread t1(LockedSyncedInc1);
        thread t2(LockedSyncedInc2);

        t1.join();
        t2.join();
        
        cout << "locked synced: " << value << endl;
    }

    value = 0;
    {
        thread t1(LockedAtomicInc);
        thread t2(LockedAtomicInc);

        t1.join();
        t2.join();
        
        cout << "locked atomic: " << value << endl;
    }

    return 0;
}
