#include <iostream>
using namespace std;

//Membuat kelas makanan
class makanan {
public:
    string Nama;
    double Harga;

    void tampilkanInfo() {
        cout << "Nama: " << Nama << endl;
        cout << "Harga: " << Harga << endl;
    }
};

// Membuat objek dari kelas makanan
int main() {
    makanan apaya;
    apaya.Nama = "Nasi Padang";
    apaya.Harga = 10000.0;
    apaya.tampilkanInfo();
    return 0;
}