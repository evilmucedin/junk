#ifndef _MSC_VER 
#	pragma GCC target("sse4.2") 
#   pragma GCC optimize("O3") 
#endif 

#include <smmintrin.h>

#include <cstdio>
#include <cstdlib>

#include <vector>
#include <string>
#include <iostream>
#include <chrono>

using namespace std;

class Solution
{
public:
    typedef vector<int> TIntVector;

    static void String2IntVector(const string& s, TIntVector* result)
    {
        result->resize(s.length());
        for (size_t i = 0; i < s.length(); ++i)
        {
            (*result)[i] = s[s.length() - i - 1] - '0';
        }
    }

    string multiplySlow(string num1, string num2)
    {
        TIntVector a;
        TIntVector b;
        String2IntVector(num1, &a);
        String2IntVector(num2, &b);

        TIntVector result(a.size() + b.size() + 1);
        for (size_t i = 0; i < a.size(); ++i)
        {
            if (a[i])
            {
                for (size_t j = 0; j < b.size(); ++j)
                {
                    result[i + j] += a[i]*b[j];
                }
            }
        }

        int index = -1;
        for (size_t i = 0; i + 1 < result.size(); ++i)
        {
            result[i + 1] += result[i]/10;
            result[i] %= 10;
            if (result[i])
            {
                index = i;
            }
        }

        if (-1 == index)
        {
            return "0";
        }

        string sResult;
        sResult.resize(index + 1);
        for (int i = 0; i <= index; ++i)
        {
            sResult[i] = result[index - i] + '0';
        }

        return sResult;
    }

    typedef vector<long long int> TLIntVector;

    static void String2IntVectorGrouped(const string& s, TLIntVector* result)
    {
        result->clear();
        result->reserve(s.length()/7 + 1);
        auto it = s.rbegin();
        while (it != s.rend())
        {
        	int num = *it - '0';
        	++it;
        	if (it != s.rend())
        	{
        		num += 10*(*it - '0');
        		++it;
        	}
        	if (it != s.rend())
        	{
        		num += 100*(*it - '0');
        		++it;
        	}
        	if (it != s.rend())
        	{
        		num += 1000*(*it - '0');
        		++it;
        	}
        	if (it != s.rend())
        	{
        		num += 10000*(*it - '0');
        		++it;
        	}
        	if (it != s.rend())
        	{
        		num += 100000*(*it - '0');
        		++it;
        	}
        	if (it != s.rend())
        	{
        		num += 1000000*(*it - '0');
        		++it;
        	}
        	if (it != s.rend())
        	{
        		num += 10000000*(*it - '0');
        		++it;
        	}
        	result->push_back(num);
        }
    }

    TLIntVector _a;
    TLIntVector _b;
    TLIntVector _result1000;
    TIntVector _result;
    string _sResult;

    const string& multiply(const string& num1, const string& num2)
    {
        String2IntVectorGrouped(num1, &_a);
        String2IntVectorGrouped(num2, &_b);

        _result1000.resize(_a.size() + _b.size() + 1);
        fill(_result1000.begin(), _result1000.end(), 0);
        for (size_t i = 0; i < _a.size(); ++i)
        {
            for (size_t j = 0; j < _b.size(); ++j)
            {
                _result1000[i + j] += _a[i]*_b[j];
            }
        }

        for (size_t i = 0; i + 1 < _result1000.size(); ++i)
        {
        	static const long long int MUL = 100000000;
            _result1000[i + 1] += _result1000[i]/MUL;
            _result1000[i] %= MUL;
        }

        static const size_t K = 8;
        _result.resize(_result1000.size()*K);
        for (size_t i = 0; i < _result1000.size(); ++i)
        {
        	int num = _result1000[i];
        	size_t index = K*i;
        	for (size_t j = 0; j < K; ++j)
        	{
        		_result[index++] = num % 10;
        		num /= 10;
        	}
        }

        int index = -1;
        for (int i = _result.size() - 1; i >= 0; --i)
        {
            if (_result[i])
            {
                index = i;
                break;
            }
        }

        static const string ZERO = "0";
        if (-1 == index)
        {
            return ZERO;
        }

        _sResult.resize(index + 1);
        for (int i = 0; i <= index; ++i)
        {
            _sResult[i] = _result[index - i] + '0';
        }

        return _sResult;
    }

    struct SIMDNumber
    {
    	__m128i* _data;
    	size_t _length;

    	void Construct(size_t length)
    	{
    		_length = length;
    		_data = (__m128i*)_mm_malloc(sizeof(__m128i)*_length, 32);
    	}

    	void Zero()
    	{
    		__m128i zero = _mm_set_epi32(0, 0, 0, 0);
    		for (size_t i = 0; i < _length; ++i)
    		{
    			_data[i] = zero;
    		}
    	}

    	void ToVector(TIntVector* result) const
    	{
    		result->resize(4*_length);
    		for (size_t i = 0; i < _length; ++i)
    		{
    			const int* pData = (const int*)(_data + i);
    			(*result)[4*i + 0] = pData[0];
    			(*result)[4*i + 1] = pData[1];
    			(*result)[4*i + 2] = pData[2];
     			(*result)[4*i + 3] = pData[3];
   			}
    	}
    };

    static void String2IntVectorSIMD(const string& s, SIMDNumber* result)
    {
    	size_t length = (s.length()/4) + 1;
    	result->Construct(length);
    	for (size_t i = 0; i < length; ++i)
    	{
    		int i0 = (4*i < s.length()) ? (s[4*i] - '0') : 0;
    		int i1 = (4*i + 1 < s.length()) ? (s[4*i + 1] - '0') : 0;
    		int i2 = (4*i + 2 < s.length()) ? (s[4*i + 2] - '0') : 0;
    		int i3 = (4*i + 3 < s.length()) ? (s[4*i + 3] - '0') : 0;
    		result->_data[i] = _mm_set_epi32(i0, i1, i2, i3);
    	}
    }

    static void String2IntVectorSIMDDup(const string& s, SIMDNumber* result)
    {
    	size_t length = s.length();
    	result->Construct(length);
    	for (size_t i = 0; i < length; ++i)
    	{
    		int i0 = s[4*i] - '0';
    		result->_data[i] = _mm_set_epi32(i0, i0, i0, i0);
    	}
    }

    string multiplyFast(const string& num1, const string& num2)
    {
#if 0
        SIMDNumber a;
        SIMDNumber b;
        String2IntVectorSIMDDup(num1, &a);
        String2IntVectorSIMD(num2, &b);

        SIMDNumber result;
        result.Construct(a._length/4 + b._length + 1);
        result.Zero();
        for (size_t i = 0; i < a._length; ++i)
        {
            for (size_t j = 0; j < b._length; ++j)
            {
            	const __m128i product = _mm_mul_epi32(a._data[i], b._data[j]);
            	result._data[i/4 + j] = _mm_add_epi32(result._data[i/4 + j], product);
            }
        }

        TIntVector resultPlain;
        result.ToVector(&resultPlain);

        int index = -1;
        for (size_t i = 0; i + 1 < resultPlain.size(); ++i)
        {
            resultPlain[i + 1] += resultPlain[i]/10;
            resultPlain[i] %= 10;
            if (resultPlain[i])
            {
                index = i;
            }
        }

        if (-1 == index)
        {
            return "0";
        }

        string sResult;
        sResult.resize(index + 1);
        for (int i = 0; i <= index; ++i)
        {
            sResult[i] = resultPlain[index - i] + '0';
        }

        return sResult;
#endif
    }

	static void GenRandomNumber(size_t length, string* result)
	{
		result->resize(length);
		for (size_t i = 0; i < length; ++i)
		{
			(*result)[i] = static_cast<char>((rand() % 10) + '0');
		}
	}
};

static void Test(int length)
{
	string a;
	string b;
	Solution::GenRandomNumber(length, &a);
	Solution::GenRandomNumber(length, &b);

	Solution s;
	{
		cout << "slow" << endl;
		auto before = chrono::high_resolution_clock::now();
		string ab = s.multiplySlow(a, b);
		auto after = chrono::high_resolution_clock::now();
		if (ab.length() > 80) 
		{
			cout << "Length: " << ab.length() << " " << hash<string>()(ab) << endl;			
		}
		else
		{
			cout << ab << endl;
		}
		auto diff = chrono::duration_cast<chrono::microseconds>(after - before);
		cout << "Duration: " << diff.count() << endl;
	}

	{
		cout << "normal" << endl;
		auto before = chrono::high_resolution_clock::now();
		string ab = s.multiply(a, b);
		auto after = chrono::high_resolution_clock::now();
		if (ab.length() > 80) 
		{
			cout << "Length: " << ab.length() << " " << hash<string>()(ab) << endl;			
		}
		else
		{
			cout << ab << endl;
		}
		auto diff = chrono::duration_cast<chrono::microseconds>(after - before);
		cout << "Duration: " << diff.count() << endl;
	}

	{
		cout << "fast" << endl;
		auto before = chrono::high_resolution_clock::now();
		string ab = s.multiplyFast(a, b);
		auto after = chrono::high_resolution_clock::now();
		if (ab.length() > 80) 
		{
			cout << "Length: " << ab.length() << " " << hash<string>()(ab) << endl;			
		}
		else
		{
			cout << ab << endl;
		}
		auto diff = chrono::duration_cast<chrono::microseconds>(after - before);
		cout << "Duration: " << diff.count() << endl;
	}
}

int main()
{
	Test(10);
	// Test(10000);
	return 0;
}