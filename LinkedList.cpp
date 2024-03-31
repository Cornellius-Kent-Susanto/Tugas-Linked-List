#include <iostream>

class LinkedList;

class Node
{
    friend class LinkedList;
    friend std::ostream &operator<<(std::ostream &os, const LinkedList &rhs);

private:
    int value;
    Node *next;

public:
    Node(int src = 0) // Constructor Node
        : value{src}, next{nullptr}
    {
    }
};

class LinkedList
{
    friend std::ostream &operator<<(std::ostream &os, const LinkedList &rhs);

private:
    unsigned int jumlahNode;
    Node *head;
    Node *tail;

public:
    LinkedList();  // constructor linked list
    ~LinkedList(); // destructor linked list
    Node *getNode(int pos) const;
    bool insertNode(int val, int pos);
    bool deleteNode(int pos);
};

Node *LinkedList::getNode(int pos) const
{
    if (pos < 0 || pos > this->jumlahNode - 1)
    {
        return nullptr;
    }
    else
    {
        Node *passer{this->head};
        for (int i{0}; i < pos; i++)
        {
            passer = passer->next;
        }
        return passer;
    }
}

LinkedList::LinkedList()
    : head{nullptr}, tail{nullptr}, jumlahNode{0}
{
}

LinkedList::~LinkedList()
{
    Node *placeHolder{this->head};
    while (placeHolder)
    {
        placeHolder = placeHolder->next;
        delete this->head;
        this->head = placeHolder;
    }
}

bool LinkedList::insertNode(int val, int pos)
{
    {
        if (pos < 0 || pos > this->jumlahNode)
        {
            std::cout << "di luar batas" << std::endl;
            return false;
        }
        else
        {
            if (this->jumlahNode == 0)
            {
                this->head = this->tail = new Node{val};
            }
            else
            {
                Node *newNode{new Node{val}};
                Node *before{getNode(pos - 1)};
                if (!before)
                {
                    newNode->next = this->head;
                    this->head = newNode;
                    this->jumlahNode++;
                    return true;
                }
                Node *after{before->next};

                before->next = newNode;
                newNode->next = after;

                if (before == this->tail)
                {
                    this->tail = before->next;
                }
            }
        }
        this->jumlahNode++;
        return true;
    }
}

bool LinkedList::deleteNode(int pos)
{
    if (pos < 0 || pos > this->jumlahNode - 1)
    {
        return false;
    }

    Node *before{getNode(pos - 1)};

    if (!before)
    {
        before = this->head;
        this->head = before->next;
        delete before;
    }
    else
    {
        Node *destroy{before->next};
        if (destroy == this->tail)
        {
            this->tail = before;
        }
        before->next = destroy->next;
        delete destroy;
    }
    this->jumlahNode--;
    return true;
}

std::ostream &operator<<(std::ostream &os, const LinkedList &rhs)
{
    os << "[ Linked List : ";
    Node *ptr{rhs.head};
    while (ptr)
    {
        os << ptr->value << " ";
        ptr = ptr->next;
    }
    os << "]";
    return os;
}

int main()
{
    LinkedList myList{};
    myList.insertNode(110, 0);
    myList.insertNode(19, 0);
    myList.insertNode(211, 2);
    myList.insertNode(322, 1);

    // 19 322 110 211
    std::cout << myList << std::endl;
    myList.deleteNode(2);

    // 19 322 211
    std::cout << myList << std::endl;
    return 0;
}
