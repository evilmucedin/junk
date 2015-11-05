#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

typedef vector<string> TStringVector;
typedef unordered_map<string, vector<TStringVector>> TState;
typedef vector<TStringVector> TResult;
typedef unordered_set<string> TSet;

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string> &wordList) {
        TState current;
        TStringVector dummy;
        dummy.push_back(beginWord);
        current[beginWord].push_back(dummy);

        TSet used;
        used.insert(beginWord);
        while (current.end() == current.find(endWord) && !current.empty())
        {
            TState next;
            TSet nextUsed = used;
            for (const TState::value_type& s : current)
            {
                for (size_t i = 0; i < s.first.length(); ++i)
                {
                    for (char ch = 'a'; ch <= 'z'; ++ch)
                    {
                        string modified = s.first;
                        modified[i] = ch;
                        if (wordList.end() != wordList.find(modified))
                        {
                            if (used.end() == used.find(modified))
                            {
                                nextUsed.insert(modified);
                                for (const auto& path : s.second)
                                {
                                    TStringVector nextPath = path;
                                    nextPath.push_back(modified);
                                    next[modified].push_back(nextPath);
                                }
                            }
                        }
                    }
                }
            }
            current = next;
            used = nextUsed;
        }

        return current[endWord];
    }
};

int main()
{


    return 0;
}
