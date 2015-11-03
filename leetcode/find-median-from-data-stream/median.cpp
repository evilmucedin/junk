#include <cstdlib>

#include <algorithm>
#include <limits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class MedianFinder
{
private:
    typedef vector<int> TIntVector;
    priority_queue<int, TIntVector, less<int>> _minHeap;
    priority_queue<int, TIntVector, greater<int>> _maxHeap;

    size_t getSize() const
    {
        return _minHeap.size() + _maxHeap.size();
    }

public:
    // Adds a number into the data structure.
    void addNum(int num)
    {
        if (0 == (getSize() & 1))
        {
            _minHeap.emplace(num);
        }
        else
        {
            _maxHeap.emplace(num);
        }
        if (!_minHeap.empty() && !_maxHeap.empty() && _minHeap.top() > _maxHeap.top())
        {
            int maxTop = _maxHeap.top();
            _maxHeap.pop();
            int minTop = _minHeap.top();
            _minHeap.pop();
            _maxHeap.emplace(minTop);
            _minHeap.emplace(maxTop);
        }
        // cerr << _minHeap.size() << "\t" << ((_minHeap.empty()) ? 0 : _minHeap.top()) << "\t" << _maxHeap.size() << "\t" << ((_maxHeap.empty()) ? 0 : _maxHeap.top()) << endl;
    }

    // Returns the median of current data stream
    double findMedian() const
    {
        if (getSize() & 1)
        {
            return _minHeap.top();
        }
        else
        {
            return (static_cast<double>(_minHeap.top()) + static_cast<double>(_maxHeap.top()))/2.0;
        }
    }

    double findMedianSlow() const
    {
        TIntVector copy;
        auto copyMin = _minHeap;
        while (!copyMin.empty())
        {
            copy.push_back(copyMin.top());
            copyMin.pop();
        }
        auto copyMax = _maxHeap;
        while (!copyMax.empty())
        {
            copy.push_back(copyMax.top());
            copyMax.pop();
        }
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
            mf.addNum(rand());
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
