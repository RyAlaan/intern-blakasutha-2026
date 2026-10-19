#include <iostream>
using namespace std;

class Ras
{                          // Class utama
protected:                 // Men set type acces ke varibale bawah bawahnya dalam mode protected
    string nama = "Dwarf"; // strin nama
    int umur = 50;         // integer umur
};

class Dwarf : public Ras
{ // Class turunan
public:
    void getRas()
    {
        cout << nama << " " << umur << endl; // mencetak data objek nama dan umur
    }
};

int main()
{
    Dwarf dw; // Membuat objek dari class Dwarf

    dw.getRas(); // Memanggil fungsi public dari objek ras
}
