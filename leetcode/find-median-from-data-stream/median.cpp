#pragma GCC optimize (2)

#include <cstdlib>

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class MedianFinder
{
private:
    typedef vector<int> TIntVector;
    TIntVector _minHeap;
    TIntVector _maxHeap;
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

    template<typename T>
    void HeapUp(TIntVector& vct, size_t index)
    {
        while (0 != index)
        {
            int parent = (index - 1) >> 1;
            if (T::F(vct[index], vct[parent]))
            {
                swap(vct[index], vct[parent]);
                index = parent;
            }
            else
            {
                return;
            }
        }
    }

    template<typename T>
    void HeapDown(TIntVector& vct, size_t index)
    {
        while (true)
        {
            int minIndex = index;
            int childIndex = (index << 1) + 1;
            if (childIndex < vct.size())
            {
                if (T::F(vct[childIndex], vct[minIndex]))
                {
                    minIndex = childIndex;
                }
                ++childIndex;
                if (childIndex < vct.size())
                {
                    if (T::F(vct[childIndex], vct[minIndex]))
                    {
                        minIndex = childIndex;
                    }
                }
                if (minIndex != index)
                {
                    swap(vct[index], vct[minIndex]);
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

public:
    MedianFinder()
        : _size(0)
    {
        _minHeap.reserve(1 << 17);
        _maxHeap.reserve(1 << 17);
    }

    // Adds a number into the data structure.
    void addNum(int num)
    {
        if (0 == (_size & 1))
        {
            size_t size = _minHeap.size();
            _minHeap.push_back(num);
            HeapUp<Greater>(_minHeap, size);
        }
        else
        {
            size_t size = _maxHeap.size();
            _maxHeap.push_back(num);
            HeapUp<Less>(_maxHeap, size);
        }
        ++_size;
        if ((_size > 2) && (_minHeap[0] > _maxHeap[0]))
        {
            swap(_minHeap[0], _maxHeap[0]);
            HeapDown<Greater>(_minHeap, 0);
            HeapDown<Less>(_maxHeap, 0);
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

    double findMedianSlow() const
    {
        TIntVector copy = _minHeap;
        copy.insert(copy.end(), _maxHeap.begin(), _maxHeap.end());
        sort(copy.begin(), copy.end());
        if (copy.size() & 1)
        {
            return copy[copy.size()/2];
        }
        else
        {
            return static_cast<double>(copy[copy.size()/2-1] + copy[copy.size()/2])/2;
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
        cout << mf.findMedian() << endl;
        cout << mf.findMedianSlow() << endl;
    }

    {
        MedianFinder mf;
        static const size_t N = 1000;
        for (size_t i = 0; i < N; ++i)
        {
            mf.addNum(rand() % 100000);
        }
        cout << mf.findMedian() << endl;
        cout << mf.findMedianSlow() << endl;
    }
    {
        MedianFinder mf;
        static const size_t N = 1001;
        for (size_t i = 0; i < N; ++i)
        {
            mf.addNum(rand() % 10);
        }
        cout << mf.findMedian() << endl;
        cout << mf.findMedianSlow() << endl;
    }

    return 0;
}
