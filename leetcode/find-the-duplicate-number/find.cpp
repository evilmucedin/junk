#include <cstdlib>
#include <cassert>

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int findDuplicate(vector<int>& nums)
    {
        static const int K = 32;
        
        if (nums.size() > K)
        {
            vector<size_t> indices(K);
            vector<int> numbers(K);
         
            for (size_t it = 0; it < nums.size(); ++it)
            {
                for (size_t i = 0; i < K; ++i)
                {
                    indices[i] = rand() % nums.size();
                }
                sort(indices.begin(), indices.end());
                vector<size_t>::const_iterator toEnd = unique(indices.begin(), indices.end());
                size_t index = 0;
                for (vector<size_t>::const_iterator it = indices.begin(); it != toEnd; ++it)
                {
                    numbers[index++] = nums[*it];   
                }
                sort(numbers.begin(), numbers.begin() + index);
                for (size_t i = 1; i < index; ++i)
                {
                    if (numbers[i - 1] == numbers[i])
                    {
                        return numbers[i];
                    }
                }
            }
        }
        else
        {
            vector<int> numbers = nums;
            sort(numbers.begin(), numbers.end());
            for (size_t i = 1; i < numbers.size(); ++i)
            {
                if (numbers[i - 1] == numbers[i])
                {
                    return numbers[i];
                }
            }
        }

        assert(false);
    }
};

int main()
{
    static const size_t N = 1000;
    vector<int> test(N + 1);
    for (size_t i = 0; i < N; ++i)
    {
        test[i] = i;
    }
    test[N] = 0;
    
    Solution s;
    cout << s.findDuplicate(test) << endl;

    return 0;    
}
