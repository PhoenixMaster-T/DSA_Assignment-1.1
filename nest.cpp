#include <iostream>
using namespace std;

class Outter
{
private:
    int data;
public:
    class Inner;
public:
    void PrintInner()
    {
        Inner* a = new Inner(4);
    }
public:
    class Inner
    {
        private:
        int dataInner;
        Inner(int _data)
        {
            dataInner = _data;
        }
        friend class Outter;
    };

};