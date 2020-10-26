#include <iostream>
#include <cassert>
#include <sstream>

using namespace std;

class IntSLinkedList
{
public:
    class Iterator; //forward declaration
    class Node;     //forward declaration
protected:
    Node *head;
    Node *tail;
    int count;

public:
    IntSLinkedList()
    {
        head = NULL;
        tail = NULL;
        count = 0;
    }
    //IntSLinkedList() : head(NULL), tail(NULL), count(0){};
    /*virtual ~IntSLinkedList()
    {
        delete this->head;
        delete this->tail;
    }*/
    virtual void add(int element)
    {
        Node *pNew = new Node(element);
        if (this->count == 0)
        {
            this->tail = this->head = pNew;
        }
        else
        {
            this->tail->next = pNew;
            this->tail = pNew;
        }
        this->count++;
    }

    virtual void add(int index, int element)
    {
        if (index < 0 || index > this->count)
            throw out_of_range("Index is out of range");
        else if (index == count)
        {
            this->add(element);
        }
        else if (index == 0)
        {
            Node *pNew = new Node(element);
            pNew->next = this->head;
            this->head = pNew;
            this->count++;
        }
        else
        {
            Node *pNew = new Node(element);
            Node *temp = head;
            int i = 0;
            while (i < index - 1)
            {
                temp = temp->next;
                i++;
            }
            pNew->next = temp->next;
            temp->next = pNew;
            this->count++;
        }
    }

    virtual int removeAt(int index)
    {
        Node *temp = this->head;
        if (index < 0 || index >= this->count)
            throw out_of_range("Index is out of range");
        else if (index == 0)
        {
            this->head = temp->next;
            temp->next = NULL;
            this->count--;
            return temp->data;
        }
        else
        {
            int i = 0;
            Node *pre = head;
            while (i < index - 1)
            {
                pre = pre->next;
                i++;
            }
            if (index == this->count - 1)
            {
                temp = pre->next;
                pre->next = NULL;
                this->tail = pre;
            }
            else
            {
                temp = pre->next;
                pre->next = temp->next;
                temp->next = NULL;
            }
            this->count--;
            return temp->data;
        }
        return 0;
    }

    virtual bool removeItem(int item)
    {
        Node *temp = this->head;
        float remove = 1.5;
        int i = 0;
        while (temp != NULL)
        {
            if (temp->data == item)
            {
                temp = temp->next;
                remove = removeAt(i);
                i--;
            }
            else
                temp = temp->next;
            i++;
        }
        if (remove != 1.5)
            return true;
        return false;
    }

    virtual bool empty()
    {
        if (this->head == NULL)
            return true;
        return false;
    }

    virtual int size()
    {
        return this->count;
        return 0;
    }

    virtual void clear()
    {
        this->head = NULL;
        this->count = 0;
    }

    virtual int get(int index)
    {
        int i = 0;
        Node *temp = this->head;
        if (index >= 0 && index < this->count)
        {
            while (i < index)
            {
                temp = temp->next;
                i++;
            }
            return temp->data;
        }
        return -1;
    }

    virtual void set(int index, int element)
    {
        Node *temp = this->head;
        int i = 0;
        while (i < index)
        {
            temp = temp->next;
            i++;
        }
        temp->data = element;
    }

    virtual int indexOf(int item)
    {
        Node *temp = this->head;
        int i = 0;
        while (temp != NULL)
        {
            if (temp->data == item)
            {
                return i;
            }
            temp = temp->next;
            i++;
        }
        return -1;
    }

    virtual bool contains(int item)
    {
        if (indexOf(item) != -1)
            return true;
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

    //virtual void dump();
    IntSLinkedList(const IntSLinkedList &list)
    {
        this->count = 0;
        this->head = NULL;
        this->tail = NULL;
    }
    Iterator begin()
    {
        return Iterator(this, true);
    }
    Iterator end()
    {
        return Iterator(this, false);
    }

public:
    class Node
    {
    private:
        int data;
        Node *next;
        friend class IntSLinkedList;

    public:
        Node()
        {
            next = 0;
        }
        Node(Node *next)
        {
            this->next = next;
        }
        Node(int data, Node *next = NULL)
        {
            this->data = data;
            this->next = next;
        }
    };
    ////////////////////////////////////////////////////////////////////
    class Iterator
    {
    private:
        IntSLinkedList *pList;
        Node *current;

    public:
        Iterator(IntSLinkedList *pList = 0, bool begin = true)
        {
            this->pList = pList;
            if (begin)
            {
                this->current = pList->head;
            }
            else
                pList->tail;
        }

        Iterator &operator=(const Iterator &iterator)
        {
            this->pList = iterator.pList;
            this->current = iterator.current;
            return *this;
        }

        void remove() {}

        void set(const int &e) {}

        int &operator*()
        {
            return this->current->data;
        }
        bool operator!=(const Iterator &iterator)
        {
            return this->current != iterator.current;
        }
        // Prefix ++ overload
        Iterator &operator++()
        {
            this->current = this->current->next;
            return *this;
        }
        // Postfix ++ overload
        Iterator operator++(int)
        {
            Iterator operation = *this;
            ++*this;
            return operation;
        }
    };
};
int main()
{
    IntSLinkedList list;
    cout << "Build successfully" << endl;
    assert(list.size() == 0);

    int size = 10;
    for (int idx = 0; idx < size; idx++)
    {
        list.add(idx);
    }
    assert(list.size() == 10);

    IntSLinkedList::Iterator it;
    int expvalue = 0;
    for (it = list.begin(); it != list.end(); it++)
    {
        cout << *it << endl;
    }
    cout << "ok" <<endl;
}
