#include <iostream>
#include <queue>
#include <string>
#include <list>
#include <fstream>
#include <cmath>
#include "DLL.h"
using namespace std;

string Text;

struct TNode
{
    int Frequency;
    char Letter;
    TNode *Left, *Right;

    TNode()
    {
        Left = Right = NULL;
        Frequency = 0;
    }
};

struct LNode
{
    char Letter;
    string HC;
};

struct Comparator
{
    bool operator()(TNode *const &c1, TNode *const &c2)
    {
        return c1->Frequency > c2->Frequency;
    }
};

class Huffman
{
    priority_queue<TNode *, vector<TNode *>, Comparator> FrequencyQueue;
    string HuffCode, Compressed;
    list<LNode *> HuffCodes;

public:
    Huffman()
    {
        HuffCode = Compressed = "";
    }

    void FileToText()
    {
        fstream FileHandle;
        FileHandle.open("ProjectFile.txt", ios::in);

        getline(FileHandle, Text);

        cout << "From File: " << Text << endl;
    }

    void HuffmanEncoding()
    {
        FileToText();
        HLinkedList Scanned;

        char CL;

        for (int i = 0; i < Text.size(); i++)
        {
            CL = Text[i];

            Scanned.LInsert(CL, 1);
        }

        int PFreq;
        char Letter;

        for (int i = 1; i < Scanned.Size() + 1; i++)
        {
            Letter = Scanned.ReturnLetter(i);
            PFreq = Scanned.ReturnFreq(i);

            TNode *Ins = new TNode;
            Ins->Frequency = PFreq;
            Ins->Letter = Letter;

            FrequencyQueue.push(Ins);
        }
    }

    void ShowQueue()
    {
        priority_queue<TNode *, vector<TNode *>, Comparator> gq;
        gq = FrequencyQueue;
        TNode *Out = new TNode;

        while (!gq.empty())
        {
            Out = gq.top();
            cout << Out->Letter << Out->Frequency << " ";
            gq.pop();
        }

        cout << endl;
    }

    void CreateBT()
    {
        while (FrequencyQueue.size() > 1)
        {
            TNode *Ins = new TNode;
            Ins->Left = FrequencyQueue.top();
            Ins->Frequency = FrequencyQueue.top()->Frequency;
            FrequencyQueue.pop();
            Ins->Right = FrequencyQueue.top();
            Ins->Frequency += FrequencyQueue.top()->Frequency;
            FrequencyQueue.pop();

            FrequencyQueue.push(Ins);
        }
    }

    void Display()
    {
        Encode(FrequencyQueue.top());
    }

    void Encode(TNode *n, string str = "")
    {
        if (!n)
            return;

        Encode(n->Left, str + '0');
        Encode(n->Right, str + '1');

        if (!n->Left && !n->Right) // if leaf node
        {
            LNode *Ins = new LNode;

            Ins->Letter = n->Letter;
            Ins->HC = str;

            HuffCodes.push_front(Ins);
        }
    }

    void DisplayList()
    {
        list<LNode *>::iterator CN;

        for (CN = HuffCodes.begin(); CN != HuffCodes.end(); CN++)
        {
            cout << (*CN)->Letter << " ";
        }
    }

    void GenerateHuffCode()
    {
        char x;

        for (int i = 0; i < Text.size(); i++)
        {
            for (list<LNode *>::iterator CN = HuffCodes.begin(); CN != HuffCodes.end(); CN++)
            {
                if (Text[i] == (*CN)->Letter)
                {
                    HuffCode += (*CN)->HC;
                    break;
                }
            }
        }
        cout << HuffCode << endl;
    }

    void DecodeHuffCode()
    {
        TNode *Temp = FrequencyQueue.top();
        string Output = "";
        for (int i = 0; i < HuffCode.size(); i++)
        {
            if (HuffCode[i] == '1')
            {
                Temp = Temp->Right;
            }
            else
            {
                Temp = Temp->Left;
            }

            if ((!(Temp->Left)) && (!(Temp->Right)))
            {
                Output += Temp->Letter;
                Temp = FrequencyQueue.top();
            }
        }

        Compressed = Output;
        cout << "DECODED: " << Output << endl;
    }

    string tochar(string binary)
    {
        string newString;
        int ind = 0;
        for (int i = 0; 8 < binary.size() - i; i += 8)
        {
            newString += stoi(binary.substr(i, 8), nullptr, 2);
            ind = i + 8;
            cout << newString << endl;
        }

        int x = 128;
        int sum = 0;

        for (int i = ind; i < binary.size(); i++)
        {
            sum = sum + (x * (int)binary[ind]);
            x = x / 2;
        }

        // cout << sum << endl;
        // cout << newString << endl;

        newString += (char)sum;

        cout << newString << endl;
        return newString;
    }

    /* string toBinary(string const &str)
    {
        string binary = "";
        for (char const &c : str)
        {
            binary += bitset<8>(c).to_string();
        }
        return binary;
    } */

    void CompressedToFile()
    {
        string Characters = "";
        fstream FileHandle;
        FileHandle.open("Compressed.txt", ios::out);

        Characters = tochar(HuffCode);

        cout << Characters << endl;

        FileHandle << Characters << endl;
    }

    int BinaryToDecimal(string Input)
    {
        int Decimal = 0;

        for (int i = 0; i < Input.size(); i++)
        {
            if (Input[i] == '1')
            {
                Decimal += pow(2, (7 - i));
            }
        }

        return Decimal;
    }

    void DecimalToBinary()
    {
        fstream MyFile;
        MyFile.open("Compressed.txt", ios::in);
        string FromFile, Decimal = "", Binary = "";
        int Bin;

        getline(MyFile, FromFile);

        for (int i = 0; i < FromFile.size(); i++)
        {
            while (int(FromFile[i]) != 32)
            {
                Decimal += FromFile[i];
            }
        }
    }
};

int main()
{
    Huffman Obj1;

    Obj1.HuffmanEncoding();
    Obj1.CreateBT();

    Obj1.Display();

    cout << endl;
    Obj1.GenerateHuffCode();
    cout << endl;

    Obj1.CompressedToFile();

    Obj1.DecodeHuffCode();

    return 0;
}
