#include <iostream>
using namespace std;

class Ras
{
private: // Men set type acces varibale bawahnya ke private
    string atribut;
    float mana_power = 100.50;

public:          // Men set type acces ke varibale bawah bawahnya dalam mode public
    string nama; // strin nama
    int umur;    // integer umur
    void getRas()
    {
        cout << nama << " " << umur << endl; // mencetak data objek nama dan umur
    }
    void setAtribut(string a)
    {
        atribut = a; // Mengisi varibale private
    }
    string getAtribut()
    {
        return atribut; // Mengambil data private atribut
    }
    float getManaPower()
    {
        return mana_power; // Mengambil data private mana power
    }
};

int main()
{
    Ras ras; // Membuat objek dari class Ras

    ras.nama = "Elf"; // Mengisi variable public nama
    ras.umur = 100;   // Mengisi variable public umur

    ras.setAtribut("Angin");
    string attr = ras.getAtribut();
    float mana = ras.getManaPower();

    // jika memaksa mengambil data private langsung
  /*   cout << ras.atribut << endl;
    cout << ras.mana_power << endl; */

    ras.getRas(); // Memanggil fungsi public di objek ras

    cout << attr + " " << mana << endl;
}
