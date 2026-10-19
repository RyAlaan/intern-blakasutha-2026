#include <iostream>
using namespace std;

class Ras
{                          // Class utama
public:                    // Men set type acces ke varibale bawah bawahnya dalam mode public
    string nama = "Dwarf"; // strin nama
    int umur = 50;         // integer umur
    void getRas()
    {
        cout << nama << " " << umur <<endl; // mencetak data objek nama dan umur
    }
};

class Dwarf : public Ras
{ // Class turunan
};

int main()
{
    Dwarf dw; // Membuat objek dari class Dwarf

    dw.getRas(); // Memanggil fungsi public dari objek ras
}
