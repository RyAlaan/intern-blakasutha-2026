#include <iostream>
using namespace std;

class Ras
{
public:
    void skill()
    {
        cout << "Terdapat 3 skill yang dimiliki 3 ras \n";
    }
};

class Manusia : public Ras
{
public:
    void skill()
    {
        cout << "Knight dan Pedang Manusia\n";
    }
};

class Elf : public Ras
{
public:
    void skill()
    {
        cout << "Penyihir dan Sihir Elf\n";
    }
    
};

class Dwarf : public Ras
{
public:
    void skill()
    {
        cout << "Blacksmith dan Martil Dwarf\n";
    }
};

int main()
{
    Ras ras;
    Manusia man;
    Elf el;
    Dwarf dw;

    ras.skill();
    man.skill();
    el.skill();
    dw.skill();
}