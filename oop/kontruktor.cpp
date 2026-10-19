#include<iostream>
using namespace std;

class Ras {
    public: // Men set type acces ke varibale bawah bawahnya dalam mode public
        string nama; // string nama
        int umur; // integer umur
        void getRas()
      {
        cout << nama << " " << umur << endl; // mencetak data objek nama dan umur
      }
      Ras()
{}      Ras (string m, int i) {
        nama = m;
        umur = i;
      }
};

int main () {
    Ras ras;
    Ras ras("Manusia", 18); // Membuat objek dari class Ras
    ras.getRas(); // Memanggil fungsi public di objek ras

    
    ras.nama = "Elf"; // Mengisi variable public nama
    ras.umur = 30; // Mengisi variable public umur
    
    ras.getRas(); // Memanggil fungsi public di objek ras
}
