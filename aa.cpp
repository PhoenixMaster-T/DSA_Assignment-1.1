#include <iostream>
using namespace std;

int main()
{
    int *a = new int[3];
    a = new int[6];
    int index = 7;
    int fragmentMaxSize = 3;
    int indexBegin = (index % fragmentMaxSize == 0)? index / fragmentMaxSize: (index / fragmentMaxSize)+1;
    cout <<indexBegin <<endl;
    system("pause");
    return 0;
}