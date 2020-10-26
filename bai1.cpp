#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    // max k, voi dieu kien  k(k+1)(k+5) < 6(n+1);
    int n = 2017;
    int temp = 6 * (n + 1);
    int k = pow(temp, 1.0 / 3);
    while (true)
    {
        int s = k * (k + 1) * (k + 5);
        if (s <= temp)
            break;
        k--;
    } 
    cout << k <<endl;
    system("pause");
    return 0;
}