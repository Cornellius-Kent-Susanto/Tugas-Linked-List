#include <iostream>
#include <thread>
#include <chrono>

//?==================== Deklarasi Struct ==========================
struct LinkedList;

typedef struct Node
{
    // agar fungsi operator<< dan class LinkedList dapat akses private member
    friend std::ostream &operator<<(std::ostream &os, const LinkedList &rhs);
    friend struct LinkedList;

    //! Jelasin Spesifikasi Node
private:
    std::string val;
    Node *next;

public:
    Node(const std::string &src)
        : val{src}, next{nullptr}
    {
    }
    ~Node() = default;
} Node;

typedef struct LinkedList
{
    // Operator overloading (agar lebih intuitif)
    friend std::ostream &operator<<(std::ostream &os, const LinkedList &rhs);

private:
    Node *head;
    Node *tail;
    int jumlahNode{}; // simpan jumlah Node

public:
    LinkedList()
        : head{nullptr}, tail{nullptr}, jumlahNode{0}
    {
    }

    // jelasin spesifikasi class
    void insertFirst(const std::string &src);
    void insertLast(const std::string &src);
    void insertOn(const std::string &src, int pos);
    void insertAfter(const std::string &src, int pos);

    void deleteFirst();
    void deleteLast();
    void deleteOn(int pos);
    void deleteAfter(int pos);

    ~LinkedList()
    {
        Node *temp{this->head};
        while (this->head)
        {
            this->head = this->head->next;
            delete temp;
            temp = this->head;
        }
    }

} LinkedList;
//?================================================================

//=================== implementasi operator<< =====================
std::ostream &operator<<(std::ostream &os, const LinkedList &rhs)
{
    Node *traverse{rhs.head};
    os << "LinkedList : [";
    while (traverse)
    {
        os << "(" << traverse->val << ", " << traverse->next << ")" << (traverse->next == nullptr ? "" : ", ");
        traverse = traverse->next;
    }
    os << "]\n"
       << "Jumlah Node : " << rhs.jumlahNode;
    os << std::endl;

    return os;
}
//=================================================================

//!================ implementasi member function ==================
void LinkedList::insertFirst(const std::string &src)
{
    // jika LinkedList kosong
    if (head == nullptr)
    {
        this->head = this->tail = new Node{src};
    }

    // jika ada isinya
    else
    {
        Node *temp{new Node{src}};
        temp->next = this->head;
        this->head = temp;
    }

    jumlahNode++;
}

void LinkedList::insertLast(const std::string &src)
{
    // jika LinkedList kosong
    if (!this->head)
    {
        insertFirst(src);
    }

    // jika ada isinya
    else
    {
        Node *temp{new Node{src}};
        this->tail->next = temp;
        this->tail = temp;
        jumlahNode++;
    }
}

void LinkedList::insertOn(const std::string &src, int pos)
{
    // jika posisi tidak valid
    if (pos > (this->jumlahNode) || pos < 0)
    {
        std::cout << "posisi Node invalid" << std::endl;
        return;
    }

    // jika posisi valid
    else
    {
        if (pos == 0)
        {
            insertFirst(src);
        }
        else if (pos == this->jumlahNode)
        {
            insertLast(src);
        }
        else
        {
            Node *NodeBaru{new Node{src}};
            Node *temp{this->head};
            for (int i{0}; i < pos - 1; i++)
            {
                temp = temp->next;
            }
            NodeBaru->next = temp->next;
            temp->next = NodeBaru;
            jumlahNode++;
        }
    }
}

void LinkedList::insertAfter(const std::string &src, int pos)
{
    insertOn(src, pos + 1);
}

void LinkedList::deleteFirst()
{
    if (!this->head)
    {
        std::cout << "Element Habis" << std::endl;
        return;
    }
    else
    {
        Node *temp{this->head->next};
        delete this->head;
        this->head = temp;
        this->jumlahNode--;
    }
}

void LinkedList::deleteOn(int pos)
{
    if (pos < 0 || pos > (this->jumlahNode) - 1)
    {
        std::cout << "posisi invalid";
        return;
    }
    else
    {
        if (pos == 0)
        {
            deleteFirst();
        }
        else if (pos == this->jumlahNode - 1)
        {
            deleteLast();
        }
        else
        {
            Node *prev{this->head};
            for (int i{0}; i < pos - 1; i++)
            {
                prev = prev->next;
            }
            Node *after{prev->next};
            prev->next = after->next;
            if (after)
            {
                delete after;
                jumlahNode--;
            }
        }
    }
}

void LinkedList::deleteAfter(int pos)
{
    deleteOn(pos + 1);
}

void LinkedList::deleteLast()
{
    if (!this->head)
    {
        return;
    }
    else if (this->head == this->tail)
    {
        delete this->head;
        this->head = this->tail = nullptr;
        this->jumlahNode = 0;
    }
    else
    {
        Node *temp{this->head};
        while (temp->next->next)
        {
            temp = temp->next;
        }
        delete this->tail;
        this->jumlahNode--;
        this->tail = temp;
        this->tail->next = nullptr;
    }
}
//!================================================================

int main()
{
    LinkedList myList;
    short opt{0};

    while (true)
    {
        std::cout << "==== Pilihan Aksi ==== \n";
        std::cout << "1. Insert First\n";
        std::cout << "2. Insert Last\n";
        std::cout << "3. Insert On\n";
        std::cout << "4. Insert After\n";
        std::cout << "5. Delete First\n";
        std::cout << "6. Delete Last\n";
        std::cout << "7. Delete On\n";
        std::cout << "8. Delete After\n";
        std::cout << "9. Clear Screen\n";
        std::cout << "0. Exit\n=====================\n";
        std::cout << myList << "\n";
        std::cout << "Masukan Perintah : ";
        std::cin >> opt;

        std::string placeHolder{0};
        int pos{0};

        switch (opt)
        {
        case 0:
            std::cout << "Exiting.";
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            std::cout << ".";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << ".";
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            return 0;

        case 1:

            std::cout << "Nilai : ";
            std::cin >> placeHolder;
            myList.insertFirst(placeHolder);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            std::cout << "\nOperasi selesai\n\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(600));
            break;
        case 2:
            std::cout << "Nilai : ";
            std::cin >> placeHolder;
            myList.insertLast(placeHolder);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            std::cout << "\nOperasi selesai\n\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(600));
            break;
        case 3:
            std::cout << "Nilai : ";
            std::cin >> placeHolder;
            std::cout << "Posisi : ";
            std::cin >> pos;
            myList.insertOn(placeHolder, pos);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            std::cout << "\nOperasi selesai\n\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(600));
            break;
        case 4:
            std::cout << "Nilai : ";
            std::cin >> placeHolder;
            std::cout << "Target : ";
            std::cin >> pos;
            myList.insertAfter(placeHolder, pos);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            std::cout << "\nOperasi selesai\n\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(600));
            break;
        case 5:
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            myList.deleteFirst();
            std::cout << "\nOperasi selesai\n\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(600));

            break;
        case 6:
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            myList.deleteLast();
            std::cout << "\nOperasi selesai\n\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(600));

            break;
        case 7:
            std::cout << "Posisi : ";
            std::cin >> pos;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            myList.deleteOn(pos);
            std::cout << "\nOperasi selesai\n\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(600));
            break;
        case 8:
            std::cout << "Target : ";
            std::cin >> pos;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            myList.deleteAfter(pos);
            std::cout << "\nOperasi selesai\n\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(600));
            break;
        case 9:
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            system("CLS");
            break;
        default:
            std::cout << "Invalid option! Please try again.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
    }

    return 0;
}
