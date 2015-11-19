#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution
{
public:
    inline static bool IsDigit(char ch)
    {
        return (ch >= '0') && (ch <= '9');
    }

    bool isNumber(const string& s)
    {
        int state = 0;
        static const int T = 9999;
        for (char ch: s)
        {
            switch (state)
            {
            case 0:
                if ('-' == ch || '+' == ch)
                {
                    state = 8;
                }
                else if (IsDigit(ch))
                {
                    state = 1;
                }
                else if (' ' == ch)
                {
                    
                }
                else if ('.' == ch)
                {
                    state = 7;
                }
                else
                {
                    state = T;
                }
                break;
            case 8:
                if (IsDigit(ch))
                {
                    state = 1;
                }
                else if ('.' == ch)
                {
                    state = 7;
                }
                else
                {
                    state = T;
                }
                break;
            case 1:
                if (IsDigit(ch))
                {

                }
                else if ('.' == ch)
                {
                    state = 6;
                }
                else if ('e' == ch || 'E' == ch)
                {
                    state = 3;
                }
                else if (' ' == ch)
                {
                    state = 5;
                }
                else
                {
                    state = T;
                }
                break;
            case 6:
                if (IsDigit(ch))
                {
                    state = 2;
                }
                else if ('e' == ch || 'E' == ch)
                {
                    state = 3;
                }
                else if (' ' == ch)
                {
                    state = 5;
                }
                else
                {
                    state = T;
                }
                break;
            case 7:
                if (IsDigit(ch))
                {
                    state = 2;
                }
                else
                {
                    state = T;
                }
                break;
            case 2:
                if (IsDigit(ch))
                {

                }
                else if ('e' == ch || 'E' == ch)
                {
                    state = 3;
                }
                else if (' ' == ch)
                {
                    state = 5;
                }
                else
                {
                    state = T;
                }
                break;
            case 3:
                if (IsDigit(ch))
                {
                    state = 4;
                }
                else if ('+' == ch || '-' == ch)
                {

                }
                else
                {
                    state = T;
                }
                break;
            case 4:
                if (IsDigit(ch))
                {
                }
                else if (' ' == ch)
                {
                    state = 5;
                }
                else
                {
                    state = T;
                }
                break;
            case 5:
                if (' ' == ch)
                {

                }
                else
                {
                    state = T;
                }
                break;
            case T:
                return false;
            }
        }

        return (1 == state) || (2 == state) || (4 == state) || (5 == state) || (6 == state);
    }
};

struct TestItem
{
    string _s;
    bool _isNumber;
};

int main()
{
    vector<TestItem> tests = { { "0", true }, { " 0.1 ", true }, { "abc", false }, { "1 a", false }, { "2e10", true }, { "1 ", true }, { ".1", true }, { ".", false }, { "3.", true }, { "3. ", true }, { ". ", false }, { "0e", false }, { "+.8", true }, { "-0.8", true }, { "-.8", true }, { "1e-10", true }, { "1e+10", true }, { " -.", false }, { "46.e3", true }, { " -1.e49046 ", true } };

    Solution s;
    for (auto test : tests)
    {
        bool isNumber = s.isNumber(test._s);
        if (isNumber != test._isNumber)
        {
            cout << "Failed: '" << test._s << "' returned " << isNumber << " instead of " << test._isNumber << endl;
        }
    }

    return 0;
}