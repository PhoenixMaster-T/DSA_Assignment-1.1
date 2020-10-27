#include <sstream>
#include <string>
#include <iostream>
#include <type_traits>
using namespace std;

#ifndef ILIST_H
#define ILIST_H

template <class T>
class IList
{
public:
    virtual void add(const T& element) = 0;
    virtual void add(int index, const T& element) = 0;
    virtual T removeAt(int index) = 0;
    virtual bool removeItem(const T& item) = 0;
    virtual bool empty() = 0;
    virtual int size() = 0;
    virtual void clear() = 0;
    virtual T get(int index) = 0;
    virtual void set(int index, const T& element) = 0;
    virtual int indexOf(const T& item) = 0;
    virtual bool contains(const T& item) = 0;
    virtual string toString() = 0;
};

#endif

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

public:
    FragmentLinkedList(int fragmentMaxSize = 5)
    {
        this->count = 0;
        this->fragmentMaxSize = fragmentMaxSize;
        this->fragmentPointers = new Node *[2];
        this->fragmentPointers[0] = NULL;
        this->fragmentPointers[1] = NULL;
    }
    virtual ~FragmentLinkedList()
    {
        delete[] * fragmentPointers;

        delete fragmentPointers;
        //
        this->count = fragmentMaxSize = 0;
    }



    void thaydoisize() {
        int NumElementFragment = (int)(this->count - 1) / fragmentMaxSize + 2; //VVVvvv

        
       
        Node* head = fragmentPointers[0];
        delete[] fragmentPointers;
        if (head == NULL) {
            this->fragmentPointers = new Node* [2];
            
            this->fragmentPointers[0] = NULL;

            this->fragmentPointers[1] = NULL;
            return;
        }
        this->fragmentPointers = new Node* [NumElementFragment];
        fragmentPointers[0] = head; //
        int i = 1;//
        int countSize = 0;//
        while (head->next != NULL)
        {
            head = head->next;//
            countSize++;//
            if (countSize == fragmentMaxSize) {//
                fragmentPointers[i] = head;//
                i++;//
                countSize = 0;//
            }
        }

        //cout << i << endl;
        fragmentPointers[NumElementFragment - 1] = head;//
    }



    virtual void add(const T& element)
    {
        Node* newnode = new Node( element, NULL, NULL);
        this->count++;
        Node* mouse = fragmentPointers[0];
        if (fragmentPointers[0] == NULL)
        {
           this->fragmentPointers[0] = newnode;
           this->fragmentPointers[1] = newnode;
            return;

        }
        else
        {
            while (mouse->next != NULL)
                mouse = mouse->next;
        }
        mouse->next = newnode;
        newnode->prev = mouse;
        //////////////////Resize Fragmen t LikedList:
        thaydoisize();

    
    }
    virtual void add(int index, const T& element)
    {
        Node* newnode = new Node(element, NULL, NULL);
        this->count++; //
        
        if (index < 0)
            throw std::out_of_range("The index is out of range!");
        //them vao dau:

        else if (index == 0) {
            if (fragmentPointers[0] == NULL) {
                fragmentPointers[0] = newnode;
                fragmentPointers[1] = newnode;
                return;
            }
            newnode->next = fragmentPointers[0];
            fragmentPointers[0]->prev = newnode;
            fragmentPointers[0] = newnode;

        }
        //them vao cuoi: 
        else if (index >= this->size()) {//
            Node* mtp = fragmentPointers[0];//
            while (mtp->next != NULL)//
                mtp = mtp->next;//
            mtp->next = newnode;//
            newnode->prev = mtp;//
        }
        //Add to index's position:
        else {//
            int i = 1;//
            Node* prenode = fragmentPointers[0];//
            Node* nextnode = NULL;//


            while (i != index) {//
                i++;//
                prenode = prenode->next;//
            }//
            if (prenode->next == NULL) {//
                this->add(element);//
                this->count--;//
                return;//
            }
            else {
                nextnode = prenode->next;//
                prenode->next = newnode;//

                nextnode->prev = newnode;//
                newnode->prev = prenode;//
                newnode->next = nextnode; //
            }
        }
        //Resize Fragment LikedList:
        thaydoisize();
    }
    virtual T removeAt(int index)
    {
        Node* result = new Node(NULL, NULL);
        //Remove Node://
        if ((index < 0) || (index >= this->count))
            throw std::out_of_range("The index is out of range!");
        //Remove at head: //
        else if (index == 0) {
            this->count--;//
            result->data = fragmentPointers[0]->data;//
            Node* tmp = fragmentPointers[0];//
            fragmentPointers[0] = fragmentPointers[0]->next;//
            //fragmentPointers[0]->prev = nullptr;//
            delete[] tmp;//
        }
        //xoa cuoi
        else if (index >= (this->size() - 1)) { //
            this->count--;//
            Node* mtp = fragmentPointers[0];//
            Node* mtp_pre = nullptr;//
            while (mtp->next != nullptr) {//
                mtp = mtp->next;
            }
            result->data = mtp->data;
           mtp_pre = mtp->prev;
            mtp->prev = NULL;
            mtp_pre->next = NULL;
            delete[] mtp;
        }
        //Remove at index: //
        else {
            this->count--; //
            int i = 0;//
            Node* currentnode = fragmentPointers[0];
            Node* nextnode = NULL;
            Node* prenode = NULL;
            while (i != index) {
                i++;
                currentnode = currentnode->next;
            }
            //Delete at index position
            result->data = currentnode->data;
            nextnode = currentnode->next;
            prenode = currentnode->prev;
            nextnode->prev = prenode;
            prenode->next = nextnode;
            delete[] currentnode;
        }
        //Resize Fragment LikedList:
        thaydoisize();
        return result->data;
    }
    virtual bool removeItem(const T& item)
    {
        Node* currentnode = fragmentPointers[0]; //
        int index = 0;//
        bool flag = false;//
        while (currentnode != nullptr) { //ee
            if (currentnode->data == item) { //ee
                flag = true;//
                break;//
            }
            index++;//
            currentnode = currentnode->next; //ee
        }
        //Available to remove://ee
        if (flag == 1) {//ee
            this->count--;//ee
            this->removeAt(index);//ee
            // thay doi size//ee
            thaydoisize();//ee
        }
        //Removed = 1 if not = 0:eee
        return flag;
    }
    virtual bool empty()
    {
        if (fragmentPointers[0] == NULL)
            return true;
        return false; //
    }
    virtual int size()
    {
        return count;
    }
    virtual void clear()
    {
        Node* mtp = NULL; //z
        Node* head = fragmentPointers[0];//z

        while (head->next != NULL) {//z
            mtp = head;//z
            head = head->next;//z


            head->prev = NULL;//z
            delete[] mtp;//z
        }
        head = NULL;//z
        delete[] head;//z
        delete[] fragmentPointers;//

        this->fragmentPointers = new Node* [2];//z
        this->fragmentPointers[0] = NULL;//z
        this->fragmentPointers[1] = NULL;//z
    }
    virtual T get(int index)
    {
        if ((index < 0) || (index >= this->count))//b
            throw std::out_of_range("The index is out of range!");//nn
        else {//nn
            Node* currentnode = fragmentPointers[0];//nn
            int count = 0;//nn
            while (currentnode != NULL) {//nn
                if (count == index)//nn
                    break;
                count++;//v
                currentnode = currentnode->next;// v
            }
            return currentnode->data;
            //vvvvvvv
        }
    }
    virtual void set(int index, const T& element)
    {
        if ((index < 0) || (index >= this->count))
            return;//mm
        else {//
            Node* currentnode = fragmentPointers[0];//mm
            int count = 0;//

            while  (currentnode != nullptr) 
             {//mm

                if (count == index)//mm
                    break;//mm


                count++;//mm
                currentnode   = currentnode->next;//mm
            }//m
            currentnode->data = element;//mm
        }
    }
    virtual int indexOf(const T& item)
    {
        Node* currentnode = fragmentPointers[0];//jj
        int index = 0;//jj
        while (currentnode != NULL) {//jj
            if (currentnode->data == item)//jj
                return index;//jj
            index++;//jj
            currentnode = currentnode->next;//jj
        }//jj
        return -1; //jj
    }
    virtual bool contains(const T& item)
    {
        Node* currentnode = fragmentPointers[0];//
        while (currentnode != NULL) {//
            if (currentnode->data == item)//
                return true;//
            currentnode = currentnode->next;//
        }//
        return false; //
    }

    virtual string toString();


    Iterator begin(int index = 0)
    {
        if (index == 0) {
            Iterator FirstElement(this, true);// //

            return FirstElement;//


        }
        else {
            Iterator FirstElement(index, this, true);  // 
            return FirstElement;
        }
    }
    Iterator end(int index = -1)
    {
        if (index == -1) {
            Iterator thelast(this, false);
            return thelast;
        }
        else {
            Iterator thelast(this, index, false);
            return thelast;
        }
    } 

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

    public:
         Iterator(FragmentLinkedList<T>* pList = 0, bool begin = true) 
         {
            this->pList = pList;  //nnnnn
 

            //Return first element of list:  ....
             pNode = pList->fragmentPointers[0]; 
            
            
            //nnn

            //Return last element of list: .......
             if (begin == 0) 
             { ///kkkk
                if (pNode != NULL) //tttttt


                    while (pNode->next != NULL)//kkkkkkk

                        pNode = pNode->next;  //vvvvvvv 
                else
                    cout <<   this->pList->toString();//ffff
            }
        }
        Iterator(int fragmentIndex, FragmentLinkedList<T>* pList = 0, bool begin = true)
        {
            this->pList = pList; //tttttt
            //    Return first element of fragment ....


            pNode = pList->fragmentPointers[fragmentIndex]; //uuuu
            //  Return last element of fragment ....



            int i = pList->fragmentMaxSize - 1; //b
            if (!begin ) //bb


            {
                while ((pNode->next != NULL) && (i != 0)) //bbbb
                {
                    pNode = pNode->next; //gggg
                    i--;
                }
            }
        }
        Iterator& operator=(const Iterator& iterator)



        {



            pList = iterator.pList; //c
            pNode = iterator.pNode; //c


            return *this;
        }
        T& operator*()
        {
            return pNode->data;
        }
        bool operator!=(const Iterator& iterator)
        {
            if (iterator.pNode == NULL) 


                return (pNode != iterator.pNode); //gg
            return (pNode != iterator.pNode->next); //gg

        }
        void remove()
        {
            delete[] pNode;



            delete[] pList;


        }
        void set(const T& element)
        {
            pNode->data = element; //gg
        }
        Iterator& operator++()
        {
            Iterator i(*this);

            pNode = pNode->next; //gg


            return i;
        }
        Iterator operator++(int)
        {
            pNode = pNode->next; //gg

            return *this;
        }
    };
};

template <class T>
string FragmentLinkedList<T>::toString()
{
    stringstream ss;
    ss << "[";
    Node *ptr = this->fragmentPointers[0];

    if (this->count == 0)
        ss << "]";

    // TODO

    while (ptr != NULL)
    {
        if (ptr->next == NULL)
        {
            ss << ptr->data << "]";
            ptr = ptr->next;
        }
        else
        {
            ss << ptr->data << ", ";
            ptr = ptr->next;
        }
    }

    // END: TODO

    return ss.str();
}

#endif
// END: STUDENT ANSWER

int main()
{
    FragmentLinkedList<int> fList(5);
    for (int i = 0; i < 20; i++)
        fList.add(i);
    FragmentLinkedList<int>::Iterator a = fList.begin(2);
    a++;
    FragmentLinkedList<int>::Iterator b = a;
    a++;
    b.remove();
    cout << fList.toString() << endl;
    b++;
    cout << "value of node pointed by a: " << *a << "\nvalue of node pointed by b: " << *b << endl;
    cout << "So, a " << (!(a != b) ? "equal" : "not equal") << " b";
    cout << endl;
}
