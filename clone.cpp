#include <stack>
#include <queue>
#include <string>
using namespace std;

string solve(string _str)
{
    stack<char> lastWord;
    queue<char> firstWord;
    int size = _str.length();
    for(char i : _str)
    {
        if(i == ' ')
            break;
        else
        {
            firstWord.push(i);
        }
            
    }
    for(int i = size -1; i >=0; --i)
        if(i == ' ')
            break;
        else 
            lastWord.push(_str.at(i));
    string res;
    while(!firstWord.empty())
    {
        res.push_back(firstWord.front());
        firstWord.pop();
    }
}
int main()
{
    string str ="bo an co";
    string result = solve(str);
    cout << result;
}