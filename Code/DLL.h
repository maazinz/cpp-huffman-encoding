#include <iostream>
using namespace std;

// template <class T>
struct Node
{
    char data;
    int Frequency;
    Node *next;
};

// template <class T>
class HLinkedList
{
    Node *head;

public:
    HLinkedList()
    {
        head = NULL; // LinkedList is empty
    }

    bool isEmpty()
    {
        if (head == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int Size()
    {
        Node *temp = head;
        int c = 0;

        while (temp != NULL)
        {
            temp = temp->next;
            c++;
        }

        return c;
    }

    void Display() // Traversal
    {
        if (head)
        {
            Node *temp = head;
            while (temp != NULL)
            {
                cout << temp->data << temp->Frequency << " ";
                temp = temp->next;
            }
            cout << endl;
        }
        else
        {
            cout << "List is Empty" << endl;
        }
    }

    void IAS(char Data, int Frequency)
    {
        Node *n = new Node;
        n->data = Data;
        n->Frequency = Frequency;

        if (head == NULL)
        {
            head = n;
            n->next = NULL;
        }
        else
        {
            n->next = head;
            head = n;
        }
    }

    void IAE(char Data, int Frequency)
    {
        Node *n = new Node;
        n->data = Data;
        n->Frequency = Frequency;
        n->next = NULL;

        if (head == NULL)
        {
            IAS(Data, Frequency);
        }
        else
        {
            Node *temp = head;

            while (temp->next != NULL)
            {
                temp = temp->next;
            }

            temp->next = n;
            // temp->next->next = NULL;
        }
    }

    void DAS()
    {
        Node *temp = head;
        head = temp->next;
        delete temp;
    }

    void DAE()
    {
        Node *temp = head;

        while (temp->next->next != NULL) // runtime error
        {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = NULL;
    }

    void DAAP(int Pos)
    {
        Node *temp = head;
        int c = 1;

        if (Pos == 1)
        {
            DAS();
        }
        else if (Pos >= Size())
        {
            DAE();
        }
        else
        {
            while ((temp != NULL))
            {
                if (c == Pos - 1)
                {
                    break;
                }
                temp = temp->next;
                c++;
            }
            Node *a = temp->next;
            temp->next = temp->next->next;
            free(a);
        }
    }

    ~HLinkedList()
    {
        Node *temp = head;

        while (head != NULL)
        {
            temp = head->next;
            delete head;
            head = temp;
        }
        delete temp;
        // cout << "Destructor Called" << endl;
    }

    void LInsert(char Data, int Frequency)
    {
        Node *Temp = head;

        if (isEmpty())
        {
            IAE(Data, Frequency);
        }
        else
        {
            while (Temp)
            {
                if (Temp->data == Data)
                {
                    Temp->Frequency++;
                    return;
                }
                Temp = Temp->next;
            }

            IAE(Data, Frequency);
        }
    }

    int ReturnFreq(int Count)
    {
        Node *Temp = head;
        int Freq;

        for (int i = 1; i < Count; i++)
        {
            Temp = Temp->next;
        }

        Freq = Temp->Frequency;

        return Freq;
    }

    char ReturnLetter(int Count)
    {
        Node *Temp = head;
        char Letter;

        for (int i = 1; i < Count; i++)
        {
            Temp = Temp->next;
        }

        Letter = Temp->data;

        return Letter;
    }
};
