#include <iostream>

using namespace std;

double e(int x, int n)
{
    static double p = 1, f = 1;
    double r;

    if (n==0)
        return 1;

    r = e(x, n - 1);
    p = p * x;
    f = f * n;
    return r + p / f;
} // time complexity O(n**2) - space complexity O(n)

double eHornersRule(double x, double n)
{
    double s = 1;

    for (n = n; n > 0; n--)
        s = 1 + x/n * s;

    return s;
} // time complexity O(n) - space complexity O(1)

double recursiveEHornersRule(double x, double n)
{
    static double s = 1;
    if (n==0)
        return s;

    s = 1 + x / n * s;

    return recursiveEHornersRule(x, n-1);
} // time complexity O(n) - space complexity O(n)

int main()
{
    cout << e(1, 10) << endl;
    cout << eHornersRule(1, 10) << endl;
    cout << recursiveEHornersRule(1, 10) << endl;
    return 0;
}