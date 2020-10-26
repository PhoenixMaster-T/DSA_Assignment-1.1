#include <iostream>
#include <sstream>
#include <string.h>
#include <assert.h>
#include <stdexcept>
using namespace std;
class IntDLinkedList
{
public:
    class Node; // Forward declaration

private:
    Node *head;
    Node *tail;
    int count;

public:
    IntDLinkedList() : head(NULL), tail(NULL), count(0){};
    virtual void add(int element)
    {
        Node *newNode = new Node(element);
        if (this->count == 0)
        {
            this->head = this->tail = newNode;
        }
        else
        {
            this->tail->next = newNode;
            newNode->previous = this->tail;
            this->tail = newNode;
        }
        this->count++;
    }

    virtual void add(int index, int element)
    {
        if (index == 0)
        {
            Node *newNode = new Node(element);
            if (count == 0)
            {
                this->tail = newNode;
                this->head = newNode;
            }
            else
            {
                head->previous = newNode;
                newNode->next = head;
                head = newNode;
            }
            count++;
        }
        else if (index == count)
            add(element);
        else
        {
            Node *newNode = new Node(element);
            Node *temp = head;
            for (int i = 1; i < index; i++)
                temp = temp->next;
            newNode->next = temp->next;
            newNode->previous = temp;
            temp->next->previous = newNode;
            temp->next = newNode;
            count++;
        }
    }

    virtual int removeAt(int index)
    {
        int res = 0;
        if(count == 1)
        {
            res = head->data;
            delete head;
            head = NULL;
            tail = NULL;
            count--;
            return res;
        }
        else if(count == 0)
            throw std::out_of_range("");
        else if (index == 0)
        {
            // remove first
            res = head->data;
            head = head->next;
            delete head->previous;
            head->previous = NULL;
            count--;
        }
        else if (index == count - 1)
        {
            // remove last
            res = tail->data;
            tail = tail->previous;
            delete tail->next;
            tail->next = NULL;
            count--;
        }
        else
        {
            Node *temp = head;
            for (int i = 1; i < index; i++)
                temp = temp->next;
            res = temp->next->data;
            temp->next = temp->next->next;
            delete temp->next->previous;
            temp->next->previous = temp;

            count--;
        }
        return res;
    }

    virtual bool removeItem(int item)
    {

        return false;
    }

    virtual bool empty()
    {

        return false;
    }

    virtual int size()
    {
        return count;
    }

    virtual void clear()
    {
    }

    virtual int get(int index)
    {
        if (index < (count + 1) / 2) //duyet tu dau
        {
            Node *temp = head;
            while (index)
            {
                temp = temp->next;
                index--;
            }
            return temp->data;
        }
        else // duyet tu cuoi
        {
            Node *temp = tail;
            index = count - index - 1;
            while (index)
            {
                temp = temp->previous;
                index--;
            }
            return temp->data;
        }
    }

    virtual void set(int index, int element)
    {
    }

    virtual int indexOf(int item)
    {
        return -1;
    }

    virtual bool contains(int item)
    {
        return false;
    }

    virtual string toString()
    {
        stringstream ss;
        ss << "[";
        Node *ptr = head;
        while (ptr != tail)
        {
            ss << ptr->data << ",";
            ptr = ptr->next;
        }

        if (count > 0)
            ss << ptr->data << "]";
        else
            ss << "]";
        return ss.str();
    }

public:
    class Node
    {
    public:
        int data;
        Node *next;
        Node *previous;

    public:
        Node() : next(NULL), previous(NULL){};
        Node(int data) : data(data), next(NULL), previous(NULL){};
    };
};
int main()
{

    // Test: Removing items with removeAt
    IntDLinkedList list;
    int size = 10;
    for (int index = 0; index < size; index++)
    {
        list.add(index);
    }

    int count = size;
    for (int idx = 0; idx < size; idx++)
    {
        assert(list.removeAt(0) == idx);
        count--;
        assert(list.size() == count);
    }

    try
    {
        list.removeAt(0);
    }
    catch (std::out_of_range e)
    {
        cout << "Passed";
    }
    system("pause");
}
/*        res = temp->data;
        temp->next = temp->next->next;
        delete temp->next->prev;
        temp->next->prev = temp->next;
        count--;*/