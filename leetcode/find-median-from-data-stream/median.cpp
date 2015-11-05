#pragma GCC optimize (3)

#include <cstdlib>
#include <cstdio>

using namespace std;

class MedianFinder
{
private:
    static const size_t MAXSIZE = 1 << 16;

    int* _minHeap;
    size_t _minHeapSize;

    int* _maxHeap;
    size_t _maxHeapSize;

    size_t _size;

    struct Greater
    {
        inline static bool F(int a, int b)
        {
            return a > b;
        }
    };

    struct Less
    {
        inline static bool F(int a, int b)
        {
            return a < b;
        }
    };

    void Swap(int& a, int& b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

    template<typename T>
    void HeapUp(int* vct, size_t index)
    {
        while (0 != index)
        {
            size_t parent = (index - 1) >> 1;
            if (T::F(vct[index], vct[parent]))
            {
                Swap(vct[index], vct[parent]);
                index = parent;
            }
            else
            {
                return;
            }
        }
    }

    template<typename T>
    void HeapDown(int* vct, size_t size, size_t index)
    {
        while (true)
        {
            size_t minIndex = index;
            size_t childIndex = (index << 1) + 1;
            if (childIndex < size)
            {
                if (T::F(vct[childIndex], vct[minIndex]))
                {
                    minIndex = childIndex;
                }
                ++childIndex;
                if (childIndex < size)
                {
                    if (T::F(vct[childIndex], vct[minIndex]))
                    {
                        minIndex = childIndex;
                    }
                }
                if (minIndex != index)
                {
                    Swap(vct[index], vct[minIndex]);
                    index = minIndex;
                }
                else
                {
                    return;
                }
            }
            else
            {
                return;
            }
        }
    }

    template<typename T>
    void Insert(int* v, size_t& size, int num)
    {
        // static const size_t LIMIT = 15000;
        v[size] = num;
        HeapUp<T>(v, size);
        ++size;
        /*
        if (size > LIMIT)
        {
            --size;
        }
        */
    }

public:
    MedianFinder()
        : _size(0)
        , _minHeap(new int[MAXSIZE])
        , _minHeapSize(0)
        , _maxHeap(new int[MAXSIZE])
        , _maxHeapSize(0)
    {
    }

    // Adds a number into the data structure.
    void addNum(int num)
    {
        if (0 == (_size & 1))
        {
            Insert<Greater>(_minHeap, _minHeapSize, num);
        }
        else
        {
            Insert<Less>(_maxHeap, _maxHeapSize, num);
        }
        ++_size;
        if ((_size > 2) && (_minHeap[0] > _maxHeap[0]))
        {
            Swap(_minHeap[0], _maxHeap[0]);
            HeapDown<Greater>(_minHeap, _minHeapSize, 0);
            HeapDown<Less>(_maxHeap, _maxHeapSize, 0);
        }
        // cerr << _minHeap.size() << "\t" << ((_minHeap.empty()) ? 0 : _minHeap.top()) << "\t" << _maxHeap.size() << "\t" << ((_maxHeap.empty()) ? 0 : _maxHeap.top()) << endl;
    }

    // Returns the median of current data stream
    double findMedian() const
    {
        if (_size & 1)
        {
            return _minHeap[0];
        }
        else
        {
            return (static_cast<double>(_minHeap[0] + _maxHeap[0]))/2.0;
        }
    }
};

int main()
{
    {
        MedianFinder mf;
        static const size_t N = 1000;
        for (size_t i = 0; i < N; ++i)
        {
            mf.addNum(rand() % 1000000000);
        }
        printf("%lf\n", mf.findMedian());
    }

    {
        MedianFinder mf;
        static const size_t N = 1000;
        for (size_t i = 0; i < N; ++i)
        {
            mf.addNum(rand() % 100000);
        }
        printf("%lf\n", mf.findMedian());
    }
    {
        MedianFinder mf;
        static const size_t N = 1001;
        for (size_t i = 0; i < N; ++i)
        {
            mf.addNum(rand() % 10);
        }
        printf("%lf\n", mf.findMedian());
    }

    return 0;
}
