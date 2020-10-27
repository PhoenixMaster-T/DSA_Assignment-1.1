#include <sstream>
#include <string>
#include <iostream>
#include <type_traits>
#include <stdexcept>
#include <time.h>
using namespace std;
template <class T>
class IList
{
public:
    virtual void add(const T &element) = 0;
    virtual void add(int index, const T &element) = 0;
    virtual T removeAt(int index) = 0;
    virtual bool removeItem(const T &item) = 0;
    virtual bool empty() = 0;
    virtual int size() = 0;
    virtual void clear() = 0;
    virtual T get(int index) = 0;
    virtual void set(int index, const T &element) = 0;
    virtual int indexOf(const T &item) = 0;
    virtual bool contains(const T &item) = 0;
    virtual string toString() = 0;
};
// STUDENT ANSWER
#ifndef FRAGMENT_LINKED_LIST
#define FRAGMENT_LINKED_LIST
template <class T>
class FragmentLinkedList : IList<T>
{
public:
    class Node;
    class Iterator;

protected:
    Node **fragmentPointers;
    int fragmentMaxSize;
    int count;
    int sizePointer;
    virtual FragmentLinkedList<T>::Node *traverseTo(int index);
    virtual void addFirst(const T &element);
    virtual T removeFirst();
    virtual T removeLast();
    virtual void increaseFragmentPointer();
    virtual void decreaseFragmentPointer();
    virtual int getSizePointer();

public:
    FragmentLinkedList(int fragmentMaxSize = 5)
    {
        this->count = 0;
        this->fragmentMaxSize = fragmentMaxSize;
        this->sizePointer = 2;
        this->fragmentPointers = new Node *[sizePointer];
        this->fragmentPointers[0] = NULL;
        this->fragmentPointers[sizePointer - 1] = NULL;
    }
    virtual ~FragmentLinkedList()
    {
        clear();
    }
    virtual void add(const T &element);
    virtual void add(int index, const T &element);
    virtual T removeAt(int index);
    virtual bool removeItem(const T &item);
    virtual bool empty();
    virtual int size();
    virtual void clear();
    virtual T get(int index);
    virtual void set(int index, const T &element);
    virtual int indexOf(const T &item);
    virtual bool contains(const T &item);
    virtual string toString();
    Iterator begin(int index = 0);
    Iterator end(int index = -1);

public:
    class Node
    {
    private:
        T data;
        Node *next;
        Node *prev;
        friend class FragmentLinkedList<T>;

    public:
        Node()
        {
            next = 0;
            prev = 0;
        }
        Node(Node *next, Node *prev)
        {
            this->next = next;
            this->prev = prev;
        }
        Node(T data, Node *next, Node *prev)
        {
            this->data = data;
            this->next = next;
            this->prev = prev;
        }
    };
    class Iterator
    {
    private:
        FragmentLinkedList<T> *pList;
        Node *pNode;
        int index;
        //friend class FragmentLinkedList<T>;
    public:
        Iterator(FragmentLinkedList<T> *pList = 0, bool begin = true)
        {
            if (pList == NULL)
            {
                this->pList = NULL;
                this->pNode = NULL;
                this->index = -1;
            }
            else
            {
                this->pList = pList;
                if (begin)
                {
                    pNode = pList->fragmentPointers[0];
                    index = 0;
                }
                else
                {
                    pNode = NULL;
                    index = pList->size();
                }
            }
        }
        Iterator(int fragmentIndex, FragmentLinkedList<T> *pList = 0, bool begin = true)
        {
            if (pList == NULL)
            {
                this->pList = NULL;
                this->pNode = NULL;
                this->index = -1;
            }
            else
            {
                this->pList = pList;
                if (begin)
                {
                    if (fragmentIndex > pList->getSizePointer() - 2)
                        throw std::out_of_range("The index is out of range!");
                    pNode = pList->fragmentPointers[fragmentIndex];
                    index = fragmentIndex * pList->fragmentMaxSize;
                }
                else // end
                {
                    if (fragmentIndex > pList->getSizePointer() - 2)
                        throw std::out_of_range("The index is out of range!");
                    else if (fragmentIndex == pList->getSizePointer() - 2)
                    {
                        pNode = NULL;
                        index = pList->size();
                    }
                    else
                    {
                        pNode = pList->fragmentPointers[fragmentIndex + 1];
                        index = (fragmentIndex + 1) * pList->fragmentMaxSize;
                    }
                }
            }
        }
        Iterator &operator=(const Iterator &iterator)
        {
            this->pNode = iterator.pNode;
            this->pList = iterator.pList;
            this->index = iterator.index;
            return *this;
        }
        T &operator*()
        {
            if (pNode == NULL)
                throw std::out_of_range("Segmentation fault!");
            else
                return pNode->data;
        }
        bool operator!=(const Iterator &iterator)
        {
            return !(pNode == iterator.pNode);
        }
        void remove()
        {
            if (index == 0)
            {
                pList->removeAt(0);
                pNode = NULL;
                index = -1;
            }
            else
            {
                pNode = pNode->prev;
                pList->removeAt(this->index);
                --index;
            }
        }
        void set(const T &element)
        {
            pList->set(index, element);
        }
        Iterator &operator++()
        {
            if (index == pList->size() - 1)
            {
                pNode = NULL;
                index = pList->size();
            }
            else if (index == -1)
            {
                ++index;
                pNode = pList->fragmentPointers[0];
            }
            else
            {
                ++index;
                pNode = pNode->next;
            }
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator temp = *this;
            if (index == pList->size() - 1)
            {
                pNode = NULL;
                index = pList->count;
            }
            else if (index == -1)
            {
                index++;
                pNode = pList->fragmentPointers[0];
            }
            else
            {
                pNode = this->pNode->next;
                index++;
            }
            return temp;
        }
    };
};

/*-----------------------------------------------------------------------------------------------------------------*/
//Support functions. These fuctions can't be called in main() fuction.
template <class T>
void FragmentLinkedList<T>::increaseFragmentPointer()
{
    Node **newArr = new Node *[sizePointer + 1];
    for (int i = 0; i < sizePointer - 1; i++)
    {
        newArr[i] = this->fragmentPointers[i];
    }
    newArr[sizePointer] = this->fragmentPointers[sizePointer - 1];
    newArr[sizePointer - 1] = NULL;
    Node **temp = this->fragmentPointers;
    this->fragmentPointers = newArr;
    delete[] temp;
    sizePointer++;
}
template <class T>
void FragmentLinkedList<T>::decreaseFragmentPointer()
{
    Node **newArr = new Node *[sizePointer - 1];
    for (int i = 0; i < sizePointer - 1; i++)
        newArr[i] = fragmentPointers[i];
    newArr[sizePointer - 2] = fragmentPointers[sizePointer - 1];
    Node **temp = fragmentPointers;
    fragmentPointers = newArr;
    delete[] temp;
    sizePointer--;
}
template <class T>
void FragmentLinkedList<T>::addFirst(const T &element)
{
    FragmentLinkedList::Node *newNode = new Node(element, NULL, NULL);
    if (count == 0)
    {
        this->fragmentPointers[0] = newNode;
        this->fragmentPointers[sizePointer - 1] = newNode;
    }
    else
    {
        fragmentPointers[0]->prev = newNode;
        newNode->next = fragmentPointers[0];
        fragmentPointers[0] = newNode;
        if (count % fragmentMaxSize == 0)
        {
            increaseFragmentPointer();
            fragmentPointers[sizePointer - 2] = fragmentPointers[sizePointer - 1];
            for (int i = sizePointer - 3; i > 0; i--)
                fragmentPointers[i] = fragmentPointers[i]->prev;
        }
        else
        {
            for (int i = sizePointer - 2; i > 0; i--)
                fragmentPointers[i] = fragmentPointers[i]->prev;
        }
    }
    count++;
}
template <class T>
T FragmentLinkedList<T>::removeFirst()
{
    T res;
    if (count == 0)
    {
        throw std::out_of_range("The index is out of range!");
    }
    else
    {
        res = fragmentPointers[0]->data;
        fragmentPointers[0] = fragmentPointers[0]->next;
        delete fragmentPointers[0]->prev;
        fragmentPointers[0]->prev = NULL;
        if (count % fragmentMaxSize == 1)
        {
            decreaseFragmentPointer();
            for (int i = 1; i < sizePointer - 1; i++)
                fragmentPointers[i] = fragmentPointers[i]->next;
        }
        else
        {
            for (int i = 1; i < sizePointer - 1; i++)
                fragmentPointers[i] = fragmentPointers[i]->next;
        }
        count--;
    }
    return res;
}
template <class T>
T FragmentLinkedList<T>::removeLast()
{
    T res;
    if (count == 0)
    {
        throw std::out_of_range("Segmentation fault!");
    }
    else
    {
        res = fragmentPointers[sizePointer - 1]->data;
        fragmentPointers[sizePointer - 1] = fragmentPointers[sizePointer - 1]->prev;
        delete fragmentPointers[sizePointer - 1]->next;
        fragmentPointers[sizePointer - 1]->next = NULL;
        if (count % fragmentMaxSize == 1)
            decreaseFragmentPointer();
        count--;
    }
    return res;
}
template <class T>
typename FragmentLinkedList<T>::Node *FragmentLinkedList<T>::traverseTo(int index)
{
    if (index < 0 || index >= count)
        throw std::out_of_range("The index is out of range!");
    else if (count == 0)
        throw std::out_of_range("Segmentation fault!");
    Node *res;
    int modIndex = index % fragmentMaxSize;
    if (modIndex < (fragmentMaxSize + 1) / 2)
    {
        res = fragmentPointers[index / fragmentMaxSize];
        while (modIndex)
        {
            res = res->next;
            modIndex--;
        }
    }
    else
    {
        res = fragmentPointers[index / fragmentMaxSize + 1];
        if (index / fragmentMaxSize != sizePointer - 2)
            res = res->prev;
        modIndex = fragmentMaxSize - modIndex - 1;
        while (modIndex)
        {
            res = res->prev;
            modIndex--;
        }
    }
    return res;
}
template <class T>
int FragmentLinkedList<T>::getSizePointer()
{
    return sizePointer;
}

/*-------------------------------------------------------------------------------------------------------------------------------*/
/*TODO: implement interface Ilist here*/
template <class T>
void FragmentLinkedList<T>::add(const T &element) // addLast
{
    FragmentLinkedList::Node *newNode = new Node(element, NULL, NULL);
    if (count == 0)
    {
        this->fragmentPointers[0] = newNode;
        this->fragmentPointers[sizePointer - 1] = newNode;
    }
    else
    {
        // update value each of fragmentPointer[i]
        fragmentPointers[sizePointer - 1]->next = newNode;
        newNode->prev = fragmentPointers[sizePointer - 1];
        fragmentPointers[sizePointer - 1] = newNode;
        if (count % fragmentMaxSize == 0) // addition that increases fragment by one
        {
            increaseFragmentPointer();
            fragmentPointers[sizePointer - 2] = fragmentPointers[sizePointer - 1];
        }
    }
    count++;
}
template <class T>
void FragmentLinkedList<T>::add(int index, const T &element)
{
    FragmentLinkedList::Node *newNode = new Node(element, NULL, NULL);
    if (index > count)
        throw std::out_of_range("The index is out of range!");
    else if (!index)
        addFirst(element);
    else if (index == count)
        add(element);
    else
    {
        Node *temp = traverseTo(index - 1);
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
        // update value each of fragmentPointer[i]
        if (count % fragmentMaxSize == 0) // addition that increases fragment by one
        {
            increaseFragmentPointer();
            fragmentPointers[sizePointer - 2] = fragmentPointers[sizePointer - 1];
            int indexBegin = (index % fragmentMaxSize == 0) ? index / fragmentMaxSize : (index / fragmentMaxSize) + 1;
            for (int i = indexBegin; i < sizePointer - 2; i++)
                fragmentPointers[i] = fragmentPointers[i]->prev;
        }
        else
        {
            int indexBegin = (index % fragmentMaxSize == 0) ? index / fragmentMaxSize : (index / fragmentMaxSize) + 1;
            for (int i = indexBegin; i < sizePointer - 1; i++)
                fragmentPointers[i] = fragmentPointers[i]->prev;
        }
        count++;
    }
}

template <class T>
T FragmentLinkedList<T>::removeAt(int index)
{
    T res;
    if (index < 0 || index >= count)
        throw std::out_of_range("The index is out of range!");
    else if (!count)
        throw std::out_of_range("Segmentation fault!");
    else if (count == 1)
    {
        res = fragmentPointers[0]->data;
        delete fragmentPointers[0];
        fragmentPointers[0] = NULL;
        fragmentPointers[1] = NULL;
        count--;
        return res;
    }
    else if (index == 0)
        return removeFirst();
    else if (index == count - 1)
        return removeLast();
    else
    {
        Node *temp = traverseTo(index - 1);
        res = temp->next->data;
        if (index % fragmentMaxSize == 0)
        {
            fragmentPointers[index / fragmentMaxSize] = temp->next->next;
        }
        temp->next = temp->next->next;
        delete temp->next->prev;
        temp->next->prev = temp;
        if (count % fragmentMaxSize == 1) // removation that decreases fragment by one
            decreaseFragmentPointer();
        int indexBegin = (index / fragmentMaxSize) + 1;
        for (int i = indexBegin; i < sizePointer - 1; i++)
        {
            fragmentPointers[i] = fragmentPointers[i]->next;
        }
        count--;
        return res;
    }
}
template <class T>
bool FragmentLinkedList<T>::removeItem(const T &item)
{
    int index = 0;
    for (FragmentLinkedList::Node *temp = this->fragmentPointers[0]; temp != NULL; temp = temp->next)
    {
        if (temp->data == item)
        {
            this->removeAt(index);
            return true;
        }
        index++;
    }
    return false;
}
template <class T>
bool FragmentLinkedList<T>::empty()
{
    return (count == 0);
}
template <class T>
int FragmentLinkedList<T>::size()
{
    return count;
}
template <class T>
void FragmentLinkedList<T>::clear()
{
    while (!this->empty())
    {
        FragmentLinkedList::Node *temp = this->fragmentPointers[0];
        this->fragmentPointers[0] = this->fragmentPointers[0]->next;
        delete temp;
        count--;
    }
    // reset FragmentPointer to default
    Node **defaultArr = new Node *[2];
    defaultArr[0] = defaultArr[1] = NULL;
    Node **temp = fragmentPointers;
    fragmentPointers = defaultArr;
    sizePointer = 2;
    delete[] temp;
}
template <class T>
T FragmentLinkedList<T>::get(int index)
{
    Node *result = traverseTo(index);
    return result->data;
}
template <class T>
void FragmentLinkedList<T>::set(int index, const T &element)
{
    Node *curr = traverseTo(index);
    curr->data = element;
}
template <class T>
int FragmentLinkedList<T>::indexOf(const T &item)
{
    int index = -1;
    for (Node *k = this->fragmentPointers[0]; k != NULL; k = k->next)
    {
        ++index;
        if (k->data == item)
            return index;
    }
    return -1;
}
template <class T>
bool FragmentLinkedList<T>::contains(const T &item)
{
    for (Node *k = this->fragmentPointers[0]; k != NULL; k = k->next)
    {
        if (k->data == item)
            return true;
    }  
    return false;
}
template <class T>
typename FragmentLinkedList<T>::Iterator FragmentLinkedList<T>::begin(int indexFragment)
{
    if (indexFragment >= sizePointer - 1)
        throw std::out_of_range("The index is out of range!");
    else
        return Iterator(indexFragment, this, true);
}
template <class T>
typename FragmentLinkedList<T>::Iterator FragmentLinkedList<T>::end(int indexFragment)
{
    if (indexFragment == -1 || indexFragment == sizePointer - 2)
        return Iterator(this, false);
    else if (indexFragment >= sizePointer - 1)
        throw std::out_of_range("The index is out of range!");
    else
        return Iterator(indexFragment, this, false);
}

template <class T>
string FragmentLinkedList<T>::toString()
{
    stringstream ss;
    ss << "[";
    Node *ptr = this->fragmentPointers[0];

    if (this->count == 0)
        ss << "]";

    // TODO
    Node *tail = this->fragmentPointers[sizePointer - 1];
    while (ptr != tail)
    {
        ss << ptr->data << ", ";
        ptr = ptr->next;
    }
    if (count > 0)
        ss << ptr->data << "]";
    // END: TODO

    return ss.str();
}

#endif
int main()
{
    clock_t start = clock();
    cout << "check set, add and remove method:\n";
    FragmentLinkedList<int> fList(5000);
    for (int i = 0; i < 100000; i++)
        fList.add(i);
    fList.add(55555, -1);
    cout << "current value at index 5555555: " << fList.get(55555) << endl;
    fList.set(55555, -99);
    cout << "current value at index 5555555: " << fList.get(55555) << endl;
    fList.removeAt(55555);
    cout << "current value at index 5555555: " << fList.get(55555) << endl;
    FragmentLinkedList<int>::Iterator i = fList.begin();
    FragmentLinkedList<int>::Iterator end = fList.end(0);
    cout << "begin and end of fragment 0 (before): " << *i << " " << *end << endl;
    for (; i != end; i++)
        i.remove();
    i = fList.begin();
    cout << fList.contains(60000) <<endl;
    end = fList.end(0);
    cout << "begin and end of fragment 0 (after): " << *i << " " << *end << endl;
    printf("excute time: %.6fs\n", (double)(clock() - start) / CLOCKS_PER_SEC);
    return 0;
}
