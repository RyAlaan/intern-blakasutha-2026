#include<iostream>
using namespace std;

class Ras {
    public: // Men set type acces ke varibale bawah bawahnya dalam mode public
        string nama; // string nama
        int umur; // integer umur
        void getRas()
      {
        cout << nama << " " << umur; // mencetak data objek nama dan umur
      }
};

int main () {
    Ras ras; // Membuat objek dari class Ras

    ras.nama = 'Manusia'; // Mengisi variable public nama
    ras.umur = 18; // Mengisi variable public umur
    
    ras.getRas(); // Memanggil fungsi public di objek ras
}
