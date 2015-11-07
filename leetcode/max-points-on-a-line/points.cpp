#include <vector>
#include <iostream>

using namespace std;

struct Point
{
    int x;
    int y;

    Point()
        : x(0)
        , y(0)
    {
    }

    Point(int a, int b)
        : x(a)
        , y(b)
    {
    }
};

class Solution
{
public:
    int maxPoints(vector<Point>& points)
    {
        if (points.size() < 2)
        {
            return points.size();
        }
        int max = 0;
        for (size_t i = 0; i < points.size(); ++i)
        {
            const Point& p1 = points[i];
            for (size_t j = i + 1; j < points.size(); ++j)
            {
                const Point& p2 = points[j];
                long long int a = p2.y - p1.y;
                long long int b = p1.x - p2.x;
                if (a || b)
                {
                    long long int c = -a*p1.x - b*p1.y;
                    int current = 0;
                    for (const auto& p: points)
                    {
                        long long int lx = p.x;
                        long long int ly = p.y;
                        if (0 == a*lx + b*ly + c)
                        {
                            ++current;
                        }
                    }
                    if (current > max)
                    {
                        max = current;
                        // cout << current << " " << max << " " << a << " " << b << " " << c << endl;
                    }
                }
                else
                {
                    int current = 0;
                    for (const auto& p: points)
                    {
                        if (p.x == p1.x && p.y == p2.y)
                        {
                            ++current;
                        }
                    }
                    if (current > max)
                    {
                        max = current;
                        // cout << current << " " << max << " " << a << " " << b << " " << c << endl;
                    }
                }
            }
        }
        return max;
    }
};

int main()
{
    vector<Point> data = {{84, 250}, {0, 0}, {1, 0}, {0, -70}, {0, -70}, {1, -1}, {21, 10}, {42, 90}, {-42, -230}};
    Solution s;
    cout << s.maxPoints(data) << endl;
    return 0;
}
