#include<iostream>
#include<string>
#include<ctime>

using namespace std;

class mahasiswa{
    private:
        string nama, nim, prodi, fakultas, tmptLahir, strTglLahir, thnMasuk;
      
    public:
        mahasiswa(){
            cout << "Nama lengkap: ";
            getline(cin, nama);
            cout << "NIM: ";
            getline(cin, nim);
            cout << "Fakultas: ";
            getline(cin, fakultas);
            cout << "Program studi: ";
            getline(cin, prodi);
            cout << "Masukkan tempat lahir: ";
            getline(cin, tmptLahir);
            cout << "Masukkan tanggal lahir (DD/MM/YYYY): ";
            getline(cin, strTglLahir);     
            
            cout << "Masukkan tahun masuk: ";
            getline(cin, thnMasuk);
        }

        mahasiswa(
            string inputNama,
            string inputNIM,
            string inputFakultas,
            string inputProdi,
            string inputTmptLahir,
            string inputStrTglLahir,
            string inputThnMasuk
        ){
            nama = inputNama;
            nim = inputNIM;
            prodi = inputProdi;
            fakultas = inputFakultas;
            tmptLahir = inputTmptLahir;
            strTglLahir = inputStrTglLahir;
            thnMasuk = inputThnMasuk;
         }

        
        void tampilkanData(){
            cout << "Data Mahasiswa\n";
            cout << "------------------\n";
            cout << "Nama lengkap  : " << nama << endl;
            cout << "NIM           : " << nim << endl;
            cout << "Fakultas      : " << fakultas << endl;
            cout << "Program studi : " << prodi << endl;
            cout << "TTL           : " << tmptLahir << ", " << strTglLahir << endl;
            cout << "Tahun Masuk   : " << thnMasuk << endl << endl;
        }
};

int main(){
    
    mahasiswa mahasiswa1(
        "Riyanto Usman",
        "H1D027034",
        "Teknik",
        "Informatika",
        "Jakarta",
        "08/09/2009",
        "2027"
    );
    mahasiswa1.tampilkanData();

    mahasiswa mahasiswa2;
    mahasiswa2.tampilkanData();
    return 0;
}
